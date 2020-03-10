#ifndef DEPARTMENTEDITIONVIEWMODEL_HPP
#define DEPARTMENTEDITIONVIEWMODEL_HPP

#include <QObject>

#include "xdao.hpp"
#include "department.hpp"

class DepartmentEditionViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isWorking READ isWorking NOTIFY isWorkingChanged)

public:
    explicit DepartmentEditionViewModel(QObject *parent = nullptr);

    bool isWorking() const;

    Q_INVOKABLE void createDepartment(const QString &name, const QString &description);

signals:
    void isWorkingChanged(const bool &isWorking);

    void departmentCreated(Department *department);

private:
    bool m_isWorking;

    QSqlDatabase m_appDatabase;
    XDao<Department> m_departmentDao;

private slots:
    void setIsWorking(const bool &isWorking);
};

#endif // DEPARTMENTEDITIONVIEWMODEL_HPP
