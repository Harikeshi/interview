#pragma once

#include <QMainWindow>
#include <QStringListModel>

#include <ContactsLib/Database/DatabaseManager.hpp>
#include <ContactsLib/Models/ContactListModel.hpp>
#include <ContactsLib/Widgets/ButtonsWidget.hpp>
#include <ContactsLib/Widgets/ContactFormWidget.hpp>
#include <ContactsLib/Widgets/ContactListWidget.hpp>
/*!
 * Интерфейс:
 *  Слева: Список (QListView или QListWidget) существующих контактов, отображающий Имя и Фамилию.
 *  Справа: Форма (QLineEdit, QTextEdit и т.д.) для просмотра, добавления и редактирования выбранного контакта.
 * Кнопки:
 *  "Добавить" — очищает форму для ввода нового контакта.
 *  "Сохранить" — сохраняет новый или измененный контакт. Кнопка должна быть неактивна,
 *      если обязательные поля не заполнены или не прошли валидацию.
 *  "Удалить" — удаляет выбранный контакт из списка (с подтверждением через QMessageBox).
 * Логика:
 *  При выборе контакта из списка справа отображаются его данные.
 *  При нажатии "Добавить" форма очищается, а фокус устанавливается на поле "Имя".
 *  Данные должны сохраняться локально в файл (на выбор: JSON через QJsonDocument, XML
 *      через QXmlStreamReader/Writer, или SQLite через QSqlDatabase). При запуске приложения данные должны загружаться.
*/

class MainWindow : public QMainWindow
{
    using ButtonsWidget = Widgets::ButtonsWidget;
    using ContactListWidget = Widgets::ContactListWidget;
    using ContactFormWidget = Widgets::ContactFormWidget;

    Q_OBJECT
public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow() = default;

protected:
    void onAddButton();
    void onSaveButton();
    void onDeleteButton();
    void onListChanged(const QModelIndex& rowIndex);

private:
    void buildUi();
    void loadData();
    void reset();

    bool canAddNew = true;
    ButtonsWidget* buttonsWidget;
    ContactListWidget* contactListWidget;
    ContactFormWidget* contactFormWidget;
    Database::DatabaseManager* dataManager;

    Models::ContactListModel* contactListModel;
};
