#include <QtConcurrent/QtConcurrent>

#include "memberdetailsviewmodel.hpp"
#include "databasemanager.hpp"


MemberDetailsViewModel::MemberDetailsViewModel(QObject *parent)
    : QObject (parent)
{
    m_isWorking = false;
    m_currentMember = nullptr;
    m_appDatabase = QSqlDatabase::database(DATABASE_CONNECTION_NAME);
}

MemberDetailsViewModel::~MemberDetailsViewModel()
{
    if(m_currentMember != nullptr)
    {
        m_currentMember->deleteLater();
    }
}

bool MemberDetailsViewModel::isWorking() const
{
    return m_isWorking;
}

Member* MemberDetailsViewModel::currentMember() const
{
    return m_currentMember;
}

void MemberDetailsViewModel::readMember(const quint64 &guid)
{
    setIsWorking(true);
    MemberDetailsViewModel *viewModel = this;
    QFuture<void> future = QtConcurrent::run([viewModel, guid]() {
        viewModel->m_memberDao.setDatabase(viewModel->m_appDatabase);
        if (viewModel->m_currentMember != nullptr)
        {
            Member *oldMember = viewModel->m_currentMember;
            oldMember->deleteLater();
            oldMember = nullptr;
            viewModel->m_currentMember = new Member();
        }
        XMatcher matcher;
        matcher.insert("guid", guid);
        viewModel->m_memberDao.findOneBy(viewModel->m_currentMember, matcher);
        viewModel->m_memberDao.resolveForeigns(viewModel->m_currentMember);
        viewModel->m_currentMember->moveToThread(viewModel->thread());
        if(viewModel->m_currentMember->department() != nullptr)
        {
            viewModel->m_currentMember->department()->moveToThread(viewModel->thread());
        }
        emit viewModel->currentMemberChanged(viewModel->m_currentMember);
        viewModel->setIsWorking(false);
    });
}

void MemberDetailsViewModel::setIsWorking(const bool &isWorking)
{
    if(m_isWorking != isWorking)
    {
        m_isWorking = isWorking;
        emit isWorkingChanged(m_isWorking);
    }
}
