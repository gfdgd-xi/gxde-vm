#ifndef VMINSTALLWINDOW_H
#define VMINSTALLWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QLineEdit>
#include <QScrollArea>
#include <QPushButton>
#include "configreader.h"
#include "qbrowseredit.h"

class VMInstallWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit VMInstallWindow(QWidget *parent = nullptr);
    ~VMInstallWindow();

private:
    void initSettingPage();
    void read();
    void save();

    QPushButton m_applyButton;
    QPushButton m_cancelButton;

    QWidget m_mainWidget;
    QScrollArea m_settingWidget;
    ConfigReader *m_configReader;
    QList<QObject *> m_objectList;

    QMap<QString, QBrowserEdit *> m_browserEditList;
};

#endif // VMINSTALLWINDOW_H
