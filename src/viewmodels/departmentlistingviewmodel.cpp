#include <QtConcurrent/QtConcurrent>

#include "databasemanager.hpp"
#include "departmentlistingviewmodel.hpp"

DepartmentListingViewModel::DepartmentListingViewModel(QObject *parent)
    : QObject(parent)
{
    m_isWorking = false;
    m_appDatabase = QSqlDatabase::database(DATABASE_CONNECTION_NAME);
    connect(this, &DepartmentListingViewModel::departmentsReset, &m_departmentModel, &DepartmentModel::departmentsReset);
    connect(this, &DepartmentListingViewModel::departmentDeleted, &m_departmentModel, &DepartmentModel::deleteDepartment);
}

bool DepartmentListingViewModel::isWorking() const
{
    return m_isWorking;
}

QObject* DepartmentListingViewModel::departmentModel()
{
    return dynamic_cast<QObject*>(&m_departmentModel);
}

void DepartmentListingViewModel::readDepartments()
{
    setIsWorking(true);
    DepartmentListingViewModel *viewModel = this;
    QFuture<void> future = QtConcurrent::run([viewModel]() {
        viewModel->m_departmentDao.setDatabase(viewModel->m_appDatabase);
        QList<Department*> departments;
        viewModel->m_departmentDao.readAll(departments);
        emit viewModel->departmentsReset(departments);
        viewModel->setIsWorking(false);
    });
}

void DepartmentListingViewModel::deleteDepartment(const quint64 &guid, const qint32 &index)
{
    setIsWorking(true);
    DepartmentListingViewModel *viewModel = this;
    QFuture<void> future = QtConcurrent::run([viewModel, guid, index]() {
        viewModel->m_departmentDao.setDatabase(viewModel->m_appDatabase);
        QVariantMap map;
        map.insert("guid", guid);
        viewModel->m_departmentDao.deleteBy(map);
        emit viewModel->departmentDeleted(guid, index);
        viewModel->setIsWorking(false);
    });
}

void DepartmentListingViewModel::setIsWorking(const bool &isWorking)
{
    if (m_isWorking != isWorking)
    {
        m_isWorking = isWorking;
        emit isWorkingChanged(m_isWorking);
    }
}
