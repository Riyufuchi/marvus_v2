//==============================================================================
// Author     : riyufuchi
// Created on : 2026-04-28
// Last edit  : 2026-04-28
// Copyright  : Copyright (c) 2026, riyufuchi
//==============================================================================
#include "controller.h"


marvus::Controller::Controller()
{
	db_connection.is_open();
	db_connection.initialize_database();

	labels.emplace_back("Employee");
	labels.emplace_back("Job");
	labels.emplace_back("Message");
	labels.emplace_back("Latitude");
	labels.emplace_back("Longitude");

}

void marvus::Controller::import_from_json_to_db(QWidget* parent)
{
	QJsonOptional doc_opt = import_json(parent);

	if (!doc_opt && !((*doc_opt).isObject()))
		return;

	QJsonObject obj = doc_opt.value().object();

	db_connection.insert_from_json(obj);
}

QSqlTableModel* marvus::Controller::obtain_model(const QString& TABLE_NAME, QObject* parent)
{
	return db_connection.obtain_model(TABLE_NAME, parent, labels);
}
