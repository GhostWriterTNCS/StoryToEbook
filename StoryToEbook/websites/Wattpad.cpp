#include "MyCurl.h"
#include "MyUtils.h"
#include "Wattpad.h"

QStringList Wattpad::downloadStoryInfo(QString url) {
	QStringList list;
	if (url[24].isDigit()) {
		url = MyCurl::urlToString(url);
		if (!url.contains("data-story-id=\"")) {
			return list;
		}
		url = MyUtils::substring(url, "data-story-id=\"", "\"");
		url = "https://www.wattpad.com/story/" + url + "/parts";
	} else if (!url.startsWith("https://www.wattpad.com/story/")) {
		return list;
	}

	if (!url.contains("/parts")) {
		url += "/parts";
	}
	QString caps = MyCurl::urlToString(url);

	if (!caps.isEmpty()) {
		Website::intro =
			(MyUtils::substring(caps, "<h2 class=\"description\"><pre>", "</pre>")).trimmed();
		Website::intro = "<div style='text-align:justify'><p>" +
						 Website::intro.replace("\n", "</p><p>") + "</p></div>";
		Website::title = (MyUtils::substring(caps, "<h1>", "</h1>")).trimmed();
		Website::title = Website::title.replace("&#x27;", "'");

		Website::author = MyUtils::substring(caps, "author-info", "</div>");
		Website::author = (MyUtils::substring(Website::author, "<a href=\"/user/", "\"")).trimmed();

		Website::cover = MyUtils::substring(caps, "cover cover-lg", "</div>");
		Website::cover = MyUtils::substring(Website::cover, "src=\"", "\"");

		caps = MyUtils::substring(caps, "class=\"table-of-contents\"", "</ul>");
		list = caps.split("</li>");
		list.removeLast();
		for (int i = 0; i < list.size(); i++) {
			list[i] = "https://www.wattpad.com" + MyUtils::substring(list[i], "<a href=\"", "\"");
		}
		return list;
	}
	return list;
}

bool Wattpad::downloadChapter(QStringList chapterUrls, int chapterIndex) {
	QString temp = MyCurl::urlToString(chapterUrls[chapterIndex]);
	QString s = "<h1 style=\"text-align: center;\">" +
				(MyUtils::substring(temp, "<h2>", "</h2>")).trimmed() + "</h1>\n";
	int p = 2;
	while (temp.contains("data-page-number=")) {
		temp = MyUtils::substring(temp, "data-page-number=", "</div>");
		if (!temp.contains("</pre>")) {
			return false;
		}
		s += MyUtils::substring(temp, "<pre>", "</pre>") + "\n";
		if (!MyUtils::substring(temp, "", "<pre>").contains("last-page")) {
			std::cout << "\n\n" + (chapterUrls[chapterIndex] + "/page/" + QString::number(p))
									  .toStdString()
					  << std::endl;
			temp = MyCurl::urlToString(chapterUrls[chapterIndex] + "/page/" + QString::number(p));
			p++;
		} else
			break;
	}
	s = MyUtils::advancedReplace(s, "<p data-p-id=", ">", "<p>");
	s = s.replace("                            <p", "<p");
	Website::story += s + "\n</div>\n";
	return true;
}
