#include "MyUtils.h"

namespace MyUtils {

QString readFile(QString filename) {
	QFile file(filename);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		return NULL;
	}
	QByteArray total;
	QByteArray line;
	while (!file.atEnd()) {
		line = file.read(1024);
		total.append(line);
	}
	return QString(total);
}

QString validateFilename(QString filename) {
	QString illegalChars = "\\/:?\"<>|";
	QString::iterator it;
	for (it = filename.begin(); it < filename.end(); it++) {
		if (illegalChars.contains(*it))
			*it = '_';
	}
	return filename;
}

bool writeFile(QString filename, QString content) {
	QFile file(filename);
	if (file.open(QFile::WriteOnly | QFile::Truncate)) {
		QTextStream stream(&file);
		stream << content;
		return true;
	}
	return false;
}

QString substring(QString str, QString start, QString end) {
	if (!start.isEmpty() && str.indexOf(start) >= 0)
		str = str.mid(str.indexOf(start) + start.length(),
					  str.length() - str.indexOf(start) - start.length());
	if (!end.isEmpty() && str.indexOf(end) >= 0)
		str = str.mid(0, str.indexOf(end));
	return str;
}

QString advancedReplace(QString str, QString startReplace, QString endReplace, QString newText) {
	int indexOfStart = str.indexOf(startReplace);
	int indexOfEnd = str.indexOf(endReplace, indexOfStart);
	while (indexOfStart != std::string::npos && indexOfEnd != std::string::npos) {
		str.replace(indexOfStart, indexOfEnd + endReplace.length() - indexOfStart, newText);
		indexOfStart = str.indexOf(startReplace, indexOfStart + newText.length());
		indexOfEnd = str.indexOf(endReplace, indexOfStart + startReplace.length());
	}
	return str;
}

} // namespace MyUtils
