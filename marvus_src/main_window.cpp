//==============================================================================
// Author     : riyufuchi
// Created on : 2026-04-15
// Last edit  : 2026-10-11
// Copyright  : Copyright (c) 2026, riyufuchi
//==============================================================================
#include "main_window.h"
#include "ui_main_window.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), current_tab_view(TabView::CURRENT_MONTH)
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

	entity_model->refresh();
	category_model->refresh();

	for (const auto& model : model_map)
		model.second->refresh();
}

void  MainWindow::init_models()
{
	this->entity_model = controller.select_entities(this);
	ui->entity_view->setModel(entity_model);
	ui->entity_view->setEditTriggers(QAbstractItemView::NoEditTriggers);

	this->category_model = controller.select_categories(this);
	ui->category_view->setModel(category_model);
	ui->category_view->setEditTriggers(QAbstractItemView::NoEditTriggers);

	model_map[TabView::CURRENT_MONTH] = std::unique_ptr<QSqlQueryModel>(controller.select(this));
	model_map[TabView::ALL_LOGS] = std::unique_ptr<QSqlQueryModel>(controller.select_money_flows(this));
	model_map[TabView::YEAR_OVERVIEW] = std::unique_ptr<QSqlQueryModel>(controller.select_year_overview(this));

	ui->db_view->setModel(model_map.at(TabView::CURRENT_MONTH).get());
	ui->db_view->setEditTriggers(QAbstractItemView::NoEditTriggers);
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

void MainWindow::select_model(TabView tabView)
{
	current_tab_view = tabView;
	ui->db_view->setModel(model_map.at(tabView).get());
}

void MainWindow::on_actionCurrent_month_triggered()
{
	select_model(TabView::CURRENT_MONTH);
}


void MainWindow::on_actionAll_logs_triggered()
{
	select_model(TabView::ALL_LOGS);
}


void MainWindow::on_actionYear_overview_triggered()
{
	select_model(TabView::YEAR_OVERVIEW);
}

