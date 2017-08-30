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

	/**
		Get the story informations by url.
		The implementation is different for each website.
	*/
	virtual void downloadStoryInfo(QString url) {
		return;
	};
	/**
		Initialize the story text with title and intro.
	*/
	void initializeStory();
	/**
		Download a character by index.
		The implementation is different for each website.
	*/
	virtual bool downloadChapter(int chapterIndex) {
		return false;
	};
	/**
		Create the ebook with Calibre.
	*/
	QString createEbook(QString extension, bool downloadCover, QString folder);

}; // class Website
