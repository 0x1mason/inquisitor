
#include <QJsonObject>


#include "cap.h"


QString Cap::group() const
{
    return _group;
}

void Cap::setGroup(const QString &group)
{
    _group = group;
}

QString Cap::friendlyName() const
{
    return _friendlyName;
}

void Cap::setFriendlyName(const QString &friendlyName)
{
    _friendlyName = friendlyName;
}

QString Cap::name() const
{
    return _name;
}

void Cap::setName(const QString &name)
{
    _name = name;
}

QString Cap::description() const
{
    return _description;
}

void Cap::setDescription(const QString &description)
{
    _description = description;
}

QString Cap::value() const
{
    return _value;
}

void Cap::setValue(const QString &value)
{
    _value = value;
}

void Cap::read(const QJsonObject &json)
{
    _name = json["name"].toString();
    _description = json["description"].toString();
    _friendlyName = json["friendlyName"].toString();
    _group = json["group"].toString();
}

void Cap::write(QJsonObject &json) const
{
    json["name"] = _name;
    json["description"] = _description;
    json["friendlyName"] = _friendlyName;
    json["group"] = _group;
}
