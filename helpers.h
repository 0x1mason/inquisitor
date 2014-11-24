#ifndef HELPERS_H
#define HELPERS_H
#include <QSharedPointer>
#include <cap.h>

bool loadJson(const QString &path, std::map<const QString, QSharedPointer<Cap> > &capMap /* out */);

#endif // HELPERS_H
