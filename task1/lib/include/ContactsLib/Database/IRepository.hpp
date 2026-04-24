#pragma once

#include <ContactsLib/Database/IRepository.hpp>
#include <ContactsLib/Models/Contact.hpp>

namespace Database {
enum Type
{
    Json,
    SQL
};

class IRepository
{
    using Contact = Models::Contact;

public:
    virtual bool DeleteContact(int number) = 0;
    virtual bool UpdateContact(int number, const Contact& contact) = 0;
    virtual bool AddContact(const Contact& contact) = 0;
    virtual QVector<Contact> GetAllContacts() const = 0;
    virtual Contact GetContact(int index) const = 0;
    virtual int GetContactsCount() const = 0;
    virtual void SaveAllContacts(const QVector<Contact>& contacts) = 0;
    virtual ~IRepository() = default;

protected:
    virtual void loadAllContacts() = 0;
};
} // namespace Database