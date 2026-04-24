#include <ContactsLib/Widgets/ContactFormWidget.hpp>

#include <QFormLayout>
#include <QGroupBox>

#include <ContactsLib/Utilities/Validator.hpp>

namespace Widgets {

using Contact = Models::Contact;

ContactFormWidget::ContactFormWidget(QWidget* parent)
    : QWidget(parent)
{
    buildUi();
}

/* private */
void ContactFormWidget::buildUi()
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    auto* infoGroup = new QGroupBox("Контакт", this);
    QFormLayout* formLayout = new QFormLayout(infoGroup);

    nameEdit = new QLineEdit(this);
    nameEdit->setPlaceholderText("Имя (обязательно)");

    surnameEdit = new QLineEdit(this);
    surnameEdit->setPlaceholderText("Фамилию (обязательно)");

    phoneEdit = new QLineEdit(this);
    phoneEdit->setPlaceholderText("Телефон (обязательно)");

    emailEdit = new QLineEdit(this);
    emailEdit->setPlaceholderText("Email");

    descEdit = new QTextEdit(this);
    descEdit->setPlaceholderText("Заметка");
    descEdit->setMinimumHeight(150);
    descEdit->setMaximumHeight(200);

    formLayout->addRow("Имя:", nameEdit);
    formLayout->addRow("Фамилия:", surnameEdit);
    formLayout->addRow("Телефон:", phoneEdit);
    formLayout->addRow("Email:", emailEdit);
    formLayout->addRow("Заметка:", descEdit);

    mainLayout->addWidget(infoGroup);

    QString lineEditStyle = "QLineEdit { padding: 5px; border: 1px solid #ccc; border-radius: 3px; }"
                            "QLineEdit:focus { border: 2px solid #4CAF50; }"
                            "QLineEdit:read-only { background-color: #f5f5f5; color: #666; }";

    nameEdit->setStyleSheet(lineEditStyle);
    surnameEdit->setStyleSheet(lineEditStyle);
    phoneEdit->setStyleSheet(lineEditStyle);
    emailEdit->setStyleSheet(lineEditStyle);
    descEdit->setStyleSheet(lineEditStyle);

    nameEdit->setMinimumWidth(300);

    connect(nameEdit, &QLineEdit::textChanged, this, &ContactFormWidget::updateValidation);
    connect(surnameEdit, &QLineEdit::textChanged, this, &ContactFormWidget::updateValidation);
    connect(phoneEdit, &QLineEdit::textChanged, this, &ContactFormWidget::updateValidation);
    connect(emailEdit, &QLineEdit::textChanged, this, &ContactFormWidget::updateValidation);
}
Contact ContactFormWidget::GetContact() const
{
    Contact contact;
    contact.SetName(nameEdit->text());
    contact.SetSurname(surnameEdit->text());
    contact.SetPhone(phoneEdit->text());
    contact.SetEmail(emailEdit->text());
    contact.SetDesc(descEdit->toPlainText());

    return contact;
}
void ContactFormWidget::ClearForm()
{
    nameEdit->clear();
    surnameEdit->clear();
    phoneEdit->clear();
    emailEdit->clear();
    descEdit->clear();

    emit SendValidation(false);
}
void ContactFormWidget::LoadForm(const Contact& contact)
{
    nameEdit->setText(contact.GetName());
    surnameEdit->setText(contact.GetSurname());
    phoneEdit->setText(contact.GetPhone());
    emailEdit->setText(contact.GetEmail());
    descEdit->setPlainText(contact.GetDesc());
}
bool ContactFormWidget::IsValidForm() const
{
    if (nameEdit->text().isEmpty())
        return false;
    if (surnameEdit->text().isEmpty())
        return false;
    if (!Utilities::Validator::ValidatePhone(phoneEdit->text()).IsValid())
        return false;
    if (!Utilities::Validator::ValidateEmail(emailEdit->text()).IsValid())
        return false;

    return true;
}
void ContactFormWidget::updateValidation()
{
    emit SendValidation(IsValidForm());
}
} // namespace Widgets