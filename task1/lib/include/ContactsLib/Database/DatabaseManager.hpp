#pragma once
#include <ContactsLib/Database/IRepository.hpp>
#include <memory>

namespace Database {
class DatabaseManager
{
    using Contact = Models::Contact;

public:
    DatabaseManager(Database::Type type, QString connString = nullptr);

    bool DeleteContact(int index);
    bool UpdateContact(int index, const Contact& contact);
    bool AddContact(const Contact& contact);
    Contact GetContact(int index);
    QVector<Contact> GetAllContacts();
    void SaveAllContacts(const QVector<Contact>& contacts);
    int ContactsCount() const;

private:
    std::unique_ptr<IRepository> repository;
};
} // namespace Database