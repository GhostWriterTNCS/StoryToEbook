#include <QComboBox>
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include <QProgressDialog>
#include <QString>
#include <QTextStream>
#include "MainWindow.h"
#include "MyUtils.h"
#include "Website.h"

// Websites:
#include "EFP.h"
#include "Wattpad.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
	settings = new QSettings("settings.ini", QSettings::IniFormat);

	ui.setupUi(this);
	ui.formatComboBox->addItems({"epub", "mobi", "azw3", "pdf", "html"});
	ui.formatComboBox->setCurrentIndex(
		ui.formatComboBox->findText(settings->value("format", "epub").toString()));

	ui.downloadCoverCheckBox->setChecked(settings->value("downloadCover", false).toBool());

	ui.directoryLineEdit->setText(settings->value("directory", QDir::currentPath()).toString());
}

MainWindow::~MainWindow() {
	settings->setValue("format", ui.formatComboBox->currentText());
	settings->setValue("downloadCover", ui.downloadCoverCheckBox->isChecked());
	settings->setValue("directory", ui.directoryLineEdit->displayText().trimmed());
	settings->sync();
}

void MainWindow::on_downloadAndConvert_clicked() {
	QString url = ui.textEdit->toPlainText().trimmed();
	if (url.isEmpty()) {
		QMessageBox::warning(this, "Error", "You didn't insert any url!");
		return;
	}

	ui.statusBar->showMessage("Downloading story info...");
	Website* website;
	if (url.startsWith("http://www.efpfanfic.net/")) {
		website = new EFP();
	} else if (url.startsWith("https://www.wattpad.com/")) {
		website = new Wattpad();
	} else {
		QMessageBox::warning(this, "Error", "Url not valid.");
		ui.statusBar->clearMessage();
		return;
	}

	website->downloadStoryInfo(url);
	if (website->list.size() == 0) {
		QMessageBox::warning(this, "Error", "I can't download the story.");
		ui.statusBar->clearMessage();
		return;
	}

	QString title = website->title;
	if (title.length() > 30)
		title = title.mid(0, 30) + "...";

	website->initializeStory();
	for (int i = 0; i < website->list.size(); i++) {
		if (website->list.size() > 1)
			ui.statusBar->showMessage(title + " | Downloading chapter " + QString::number(i + 1) +
									  " of " + QString::number(website->list.size()) + "...");
		else
			ui.statusBar->showMessage(title + " | Downloading story...");

		if (!website->downloadChapter(i))
			QMessageBox::warning(this, "Error",
								 "I can't download capther " + QString::number(i + 1) + ".");
	}

	ui.statusBar->showMessage(title + " | Creating file...");
	QString filename = website->createEbook(ui.formatComboBox->currentText().trimmed(),
											ui.downloadCoverCheckBox->isChecked(),
											ui.directoryLineEdit->displayText().trimmed());

	ui.statusBar->clearMessage();
	QMessageBox::information(this, "Ok",
							 "<p><b>Download and conversion complete!</b></p>File saved as <i>" +
								 filename + "</i>",
							 true);
	ui.textEdit->setPlainText("");
}

void MainWindow::on_directoryButton_clicked() {
	QString folder = QFileDialog::getExistingDirectory(
		this, tr("Open Directory"), ui.directoryLineEdit->displayText(),
		QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
	if (!folder.isEmpty())
		ui.directoryLineEdit->setText(folder);
}
