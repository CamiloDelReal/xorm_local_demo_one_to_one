#ifndef DEPARTMENTLISTINGVIEWMODEL_HPP
#define DEPARTMENTLISTINGVIEWMODEL_HPP

#include <QObject>

#include "xdao.hpp"
#include "departmentmodel.hpp"

class DepartmentListingViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isWorking READ isWorking NOTIFY isWorkingChanged)
    Q_PROPERTY(QObject* departmentModel READ departmentModel NOTIFY departmentModelChanged)

public:
    explicit DepartmentListingViewModel(QObject *parent = nullptr);

    bool isWorking() const;
    QObject* departmentModel();

    Q_INVOKABLE void readDepartments();
    Q_INVOKABLE void deleteDepartment(const quint64 &guid, const qint32 &index);

signals:
    void isWorkingChanged(const bool &isWorking);
    void departmentModelChanged(QObject* departmentModel);

    void departmentsReset(const QList<Department*> departments);
    void departmentDeleted(const quint64 &guid, const qint32 &index);

private:
    bool m_isWorking;
    DepartmentModel m_departmentModel;

    QSqlDatabase m_appDatabase;
    XDao<Department> m_departmentDao;

private slots:
    void setIsWorking(const bool &isWorking);
};

#endif // DEPARTMENTLISTINGVIEWMODEL_HPP
