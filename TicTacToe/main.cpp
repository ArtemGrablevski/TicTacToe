#include <QApplication>
#include <QStyleFactory>

#include "tictactoe.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setStyle(QStyleFactory::create("Fusion"));

    QPalette darkPalette;
    darkPalette.setColor(QPalette::Window, QColor(25, 25, 25));
    darkPalette.setColor(QPalette::WindowText, Qt::white);
    darkPalette.setColor(QPalette::Text, Qt::white);
    darkPalette.setColor(QPalette::Button, QColor(30, 30, 30));

    app.setPalette(darkPalette);

    MainWindow w;
    w.setFixedSize(480, 480);
    w.show();

    return app.exec();
}
