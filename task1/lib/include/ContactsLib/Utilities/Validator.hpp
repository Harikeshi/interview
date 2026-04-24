#pragma once

#include <QString>

namespace Utilities {
class Validator
{
public:
    class ValidationResult
    {
        bool isValid = false;
        QString infoMessage = "";

    public:
        ValidationResult(bool valid, QString info);
        bool IsValid() const;
        QString GetMessage() const;
    };

    static ValidationResult ValidatePhone(const QString& phone);
    static ValidationResult ValidateEmail(const QString& email);
};
} // namespace Utilities