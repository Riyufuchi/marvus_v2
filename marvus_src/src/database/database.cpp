//==============================================================================
// Author     : riyufuchi
// Created on : 2026-04-28
// Last edit  : 2026-04-28
// Copyright  : Copyright (c) 2026, riyufuchi
//==============================================================================
#include "database.h"


marvus::Database::Database(const QString& DB_NAME) : database(QSqlDatabase::addDatabase("QSQLITE")), m_last_error("")
{
	database.setDatabaseName(DB_NAME);
	database.open();
}

bool marvus::Database::initialize_database()
{
	QSqlQuery query(database);
	std::vector<QString> queries;
	queries.emplace_back("PRAGMA foreign_keys = ON");
	queries.emplace_back(marvus_sql::create_categories_table);
	queries.emplace_back(marvus_sql::create_entities_table);
	queries.emplace_back(marvus_sql::create_money_flow_table);

	for (const auto q : queries)
	{
		if (!query.exec(q))
		{
			m_last_error = query.lastError().text();
			return true;
		}
	}

	return false;
}

int marvus::Database::insert_category(const EnumEntity& category)
{
	QSqlQuery query(database);

	query.prepare(marvus_sql::insert_category);

	query.bindValue(":name", category.get_name());

	if (!query.exec())
	{
		m_last_error = query.lastError().text();
		return 0;
	}

	return query.lastInsertId().toInt();
}

int marvus::Database::insert_entity(const EnumEntity& entity)
{
	QSqlQuery query(database);

	query.prepare(marvus_sql::insert_entity);

	query.bindValue(":name", entity.get_name());

	if (!query.exec())
	{
		m_last_error = query.lastError().text();
		return 0;
	}

	return query.lastInsertId().toInt();
}

int marvus::Database::insert_money_flow(const MoneyFlow& money_flow)
{
	QSqlQuery query(database);

	query.prepare(marvus_sql::insert_money_flow);

	query.bindValue(":entity_id", money_flow.get_entity_id());
	query.bindValue(":category_id", money_flow.get_category_id());
	query.bindValue(":amount", money_flow.get_value()); // -399 Kč
	query.bindValue(":date", money_flow.get_date());

	if (!query.exec())
	{
		m_last_error = query.lastError().text();
		return 0;
	}

	return query.lastInsertId().toInt();
}

const QString& marvus::Database::get_last_error() const
{
	return m_last_error;
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

	if (!query.exec())
	{
		m_last_error = query.lastError().text();
		return true;
	}

	return false;
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
