#include "window.h"
#include <vector>
#include <QTimer>

Window::Window(const QString& title) : QWidget() {
    this->setFocusPolicy(Qt::StrongFocus);
    setWindowTitle(title);
    setFixedSize(m_windowWidth, m_windowHeight);

    m_grid = new QGridLayout(this);
    m_grid->setSpacing(m_spacing);

    m_resultLabel = new Label {m_spacing};

    // Initializing the buttons
    m_numberButtons.resize(10);
    for (int i = 0; i < 10; i++) {
        m_numberButtons[i] = new Button{QString::number(i), m_resultLabel};
    }

    for (int i = 1; i < 10; i++) {
        m_grid->addWidget(m_numberButtons[i], 4-(i-1)/3, (i-1)%3);
    }

    m_plusButton = new ActionButton{"+", m_resultLabel, std::bind(&Window::add, this)};
    m_minusButton = new ActionButton{"-", m_resultLabel, std::bind(&Window::subtract, this)};
    m_divideButton = new ActionButton{"/", m_resultLabel, std::bind(&Window::divide, this)};
    m_multiplyButton = new ActionButton{"*", m_resultLabel, std::bind(&Window::multiply, this)};
    m_clearButton = new ActionButton{"AC", std::bind(&Window::reset, this)};
    m_evalButton = new ActionButton{"=", nullptr, nullptr};
    m_dotButton = new ActionButton{".", m_resultLabel};;

    QObject::connect(m_clearButton, &Button::pressed, m_resultLabel, &Label::clear);

    m_grid->addWidget(m_resultLabel, 0, 0, 1, 4);
    m_grid->addWidget(m_clearButton, 1, 0);
    m_grid->addWidget(m_divideButton, 1, 1);
    m_grid->addWidget(m_multiplyButton, 1, 2);
    m_grid->addWidget(m_minusButton, 1, 3);
    m_grid->addWidget(m_plusButton, 2, 3, 2, 1);
    m_grid->addWidget(m_evalButton, 4, 3, 2, 1);
    m_grid->addWidget(m_numberButtons[0], 5, 0, 1, 2);
    m_grid->addWidget(m_dotButton, 5, 2);
}

void Window::handleActionButtonClick(ActionButton* const btn) {
    btn->click();
    btn->setDown(true);
    m_hasOperator = true;
    m_evalButton->func = btn->func;
}

void Window::keyPressEvent(QKeyEvent* event) {
    const int code = event->key();
    qDebug() << code;

    if (code == Qt::Key_Backspace) {
        QString label = m_resultLabel->text();
        m_resultLabel->setText(label.left(label.length()-1));
        return;
    }

    // auto repeat is only allowed for backspace
    if (event->isAutoRepeat()) return;

    if (m_hasOperator) {
        m_resultLabel->clear();
        m_hasOperator = false;
    }

    if ('0' <= code && code <= '9') {
        m_numberButtons[code-'0']->click();
        m_numberButtons[code-'0']->setDown(true);
    } else if (code == Qt::Key_Return || code == Qt::Key_Enter) {
        m_evalButton->click();
        m_evalButton->setDown(true);
        m_result = 0;
    } else {
        switch(code) {
        case Qt::Key_Plus:
            handleActionButtonClick(m_plusButton);
            break;
        case Qt::Key_Minus:
            handleActionButtonClick(m_minusButton);
            break;
        case Qt::Key_Asterisk:
            handleActionButtonClick(m_multiplyButton);
            break;
        case Qt::Key_Slash:
            handleActionButtonClick(m_divideButton);
            break;
        case Qt::Key_Period:
            break;
        }
    }
}

void Window::keyReleaseEvent(QKeyEvent*) {
    for (int i = 0; i < 10; i++) {
        m_numberButtons[i]->setDown(false);
    }
    m_plusButton->setDown(false);
    m_minusButton->setDown(false);
    m_divideButton->setDown(false);
    m_multiplyButton->setDown(false);
    m_clearButton->setDown(false);
    m_evalButton->setDown(false);
    m_dotButton->setDown(false);
}

void Window::add() {
    qlonglong curNum = m_resultLabel->text().toLongLong();
    m_result += curNum;
    m_resultLabel->setText(QString::number(m_result));
}
void Window::multiply() {
    qlonglong curNum = m_resultLabel->text().toLongLong();
    if (m_result == 0) m_result = 1;
    m_result *= curNum;
    m_resultLabel->setText(QString::number(m_result));
}
void Window::divide() {
    qlonglong curNum = m_resultLabel->text().toLongLong();
    if (curNum == 0) {
        m_resultLabel->setText("Don't divide by zero bro");
        return;
    }
    m_result /= curNum;
    m_resultLabel->setText(QString::number(m_result));
}
void Window::subtract() {
    qlonglong curNum = m_resultLabel->text().toLongLong();
    if (m_result == 0) m_result = curNum*2;
    m_result -= curNum;
    m_resultLabel->setText(QString::number(m_result));
}

void Window::reset() {
    m_resultLabel->setText("");
    m_result = 0;
    m_evalButton->func = nullptr;
}
