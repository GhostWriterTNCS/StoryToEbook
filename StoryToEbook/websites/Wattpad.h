#pragma once

#include "Website.h"

class Wattpad : public Website {

public:
	void downloadStoryInfo(QString url);
	bool downloadChapter(int chapterIndex);

}; // class Wattpad
