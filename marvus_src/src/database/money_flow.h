//==============================================================================
// Author     : riyufuchi
// Created on : 2026-10-04
// Last edit  : 2026-10-04
// Copyright  : Copyright (c) 2026, riyufuchi
//==============================================================================
#ifndef MONEY_FLOW_H
#define MONEY_FLOW_H

#include <QString>

namespace marvus
{

class MoneyFlow
{
private:
	int entity_id, category_id;
	int value;
	QString date;
public:
	MoneyFlow(int entity_id, int category_id, int value, const QString& date);

	int get_entity_id() const;
	int get_category_id() const;
	int get_value() const;
	const QString& get_date() const;
};

}
#endif // MONEY_FLOW_H
