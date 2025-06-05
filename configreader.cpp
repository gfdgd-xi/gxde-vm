#include "configreader.h"
#include <QDir>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>

ConfigReader::ConfigReader(QString programName)
{
    setProgramName(programName);
}

void ConfigReader::setProgramName(QString programName)
{
    m_programName = programName;
    m_configDirPath = QDir::homePath() + "/.config/" + m_programName;
    // 如果配置文件夹不存在则重新创建
    QDir configDir(m_configDirPath);
    if (!configDir.exists()) {
        configDir.mkpath(m_configDirPath);
    }
}

QVariant ConfigReader::read(QString name, QString item)
{
    QJsonDocument document = readName(name);
    QJsonObject object = document.object();
    return object.value(item).toVariant();
}

QJsonDocument ConfigReader::readName(QString name)
{
    return readJsonFile(m_configDirPath + "/" + name + ".json");
}

void ConfigReader::write(QString name, QString item, QVariant value)
{
    QJsonObject object = readName(name).object();
    object.insert(item, QJsonValue::fromVariant(value));
    writeName(name, QJsonDocument(object));
}

void ConfigReader::writeName(QString name, QJsonDocument json)
{
    writeJsonFile(m_configDirPath + "/" + name + ".json", json);
}

void ConfigReader::remove(QString name, QString item)
{
    QJsonObject object = readName(name).object();
    object.remove(item);
    writeName(name, QJsonDocument(object));
}

QJsonDocument ConfigReader::readJsonFile(QString path)
{
    QFile file(path);
    if (!file.exists()) {
        return QJsonDocument();
    }
    file.open(QFile::ReadOnly);
    QJsonDocument json = QJsonDocument::fromJson(file.readAll());
    file.close();
    return json;
}

void ConfigReader::writeJsonFile(QString path, QJsonDocument json)
{
    QFile file(path);
    file.open(QFile::WriteOnly);
    file.write(json.toJson(QJsonDocument::JsonFormat::Compact));
    file.close();
}
