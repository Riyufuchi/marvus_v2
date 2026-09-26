//==============================================================================
// Author     : riyufuchi
// Created on : 2026-04-15
// Last edit  : 2026-04-15
// Copyright  : Copyright (c) 2026, riyufuchi
//==============================================================================
#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
// Nocovka
#include "src/controller.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT

private:
	marvus::Controller controller;
	QSqlTableModel* model;

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

private slots:
	void on_actionExit_triggered();

	void on_actionImport_triggered();

private:
	Ui::MainWindow *ui;
};
#endif // MAIN_WINDOW_H
