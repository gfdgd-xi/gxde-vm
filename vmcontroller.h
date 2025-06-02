#ifndef VMCONTROLLER_H
#define VMCONTROLLER_H

#include <KWindowSystem>

#define VM_NAME "windows-10"

class VMController
{
public:
    VMController();
    void switchToVM();
    void switchToPC();
    void switchAuto();
    void researchVMWindow();
    bool isInVM();

private:
    WId m_spiceID;
};

#endif // VMCONTROLLER_H
