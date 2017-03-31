#include "MyQtUtils.h"
#include "Wattpad.h"

QStringList Wattpad::downloadStoryInfo(QString url) {
	QStringList list;
	if (url[24].isDigit()) {
		url = MyQtUtils::urlToQString(url);
		if (!url.contains("data-story-id=\"")) {
			return list;
		}
		url = MyQtUtils::substring(url, "data-story-id=\"", "\"");
		url = "https://www.wattpad.com/story/" + url + "/parts";
	} else if (!url.startsWith("https://www.wattpad.com/story/")) {
		return list;
	}

	if (!url.contains("/parts")) {
		url += "/parts";
	}
	QString caps = MyQtUtils::urlToQString(url);

	if (!caps.isEmpty()) {
		Website::intro =
			(MyQtUtils::substring(caps, "<h2 class=\"description\"><pre>", "</pre>")).trimmed();
		Website::intro = "<div style='text-align:justify'><p>" +
						 Website::intro.replace("\n", "</p><p>") + "</p></div>";
		Website::title = (MyQtUtils::substring(caps, "<h1>", "</h1>")).trimmed();
		Website::title = Website::title.replace("&#x27;", "'");

		Website::author = MyQtUtils::substring(caps, "author-info", "</div>");
		Website::author =
			(MyQtUtils::substring(Website::author, "<a href=\"/user/", "\"")).trimmed();

		Website::cover = MyQtUtils::substring(caps, "cover cover-lg", "</div>");
		Website::cover = MyQtUtils::substring(Website::cover, "src=\"", "\"");

		caps = MyQtUtils::substring(caps, "class=\"table-of-contents\"", "</ul>");
		list = caps.split("</li>");
		list.removeLast();
		for (int i = 0; i < list.size(); i++) {
			list[i] = "https://www.wattpad.com" + MyQtUtils::substring(list[i], "<a href=\"", "\"");
		}
		return list;
	}
	return list;
}

bool Wattpad::downloadChapter(QStringList chapterUrls, int chapterIndex) {
	QString temp = MyQtUtils::urlToQString(chapterUrls[chapterIndex]);
	QString s = "<h1 style=\"text-align: center;\">" +
				(MyQtUtils::substring(temp, "<h2>", "</h2>")).trimmed() + "</h1>\n";
	int p = 2;
	while (temp.contains("data-page-number=")) {
		temp = MyQtUtils::substring(temp, "data-page-number=", "</div>");
		if (!temp.contains("</pre>")) {
			return false;
		}
		s += MyQtUtils::substring(temp, "<pre>", "</pre>") + "\n";
		if (!MyQtUtils::substring(temp, "", "<pre>").contains("last-page")) {
			temp =
				MyQtUtils::urlToQString(chapterUrls[chapterIndex] + "/page/" + QString::number(p));
			p++;
		} else
			break;
	}
	s = MyQtUtils::advancedReplace(s, "<p data-p-id=", ">", "<p>");
	s = s.replace("                            <p", "<p");
	Website::story += s + "\n</div>\n";
	return true;
}
