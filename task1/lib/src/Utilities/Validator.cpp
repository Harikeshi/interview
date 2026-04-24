#include <ContactsLib/Utilities/Validator.hpp>

#include <QString>
#include <utility>

namespace Utilities {
Validator::ValidationResult::ValidationResult(bool valid, QString info) : isValid(valid), infoMessage(std::move(info))
{
}
bool Validator::ValidationResult::IsValid() const
{
    return isValid;
}
QString Validator::ValidationResult::GetMessage() const
{
    return infoMessage;
}

Validator::ValidationResult Validator::ValidatePhone(const QString& phone)
{
    if (phone.isEmpty())
    {
        return {false, "Номер телефона обязателен для заполнения"};
    }
    for (auto digit : phone)
    {
        if (!digit.isDigit())
        {
            return {false, "Номер телефона должен содержать хотя бы одну цифру"};
        }
    }
    return {true, ""};
}
Validator::ValidationResult Validator::ValidateEmail(const QString& email)
{
    if (email.trimmed().isEmpty())
    {
        return {true, ""};
    }
    if (!email.contains('@'))
    {
        return {false, "Email должен содержать символ @"};
    }
    return {true, ""};
}
} // namespace Utilities