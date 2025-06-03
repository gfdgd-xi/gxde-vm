#include <QApplication>
#include <QProcess>
#include "switchwindow.h"

int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
    QApplication a(argc, argv);

    auto switchWindow = SwitchWindow();
    switchWindow.show();

    return a.exec();
}
