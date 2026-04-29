#include <ContactsLib/Database/DatabaseManager.hpp>
#include <ContactsLib/Database/JsonRepository.hpp>
#include <ContactsLib/Database/SQLRepository.hpp>

namespace Database {
inline QString getHomePath()
{
    QString result;
#ifdef _WIN32
    result = QString(std::getenv("USERPROFILE")) + "//";
#else
    result = QString(getenv("HOME")) + "/";
#endif
    return result;
}
using Contact = Models::Contact;

DatabaseManager::DatabaseManager(Type type, QString connString)
{
    if (type == Json)
        repository = std::make_unique<JsonRepository>(connString != nullptr ? connString : getHomePath() + "contacts.json");
    else if (type == SQL)
        repository = std::make_unique<SQLRepository>(connString != nullptr ? connString : "");
}
bool DatabaseManager::DeleteContact(int index)
{
    return repository->DeleteContact(index);
}

bool DatabaseManager::UpdateContact(int index, const Contact& contact)
{
    return repository->UpdateContact(index, contact);
}

bool DatabaseManager::AddContact(const Contact& contact)
{
    return repository->AddContact(contact);
}

Contact DatabaseManager::GetContact(int index)
{
    return repository->GetContact(index);
}

QVector<Contact> DatabaseManager::GetAllContacts()
{
    return repository->GetAllContacts();
}

void DatabaseManager::SaveAllContacts(const QVector<Contact>& contacts)
{
    repository->SaveAllContacts(contacts);
}

int DatabaseManager::ContactsCount() const
{
    return repository->GetContactsCount();
}
} // namespace Database
