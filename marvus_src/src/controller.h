//==============================================================================
// Author     : riyufuchi
// Created on : 2026-04-28
// Last edit  : 2026-10-05
// Copyright  : Copyright (c) 2026, riyufuchi
//==============================================================================
#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QFileDialog>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QStandardItemModel>
#include <QMessageBox>
// Nocovka
#include "io/io_tools.hpp"
#include "database/database.h"

namespace marvus
{

class Controller
{
private:
	Database db_connection;
public:
	Controller();
	/*
	 * Returns false on success
	 */
	bool create_new_database(QWidget* parent);
	/*
	 * Returns false on success
	 */
	bool open_database(QWidget* parent);
	void import_from_json_to_db(QWidget* parent);
	QSqlQueryModel* select(QObject* parent);
	QSqlQueryModel* select_entities(QObject* parent);
	QSqlQueryModel* select_categories(QObject* parent);
	QSqlQueryModel* select_money_flows(QObject* parent);
	Database& expose_db();
};

}

#endif // CONTROLLER_H
