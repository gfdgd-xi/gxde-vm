#include "vmcontroller.h"
#include <KWindowSystem>
#include <KWindowInfo>
#include <QDebug>
#include <KX11Extras>
#include <NETWM>
#include <QX11Info>
#include <QTimer>

VMController::VMController()
{
    researchVMWindow();
    connect(&m_searchVM, &QTimer::timeout, this, &VMController::researchVMWindow);
    m_searchVM.setInterval(1000);
    m_searchVM.start();
}

void VMController::researchVMWindow()
{
    if (!isDie()) {
        // 如果虚拟机窗口没有销毁则不重新获取 id
        return;
    }
    for (WId id : KWindowSystem::windows()) {
        KWindowInfo info(id, NET::WMVisibleName | NET::WMName | NET::WMState);
        if (VM_NAME == info.visibleName()) {
            m_spiceID = id;
            break;
        }
    }
    // 隐藏任务栏图标
    KWindowSystem::setState(m_spiceID, NET::SkipTaskbar);
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
    KX11Extras::activateWindow(m_spiceID);  // 激活并显示窗口
    KX11Extras::forceActiveWindow(m_spiceID); // 强制聚焦
}

void VMController::switchToPC()
{
    KX11Extras::minimizeWindow(m_spiceID);

}

bool VMController::isDie()
{
    KWindowInfo info(m_spiceID, NET::WMVisibleName | NET::WMName | NET::WMState);
    return info.visibleName() == "" && !info.isMinimized();
}

bool VMController::isInVM()
{
    KWindowInfo info(m_spiceID, NET::WMVisibleName | NET::WMName | NET::WMState);
    if (isDie()) {
        // 虚拟机已销毁，则一定不在虚拟机内
        return 0;
    }
    return !info.isMinimized();
}
