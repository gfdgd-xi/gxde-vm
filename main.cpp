#include <QApplication>
#include <QProcess>
#include "switchwindow.h"
#include "vmcontroller.h"

int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
    QApplication a(argc, argv);

    auto window = SwitchWindow();
    window.show();

    return a.exec();
}
