#include "switchwindow.h"
#include "vmcontroller.h"
#include <QVBoxLayout>
#include <QScreen>
#include <QGuiApplication>
#include <QDebug>
#include <QTimer>

SwitchWindow::SwitchWindow(QWidget *parent) : QWidget(parent)
{
    m_switchTextLabel.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(&m_switchTextLabel);
    setLayout(layout);

    this->setAttribute(Qt::WA_Hover,true);
    this->installEventFilter(this);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool);
    this->setAttribute(Qt::WA_X11NetWmWindowTypeDock);
    this->setAttribute(Qt::WA_X11DoNotAcceptFocus);
    // 设置 Qt::X11BypassWindowManagerHint 以不被 gxde-top-panel 和 dde-dock 干扰
    this->setWindowFlags(Qt::WindowDoesNotAcceptFocus | Qt::X11BypassWindowManagerHint);

    refreshVMStatus();  // 刷新文案
    // 设置 Timer 定期获取虚拟机状态
    QTimer *vmRefreshTimer = new QTimer();
    connect(vmRefreshTimer, &QTimer::timeout, this, &SwitchWindow::refreshVMStatus);
    vmRefreshTimer->setInterval(500);
    vmRefreshTimer->start();
}

void SwitchWindow::show()
{
    QWidget::show();
    // 设置窗口大小和位置
    // 只有在调用 show 后才能获取到正确的窗口大小
    m_windowWidth = this->width() * 2;
    m_windowHeight = this->height();
    resizeWindow(false);

}

void SwitchWindow::resizeWindow(bool isShow)
{
    if (isShow == m_isShow) {
        // 无需重复调整，不再执行操作以减小性能消耗
        return;
    }

    auto screen = QGuiApplication::primaryScreen();
    int screenWidth = screen->geometry().width();
    m_isShow = isShow;
    if (isShow) {
        m_windowRect = QRect(screenWidth / 2 - m_windowWidth / 2,
                             0,
                             m_windowWidth,
                             m_windowHeight);
        this->setGeometry(m_windowRect);

        return;
    }
    int height = WINDOW_HIDE_HEIGHT;
    m_windowRect = QRect(screenWidth / 2 - m_windowWidth / 2,
                         0 - m_windowHeight + height,
                         m_windowWidth,
                         m_windowHeight);
    this->setGeometry(m_windowRect);
    return;
}

void SwitchWindow::refreshVMStatus()
{
    setStyleSheet("background: grey; color: white;");
    if (m_vmController.isDie()) {
        m_switchTextLabel.setText(tr("虚拟机未启动"));
        return;
    }
    m_switchTextLabel.setText(m_vmController.isInVM()
                                  ? tr("切换至宿主机")
                                  : tr("切换至虚拟机"));
}

bool SwitchWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == this) {
        if (event->type() == QEvent::HoverMove || event->type() == QEvent::HoverEnter) {
            QPoint cursorPos = QCursor::pos();

            if (m_windowRect.contains(cursorPos)) {
                resizeWindow(true);
            } else {
                resizeWindow(false);
            }

            return true;
        } else if (event->type() == QEvent::HoverLeave) {
            resizeWindow(false);
        } else if (event->type() == QEvent::MouseButtonPress) {
            m_vmController.switchAuto();
            refreshVMStatus();
        }
    }
    return QWidget::eventFilter(obj, event);
}
