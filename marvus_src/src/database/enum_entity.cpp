//==============================================================================
// Author     : riyufuchi
// Created on : 2026-10-04
// Last edit  : 2026-10-04
// Copyright  : Copyright (c) 2026, riyufuchi
//==============================================================================
#include "enum_entity.h"

marvus::EnumEntity::EnumEntity(const QString& name) : name(name)
{

}

const QString& marvus::EnumEntity::get_name() const
{
	return name;
}
