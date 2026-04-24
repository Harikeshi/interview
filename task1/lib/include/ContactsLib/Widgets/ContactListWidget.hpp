#pragma once

#include <optional>

#include <ContactsLib/Models/Contact.hpp>
#include <ContactsLib/Models/ContactListModel.hpp>
#include <QTableView>

namespace Widgets {
class ContactListWidget final : public QWidget
{
    Q_OBJECT
public:
    explicit ContactListWidget(QWidget* parent = nullptr);
    int GetCurrentRowIndex() const;
    void SetCurrentRowIndex(int index);

    void AddContact(const Models::Contact&);
    void UpdateContact(int, const Models::Contact&);
    void DeleteContact(int index);
    std::optional<QPair<QString, QString>> ContactListWidget::GetCurrentNameAndSurname() const;
    const Models::Contact* ContactAt(int index) const;

    void Update(const QVector<Models::Contact>& contacts);
signals:
    void ContactActivated(const QModelIndex&);

private:
    void buildUi();
    void onRowClicked(const QModelIndex& index);
    void setCurrent(const QModelIndex& rowIndex);

    QTableView* tableView;
    Models::ContactListModel* model;
};
} // namespace Widgets