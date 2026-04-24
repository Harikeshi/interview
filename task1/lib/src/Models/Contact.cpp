#include <ContactsLib/Models/Contact.hpp>
#include <QStringList>

namespace Models {
Contact::Contact()
    : name{}, surname{}, phoneNumber{}, email{}, desc{}
{
}
Contact::Contact(const QString& name, const QString& surname, const QString& phone, const QString& email, const QString& desc)
    : name(name), surname(surname), phoneNumber(phone), email(email), desc(desc)
{
}
QString Contact::GetName() const
{
    return this->name;
}
QString Contact::GetSurname() const
{
    return this->surname;
}
QString Contact::GetPhone() const
{
    return this->phoneNumber;
}
QString Contact::GetEmail() const
{
    return this->email;
}
QString Contact::GetDesc() const
{
    return this->desc;
}
void Contact::SetName(const QString& name)
{
    this->name = name;
}
void Contact::SetSurname(const QString& surname)
{
    this->surname = surname;
}
void Contact::SetPhone(const QString& phone)
{
    this->phoneNumber = phone;
}
void Contact::SetEmail(const QString& email)
{
    this->email = email;
}
void Contact::SetDesc(const QString& desc)
{
    this->desc = desc;
}
bool Contact::operator==(const Contact& contact) const
{
    return name == contact.name && surname == contact.surname &&
           phoneNumber == contact.phoneNumber && email == contact.email && desc.size() == contact.desc.size() && desc == contact.desc;
}
} // namespace Models