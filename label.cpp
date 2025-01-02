#include "label.h"

Label::Label(const int spacing) {
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->setStyleSheet("padding: " + QString::number(spacing*2) + "px");
    this->setReadOnly(true);
}

void Label::updateLabel(const QString& txt) {
    this->setText(text()+txt);
}
