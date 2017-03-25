#pragma once

#include "Website.h"

namespace EFP
{
	QStringList downloadStoryInfo(QString url);
	bool downloadChapter(QStringList chapterUrls, int chapterIndex);
};
