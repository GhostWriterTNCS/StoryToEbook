#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = Q_NULLPTR);
	//~MainWindow();
	Ui::MainWindowClass ui;

private slots:
	void on_downloadAndConvert_clicked();
	void on_directoryButton_clicked();

private:
	//void download_story();
};
