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
#include <QSqlTableModel>
#include <QJsonObject>

namespace marvus
{

class Database
{
private:
	QSqlDatabase database;
public:
	Database(const QString& DB_NAME = "nocovka_erp.db");
	bool initialize_database();
	bool insert_from_json(const QJsonObject& json);
	QSqlTableModel* obtain_model(const QString& TABLE_NAME, QObject* parent, const std::vector<QString>& header_labels);
	// IS functions
	bool is_open() const;
};

}

#endif // DATABASE_H
