#pragma once

#include <QLineEdit>
#include <QTextEdit>

#include <ContactsLib/Models/Contact.hpp>

namespace Widgets {
class ContactFormWidget final : public QWidget
{
    using Contact = Models::Contact;
    Q_OBJECT
public:
    explicit ContactFormWidget(QWidget* parent = nullptr);
    Contact GetContact() const;

    void ClearForm();
    void LoadForm(const Contact& contact);
    bool IsValidForm() const;
signals:
    void SendValidation(bool);

private:
    void buildUi();
    void updateValidation();

    QLineEdit* nameEdit;
    QLineEdit* surnameEdit;
    QLineEdit* phoneEdit;
    QLineEdit* emailEdit;
    QTextEdit* descEdit;
};
} // namespace Widgets