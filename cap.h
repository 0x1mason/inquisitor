#ifndef CAP_H
#define CAP_H
#include <QString>
#include <QObject>

class Cap : public QObject
{
     Q_OBJECT
public slots:
    void setValue(const QString &description);

public:
    QString name() const;
    void setName(const QString &name);

    QString group() const;
    void setGroup(const QString &group);

    QString friendlyName() const;
    void setFriendlyName(const QString &friendlyName);

    QString description() const;
    void setDescription(const QString &description);

    QString value() const;

    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;

private:
    QString _name;
    QString _group;
    QString _friendlyName;
    QString _description;
    QString _value;
};

#endif // CAP_H
