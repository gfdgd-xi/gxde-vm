#ifndef VMCONTROLLER_H
#define VMCONTROLLER_H

#include <KWindowSystem>
#include <QObject>
#include <QTimer>

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
    QTimer m_searchVM;
};

#endif // VMCONTROLLER_H
