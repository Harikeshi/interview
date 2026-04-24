#include <ContactsLib/Database/JsonRepository.hpp>

#include <QDir>
#include <QJsonParseError>

namespace Database {
using Contact = Models::Contact;

JsonRepository::JsonRepository(const QString& basePath) : path(basePath)
{
    JsonRepository::loadAllContacts();
}
bool JsonRepository::DeleteContact(int number)
{
    if (number >= 0 && number < contacts.size())
    {
        contacts.removeAt(number);
        return writeContactsToJsonFile(contacts, path);
    }

    return false;
}
bool JsonRepository::UpdateContact(int number, const Contact& contact)
{
    if (number >= 0 && number < contacts.size())
    {
        const auto object = toJson(contact);
        if (contacts.at(number) == object)
            return true;

        contacts[number] = object;

        return writeContactsToJsonFile(contacts, path);
    }

    return false;
}
bool JsonRepository::AddContact(const Contact& contact)
{
    const auto object = toJson(contact);

    contacts.append(object);

    return writeContactsToJsonFile(contacts, path);
}
Contact JsonRepository::GetContact(int index) const
{
    return (index >= 0 && index < contacts.size()) ? fromJson(contacts.at(index).toObject()) : Models::Contact();
}
QVector<Contact> JsonRepository::GetAllContacts() const
{
    QVector<Contact> result;
    result.reserve(contacts.size());

    for (const auto& contact : contacts)
    {
        result.append(fromJson(contact.toObject()));
    }
    return result;
}
/* protected */
void JsonRepository::loadAllContacts()
{
    const auto _contacts = loadContactsFromJsonFile(path);
    if (_contacts)
        contacts = *_contacts;
}
bool JsonRepository::isValidContact(const QJsonObject& obj)
{
    if (!obj.contains("Name") ||
        !obj.contains("Surname") ||
        !obj.contains("Phone") ||
        !obj.contains("Email") ||
        !obj.contains("Desc"))
    {
        return false;
    }
    if (!obj["Name"].isString())
        return false;
    if (!obj["Surname"].isString())
        return false;
    if (!obj["Phone"].isString())
        return false;
    if (!obj["Email"].isString())
        return false;
    if (!obj["Desc"].isString())
        return false;
    return true;
}
std::optional<QJsonArray> JsonRepository::loadContactsFromJsonFile(const QString& fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly))
        return std::nullopt;
    QByteArray data = file.readAll();
    file.close();
    QJsonParseError err{};
    QJsonDocument doc = QJsonDocument::fromJson(data);

    if (err.error != QJsonParseError::NoError || !doc.isArray())
        return std::nullopt;

    auto array = doc.array();
    for (const auto& elem : array)
    {
        if (!JsonRepository::isValidContact(elem.toObject()))
            return std::nullopt;
    }
    return doc.array();
}
bool JsonRepository::writeContactsToJsonFile(const QJsonArray& array, const QString& fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly))
    {
        return false;
    }
    QJsonDocument doc(array);
    if (file.write(doc.toJson()) == -1)
    {
        file.close();
        return false;
    }
    file.close();
    return true;
}
Contact JsonRepository::fromJson(const QJsonObject& obj)
{
    Contact contact;

    contact.SetName(obj["Name"].toString());
    contact.SetSurname(obj["Surname"].toString());
    contact.SetPhone(obj["Phone"].toString());
    contact.SetEmail(obj["Email"].toString());
    contact.SetDesc(obj["Desc"].toString());

    return contact;
}
QJsonObject JsonRepository::toJson(const Contact& contact)
{
    QJsonObject obj;
    obj["Name"] = contact.GetName();
    obj["Surname"] = contact.GetSurname();
    obj["Phone"] = contact.GetPhone();
    obj["Email"] = contact.GetEmail();
    obj["Desc"] = contact.GetDesc();

    return obj;
}
int JsonRepository::GetContactsCount() const
{
    return contacts.size();
}
void JsonRepository::SaveAllContacts(const QVector<Contact>& contacts)
{
    this->contacts = QJsonArray();

    for (const auto& contact : contacts)
    {
        const auto object = toJson(contact);
        this->contacts.append(object);
    }
    writeContactsToJsonFile(this->contacts, path);
}
} // namespace Database