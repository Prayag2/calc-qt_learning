#include <QApplication>
#include <QLineEdit>
#include <window.h>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    Window w {"Calculator"};

    w.show();
    return app.exec();
}
