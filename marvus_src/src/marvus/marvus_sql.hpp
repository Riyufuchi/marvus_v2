//==============================================================================
// Author     : riyufuchi
// Created on : 2026-09-30
// Last edit  : 2026-10-05
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
INSERT INTO ENTITIES (entity_name)
VALUES (:entity_name)
)";

constexpr auto insert_category = R"(
INSERT INTO CATEGORIES (category_name)
VALUES (:category_name)
)";

constexpr auto insert_money_flow = R"(
INSERT INTO MONEY_FLOWS  (entity_id, category_id, amount, date)
VALUES (:entity_id, :category_id, :amount, :date)
)";

constexpr auto select_all_entities = R"(
SELECT * FROM ENTITIES
)";

constexpr auto select_all_categories = R"(
SELECT * FROM CATEGORIES
)";

constexpr auto select_current_month_expenses = R"(
SELECT
CATEGORIES.category_name AS "Kategorie",
SUM(MONEY_FLOWS.amount) / 100.00 AS "Celkem"
FROM MONEY_FLOWS
JOIN CATEGORIES
	ON MONEY_FLOWS.category_id = CATEGORIES.category_id
WHERE MONEY_FLOWS.date >= date('now', 'start of month')
AND MONEY_FLOWS.date < date('now', 'start of month', '+1 month')
GROUP BY CATEGORIES.category_id
ORDER BY "Kategorie"
)";

constexpr auto select_all_money_flows = R"(
SELECT
ENTITIES.entity_name AS "Entity",
CATEGORIES.category_name AS "Kategorie",
MONEY_FLOWS.amount / 100.00 AS "Částka",
MONEY_FLOWS.date AS "Datum"
FROM MONEY_FLOWS
JOIN CATEGORIES
	ON MONEY_FLOWS.category_id = CATEGORIES.category_id
JOIN ENTITIES
	ON MONEY_FLOWS.entity_id = ENTITIES.entity_id
)";

}

#endif // MARVUS_SQL_HPP
