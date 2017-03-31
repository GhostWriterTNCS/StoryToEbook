#pragma once

#include <QFile>
#include <QString>
#include <QTextStream>

namespace MyQtUtils {

QString readFile(QString filename);
QString validateFilename(QString filename);
bool writeFile(QString filename, QString content);

QString substring(QString str, QString start, QString end = "");
QString advancedReplace(QString str, QString startReplace, QString endReplace, QString newText);

QString urlToQString(QString url);
QString redirectedUrlQt(QString url);

} // namespace MyQtUtils
