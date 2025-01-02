#include "button.h"

Button::Button(const QString& txt, Label* const result) {
    this->setText(txt);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    if (result != nullptr) {
        m_labelPtr = result;
    }
    QObject::connect(this, &Button::pressed, this, &Button::handlePressed);
}

ActionButton::ActionButton(const QString& txt, Label* const result, std::function<void()> f)
    : Button(txt, result)
{
    func = f;
}
ActionButton::ActionButton(const QString& txt, std::function<void()> f)
    : Button(txt)
{
    func = f;
}

void Button::handlePressed() {
    if (m_labelPtr != nullptr) {
        m_labelPtr->updateLabel(this->text());
    }
}

void ActionButton::handlePressed() {
    if (func != nullptr) {
        func();
    }
}
