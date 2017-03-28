#pragma once

#include <QString>

namespace Website {

QStringList downloadStoryInfo(QString url);
void initializeStory();
bool downloadChapter(QStringList chapterUrls, int chapterIndex);
QString createEbook(QString extension, bool downloadCover, QString folder);

extern QString title;
extern QString author;
extern QString intro;
extern QString cover;
extern QString story;

} // namespace Website
