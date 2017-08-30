#pragma once

#include <QFile>
#include <QString>
#include <QTextStream>

namespace MyUtils {

/**
	Parse a file and get content as string.
*/
QString readFile(QString filename);
/**
	Return the filename as a valid filename.
*/
QString validateFilename(QString filename);
/**
	Create a file with content.
*/
bool writeFile(QString filename, QString content);

/**
	Get a substring using starting and ending delimiters.
	Leave start or end as empty strings to get from the begging of the string or to the end of the
	string.
	Example: substring("Hi, my name is Tom.", "", "is") -> "Hi, my name ".
*/
QString substring(QString str, QString start, QString end = "");
/**
	Replace a substring using starting and ending delimiters.
	Example: advancedReplace("Hi, my name is Tom.", "my", "is", "I'm") -> "Hi, I'm Tom".
*/
QString advancedReplace(QString str, QString startReplace, QString endReplace, QString newText);

/**
	Parse the html by url and return the content as QString.
*/
QString urlToQString(QString url);
/**
	Get the redirected url for an url.
*/
QString redirectedUrlQt(QString url);

} // namespace MyUtils
