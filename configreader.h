#ifndef CONFIGREADER_H
#define CONFIGREADER_H

#include <QObject>
#include <QJsonDocument>

class ConfigReader : public QObject
{
    Q_OBJECT
public:
    ConfigReader(QString programName);
    void setProgramName(QString programName);

    QVariant read(QString name, QString item);
    QJsonDocument readName(QString name);

    void write(QString name, QString item, QVariant value);
    void writeName(QString name, QJsonDocument json);

    void remove(QString name, QString item);

    QJsonDocument readJsonFile(QString path);
    void writeJsonFile(QString path, QJsonDocument json);

private:
    QString m_programName;
    QString m_configDirPath;
};

#endif // CONFIGREADER_H
