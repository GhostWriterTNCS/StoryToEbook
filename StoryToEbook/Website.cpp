#include <QFileInfo>
#include "MyQtUtils.h"
#include "Wattpad.h"
#include "Website.h"

// Websites:
#include "EFP.h"
#include "Wattpad.h"

QString Website::title;
QString Website::author;
QString Website::intro;
QString Website::cover;
QString Website::story;

QStringList Website::downloadStoryInfo(QString url) {
	if (url.startsWith("http://www.efpfanfic.net/"))
		return EFP::downloadStoryInfo(url);

	if (url.startsWith("https://www.wattpad.com/"))
		return Wattpad::downloadStoryInfo(url);

	return QStringList();
}

bool Website::downloadChapter(QStringList chapterUrls, int chapterIndex) {
	if (chapterUrls[0].startsWith("http://www.efpfanfic.net/"))
		return EFP::downloadChapter(chapterUrls, chapterIndex);

	if (chapterUrls[0].startsWith("https://www.wattpad.com/"))
		return Wattpad::downloadChapter(chapterUrls, chapterIndex);

	return false;
}

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

	Website::title = MyQtUtils::validateFilename(Website::title);
	if (extension == "html") {
		MyQtUtils::writeFile(Website::title + ".html", Website::story);
	} else {
		int i = 0;
		QFile file;
		while (file.exists(QString::number(i) + ".htm"))
			i++;
		MyQtUtils::writeFile(QString::number(i) + ".htm", Website::story);

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
