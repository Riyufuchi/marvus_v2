//==============================================================================
// Author     : riyufuchi
// Created on : 2026-04-28
// Last edit  : 2026-10-04
// Copyright  : Copyright (c) 2026, riyufuchi
//==============================================================================
#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlTableModel>
#include <QJsonObject>
// Marvus
#include "../marvus/marvus_sql.hpp"
#include "enum_entity.h"
#include "money_flow.h"

namespace marvus
{

class Database
{
private:
	QSqlDatabase database;
	QString m_last_error;
public:
	Database(const QString& DB_NAME = "marvus.db");
	const QString& get_last_error() const;
	bool initialize_database();
	int insert_category(const EnumEntity& category);
	int insert_entity(const EnumEntity& entity);
	int insert_money_flow(const MoneyFlow& money_flow);
	QSqlTableModel* obtain_model(const QString& TABLE_NAME, QObject* parent, const std::vector<QString>& header_labels);
	QSqlQueryModel* get_current_month_expenses(QObject* parent);
	// IS functions
	bool is_open() const;
};

}

#endif // DATABASE_H
