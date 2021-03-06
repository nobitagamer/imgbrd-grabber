#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include "sql-worker.h"
#include "functions.h"


SqlWorker::SqlWorker(QString driver, QString host, QString user, QString password, QString database, QObject *parent)
	: QThread(parent), m_driver(driver), m_host(host), m_user(user), m_password(password), m_database(database)
{
	m_enabled = (m_driver == "QSQLITE" && !m_database.isEmpty())
			  || (!m_host.isEmpty() && !m_user.isEmpty() && !m_database.isEmpty());

	m_started = false;
}

bool SqlWorker::connect()
{
	if (!m_enabled || m_started)
		return true;

	m_started = true;

	QSqlDatabase db = QSqlDatabase::addDatabase(m_driver);
	db.setHostName(m_host);
	db.setDatabaseName(m_database);
	db.setUserName(m_user);
	db.setPassword(m_password);

	if (!db.open())
	{
		log(QString("Error initializing commands: %1").arg(db.lastError().text()));
		return false;
	}

	return true;
}

bool SqlWorker::execute(QString sql)
{
	if (!m_enabled || !connect())
		return false;

	log(QString("SQL execution of \"%1\"").arg(sql));
	logCommandSql(sql);

	QSqlQuery query;
	return query.exec(sql);
}
