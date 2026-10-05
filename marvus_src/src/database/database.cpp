//==============================================================================
// Author     : riyufuchi
// Created on : 2026-04-28
// Last edit  : 2026-10-05
// Copyright  : Copyright (c) 2026, riyufuchi
//==============================================================================
#include "database.h"


marvus::Database::Database() : database(QSqlDatabase::addDatabase("QSQLITE")), m_last_error("Unknown error")
{
}

bool marvus::Database::open_database(const QString& DB_NAME)
{
	database.setDatabaseName(DB_NAME);
	return database.open();
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

	query.bindValue(":category_name", category.get_name());

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

	query.bindValue(":entity_name", entity.get_name());

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

QSqlQueryModel* marvus::Database::select(QObject* parent, const QString& select_sql)
{
	QSqlQueryModel* model = new QSqlQueryModel(parent);

	model->setQuery(select_sql, database);

	if (model->lastError().isValid())
	{
		m_last_error = model->lastError().text();
		return 0;
	}

	return model;
}

QSqlQueryModel* marvus::Database::get_current_month_expenses(QObject* parent)
{
	return select(parent, marvus_sql::select_current_month_expenses);
}

QSqlQueryModel* marvus::Database::get_entities(QObject* parent)
{
	return select(parent, marvus_sql::select_all_entities);
}

QSqlQueryModel* marvus::Database::get_categories(QObject* parent)
{
	return select(parent, marvus_sql::select_all_categories);
}

QSqlQueryModel* marvus::Database::get_money_flows(QObject* parent)
{
	return select(parent, marvus_sql::select_all_money_flows);
}

bool marvus::Database::is_open() const
{
	return database.isOpen();
}
