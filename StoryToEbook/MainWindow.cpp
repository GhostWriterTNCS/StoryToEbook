#include "MainWindow.h"
#include "MyCurl.h"
#include "MyUtils.h"
#include "Website.h"
#include <QDir>
#include <QString>
#include <QTextStream>
#include <QComboBox>
#include <QMessageBox>
#include <QFileDialog>
#include <QProgressDialog>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.comboBox->addItems({ "epub", "mobi", "azw3", "pdf", "html" });
	ui.currentDir->setText(QDir::currentPath());
}

void MainWindow::on_downloadAndConvert_clicked()
{
	QString url = ui.textEdit->toPlainText().trimmed();
	if (url.isEmpty()) {
		QMessageBox::warning(this, "Error", "You didn't insert any url!");
		return;
	}

	QString website;
	ui.statusBar->showMessage("Downloading story info...");
	QStringList list = Website::downloadStoryInfo(url);
	if (list.size() == 0) {
		QMessageBox::warning(this, "Error", "I can't download the story.");
		return;
	}

	QString title = Website::title;
	if (title.length() > 30)
		title = title.mid(0, 30) + "...";

	Website::initializeStory();
	for (int i = 0; i < list.size(); i++) {
		if (list.size() > 1)
			ui.statusBar->showMessage(title + " | Downloading chapter " + QString::number(i + 1) + " of " + QString::number(list.size()) + "...");
		else
			ui.statusBar->showMessage(title + " | Downloading story...");

		if(!Website::downloadChapter(list, i))
			QMessageBox::warning(this, "Error", "I can't download capther " + QString::number(i + 1) + ".");
	}

	ui.statusBar->showMessage(title + " | Creating file...");
	QString filename = Website::createEbook(ui.comboBox->currentText().trimmed(), ui.checkBox->isChecked(), ui.currentDir->displayText().trimmed());

	ui.statusBar->clearMessage();
	QMessageBox::information(this, "Ok", "<p><b>Download and conversion complete!</b></p>File saved as <i>" + filename + "</i>", true);
	ui.textEdit->setPlainText("");
}

void MainWindow::on_directoryButton_clicked()
{
	QString folder = QFileDialog::getExistingDirectory(this, tr("Open Directory"), ui.currentDir->displayText(),
		QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
	if (!folder.isEmpty())
		ui.currentDir->setText(folder);
}
