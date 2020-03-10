#ifndef MEMBER_HPP
#define MEMBER_HPP

#include <QObject>

#include "xtablemodel.hpp"
#include "department.hpp"


class Department;

class Member : public QObject, public XTableModel<Member>
{
    Q_OBJECT

    Q_PROPERTY(quint64 guid READ guid WRITE setGuid NOTIFY guidChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString job READ job WRITE setJob NOTIFY jobChanged)
    Q_PROPERTY(quint64 departmentId READ departmentId WRITE setDepartmentId NOTIFY departmentIdChanged)

    Q_PROPERTY(Department* department READ department WRITE setDepartment NOTIFY departmentChanged)

    X_TABLE_NAME("members")
    X_TABLE_FIELDS(X_FIELD(guid, X_PRIMARY_KEY),
                   X_FIELD(name),
                   X_FIELD(job),
                   X_FIELD(departmentId, "department_id", X_FOREIGN_KEY(Department, X_CASCADE, X_CASCADE)))

    X_FOREIGN_OBJECTS(X_FOREIGN_OBJECT(Department, guid, departmentId, department))

public:
    explicit Member(QObject *parent = nullptr);
    Member(const quint64 &guid, const QString &name, const QString &job, const quint64 &departmentId,
           QObject *parent = nullptr);
    Member(const QString &name, const QString &job, const quint64 &departmentId, QObject *parent = nullptr);
    Member(const Member &other);

    ~Member();

    Member& operator=(const Member &other);

    quint64 guid() const;
    QString name() const;
    QString job() const;    
    quint64 departmentId() const;

    Department* department() const;

public slots:
    void setGuid(const quint64 &guid);
    void setName(const QString &name);
    void setJob(const QString &job);
    void setDepartmentId(const quint64 &departmentId);

    void setDepartment(Department* department);

signals:
    void guidChanged(const quint64 &guid);
    void nameChanged(const QString &name);
    void jobChanged(const QString &job);
    void departmentIdChanged(const quint64 &departmentId);

    void departmentChanged(Department* department);

private:
    quint64 m_guid;
    QString m_name;
    QString m_job;
    quint64 m_departmentId;

    Department* m_department;

    void clearDepartment();
};

#endif // MEMBER_HPP
