#pragma once

#include <QSettings>
#include <QtWidgets/QMainWindow>
#include "Website.h"
#include "ui_MainWindow.h"

class MainWindow : public QMainWindow {
	Q_OBJECT

public:
	MainWindow(QWidget* parent = Q_NULLPTR);
	~MainWindow();
	Ui::MainWindowClass ui;
	QSettings* settings;

	private slots:
	void on_downloadAndConvert_clicked();
	void on_directoryButton_clicked();
};
