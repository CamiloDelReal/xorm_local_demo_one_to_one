#ifndef MEMBERDETAILSVIEWMODEL_HPP
#define MEMBERDETAILSVIEWMODEL_HPP

#include <QObject>

#include "member.hpp"
#include "xdao.hpp"


class MemberDetailsViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isWorking READ isWorking NOTIFY isWorkingChanged)
    Q_PROPERTY(Member* currentMember READ currentMember NOTIFY currentMemberChanged)

public:
    explicit MemberDetailsViewModel(QObject *parent = nullptr);
    ~MemberDetailsViewModel();

    bool isWorking() const;
    Member* currentMember() const;

    Q_INVOKABLE void readMember(const quint64 &guid);

signals:
    void isWorkingChanged(const bool &isWorking);
    void currentMemberChanged(Member* currentMember);

private:
    bool m_isWorking;
    QSqlDatabase m_appDatabase;
    XDao<Member> m_memberDao;
    Member* m_currentMember;

private slots:
    void setIsWorking(const bool &isWorking);
};

#endif // MEMBERDETAILSVIEWMODEL_HPP
