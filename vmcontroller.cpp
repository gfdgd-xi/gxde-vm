#include "vmcontroller.h"
#include <KWindowSystem>
#include <KWindowInfo>
#include <QDebug>

VMController::VMController()
{
    researchVMWindow();
}

void VMController::researchVMWindow()
{
    for (WId id : KWindowSystem::windows()) {
        KWindowInfo info(id, NET::WMVisibleName | NET::WMName | NET::WMState);
        if (VM_NAME == info.visibleName()) {
            m_spiceID = id;
            break;
        }
    }
}

void VMController::switchAuto()
{
    if (!isInVM()) {
        switchToVM();
        return;
    }
    switchToPC();
}

void VMController::switchToVM()
{
    KWindowSystem::activateWindow(m_spiceID);  // 激活并显示窗口
    KWindowSystem::forceActiveWindow(m_spiceID); // 强制聚焦
}

void VMController::switchToPC()
{
    KWindowSystem::minimizeWindow(m_spiceID);
}

bool VMController::isInVM()
{
    KWindowInfo info(m_spiceID, NET::WMVisibleName | NET::WMName | NET::WMState);
    return !info.isMinimized();
}
