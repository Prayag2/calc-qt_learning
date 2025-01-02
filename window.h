#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QGridLayout>
#include <QKeyEvent>
#include <vector>
#include <button.h>
#include <label.h>

class Window : public QWidget {
Q_OBJECT
public:
    explicit Window(const QString&);
    void add();
    void subtract();
    void multiply();
    void divide();
    void eval();
    void reset();
protected:
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
private:
    qint32 m_spacing {5};
    qint32 m_cellWidth {50};
    qint32 m_cellHeight {50};
    qint32 m_rowCount {6};
    qint32 m_colCount {4};

    qint32 m_windowHeight {m_rowCount*(m_cellHeight+m_spacing)-m_spacing};
    qint32 m_windowWidth {m_colCount*(m_cellWidth+m_spacing)-m_spacing};

    QGridLayout* m_grid {};

    std::vector<Button*> m_numberButtons {};
    ActionButton* m_plusButton {};
    ActionButton* m_minusButton {};
    ActionButton* m_divideButton {};
    ActionButton* m_multiplyButton {};
    ActionButton* m_clearButton {};
    ActionButton* m_evalButton {};
    ActionButton* m_dotButton {};
    Label* m_resultLabel {};

    qlonglong m_result {0};
    bool m_hasOperator {false};

    void handleActionButtonClick(ActionButton* const);
};

#endif // WINDOW_H
