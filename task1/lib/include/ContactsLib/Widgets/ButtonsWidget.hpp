#pragma once

#include <QPushButton>

namespace Widgets {
class ButtonsWidget final : public QWidget
{
    Q_OBJECT
public:
    explicit ButtonsWidget(QWidget* parent = nullptr);
    void UpdateSave(bool check);
signals:
    void onAddButtonClicked();
    void onSaveButtonClicked();
    void onDeleteButtonClicked();

private:
    void buildUi();

    QPushButton* addButton;
    QPushButton* saveButton;
    QPushButton* deleteButton;
};
} // namespace Widgets