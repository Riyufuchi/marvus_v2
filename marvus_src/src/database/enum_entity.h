//==============================================================================
// Author     : riyufuchi
// Created on : 2026-10-04
// Last edit  : 2026-10-04
// Copyright  : Copyright (c) 2026, riyufuchi
//==============================================================================
#ifndef CATEGORY_H
#define CATEGORY_H

#include <QString>

namespace marvus
{

class EnumEntity
{
private:
	QString name;
public:
	EnumEntity(const QString& name);
	const QString& get_name() const;
};

}
#endif // CATEGORY_H
