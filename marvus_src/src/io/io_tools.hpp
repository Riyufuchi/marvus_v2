//==============================================================================
// Author     : riyufuchi
// Created on : 2026-04-28
// Last edit  : 2026-04-28
// Copyright  : Copyright (c) 2026, riyufuchi
//==============================================================================
#ifndef IO_TOOLS_HPP
#define IO_TOOLS_HPP

//STL
#include <optional>
// Qt
#include <QFileDialog>
#include <QFile>
#include <QJsonDocument>

namespace marvus
{

using QJsonOptional = std::optional<QJsonDocument>;

inline QJsonOptional import_json(QWidget* parent)
{
	QString fileName = QFileDialog::getOpenFileName(
		parent,
		"Open JSON",
		"",
		"JSON Files (*.json)"
	);

	if (fileName.isEmpty())
		return std::nullopt;

	QFile file(fileName);
	if (!file.open(QIODevice::ReadOnly))
		return std::nullopt;

	QByteArray data = file.readAll();
	file.close();

	return QJsonDocument::fromJson(data);
}

}

#endif // IO_TOOLS_HPP
