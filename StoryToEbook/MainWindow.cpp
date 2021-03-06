#include <QApplication>
#include <QComboBox>
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include <QProgressDialog>
#include <QString>
#include <QTextStream>
#include <QtConcurrent\QtConcurrentRun>
#include "MainWindow.h"
#include "MyUtils.h"
#include "Website.h"

// Websites:
#include "EFP.h"
#include "Wattpad.h"

MainWindow::MainWindow(int argc, char* argv[], QWidget* parent) : QMainWindow(parent) {
	settings = new QSettings(QCoreApplication::applicationDirPath() + "\\settings.ini",
							 QSettings::IniFormat);

	ui.setupUi(this);
	ui.formatComboBox->addItems({"epub", "mobi", "azw3", "pdf", "html"});
	ui.formatComboBox->setCurrentIndex(
		ui.formatComboBox->findText(settings->value("format", "epub").toString()));

	ui.downloadCoverCheckBox->setChecked(settings->value("downloadCover", false).toBool());

	ui.directoryLineEdit->setText(settings->value("directory", QDir::currentPath()).toString());

	if (argc > 1) {
		ui.urlTextEdit->setPlainText(argv[1]);
	}

	connect(this, SIGNAL(finish(bool)), this, SLOT(finished(bool)));
}

MainWindow::~MainWindow() {
	settings->setValue("format", ui.formatComboBox->currentText());
	settings->setValue("downloadCover", ui.downloadCoverCheckBox->isChecked());
	settings->setValue("directory", ui.directoryLineEdit->displayText().trimmed());
	settings->sync();
}

void MainWindow::on_downloadAndConvert_clicked() {
	QString url = ui.urlTextEdit->toPlainText().trimmed();
	if (url.isEmpty()) {
		QMessageBox::warning(this, "Error", "You didn't insert any url!");
		ui.statusBar->clearMessage();
		return;
	}

	ui.statusBar->showMessage("Downloading story info...");
	Website* website;
	if (url.startsWith("https://efpfanfic.net/")) {
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
	if (title.length() > 50)
		title = title.mid(0, 50) + "...";

	website->initializeStory();
	for (int i = 0; i < website->list.size(); i++) {
		if (website->list.size() > 1) {
			ui.statusBar->showMessage(title + " | Downloading chapter " + QString::number(i + 1) +
									  " of " + QString::number(website->list.size()) + "...");
		} else {
			qApp->processEvents();
		}
		qApp->processEvents();

		if (!website->downloadChapter(i)) {
			QMessageBox::warning(this, "Error",
								 "I can't download capther " + QString::number(i + 1) + ".");
			ui.statusBar->clearMessage();
			return;
		}
	}

	ui.statusBar->showMessage(title + " | Creating file...");
	QString filename = website->createEbook(ui.formatComboBox->currentText().trimmed(),
											ui.downloadCoverCheckBox->isChecked(),
											ui.directoryLineEdit->displayText().trimmed());

	QMessageBox::information(this, "Done",
							 "<p><b>Download and conversion complete!</b></p>File saved as <i>" +
								 filename + "</i>");
	ui.urlTextEdit->clear();
	ui.statusBar->clearMessage();
}

void MainWindow::on_directoryButton_clicked() {
	QString folder = QFileDialog::getExistingDirectory(
		this, tr("Open Directory"), ui.directoryLineEdit->displayText(),
		QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
	if (!folder.isEmpty())
		ui.directoryLineEdit->setText(folder);
}
