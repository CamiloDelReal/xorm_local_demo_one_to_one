# XOrm persistance with One to One relationship
One to One relationship using XOrm library

## This project will not be maintenance anymore
I am not working for Qt since a while and updates started to become hard after so much changes in Qt 6

### Features
- Members
  * CRUD operations
- Departments
  * CRUD operations
- MVVM architecture

### Entity relationship diagram
<p float="left">
<img src="https://github.com/CamiloDelReal/xorm_local_demo_one_to_one/blob/develop/design/exported_diagrams/persistence.jpg" width="80%" height="80%" />
</p>

### Entities definition

	class Department : public QObject, public XTableModel<Department>
    {
        Q_OBJECT

        Q_PROPERTY(quint64 guid READ guid WRITE setGuid NOTIFY guidChanged)
        Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
        Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged)

        X_TABLE_NAME("departments")
        X_TABLE_FIELDS(X_FIELD(guid, X_PRIMARY_KEY),
                    X_FIELD(name),
                    X_FIELD(description))

    public:
        explicit Department(QObject *parent = nullptr);
        Department(const quint64 &guid, const QString &name, const QString &description, QObject *parent = nullptr);
        Department(const QString &name, const QString &description, QObject *parent = nullptr);
        Department(const Department &other);

        Department& operator=(const Department &other);

        quint64 guid() const;
        QString name() const;
        QString description() const;

    public slots:
        void setGuid(const quint64 &guid);
        void setName(const QString &name);
        void setDescription(const QString &description);

    signals:
        void guidChanged(const quint64 &guid);
        void nameChanged(const QString &name);
        void descriptionChanged(const QString &description);

    private:
        quint64 m_guid;
        QString m_name;
        QString m_description;
    };

    class Member : public QObject, public XTableModel<Member>
    {
        Q_OBJECT

        Q_PROPERTY(quint64 guid READ guid WRITE setGuid NOTIFY guidChanged)
        Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
        Q_PROPERTY(QString job READ job WRITE setJob NOTIFY jobChanged)
        Q_PROPERTY(quint64 departmentId READ departmentId WRITE setDepartmentId NOTIFY departmentIdChanged)

        Q_PROPERTY(Department* department READ department WRITE setDepartment NOTIFY departmentChanged)

        X_TABLE_NAME("members")
        X_TABLE_FIELDS(X_FIELD(guid, X_PRIMARY_KEY),
                    X_FIELD(name),
                    X_FIELD(job),
                    X_FIELD(departmentId, "department_id", X_FOREIGN_KEY(Department, X_CASCADE, X_CASCADE)))

        X_FOREIGN_OBJECTS(X_FOREIGN_OBJECT(Department, guid, departmentId, department))

    public:
        explicit Member(QObject *parent = nullptr);
        Member(const quint64 &guid, const QString &name, const QString &job, const quint64 &departmentId,
            QObject *parent = nullptr);
        Member(const QString &name, const QString &job, const quint64 &departmentId, QObject *parent = nullptr);
        Member(const Member &other);

        ~Member();

        Member& operator=(const Member &other);

        quint64 guid() const;
        QString name() const;
        QString job() const;    
        quint64 departmentId() const;

        Department* department() const;

    public slots:
        void setGuid(const quint64 &guid);
        void setName(const QString &name);
        void setJob(const QString &job);
        void setDepartmentId(const quint64 &departmentId);

        void setDepartment(Department* department);

    signals:
        void guidChanged(const quint64 &guid);
        void nameChanged(const QString &name);
        void jobChanged(const QString &job);
        void departmentIdChanged(const quint64 &departmentId);

        void departmentChanged(Department* department);

    private:
        quint64 m_guid;
        QString m_name;
        QString m_job;
        quint64 m_departmentId;

        Department* m_department;

        void clearDepartment();
    };
	
### Screenshots
<p float="left">
<img src="https://github.com/CamiloDelReal/xorm_local_demo_one_to_one/blob/develop/screenshots/sshot-1.png" width="30%" height="30%" />
<img src="https://github.com/CamiloDelReal/xorm_local_demo_one_to_one/blob/develop/screenshots/sshot-2.png" width="30%" height="30%" />
<img src="https://github.com/CamiloDelReal/xorm_local_demo_one_to_one/blob/develop/screenshots/sshot-3.png" width="30%" height="30%" />
<img src="https://github.com/CamiloDelReal/xorm_local_demo_one_to_one/blob/develop/screenshots/sshot-4.png" width="30%" height="30%" />
<img src="https://github.com/CamiloDelReal/xorm_local_demo_one_to_one/blob/develop/screenshots/sshot-5.png" width="30%" height="30%" />
<img src="https://github.com/CamiloDelReal/xorm_local_demo_one_to_one/blob/develop/screenshots/sshot-6.png" width="30%" height="30%" />
</p>