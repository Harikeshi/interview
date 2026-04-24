#include <ContactsLib/Database/SQLRepository.hpp>

namespace Database {
bool SQLRepository::DeleteContact(int number)
{
    return true;
}
bool SQLRepository::UpdateContact(int number, const Models::Contact& contact)
{
    return true;
}
bool SQLRepository::AddContact(const Models::Contact& contact)
{
    return true;
}
QVector<Models::Contact> SQLRepository::GetAllContacts() const
{
    return {};
}
void SQLRepository::SaveAllContacts(const QVector<Models::Contact>& contacts)
{
}
Models::Contact SQLRepository::GetContact(int index) const
{
    return {};
}
int SQLRepository::GetContactsCount() const
{
    return 0;
}
/*protected*/
void SQLRepository::loadAllContacts()
{
}
} // namespace Database