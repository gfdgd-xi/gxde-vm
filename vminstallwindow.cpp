#include "vminstallwindow.h"
#include "commondefine.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QDir>

VMInstallWindow::VMInstallWindow(QWidget *parent)
    : QMainWindow(parent)
{
    m_configReader = new ConfigReader(PROGRAM_NAME);

    m_cancelButton.setText(tr("Cancel"));
    m_applyButton.setText(tr("Apply"));

    QHBoxLayout *mainLayout = new QHBoxLayout(this);

    mainLayout->addWidget(&m_settingWidget);

    QVBoxLayout *controlLayout = new QVBoxLayout;
    controlLayout->addStretch();
    controlLayout->addWidget(&m_cancelButton);
    controlLayout->addWidget(&m_applyButton);
    mainLayout->addLayout(controlLayout);

    this->setCentralWidget(&m_mainWidget);
    m_mainWidget.setLayout(mainLayout);
    setWindowTitle(tr("Setting"));

    initSettingPage();

    connect(&m_cancelButton, &QPushButton::clicked, this, &QMainWindow::close);
    connect(&m_applyButton, &QPushButton::clicked, this, &VMInstallWindow::save);


    m_objectList << mainLayout << controlLayout;
}

VMInstallWindow::~VMInstallWindow()
{
    delete m_configReader;
    for (auto i: m_objectList) {
        delete i;
    }
}

void VMInstallWindow::initSettingPage()
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    QLabel *pathSettingLabel = new QLabel(tr("Virtual Machine Path:"));
    QBrowserEdit *vmPath = new QBrowserEdit(this,
                                            QBrowserEdit::DialogType::Dir,
                                            tr("Choose VM Config Path"),
                                            QDir::homePath(),
                                            "");


    layout->addWidget(pathSettingLabel);
    layout->addWidget(vmPath);

    layout->addStretch();
    m_settingWidget.setLayout(layout);

    m_browserEditList["VMConfPath"] = vmPath;

    m_objectList << layout << pathSettingLabel;

    read();

}

void VMInstallWindow::read()
{
    for (QString i: m_browserEditList.keys()) {
        m_browserEditList[i]->setText(m_configReader->read(PROGRAM_NAME, i).toString());
    }
}

void VMInstallWindow::save()
{
    for (QString i: m_browserEditList.keys()) {
        m_configReader->write(PROGRAM_NAME, i, m_browserEditList[i]->text());
    }
}
