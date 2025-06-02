#ifndef VMCONTROLLER_H
#define VMCONTROLLER_H

#include <KWindowSystem>
#include <QObject>
#include <QTimer>
#include <QProcess>

#define VM_NAME "windows-10"

class VMController : public QObject
{
    Q_OBJECT
public:
    VMController();
    void switchToVM();
    void switchToPC();
    void switchAuto();
    void researchVMWindow();
    void startVM();
    void killVM();
    bool isInVM();
    bool isDie();

private:
    WId m_spiceID;
    QTimer m_searchVM;
    QProcess m_vmProcess;
};

#endif // VMCONTROLLER_H
