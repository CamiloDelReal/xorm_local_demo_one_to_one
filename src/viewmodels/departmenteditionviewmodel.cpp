#include <QtConcurrent/QtConcurrent>

#include "departmenteditionviewmodel.hpp"
#include "databasemanager.hpp"

DepartmentEditionViewModel::DepartmentEditionViewModel(QObject *parent)
    : QObject(parent)
{
    m_isWorking = false;
    m_appDatabase = QSqlDatabase::database(DATABASE_CONNECTION_NAME);
}

bool DepartmentEditionViewModel::isWorking() const
{
    return m_isWorking;
}

void DepartmentEditionViewModel::createDepartment(const QString &name, const QString &description)
{
    setIsWorking(true);
    DepartmentEditionViewModel *viewModel = this;
    QFuture<void> future = QtConcurrent::run([viewModel, name, description]() {
        Department *department = new Department(name, description);
        viewModel->m_departmentDao.setDatabase(viewModel->m_appDatabase);
        viewModel->m_departmentDao.createOne(department);
        emit viewModel->departmentCreated(department);
        viewModel->setIsWorking(false);
    });
}

void DepartmentEditionViewModel::setIsWorking(const bool &isWorking)
{
    if(m_isWorking != isWorking)
    {
        m_isWorking = isWorking;
        emit isWorkingChanged(m_isWorking);
    }
}
