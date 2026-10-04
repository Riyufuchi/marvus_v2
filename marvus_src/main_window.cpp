//==============================================================================
// Author     : riyufuchi
// Created on : 2026-04-15
// Last edit  : 2026-10-04
// Copyright  : Copyright (c) 2026, riyufuchi
//==============================================================================
#include "main_window.h"
#include "ui_main_window.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	this->model = controller.select(this);
	ui->db_view->setModel(model);
	ui->db_view->setEditTriggers(QAbstractItemView::NoEditTriggers);
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

	marvus::EnumEntity cat("Food");
	marvus::EnumEntity cat2("AFood");
	marvus::EnumEntity entity("Lidl");

	if (!controller.expose_db().insert_category(cat))
	{
		QMessageBox::critical(this, "Chyba databáze", controller.expose_db().get_last_error());
	}

	if (!controller.expose_db().insert_category(cat2))
	{
		QMessageBox::critical(this, "Chyba databáze", controller.expose_db().get_last_error());
	}

	if (!controller.expose_db().insert_entity(entity))
	{
		QMessageBox::critical(this, "Chyba databáze", controller.expose_db().get_last_error());
	}

	marvus::MoneyFlow m1(1, 1, -100, "2026-10-1");
	marvus::MoneyFlow m2(1, 1, -200, "2026-10-10");
	marvus::MoneyFlow m4(1, 2, -200, "2026-10-10");
	marvus::MoneyFlow m3(1, 1, 1000, "2026-1-10");

	if (!controller.expose_db().insert_money_flow(m1))
	{
		QMessageBox::critical(this, "Chyba databáze", controller.expose_db().get_last_error());
	}

	if (!controller.expose_db().insert_money_flow(m2))
	{
		QMessageBox::critical(this, "Chyba databáze", controller.expose_db().get_last_error());
	}

	if (!controller.expose_db().insert_money_flow(m3))
	{
		QMessageBox::critical(this, "Chyba databáze", controller.expose_db().get_last_error());
	}

	if (!controller.expose_db().insert_money_flow(m4))
	{
		QMessageBox::critical(this, "Chyba databáze", controller.expose_db().get_last_error());
	}

	model->refresh();
}

