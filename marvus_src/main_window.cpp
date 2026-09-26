//==============================================================================
// Author     : riyufuchi
// Created on : 2026-04-15
// Last edit  : 2026-04-15
// Copyright  : Copyright (c) 2026, riyufuchi
//==============================================================================
#include "main_window.h"
#include "ui_main_window.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	this->model = controller.obtain_model("ITEMS", this);
	ui->db_view->setModel(model);
	ui->db_view->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui->db_view->hideColumn(0);
}

MainWindow::~MainWindow()
{
	delete ui;
}


void MainWindow::on_actionExit_triggered()
{
	QApplication::quit();
}


void MainWindow::on_actionImport_triggered()
{
	controller.import_from_json_to_db(this);
	model->refresh();

	/*nocovka::QJsonOptional doc_opt = nocovka::import_json(this);

	if (!doc_opt && !((*doc_opt).isObject()))
		return;

	QJsonObject obj = doc_opt.value().object();

	QStandardItemModel *model = new QStandardItemModel(this);

	QStringList headers;
	for (auto key : obj.keys())
	{
		headers << key;
	}
	model->setColumnCount(headers.size());
	model->setHorizontalHeaderLabels(headers);

	QList<QStandardItem*> row;

	for (auto key : obj.keys())
	{
		QString value = obj.value(key).toVariant().toString();
		row.append(new QStandardItem(value));
	}

	model->appendRow(row);

	ui->tableView->setModel(model);*/
}

