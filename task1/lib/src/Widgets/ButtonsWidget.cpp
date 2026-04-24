#include <ContactsLib/Widgets/ButtonsWidget.hpp>

#include <QHBoxLayout>

namespace Widgets {
ButtonsWidget::ButtonsWidget(QWidget* parent) : QWidget(parent)
{
    buildUi();
    UpdateSave(false);
}
void ButtonsWidget::UpdateSave(bool check)
{
    saveButton->setDisabled(!check);
}

/*private*/
void ButtonsWidget::buildUi()
{
    auto* mainLayout = new QHBoxLayout(this);
    addButton = new QPushButton("Добавить", this);
    saveButton = new QPushButton("Сохранить", this);
    deleteButton = new QPushButton("Удалить", this);
    mainLayout->addWidget(addButton);
    mainLayout->addWidget(saveButton);
    mainLayout->addWidget(deleteButton);

    connect(addButton, &QPushButton::clicked, this, &ButtonsWidget::onAddButtonClicked);
    connect(saveButton, &QPushButton::clicked, this, &ButtonsWidget::onSaveButtonClicked);
    connect(deleteButton, &QPushButton::clicked, this, &ButtonsWidget::onDeleteButtonClicked);
}
} // namespace Widgets