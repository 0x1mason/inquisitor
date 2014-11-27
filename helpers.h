

#ifndef HELPERS_H
#define HELPERS_H
#include <unordered_map>
#include <QSharedPointer>
#include <cap.h>

namespace std
{
template<>
struct hash<const QString> {
    size_t operator()(const QString &s) const {
        return std::hash<std::string>()(s.toStdString());
    }
};
}

template<typename T> bool isType(QObject *instance)
{
    return qobject_cast<T*>(instance) != NULL;
};

bool loadJson(const QString &path, std::unordered_map<const QString, const Cap* > &capMap /* out */);
QString getAppRoot();

#endif // HELPERS_H
