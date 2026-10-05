//==============================================================================
// Author     : riyufuchi
// Created on : 2026-04-15
// Last edit  : 2026-10-05
// Copyright  : Copyright (c) 2026, riyufuchi
//==============================================================================
#include "main_window.h"
#include "ui_main_window.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	on_actionOpen_triggered();
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
	//controller.import_from_json_to_db(this);

	for (const auto& c : marvus::categories())
	{
		if (!controller.expose_db().insert_category(c))
		{
			QMessageBox::critical(this, c.get_name(), controller.expose_db().get_last_error());
			break;
		}
	}

	for (const auto& e : marvus::entities())
	{
		if (!controller.expose_db().insert_entity(e))
		{
			QMessageBox::critical(this, e.get_name(), controller.expose_db().get_last_error());
			break;
		}
	}

	for (const auto& mf : marvus::money_flow())
	{
		if (!controller.expose_db().insert_money_flow(mf))
		{
			QMessageBox::critical(this, mf.get_date(), controller.expose_db().get_last_error());
			break;
		}
	}

	model->refresh();
	entity_model->refresh();
	category_model->refresh();
	all_model->refresh();
}

void  MainWindow::init_models()
{
	this->model = controller.select(this);
	ui->db_view->setModel(model);
	ui->db_view->setEditTriggers(QAbstractItemView::NoEditTriggers);

	this->entity_model = controller.select_entities(this);
	ui->entity_view->setModel(entity_model);
	ui->entity_view->setEditTriggers(QAbstractItemView::NoEditTriggers);

	this->category_model = controller.select_categories(this);
	ui->category_view->setModel(category_model);
	ui->category_view->setEditTriggers(QAbstractItemView::NoEditTriggers);

	this->all_model = controller.select_money_flows(this);
	ui->full_view->setModel(all_model);
	ui->full_view->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void MainWindow::on_actionNew_triggered()
{
	controller.create_new_database(this);
	init_models();
}

void MainWindow::on_actionOpen_triggered()
{
	if (!controller.open_database(this))
	{
		init_models();
	}
}

