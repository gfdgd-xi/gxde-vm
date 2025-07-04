#ifndef SWITCHWINDOW_H
#define SWITCHWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QLabel>
#include <QSystemTrayIcon>
#include "vmcontroller.h"
#include "configreader.h"

#define WINDOW_HIDE_HEIGHT  2

class SwitchWindow : public QWidget
{
public:
    explicit SwitchWindow(QWidget *parent = nullptr);
    ~SwitchWindow();

public Q_SLOTS:
    void show();

private:
    void resizeWindow(bool isShow);
    void refreshVMStatus();
    void switchVMAndHost();
    void initTrayIcon();

    int m_windowWidth;
    int m_windowHeight;
    bool m_isShow = true;
    bool m_isInVM = false;
    QRect m_windowRect;
    QWidget m_mainWidget;
    QLabel m_switchTextLabel;
    QSystemTrayIcon m_trayIcon;
    ConfigReader *m_configReader;
    VMController *m_vmController;

protected:
    bool eventFilter(QObject *obj, QEvent *event);
};

#endif // SWITCHWINDOW_H
