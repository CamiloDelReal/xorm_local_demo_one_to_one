#ifndef DEPARTMENTMODEL_HPP
#define DEPARTMENTMODEL_HPP

#include <QObject>
#include <QAbstractListModel>

#include "department.hpp"

class DepartmentModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(quint32 count READ rowCount NOTIFY countChanged)

public:
    enum DepartmentModelRoles
    {
        GuidRole = Qt::UserRole + 1,
        NameRole,
        DescriptionRole
    };

    explicit DepartmentModel(QObject *parent = nullptr);
    ~DepartmentModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    Q_INVOKABLE quint64 departmentGuid(const qint32 &index) const;

public slots:
    void departmentsReset(const QList<Department*> departments);
    void insertDepartment(Department *department);
    void deleteDepartment(const quint64 &guid, const qint32 &index);

signals:
    void countChanged(qint32 count);

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    QList<Department*> m_departments;

    void clearData();
};

#endif // DEPARTMENTMODEL_HPP
