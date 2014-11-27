

#include <QJsonObject>
#include <QString>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QSharedPointer>

#include "cap.h"
#include "helpers.h"

//void getAppRoot()
//{
//#ifdef __APPLE__

//#endif
//}



void read(const QJsonArray &capArray, std::unordered_map<const QString, const Cap* > &capMap /* out */)
{
    for (int i = 0; i < capArray.size(); ++i) {
        QJsonObject capObject = capArray[i].toObject();
        Cap *cap = new Cap();
        cap->read(capObject);
        capMap[cap->name()] = cap;
    }
}

bool loadJson(const QString &path, std::unordered_map<const QString, const Cap* > &capMap /* out */)
{
    QFile loadFile(path);

    if (!loadFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QString err("Couldn't open json file: ");
        err.append(loadFile.errorString());
        qWarning(err.toStdString().c_str());
        return false;
    }

    QString saveData = loadFile.readAll();

    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData.toUtf8()));

    read(loadDoc.array(), capMap);

    return true;
}

