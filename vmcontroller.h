#ifndef VMCONTROLLER_H
#define VMCONTROLLER_H

#include <KWindowSystem>
#include <QObject>

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
    bool isInVM();
    bool isDie();

private:
    WId m_spiceID;
};

#endif // VMCONTROLLER_H
