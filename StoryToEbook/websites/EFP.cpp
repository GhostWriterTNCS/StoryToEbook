#include "EFP.h"
#include "MyQtUtils.h"

void EFP::downloadStoryInfo(QString url) {
	if (url.contains("sid=")) {
		QString id = MyQtUtils::substring(url, "sid=", "&");
		url = "http://www.efpfanfic.net/viewstory.php?sid=" + id;

		QString s = MyQtUtils::urlToQString(url);
		Website::intro = MyQtUtils::substring(s, "<div id=\"anteprima\">", "</div>");
		Website::intro = "\n\n<center><p class=\"titolo\">Introduzione<br> *** </p></center>\n<p>" +
						 Website::intro + "</p><br><br>\n";
		Website::title =
			MyQtUtils::substring(s, "<a href=\"viewstory.php?sid=" + id + "\">", "</a>");

		if (s.contains("printsave.php?action=printall&sid="))
			list.append("http://www.efpfanfic.net/printsave.php?action=printall&sid=" + id);
		else if (s.contains("printsave.php?action=printable&sid="))
			list.append("http://www.efpfanfic.net/printsave.php?action=printable&sid=" + id);
		else if (!Website::intro.isEmpty())
			list.append("http://www.efpfanfic.net/printsave.php?action=printall&sid=" + id);
	}
	return;
}

bool EFP::downloadChapter(int chapterIndex) {
	QString s = MyQtUtils::urlToQString(list[chapterIndex]);
	s.replace(s.indexOf("***</p></center><br>") + 21, 15, "");
	s.replace(s.indexOf("</b></center><br><br>") + 21, 0, Website::intro);

	Website::author = s;
	Website::author = MyQtUtils::substring(Website::author, "uid=", "</a>");
	Website::author = MyQtUtils::substring(Website::author, ">");

	s = MyQtUtils::advancedReplace(s, "</title><table width=\"100%\"", "<center><p class=\"title",
								   "</title><center><p class=\"title");
	s = s.replace("</td></tr></table>\n<p align=\"right\"><big><a href=\"#top\">Ritorna "
				  "all'indice</a></big></p><hr>",
				  "<p align=\"right\"><big><a href=\"#top\">Ritorna all'indice</a></big></p><br "
				  "style='page-break-before:always;mso-break-type:section-break'>");
	s = s.replace("***</p></center><br>\n<table><tr><td>", "***</p></center><br>\n");
	s = s.replace("</p><br><br>\n\n<table><tr><td>", "</p><br><br>\n\n");

	Website::story = "<html><head><meta http-equiv=Content-Type content=\"text/html; "
					 "charset=windows-1252\"></head>\n" +
					 s;

	if (s.contains("<img ")) {
		Website::cover = MyQtUtils::substring(s, "<img ", ">");
		if (Website::cover.contains("src='"))
			Website::cover = MyQtUtils::substring(Website::cover, "src='", "'");
		else
			Website::cover = MyQtUtils::substring(Website::cover, "src=\"", "\"");
	}

	return true;
}
