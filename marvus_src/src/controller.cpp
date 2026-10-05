//==============================================================================
// Author     : riyufuchi
// Created on : 2026-04-28
// Last edit  : 2026-10-05
// Copyright  : Copyright (c) 2026, riyufuchi
//==============================================================================
#include "controller.h"


marvus::Controller::Controller()
{
}

bool marvus::Controller::create_new_database(QWidget* parent)
{
	if (db_connection.open_database() && db_connection.initialize_database())
	{
		QMessageBox::critical(parent, "Chyba databáze", db_connection.get_last_error());
		return true;
	}
	return false;
}

bool marvus::Controller::open_database(QWidget* parent)
{
	if (db_connection.open_database() && !db_connection.is_open())
	{
		QMessageBox::critical(parent, "Chyba databáze", db_connection.get_last_error());
		return true;
	}
	return false;
}

void marvus::Controller::import_from_json_to_db(QWidget* parent)
{
	QJsonOptional doc_opt = import_json(parent);

	if (!doc_opt && !((*doc_opt).isObject()))
		return;

	QJsonObject obj = doc_opt.value().object();

	/*if (db_connection.insert_from_json(obj))
	{
		QMessageBox::critical(nullptr, "Chyba databáze", db_connection.get_last_error());
	}*/
}

QSqlQueryModel* marvus::Controller::select(QObject* parent)
{
	return db_connection.get_current_month_expenses(parent);
}

QSqlQueryModel* marvus::Controller::select_entities(QObject* parent)
{
	return db_connection.get_entities(parent);
}

QSqlQueryModel* marvus::Controller::select_categories(QObject* parent)
{
	return db_connection.get_categories(parent);
}

QSqlQueryModel* marvus::Controller::select_money_flows(QObject* parent)
{
	return db_connection.get_money_flows(parent);
}

marvus::Database& marvus::Controller::expose_db()
{
	return db_connection;
}
