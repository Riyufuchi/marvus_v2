//==============================================================================
// Author     : riyufuchi
// Created on : 2026-04-28
// Last edit  : 2026-04-28
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
	bool insert_from_json(const QJsonObject& json);
	QSqlTableModel* obtain_model(const QString& TABLE_NAME, QObject* parent, const std::vector<QString>& header_labels);
	// IS functions
	bool is_open() const;
};

}

#endif // DATABASE_H
