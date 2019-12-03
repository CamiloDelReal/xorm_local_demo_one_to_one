#include "departmentmodel.hpp"

DepartmentModel::DepartmentModel(QObject *parent)
    : QAbstractListModel(parent)
{

}

DepartmentModel::~DepartmentModel()
{
    clearData();
}

int DepartmentModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_departments.size();
}

QVariant DepartmentModel::data(const QModelIndex &index, int role) const
{
    QVariant wrapper;

    if(index.row() >= 0 && index.row() < m_departments.size())
    {
        const Department * const item = m_departments.at(index.row());

        switch(role)
        {
        case GuidRole:
            wrapper.setValue(item->guid());
            break;
        case NameRole:
            wrapper.setValue(item->name());
            break;
        case DescriptionRole:
            wrapper.setValue(item->description());
            break;
        }
    }

    return wrapper;
}

quint64 DepartmentModel::departmentGuid(const qint32 &index) const
{
    quint64 guid = 0;

    if(index >= 0 && index < m_departments.size())
    {
        guid = m_departments.at(index)->guid();
    }

    return guid;
}

void DepartmentModel::departmentsReset(const QList<Department *> departments)
{
    beginResetModel();
    clearData();
    m_departments.clear();
    m_departments.append(departments);
    endResetModel();
    emit countChanged(m_departments.size());
}

void DepartmentModel::insertDepartment(Department *department)
{
    beginInsertRows(QModelIndex(), m_departments.size(), m_departments.size());
    m_departments.append(department);
    endInsertRows();
    emit countChanged(m_departments.size());
}

void DepartmentModel::deleteDepartment(const quint64 &guid, const qint32 &index)
{
    Q_UNUSED(guid)
    beginRemoveRows(QModelIndex(), index, index);
    Department *department = m_departments.at(index);
    m_departments.removeAt(index);
    department->deleteLater();
    department = nullptr;
    endRemoveRows();
    emit countChanged(m_departments.size());
}

QHash<int, QByteArray> DepartmentModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[GuidRole] = QByteArrayLiteral("guid");
    roles[NameRole] = QByteArrayLiteral("name");
    roles[DescriptionRole] = QByteArrayLiteral("description");
    return roles;
}

void DepartmentModel::clearData()
{
    if(!m_departments.isEmpty())
    {
        for (int i = 0; i < m_departments.size(); ++i) {
            Department* member;
            member = m_departments.at(i);
            member->deleteLater();
            member = nullptr;
        }
        m_departments.clear();
    }
}
