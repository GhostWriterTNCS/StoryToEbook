#include "Website.h"
#include "MyUtils.h"
#include "Wattpad.h"

QStringList Website::downloadStoryInfo(QString website, QString url)
{
	if(website == "Wattpad")
		return Wattpad::downloadStoryInfo(url);
	return QStringList();
}

bool Website::downloadChapter(QString website, QStringList chapterUrls, int chapterIndex)
{
	if (website == "Wattpad")
		return Wattpad::downloadChapter(chapterUrls, chapterIndex);
	return false;
}

void Website::initializeStory() {
	story = "<html><head><meta content=\"text/html; charset=utf-8\"></head>\n";
	story += "<title>" + title + "</title>\n";
	story += "<h1>" + title + "</h1>\n";
	story += "<p><b><center>Intro<br /></center></b></p>\n";
	story += intro + "\n";
}

QString Website::createEbook(QString extension, bool downloadCover, QString folder)
{
	if (!folder.isEmpty()) {
		folder = folder + "\\";
		folder = folder.replace("/", "\\");
	}

	title = MyUtils::validateFilename(title);
	if (extension == "html") {
		MyUtils::writeFile(title + ".html", story);
	}
	else {
		MyUtils::writeFile("temp.htm", story);

		if (downloadCover && !cover.isEmpty()) {
			cover = cover.replace(" ", "%20");
			cover = "--cover=" + cover;
		}
		else {
			cover = "";
		}

		system(("ebook-convert temp.htm \"" + folder + title + "." + extension + "\" --authors=\"" + author + "\" " + cover).toStdString().c_str());
		QFile file("temp.htm");
		file.remove();
	}
	return folder + title + "." + extension;
}
