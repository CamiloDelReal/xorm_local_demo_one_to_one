#include "member.hpp"

Member::Member(QObject *parent)
    : QObject(parent), XTableModel<Member>()
{
    m_guid = 0;
    m_departmentId = 0;
    m_department = nullptr;
}

Member::Member(const quint64 &guid, const QString &name, const QString &job, const quint64 &departmentId, QObject *parent)
    : QObject (parent), XTableModel<Member>()
{
    m_guid = guid;
    m_name = name;
    m_job = job;
    m_departmentId = departmentId;
    m_department = nullptr;
}

Member::Member(const QString &name, const QString &job, const quint64 &departmentId, QObject *parent)
    : QObject (parent), XTableModel<Member>()
{
    m_guid = 0;
    m_name = name;
    m_job = job;
    m_departmentId = departmentId;
    m_department = nullptr;
}

Member::Member(const Member &other)
    : QObject (other.parent()), XTableModel<Member>()
{
    m_guid = other.m_guid;
    m_name = other.m_name;
    m_job = other.m_job;
    m_departmentId = other.m_departmentId;
    m_department = other.m_department;
}

Member::~Member()
{
    clearDepartment();
}

Member& Member::operator=(const Member &other)
{
    m_guid = other.m_guid;
    m_name = other.m_name;
    m_job = other.m_job;
    m_departmentId = other.m_departmentId;
    clearDepartment();
    m_department = other.m_department;

    setParent(other.parent());

    return *this;
}

quint64 Member::guid() const
{
    return m_guid;
}

QString Member::name() const
{
    return m_name;
}

QString Member::job() const
{
    return m_job;
}

quint64 Member::departmentId() const
{
    return m_departmentId;
}

Department* Member::department() const
{
    return m_department;
}

void Member::setGuid(const quint64 &guid)
{
    if (m_guid != guid)
    {
        m_guid = guid;
        emit guidChanged(m_guid);
    }
}

void Member::setName(const QString &name)
{
    if (m_name != name)
    {
        m_name = name;
        emit nameChanged(m_name);
    }
}

void Member::setJob(const QString &job)
{
    if (m_job != job)
    {
        m_job = job;
        emit jobChanged(m_job);
    }
}

void Member::setDepartmentId(const quint64 &departmentId)
{
    if (m_departmentId != departmentId)
    {
        m_departmentId = departmentId;
        emit departmentIdChanged(m_departmentId);
        setDepartment(nullptr);
    }
}

void Member::setDepartment(Department *department)
{
    if (m_department != department)
    {
        clearDepartment();
        m_department = department;
        emit departmentChanged(m_department);
    }
}

void Member::clearDepartment()
{
    if(m_department != nullptr)
    {
        m_department->deleteLater();
        m_department = nullptr;
    }
}
