#include <ContactsLib/Widgets/ContactListWidget.hpp>

#include "ContactsLib/Models/ContactListModel.hpp"

#include <QHeaderView>
#include <QVBoxLayout>

namespace Widgets {
ContactListWidget::ContactListWidget(QWidget* parent)
    : QWidget(parent)
{
    buildUi();
}

void ContactListWidget::buildUi()
{
    auto* mainLayout = new QVBoxLayout(this);
    tableView = new QTableView(this);
    model = new Models::ContactListModel(this);
    tableView->setModel(model);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    mainLayout->addWidget(tableView);
    setLayout(mainLayout);

    connect(tableView, &QTableView::clicked, this, &ContactListWidget::onRowClicked);
}

int ContactListWidget::GetCurrentRowIndex() const
{
    return tableView->currentIndex().row();
}

void ContactListWidget::SetCurrentRowIndex(int index)
{
    QModelIndex newIndex = tableView->model()->index(index, 0);
    setCurrent(newIndex);
    emit ContactActivated(newIndex);
}

void ContactListWidget::setCurrent(const QModelIndex& rowIndex)
{
    tableView->setCurrentIndex(rowIndex);
    tableView->selectionModel()->select(rowIndex, QItemSelectionModel::Select | QItemSelectionModel::Rows);
}

std::optional<QPair<QString, QString>> ContactListWidget::GetCurrentNameAndSurname() const
{
    auto index = GetCurrentRowIndex();
    if (index == -1)
        return std::nullopt;

    auto contact = model->ContactAt(index);
    return QPair<QString, QString>(contact->GetName(), contact->GetSurname());
}

void ContactListWidget::AddContact(const Models::Contact& contact)
{
    model->AddContact(contact);
    QModelIndex newIndex = tableView->model()->index(model->rowCount() - 1, 0);
    setCurrent(newIndex);
}

void ContactListWidget::UpdateContact(int index, const Models::Contact& contact)
{
    model->UpdateContact(index, contact);
    QModelIndex newIndex = tableView->model()->index(index, 0);
    setCurrent(newIndex);
}

void ContactListWidget::DeleteContact(int index)
{
    model->RemoveContact(index);
    const auto count = model->rowCount();
    if (count == 0)
        return; // -1;

    SetCurrentRowIndex(index < count ? index : index - 1);
}

void ContactListWidget::Update(const QVector<Models::Contact>& contacts)
{
    model->Clear();
    if (contacts.isEmpty())
        return;
    model->SetContacts(contacts);
}
void ContactListWidget::onRowClicked(const QModelIndex& index)
{
    const auto* row = model->ContactAt(index.row());
    if (!row)
    {
        return;
    }
    emit ContactActivated(index);
}
const Models::Contact* ContactListWidget::ContactAt(int index) const
{
    return model->ContactAt(index);
}
} // namespace Widgets