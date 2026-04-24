#pragma once
#include <ContactsLib/Database/IRepository.hpp>

namespace Database {
class SQLRepository : public IRepository
{
    using Contact = Models::Contact;

public:
    SQLRepository(QString conneString = nullptr)
    {
    }
    bool DeleteContact(int number) override;
    bool UpdateContact(int number, const Contact& contact) override;
    bool AddContact(const Contact& contact) override;
    QVector<Contact> GetAllContacts() const override;
    Contact GetContact(int index) const override;
    int GetContactsCount() const override;
    void SaveAllContacts(const QVector<Contact>& contacts) override;

protected:
    void loadAllContacts() override;
};
} // namespace Database