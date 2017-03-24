#pragma once

#include <QString>

namespace Website
{
	QStringList downloadStoryInfo(QString website, QString url);
	void initializeStory();
	bool downloadChapter(QString website, QStringList chapterUrls, int chapterIndex);
	QString createEbook(QString extension, bool downloadCover, QString folder);

	static QString title;
	static QString author;
	static QString intro;
	static QString cover;
	static QString story;
};
