#pragma once

#include "Website.h"

class EFP : public Website {

public:
	void downloadStoryInfo(QString url);
	bool downloadChapter(int chapterIndex);

}; // class EFP
