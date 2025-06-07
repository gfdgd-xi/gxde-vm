#include "qbrowseredit.h"
#include <QFileDialog>
#include <QDir>

QBrowserEdit::QBrowserEdit(QWidget *parent)
{
    QBrowserEdit(parent, DialogType::FileOpen, "", QDir::homePath(), tr("All Files (*.*)"));
}


QBrowserEdit::QBrowserEdit(QWidget *parent, DialogType type,
    QString caption, QString dir, QString filter)
    : QWidget(parent)
{
    m_dialogType = type;
    m_caption = caption;
    m_dir = dir;
    m_filter = filter;

    m_browserButton.setText(tr("Browser"));
    connect(&m_browserButton, &QPushButton::clicked, this, &QBrowserEdit::browser);

    m_layout.addWidget(&m_lineEdit);
    m_layout.addWidget(&m_browserButton);

    setLayout(&m_layout);
}

void QBrowserEdit::browser()
{
    QString path;
    switch (m_dialogType) {
    case DialogType::FileOpen:
        path = QFileDialog::getOpenFileName(this, m_caption, m_dir, m_filter);
        break;
    case DialogType::FileSave:
        path = QFileDialog::getSaveFileName(this, m_caption, m_dir, m_filter);
        break;
    case DialogType::Dir:
        path = QFileDialog::getExistingDirectory(this, m_caption, m_dir);
        break;
    default:
        path = QFileDialog::getOpenFileName(this, m_caption, m_dir, m_filter);
        break;
    }
    if (path != NULL && path != "") {
        m_lineEdit.setText(path);
    }
}
