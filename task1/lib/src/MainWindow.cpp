#include <ContactsLib/MainWindow.hpp>

#include <QMainWindow>
#include <QMessageBox>
#include <QPushButton>
#include <QSplitter>
#include <QVBoxLayout>

#include <ContactsLib/Database/DatabaseManager.hpp>
#include <ContactsLib/Widgets/ButtonsWidget.hpp>
#include <ContactsLib/Widgets/ContactFormWidget.hpp>
#include <ContactsLib/Widgets/ContactListWidget.hpp>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    buildUi();
    loadData();
}

void MainWindow::buildUi()
{
    auto* mainWidget = new QWidget(this);
    auto* mainLayout = new QVBoxLayout(mainWidget);
    auto* topSplitter = new QSplitter(Qt::Horizontal);

    auto* topLeftWidget = new QWidget();
    auto* topLeftLayout = new QVBoxLayout(topLeftWidget);

    contactListWidget = new Widgets::ContactListWidget();
    topLeftLayout->addWidget(contactListWidget);

    auto* topRightWidget = new QWidget();
    auto* topRightLayout = new QVBoxLayout(topRightWidget);

    contactFormWidget = new Widgets::ContactFormWidget();
    topRightLayout->addWidget(contactFormWidget);

    topSplitter->addWidget(topLeftWidget);
    topSplitter->addWidget(topRightWidget);

    topSplitter->setSizes({400, 400});

    buttonsWidget = new Widgets::ButtonsWidget();

    auto* mainSplitter = new QSplitter(Qt::Vertical);
    mainSplitter->addWidget(topSplitter);
    mainSplitter->addWidget(buttonsWidget);

    mainSplitter->setSizes({500, 100});

    mainLayout->addWidget(mainSplitter);

    dataManager = new Database::DatabaseManager(Database::Type::Json);
    connect(contactListWidget, &Widgets::ContactListWidget::ContactActivated, this, &MainWindow::onListChanged);
    connect(contactFormWidget, &Widgets::ContactFormWidget::SendValidation, buttonsWidget, &Widgets::ButtonsWidget::UpdateSave);

    connect(buttonsWidget, &Widgets::ButtonsWidget::onAddButtonClicked, this, &MainWindow::onAddButton);
    connect(buttonsWidget, &Widgets::ButtonsWidget::onSaveButtonClicked, this, &MainWindow::onSaveButton);
    connect(buttonsWidget, &Widgets::ButtonsWidget::onDeleteButtonClicked, this, &MainWindow::onDeleteButton);

    setCentralWidget(mainWidget);
}
void MainWindow::onAddButton()
{
    reset();
}
void MainWindow::onSaveButton()
{
    const auto contact = contactFormWidget->GetContact();
    if (canAddNew) // Всегда сохраняем после Add
    {
        contactListWidget->AddContact(contact);
        dataManager->AddContact(contact);
        canAddNew = false;
    }
    else
    {
        const auto currentIndex = contactListWidget->GetCurrentRowIndex();
        contactListWidget->UpdateContact(currentIndex, contact);
        dataManager->UpdateContact(currentIndex, contact);
    }
}
void MainWindow::onDeleteButton()
{
    auto nameSurname = contactListWidget->GetCurrentNameAndSurname();
    if (!nameSurname)
        return;

    QMessageBox::StandardButton message = QMessageBox::question(this, "Удаление", QString("Удалить запись %1 %2?").arg(nameSurname.value().first).arg(nameSurname.value().second), QMessageBox::Yes | QMessageBox::No);
    if (message != QMessageBox::Yes)
        return;

    const auto currentIndex = contactListWidget->GetCurrentRowIndex();
    contactListWidget->DeleteContact(currentIndex);
    dataManager->DeleteContact(currentIndex);
    if (dataManager->ContactsCount() == 0)
        reset();
}
void MainWindow::onListChanged(const QModelIndex& rowIndex)
{
    canAddNew = false;
    if (rowIndex.row() == -1)
    {
        contactFormWidget->ClearForm();
        return;
    }
    const auto* contact = contactListWidget->ContactAt(rowIndex.row());
    if (contact)
        contactFormWidget->LoadForm(*contact);
}
void MainWindow::loadData()
{
    const auto contacts = dataManager->GetAllContacts();
    if (contacts.isEmpty())
        return;
    // форма пустая при загрузке
    contactListWidget->Update(contacts);
}
void MainWindow::reset()
{
    canAddNew = true;
    contactFormWidget->ClearForm();
}