#pragma once

#include <QJsonArray>
#include <QJsonObject>
#include <optional>

#include <ContactsLib/Database/IRepository.hpp>

namespace Database {
class JsonRepository : public IRepository
{
    // json: [ {name, ...}, {name, ...}]
    using Contact = Models::Contact;

public:
    explicit JsonRepository(const QString& basePath);
    bool DeleteContact(int number) override;
    bool UpdateContact(int number, const Contact& contact) override;
    bool AddContact(const Contact& contact) override;
    Contact GetContact(int index) const override;
    QVector<Contact> GetAllContacts() const override;
    void SaveAllContacts(const QVector<Contact>& contacts) override;
    int GetContactsCount() const override;

protected:
    void loadAllContacts() override;
    static bool isValidContact(const QJsonObject& obj);
    static std::optional<QJsonArray> loadContactsFromJsonFile(const QString& fileName);
    static bool writeContactsToJsonFile(const QJsonArray& array, const QString& fileName);
    static Contact fromJson(const QJsonObject& obj);
    static QJsonObject toJson(const Contact& contact);

private:
    QString path;
    QJsonArray contacts;
};
} // namespace Database
