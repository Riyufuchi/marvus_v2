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

	if (db_connection.initialize_database())
	{
		QMessageBox::critical(nullptr, "Chyba databáze", db_connection.get_last_error());
	}

	labels.emplace_back("1");
	labels.emplace_back("2");
	labels.emplace_back("3");
	labels.emplace_back("4");
	labels.emplace_back("5");

}

void marvus::Controller::import_from_json_to_db(QWidget* parent)
{
	QJsonOptional doc_opt = import_json(parent);

	if (!doc_opt && !((*doc_opt).isObject()))
		return;

	QJsonObject obj = doc_opt.value().object();

	if (db_connection.insert_from_json(obj))
	{
		QMessageBox::critical(nullptr, "Chyba databáze", db_connection.get_last_error());
	}
}

QSqlTableModel* marvus::Controller::obtain_model(const QString& TABLE_NAME, QObject* parent)
{
	return db_connection.obtain_model(TABLE_NAME, parent, labels);
}
