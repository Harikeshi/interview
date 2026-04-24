#pragma once

#include <QAbstractListModel>

#include <ContactsLib/Models/Contact.hpp>

namespace Models {
class ContactListModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    enum ContactRoles
    {
        NameRole = Qt::UserRole + 1,
        SurnameRole,
        PhoneRole,
        EmailRole,
        DescRole
    };

    ContactListModel(QObject* parent = nullptr);
    void SetContacts(const QVector<Contact>& rows);
    void AddContact(const Contact& contact);
    void RemoveContact(int row);
    void UpdateContact(int row, const Contact& contact);

    const Contact* ContactAt(int index) const;
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QHash<int, QByteArray> roleNames() const override;
    const QVector<Contact>& items() const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    void Clear();

private:
    QVector<Contact> contacts;
};
} // namespace Models