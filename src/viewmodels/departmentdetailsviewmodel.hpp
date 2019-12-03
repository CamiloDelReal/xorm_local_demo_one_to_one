#ifndef DepartmentDetailsViewModel_HPP
#define DepartmentDetailsViewModel_HPP

#include <QObject>

#include "department.hpp"
#include "xdao.hpp"


class DepartmentDetailsViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isWorking READ isWorking NOTIFY isWorkingChanged)
    Q_PROPERTY(Department* currentDepartment READ currentDepartment NOTIFY currentDepartmentChanged)

public:
    explicit DepartmentDetailsViewModel(QObject *parent = nullptr);
    ~DepartmentDetailsViewModel();

    bool isWorking() const;
    Department* currentDepartment() const;

    Q_INVOKABLE void readDepartment(const quint64 &guid);

signals:
    void isWorkingChanged(const bool &isWorking);
    void currentDepartmentChanged(Department* currentDepartment);

private:
    bool m_isWorking;
    QSqlDatabase m_appDatabase;
    XDao<Department> m_departmentDao;
    Department* m_currentDepartment;

private slots:
    void setIsWorking(const bool &isWorking);
};

#endif // DepartmentDetailsViewModel_HPP
