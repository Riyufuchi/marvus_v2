//==============================================================================
// Author     : riyufuchi
// Created on : 2026-09-30
// Last edit  : 2026-09-30
// Copyright  : Copyright (c) 2026, riyufuchi
//==============================================================================
#ifndef MARVUS_SQL_HPP
#define MARVUS_SQL_HPP

namespace marvus_sql
{

constexpr auto create_categories_table = R"(
CREATE TABLE IF NOT EXISTS CATEGORIES (
		category_id INTEGER PRIMARY KEY,
		category_name TEXT NOT NULL UNIQUE
	)
)";

constexpr auto create_entities_table = R"(
CREATE TABLE IF NOT EXISTS ENTITIES (
		entity_id INTEGER PRIMARY KEY,
		entity_name TEXT NOT NULL UNIQUE
	)
)";

constexpr auto create_money_flow_table = R"(
CREATE TABLE IF NOT EXISTS MONEY_FLOWS
(
flow_id INTEGER PRIMARY KEY,
entity_id INTEGER NOT NULL,
category_id INTEGER NOT NULL,
amount INTEGER NOT NULL,
date TEXT NOT NULL,

FOREIGN KEY (entity_id) REFERENCES ENTITIES(entity_id),
FOREIGN KEY (category_id) REFERENCES CATEGORIES(category_id)
)
)";

constexpr auto insert_entity = R"(
INSERT INTO ENTITIES (name)
VALUES (:name)
)";

constexpr auto insert_category = R"(
INSERT INTO CATEGORIES (name)
VALUES (:name)
)";

constexpr auto insert_money_flow = R"(
INSERT INTO MONEY_FLOWS  (entity_id, category_id, amount, date)
VALUES (:entity_id, :category_id, :amount, :date)
)";

}

#endif // MARVUS_SQL_HPP
