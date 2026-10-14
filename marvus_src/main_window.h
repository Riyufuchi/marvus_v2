//==============================================================================
// Author     : riyufuchi
// Created on : 2026-04-15
// Last edit  : 2026-10-13
// Copyright  : Copyright (c) 2026, riyufuchi
//==============================================================================
#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
// STD
#include <unordered_map>
#include <memory>
// Nocovka
#include "src/controller.h"
#include "src/marvus/marvus_test_data.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT

private:
	enum class TabView
	{
		CURRENT_MONTH,
		CURRENT_MONTH_BY_ENTITY,
		ALL_LOGS,
		YEAR_OVERVIEW
	};
	marvus::Controller controller;
	TabView current_tab_view;
	QSqlQueryModel* entity_model, *category_model;
	std::unordered_map<TabView, std::unique_ptr<QSqlQueryModel>> model_map;
	void init_models();
	void select_model(TabView tabView);
public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

private slots:
	void on_actionExit_triggered();

	void on_actionImport_triggered();

	void on_actionNew_triggered();

	void on_actionOpen_triggered();

	void on_actionAll_logs_triggered();

	void on_actionYear_overview_triggered();

	void on_actionBy_category_triggered();

	void on_actionBy_Entity_triggered();

private:
	Ui::MainWindow *ui;
};
#endif // MAIN_WINDOW_H
