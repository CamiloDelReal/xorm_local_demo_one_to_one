#ifndef DEPARTMENT_HPP
#define DEPARTMENT_HPP

#include <QObject>

#include "xtablemodel.hpp"


class Department : public QObject, public XTableModel<Department>
{
    Q_OBJECT

    Q_PROPERTY(quint64 guid READ guid WRITE setGuid NOTIFY guidChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged)

    X_TABLE_NAME("departments")
    X_TABLE_FIELDS(X_FIELD(guid, X_PRIMARY_KEY),
                   X_FIELD(name),
                   X_FIELD(description))

public:
    explicit Department(QObject *parent = nullptr);
    Department(const quint64 &guid, const QString &name, const QString &description, QObject *parent = nullptr);
    Department(const QString &name, const QString &description, QObject *parent = nullptr);
    Department(const Department &other);

    Department& operator=(const Department &other);

    quint64 guid() const;
    QString name() const;
    QString description() const;

public slots:
    void setGuid(const quint64 &guid);
    void setName(const QString &name);
    void setDescription(const QString &description);

signals:
    void guidChanged(const quint64 &guid);
    void nameChanged(const QString &name);
    void descriptionChanged(const QString &description);

private:
    quint64 m_guid;
    QString m_name;
    QString m_description;
};

#endif // DEPARTMENT_HPP
