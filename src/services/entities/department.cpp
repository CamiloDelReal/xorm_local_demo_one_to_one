#include "department.hpp"

Department::Department(QObject *parent)
    : QObject(parent), XTableModel<Department>()
{
}

Department::Department(const quint64 &guid, const QString &name, const QString &description, QObject *parent)
    : QObject(parent), XTableModel<Department>()
{
    m_guid = guid;
    m_name = name;
    m_description = description;
}

Department::Department(const QString &name, const QString &description, QObject *parent)
    : QObject(parent), XTableModel<Department>()
{
    m_guid = 0;
    m_name = name;
    m_description = description;
}

Department::Department(const Department &other)
    : QObject(other.parent()), XTableModel<Department>()
{
    m_guid = other.m_guid;
    m_name = other.m_name;
    m_description = other.m_description;
}

Department& Department::operator=(const Department &other)
{
    m_guid = other.m_guid;
    m_name = other.m_name;
    m_description = other.m_description;

    setParent(other.parent());

    return *this;
}

quint64 Department::guid() const
{
    return m_guid;
}

QString Department::name() const
{
    return m_name;
}

QString Department::description() const
{
    return m_description;
}

void Department::setGuid(const quint64 &guid)
{
    if (m_guid != guid)
    {
        m_guid = guid;
        emit guidChanged(m_guid);
    }
}

void Department::setName(const QString &name)
{
    if (m_name != name)
    {
        m_name = name;
        emit nameChanged(m_name);
    }
}

void Department::setDescription(const QString &description)
{
    if (m_description != description)
    {
        m_description = description;
        emit descriptionChanged(m_description);
    }
}
