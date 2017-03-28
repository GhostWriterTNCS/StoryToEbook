#pragma once

#include <QFile>
#include <QString>
#include <QTextStream>

namespace MyUtils {

QString readFile(QString filename);
QString validateFilename(QString filename);
bool writeFile(QString filename, QString content);
QString substring(QString str, QString start, QString end = "");
QString advancedReplace(QString str, QString startReplace, QString endReplace, QString newText);

} // namespace MyUtils
