#pragma once

#include <QString>
#include <QStringList>

class Website {

public:
	QString title;
	QString author;
	QString intro;
	QString cover;
	QString story;
	QStringList list;

	virtual void downloadStoryInfo(QString url) {
		return;
	};
	void initializeStory();
	virtual bool downloadChapter(int chapterIndex) {
		return false;
	};
	QString createEbook(QString extension, bool downloadCover, QString folder);

}; // class Website
