#ifndef BUTTON_H
#define BUTTON_H

#include <QPushButton>
#include <QLineEdit>
#include <label.h>

class Button : public QPushButton
{
Q_OBJECT
public:
    Button(const QString&, Label* = nullptr);
signals:
    void clicked(const QString&);
protected slots:
    virtual void handlePressed();
protected:
    Label* m_labelPtr {};
};

class ActionButton : public Button {
Q_OBJECT
public:
    ActionButton(const QString&, std::function<void()> = nullptr);
    ActionButton(const QString&, Label* = nullptr, std::function<void()> = nullptr);
    std::function<void()> func;
protected slots:
    void handlePressed() override;
};

#endif // BUTTON_H
