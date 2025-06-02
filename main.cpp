#include <QApplication>
#include <QProcess>
#include "switchwindow.h"
#include "vmcontroller.h"

int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
    QApplication a(argc, argv);

    QString configPath = "/media/gfdgd_xi/aa5c0419-e1b5-4ff5-8160-14f0c5b2bd3a/qemu-test/win10/windows-10.conf";

    VMController *vm = new VMController();
    if (vm->isDie()) {
        // 如果虚拟机未开启，则手动开启虚拟机
        QProcess *process = new QProcess();
        process->start("quickemu", QStringList() << "--vm"
                                                 << configPath
                                                 << "--display"
                                                 << "spice"
                                                 // 共享文件夹：/
                                                 << "-public-dir"
                                                 << "/"
                                                 // 全屏显示
                                                 << "--fullscreen");
        process->waitForStarted();
        process->waitForFinished();
    }
    delete vm;

    auto window = SwitchWindow();
    window.show();

    return a.exec();
}
