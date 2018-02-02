#include "MyUtils.h"
#include "Wattpad.h"

void Wattpad::downloadStoryInfo(QString url) {
	if (url[24].isDigit()) {
		url = MyUtils::urlToQString(url);
		if (!url.contains("data-story-id=\"")) {
			return;
		}
		url = MyUtils::substring(url, "data-story-id=\"", "\"");
		url = "https://www.wattpad.com/story/" + url + "/parts";
	} else if (!url.startsWith("https://www.wattpad.com/story/")) {
		return;
	}

	if (!url.contains("/parts")) {
		url += "/parts";
	}
	QString caps = MyUtils::urlToQString(url);

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
		return;
	}
	return;
}

bool Wattpad::downloadChapter(int chapterIndex) {
	QString temp = MyUtils::urlToQString(list[chapterIndex]);
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
			temp = MyUtils::urlToQString(list[chapterIndex] + "/page/" + QString::number(p));
			p++;
		} else
			break;
	}
	s = MyUtils::advancedReplace(s, "<p data-p-id=", ">", "<p>");
	s = s.replace("                            <p", "<p");

	QString id = MyUtils::substring(list[chapterIndex], "wattpad.com/", "-");
	s = s.replace("<h1 style=\"text-align: center;\">",
				  "<h1 style=\"text-align: center;\"><a name=\"" + id + "\"></a><a href=\"#" + id +
					  "\">");
	s = s.replace("</h1>", "</a></h1>");
	Website::story += s + "\n</div>\n";
	return true;
}
