//==============================================================================
// Author     : riyufuchi
// Created on : 2026-09-30
// Last edit  : 2026-10-11
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
date date NOT NULL,

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

constexpr auto select_current_month_expenses_by_entity = R"(
SELECT
ENTITIES.entity_name AS "Entity",
SUM(MONEY_FLOWS.amount) / 100.00 AS "Celkem"
FROM MONEY_FLOWS
JOIN ENTITIES
	ON MONEY_FLOWS.entity_id = ENTITIES.entity_id
WHERE MONEY_FLOWS.date >= date('now', 'start of month')
AND MONEY_FLOWS.date < date('now', 'start of month', '+1 month')
GROUP BY ENTITIES.entity_id
ORDER BY "Entity"
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

constexpr auto year_overview = R"(
WITH RECURSIVE Months(month) AS (
	SELECT 1
	UNION ALL
	SELECT month + 1
	FROM Months
	WHERE month < 12
),
Monthly AS (
	SELECT
		CAST(strftime('%m', MONEY_FLOWS.date) AS INTEGER) AS month,
		SUM(CASE
			WHEN amount > 0 THEN amount
			ELSE 0
		END) AS income,
		SUM(CASE
			WHEN amount < 0 THEN amount
			ELSE 0
		END) AS spendings
	FROM MONEY_FLOWS
	WHERE MONEY_FLOWS.date >= date('now', 'start of year')
	  AND MONEY_FLOWS.date < date('now', 'start of year', '+1 year')
	GROUP BY CAST(strftime('%m', MONEY_FLOWS.date) AS INTEGER)
),
Results AS (
	SELECT
		Months.month,
		COALESCE(Monthly.income, 0) AS income,
		COALESCE(Monthly.spendings, 0) AS spendings,
		COALESCE(Monthly.income, 0)
			+ COALESCE(Monthly.spendings, 0) AS outcome
	FROM Months
	LEFT JOIN Monthly ON Months.month = Monthly.month
),
Totals AS (
	SELECT
		month,
		income,
		spendings,
		outcome,
		SUM(outcome) OVER (
			ORDER BY month
			ROWS BETWEEN UNBOUNDED PRECEDING AND CURRENT ROW
		) AS total
	FROM Results
)
SELECT 'Income' AS Indicator,
	MAX(CASE WHEN month = 1 THEN income / 100.0 END) AS January,
	MAX(CASE WHEN month = 2 THEN income / 100.0 END) AS February,
	MAX(CASE WHEN month = 3 THEN income / 100.0 END) AS March,
	MAX(CASE WHEN month = 4 THEN income / 100.0 END) AS April,
	MAX(CASE WHEN month = 5 THEN income / 100.0 END) AS May,
	MAX(CASE WHEN month = 6 THEN income / 100.0 END) AS June,
	MAX(CASE WHEN month = 7 THEN income / 100.0 END) AS July,
	MAX(CASE WHEN month = 8 THEN income / 100.0 END) AS August,
	MAX(CASE WHEN month = 9 THEN income / 100.0 END) AS September,
	MAX(CASE WHEN month = 10 THEN income / 100.0 END) AS October,
	MAX(CASE WHEN month = 11 THEN income / 100.0 END) AS November,
	MAX(CASE WHEN month = 12 THEN income / 100.0 END) AS December
FROM Totals

UNION ALL

SELECT 'Spendings',
	MAX(CASE WHEN month = 1 THEN spendings / 100.0 END),
	MAX(CASE WHEN month = 2 THEN spendings / 100.0 END),
	MAX(CASE WHEN month = 3 THEN spendings / 100.0 END),
	MAX(CASE WHEN month = 4 THEN spendings / 100.0 END),
	MAX(CASE WHEN month = 5 THEN spendings / 100.0 END),
	MAX(CASE WHEN month = 6 THEN spendings / 100.0 END),
	MAX(CASE WHEN month = 7 THEN spendings / 100.0 END),
	MAX(CASE WHEN month = 8 THEN spendings / 100.0 END),
	MAX(CASE WHEN month = 9 THEN spendings / 100.0 END),
	MAX(CASE WHEN month = 10 THEN spendings / 100.0 END),
	MAX(CASE WHEN month = 11 THEN spendings / 100.0 END),
	MAX(CASE WHEN month = 12 THEN spendings / 100.0 END)
FROM Totals

UNION ALL

SELECT 'Outcome',
	MAX(CASE WHEN month = 1 THEN outcome / 100.0 END),
	MAX(CASE WHEN month = 2 THEN outcome / 100.0 END),
	MAX(CASE WHEN month = 3 THEN outcome / 100.0 END),
	MAX(CASE WHEN month = 4 THEN outcome / 100.0 END),
	MAX(CASE WHEN month = 5 THEN outcome / 100.0 END),
	MAX(CASE WHEN month = 6 THEN outcome / 100.0 END),
	MAX(CASE WHEN month = 7 THEN outcome / 100.0 END),
	MAX(CASE WHEN month = 8 THEN outcome / 100.0 END),
	MAX(CASE WHEN month = 9 THEN outcome / 100.0 END),
	MAX(CASE WHEN month = 10 THEN outcome / 100.0 END),
	MAX(CASE WHEN month = 11 THEN outcome / 100.0 END),
	MAX(CASE WHEN month = 12 THEN outcome / 100.0 END)
FROM Totals

UNION ALL

SELECT 'Total',
	MAX(CASE WHEN month = 1 THEN total / 100.0 END),
	MAX(CASE WHEN month = 2 THEN total / 100.0 END),
	MAX(CASE WHEN month = 3 THEN total / 100.0 END),
	MAX(CASE WHEN month = 4 THEN total / 100.0 END),
	MAX(CASE WHEN month = 5 THEN total / 100.0 END),
	MAX(CASE WHEN month = 6 THEN total / 100.0 END),
	MAX(CASE WHEN month = 7 THEN total / 100.0 END),
	MAX(CASE WHEN month = 8 THEN total / 100.0 END),
	MAX(CASE WHEN month = 9 THEN total / 100.0 END),
	MAX(CASE WHEN month = 10 THEN total / 100.0 END),
	MAX(CASE WHEN month = 11 THEN total / 100.0 END),
	MAX(CASE WHEN month = 12 THEN total / 100.0 END)
FROM Totals;
)";

}

#endif // MARVUS_SQL_HPP
