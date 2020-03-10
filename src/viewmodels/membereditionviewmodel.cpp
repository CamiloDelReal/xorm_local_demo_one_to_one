#include <QtConcurrent/QtConcurrent>

#include "membereditionviewmodel.hpp"
#include "databasemanager.hpp"

MemberEditionViewModel::MemberEditionViewModel(QObject *parent)
    : QObject(parent)
{
    m_isWorking = false;
    m_appDatabase = QSqlDatabase::database(DATABASE_CONNECTION_NAME);
}

bool MemberEditionViewModel::isWorking() const
{
    return m_isWorking;
}

void MemberEditionViewModel::createMember(const QString &name, const QString &job, const quint64 &departmentId)
{
    setIsWorking(true);
    MemberEditionViewModel *viewModel = this;
    QFuture<void> future = QtConcurrent::run([viewModel, name, job, departmentId]() {
        Member *member = new Member(name, job, departmentId);
        viewModel->m_memberDao.setDatabase(viewModel->m_appDatabase);
        viewModel->m_memberDao.createOne(member);
        emit viewModel->memberCreated(member);
        viewModel->setIsWorking(false);
    });
}

void MemberEditionViewModel::setIsWorking(const bool &isWorking)
{
    if(m_isWorking != isWorking)
    {
        m_isWorking = isWorking;
        emit isWorkingChanged(m_isWorking);
    }
}
