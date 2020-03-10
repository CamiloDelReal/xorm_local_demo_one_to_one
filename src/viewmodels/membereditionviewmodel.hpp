#ifndef MEMBEREDITIONVIEWMODEL_HPP
#define MEMBEREDITIONVIEWMODEL_HPP

#include <QObject>

#include "xdao.hpp"
#include "member.hpp"

class MemberEditionViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isWorking READ isWorking NOTIFY isWorkingChanged)

public:
    explicit MemberEditionViewModel(QObject *parent = nullptr);

    bool isWorking() const;

    Q_INVOKABLE void createMember(const QString &name, const QString &job, const quint64 &departmentId);

signals:
    void isWorkingChanged(const bool &isWorking);

    void memberCreated(Member *member);

private:
    bool m_isWorking;

    QSqlDatabase m_appDatabase;
    XDao<Member> m_memberDao;

private slots:
    void setIsWorking(const bool &isWorking);
};

#endif // MEMBEREDITIONVIEWMODEL_HPP
