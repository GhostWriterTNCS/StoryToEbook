#include <QFileInfo>
#include "MyUtils.h"
#include "Wattpad.h"
#include "Website.h"

void Website::initializeStory() {
	Website::story = "<html><head><meta content=\"text/html; charset=utf-8\"></head>\n";
	Website::story += "<title>" + Website::title + "</title>\n";
	Website::story += "<h1>" + Website::title + "</h1>\n";
	Website::story += "<p><b><center>Intro<br /></center></b></p>\n";
	Website::story += Website::intro + "\n";
}

QString Website::createEbook(QString extension, bool downloadCover, QString folder) {
	if (!folder.isEmpty()) {
		folder = folder + "\\";
		folder = folder.replace("/", "\\");
	}

	Website::title = MyUtils::validateFilename(Website::title);
	if (extension == "html") {
		MyUtils::writeFile(Website::title + ".html", Website::story);
	} else {
		int i = 0;
		QFile file;
		while (file.exists(QString::number(i) + ".htm"))
			i++;
		MyUtils::writeFile(QString::number(i) + ".htm", Website::story);

		if (downloadCover && !Website::cover.isEmpty()) {
			Website::cover = Website::cover.replace(" ", "%20");
			Website::cover = "--cover=" + Website::cover;
		} else {
			Website::cover = "";
		}

		system(("ebook-convert " + QString::number(i) + ".htm \"" + folder + Website::title + "." +
				extension + "\" --authors=\"" + Website::author + "\" " + cover)
				   .toStdString()
				   .c_str());
		file.remove(QString::number(i) + ".htm");
	}
	return folder + Website::title + "." + extension;
}
