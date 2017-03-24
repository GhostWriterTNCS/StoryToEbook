#pragma once

#include "Website.h"

namespace Wattpad
{
	QStringList downloadStoryInfo(QString url);
	bool downloadChapter(QStringList chapterUrls, int chapterIndex);
};
