//==============================================================================
// Author     : riyufuchi
// Created on : 2026-04-15
// Last edit  : 2026-10-05
// Copyright  : Copyright (c) 2026, riyufuchi
//==============================================================================
#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
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
	marvus::Controller controller;
	QSqlQueryModel* model, *entity_model, *category_model, *all_model;
	void init_models();
public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

private slots:
	void on_actionExit_triggered();

	void on_actionImport_triggered();

	void on_actionNew_triggered();

	void on_actionOpen_triggered();

private:
	Ui::MainWindow *ui;
};
#endif // MAIN_WINDOW_H
