#ifndef LABEL_H
#define LABEL_H

#include <QLineEdit>

class Label : public QLineEdit
{
Q_OBJECT
public:
    Label(const int);
    void updateLabel(const QString&);
};

#endif // LABEL_H
