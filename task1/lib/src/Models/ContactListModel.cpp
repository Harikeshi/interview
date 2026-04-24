#include <ContactsLib/Models/ContactListModel.hpp>
#include <algorithm>

namespace Models {

ContactListModel::ContactListModel(QObject* parent)
    : QAbstractTableModel(parent)
{
}
int ContactListModel::rowCount(const QModelIndex& parent) const
{
    return contacts.count();
}
int ContactListModel::columnCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return 2; // Name, Surname
}

QVariant ContactListModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole)
        return {};

    const auto& contact = contacts[static_cast<size_t>(index.row())];
    switch (index.column())
    {
    case 0:
        return QVariant::fromValue(contact.GetName());
    case 1:
        return QVariant::fromValue(contact.GetSurname());
    default:
        break;
    }
    return {};
}

QHash<int, QByteArray> ContactListModel::roleNames() const
{
    return {
        {NameRole, "Name"},
        {SurnameRole, "Surname"},
        {PhoneRole, "Phone"},
        {EmailRole, "Email"},
        {DescRole, "Description"}};
}
QVariant ContactListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation != Qt::Horizontal || role != Qt::DisplayRole)
        return {};
    switch (section)
    {
    case 0:
        return "Имя";
    case 1:
        return "Фамилия";
    default:
        break;
    }
    return {};
}
const QVector<Contact>& ContactListModel::items() const
{
    return contacts;
}

const Contact* ContactListModel::ContactAt(int index) const
{
    if (index < 0 || index >= static_cast<int>(contacts.size()))
        return nullptr;
    return &contacts[index];
}
void ContactListModel::Clear()
{
    beginResetModel();
    contacts.clear();
    endResetModel();
}

void ContactListModel::AddContact(const Contact& contact)
{
    beginInsertRows(QModelIndex(), contacts.size(), contacts.size());
    contacts.push_back(contact);
    endInsertRows();
}

void ContactListModel::UpdateContact(int row, const Contact& contact)
{
    if (row < 0 || row >= contacts.size())
        return;
    beginResetModel();
    contacts[row] = contact;
    endResetModel();
}

void ContactListModel::RemoveContact(int row)
{
    if (row < 0 || row >= contacts.size())
        return;
    beginRemoveRows(QModelIndex(), row, row);
    contacts.removeAt(row);
    endRemoveRows();
}

void ContactListModel::SetContacts(const QVector<Contact>& rows)
{
    beginResetModel();
    contacts = rows;
    endResetModel();
}
} // namespace Models