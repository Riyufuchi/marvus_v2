//==============================================================================
// Author     : riyufuchi
// Created on : 2026-04-28
// Last edit  : 2026-04-28
// Copyright  : Copyright (c) 2026, riyufuchi
//==============================================================================
#include "database.h"


marvus::Database::Database(const QString& DB_NAME) : database(QSqlDatabase::addDatabase("QSQLITE"))
{
	database.setDatabaseName(DB_NAME);
	database.open();
}

bool marvus::Database::initialize_database()
{
	QSqlQuery query(database);
	return query.exec(R"(
		CREATE TABLE IF NOT EXISTS ITEMS (
			id INTEGER PRIMARY KEY AUTOINCREMENT,
			emp_id TEXT,
			job_id TEXT,
			msg TEXT,
			gps_lat REAL,
			gps_lon REAL
		)
	)");
}

bool marvus::Database::insert_from_json(const QJsonObject& json)
{
	QSqlQuery query(database);
	query.prepare(R"(
		INSERT INTO ITEMS (emp_id, job_id, msg, gps_lat, gps_lon)
		VALUES (?, ?, ?, ?, ?)
	)");

	query.addBindValue(json["emp-id"].toString());
	query.addBindValue(json["job-id"].toString());
	query.addBindValue(json["msg"].toString());
	query.addBindValue(json["gps-lat"].toDouble());
	query.addBindValue(json["gps-lon"].toDouble());

	return query.exec();
}

QSqlTableModel* marvus::Database::obtain_model(const QString& TABLE_NAME, QObject* parent, const std::vector<QString>& header_labels)
{
	QSqlTableModel* model = new QSqlTableModel(parent, database);
	model->setTable(TABLE_NAME);
	model->setEditStrategy(QSqlTableModel::OnManualSubmit);
	model->select();

	int x = 1;
	for (const auto& item : header_labels)
	{
		model->setHeaderData(x, Qt::Horizontal, item);
		x++;
	}


	return model;
}

bool marvus::Database::is_open() const
{
	return database.isOpen();
}
