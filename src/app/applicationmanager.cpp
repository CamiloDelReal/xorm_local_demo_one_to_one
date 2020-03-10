#include <QtQml>
#include <QStandardPaths>

#include "applicationmanager.hpp"
#include "pathutils.hpp"
#include "xdatabase.hpp"

#include "memberdetailsviewmodel.hpp"
#include "membereditionviewmodel.hpp"
#include "memberlistingviewmodel.hpp"
#include "departmentdetailsviewmodel.hpp"
#include "departmenteditionviewmodel.hpp"
#include "departmentlistingviewmodel.hpp"


ApplicationManager::ApplicationManager(QObject *parent)
    : MobileManager(parent)
{
}

void ApplicationManager::addContextProperty(QQmlEngine *engine, QQmlContext *context)
{
    m_engine = engine;

    //Register singletons
    qmlRegisterSingletonType(QUrl(QLatin1String("qrc:/qml/XMaterialControls.qml")), "XApps.XMaterialControls", 1, 0, "XMaterialControls");

    //Link C++ objects with QML
    context->setContextProperty("ApplicationManagerObj", this);
    context->setContextProperty("ApplicationSettingsObj", &m_applicationSettings);

    //Register data types
    qRegisterMetaType<Member>("Member");
    qRegisterMetaType<Member*>("Member*");
    qRegisterMetaType<QList<Member*>>("QList<Member*>");
    qRegisterMetaType<Department>("Department");
    qRegisterMetaType<Department*>("Department*");
    qRegisterMetaType<QList<Department*>>("QList<Department*>");
    qmlRegisterType<MemberDetailsViewModel>("XApps.XOrmDemoOneToOne", 1, 0, "MemberDetailsViewModel");
    qmlRegisterType<MemberEditionViewModel>("XApps.XOrmDemoOneToOne", 1, 0, "MemberEditionViewModel");
    qmlRegisterType<MemberListingViewModel>("XApps.XOrmDemoOneToOne", 1, 0, "MemberListingViewModel");
    qmlRegisterType<DepartmentDetailsViewModel>("XApps.XOrmDemoOneToOne", 1, 0, "DepartmentDetailsViewModel");
    qmlRegisterType<DepartmentEditionViewModel>("XApps.XOrmDemoOneToOne", 1, 0, "DepartmentEditionViewModel");
    qmlRegisterType<DepartmentListingViewModel>("XApps.XOrmDemoOneToOne", 1, 0, "DepartmentListingViewModel");
}

void ApplicationManager::initialize()
{
    m_databaseManager.initialize();
}

void ApplicationManager::onAboutToQuit()
{
    m_applicationSettings.saveSettings();
}

void ApplicationManager::onApplicationStateChanged(Qt::ApplicationState applicationState)
{
    if(applicationState == Qt::ApplicationState::ApplicationSuspended)
        onAboutToQuit();
}
