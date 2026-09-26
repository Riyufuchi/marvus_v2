//==============================================================================
// Author     : riyufuchi
// Created on : 2026-04-28
// Last edit  : 2026-04-28
// Copyright  : Copyright (c) 2026, riyufuchi
//==============================================================================
#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QFileDialog>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QStandardItemModel>
// Nocovka
#include "io/io_tools.hpp"
#include "qt_tools/database.h"

namespace marvus
{

class Controller
{
private:
	Database db_connection;
	std::vector<QString> labels;
public:
	Controller();
	void import_from_json_to_db(QWidget* parent);
	QSqlTableModel* obtain_model(const QString& TABLE_NAME, QObject* parent);
};

}

#endif // CONTROLLER_H
