//==============================================================================
// Author     : riyufuchi
// Created on : 2026-10-04
// Last edit  : 2026-10-04
// Copyright  : Copyright (c) 2026, riyufuchi
//==============================================================================
#include "money_flow.h"


marvus::MoneyFlow::MoneyFlow(int entity_id, int category_id, int value, const QString& date) : entity_id(entity_id), category_id(category_id), value(value), date(date)
{
}

int marvus::MoneyFlow::get_entity_id() const
{
	return entity_id;
}

int marvus::MoneyFlow::get_category_id() const
{
	return category_id;
}

int  marvus::MoneyFlow::get_value() const
{
	return value;
}

const QString& marvus::MoneyFlow::get_date() const
{
	return date;
}

