#include <../include/ContactsLib/Utilities/Validator.hpp>
#include <gtest/gtest.h>

TEST(ValidatorTest, ValidateEmailValid)
{
    QString email = "main@mail.ru";

    EXPECT_TRUE(Utilities::Validator::ValidateEmail(email).IsValid());
}

TEST(ValidatorTest, ValidateEmailNoValid)
{
    QString email = "main$mail.ru";

    EXPECT_FALSE(Utilities::Validator::ValidateEmail(email).IsValid());
}

TEST(ValidatorTest, ValidatePhoneValid)
{
    QString phone = "79032201771";

    EXPECT_TRUE(Utilities::Validator::ValidatePhone(phone).IsValid());
}

TEST(ValidatorTest, ValidatePhoneNoValid)
{
    QString phone = "790З2201771";

    EXPECT_FALSE(Utilities::Validator::ValidatePhone(phone).IsValid());
}
