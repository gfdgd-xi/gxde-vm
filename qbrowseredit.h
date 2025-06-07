#ifndef QBROWSEREDIT_H
#define QBROWSEREDIT_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

class QBrowserEdit : public QWidget
{
    Q_OBJECT
public:
    enum DialogType {
        Dir = 0,
        FileOpen = 1,
        FileSave = 2
    };

    explicit QBrowserEdit(QWidget *parent = nullptr);
    QBrowserEdit(QWidget *parent, DialogType type,
                 QString caption, QString dir, QString filter);

    QString text() {
        return m_lineEdit.text();
    };

    void setText(QString text) {
        m_lineEdit.setText(text);
    }

private:
    void browser();

    QHBoxLayout m_layout;
    QLineEdit m_lineEdit;
    QPushButton m_browserButton;
    DialogType m_dialogType;
    QString m_caption;
    QString m_dir;
    QString m_filter;
};

#endif // QBROWSEREDIT_H
