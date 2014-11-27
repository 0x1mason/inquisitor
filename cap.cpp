
#include <QJsonObject>

#include <assert.h>
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

QString Cap::help() const
{
    return _help;
}

void Cap::setHelp(const QString &help)
{
    _help = help;
}

QString Cap::type() const
{
    return _type;
}

void Cap::setType(const QString &type)
{
    _type = type;
}

QString Cap::value() const
{
    return _value;
}

void Cap::setValue(const QString &value)
{
    _value = value;
}

void Cap::setValue(int i)
{
    if (type() == "bool")
    {
        assert(i >= 0 && i <= 1);
        setValue(i == 0 ? "false" : "true");
    }
    else if (type() == "int")
    {
        _value = QString::number(i);
    }
    else
    {
        assert(false);
    }
}

void Cap::read(const QJsonObject &json)
{
    _name = json["name"].toString();
    _description = json["description"].toString();
    _friendlyName = json["friendlyName"].toString();
    _group = json["group"].toString();
    _help = json["help"].toString();
    _value = json["value"].toString();
    _type = json["type"].toString();
}

void Cap::write(QJsonObject &json) const
{
    json["name"] = _name;
    json["description"] = _description;
    json["friendlyName"] = _friendlyName;
    json["group"] = _group;
    json["help"] = _help;
    json["value"] = _value;
        json["type"] = _type;
}
