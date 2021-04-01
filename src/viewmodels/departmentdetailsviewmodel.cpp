#include <QtConcurrent/QtConcurrent>

#include "departmentdetailsviewmodel.hpp"
#include "databasemanager.hpp"


DepartmentDetailsViewModel::DepartmentDetailsViewModel(QObject *parent)
    : QObject (parent)
{
    m_isWorking = false;
    m_currentDepartment = nullptr;
    m_appDatabase = QSqlDatabase::database(DATABASE_CONNECTION_NAME);
}

DepartmentDetailsViewModel::~DepartmentDetailsViewModel()
{
    if(m_currentDepartment != nullptr)
    {
        m_currentDepartment->deleteLater();
    }
}

bool DepartmentDetailsViewModel::isWorking() const
{
    return m_isWorking;
}

Department* DepartmentDetailsViewModel::currentDepartment() const
{
    return m_currentDepartment;
}

void DepartmentDetailsViewModel::readDepartment(const quint64 &guid)
{
    setIsWorking(true);
    DepartmentDetailsViewModel *viewModel = this;
    QFuture<void> future = QtConcurrent::run([viewModel, guid]() {
        viewModel->m_departmentDao.setDatabase(viewModel->m_appDatabase);
        if (viewModel->m_currentDepartment != nullptr)
        {
            Department *oldDepartment = viewModel->m_currentDepartment;
            oldDepartment->deleteLater();
            oldDepartment = nullptr;
            viewModel->m_currentDepartment = new Department();
        }
        XMatcher matcher;
        matcher.insert("guid", guid);
        viewModel->m_departmentDao.findOneBy(viewModel->m_currentDepartment, matcher);
        viewModel->m_currentDepartment->moveToThread(viewModel->thread());
        emit viewModel->currentDepartmentChanged(viewModel->m_currentDepartment);
        viewModel->setIsWorking(false);
    });
}

void DepartmentDetailsViewModel::setIsWorking(const bool &isWorking)
{
    if(m_isWorking != isWorking)
    {
        m_isWorking = isWorking;
        emit isWorkingChanged(m_isWorking);
    }
}
