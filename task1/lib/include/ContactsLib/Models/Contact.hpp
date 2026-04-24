#pragma once

#include <QVector>

namespace Models {
class Contact
{
public:
    Contact();
    Contact(const QString& name, const QString& surname, const QString& phone, const QString& email = {}, const QString& desc = {});

    QString GetName() const;
    QString GetSurname() const;
    QString GetPhone() const;
    QString GetEmail() const;
    QString GetDesc() const;
    void SetName(const QString& name);
    void SetSurname(const QString& surname);
    void SetPhone(const QString& phone);
    void SetEmail(const QString& email);
    void SetDesc(const QString& desc);

    bool operator==(const Contact& contact) const;

private:
    QString name;
    QString surname;
    QString phoneNumber;
    QString email;
    QString desc; // строка с \n
};
} // namespace Models