#include "MyCurl.h"

namespace MyCurl {

std::string html; // will hold the url's contents
size_t writeCallback(char* buf, size_t size, size_t nmemb,
					 void* up) { // callback must have this declaration buf is a pointer to the data
								 // that curl has for us, size*nmemb is the size of the buffer
	for (int c = 0; c < size * nmemb; c++) {
		html.push_back(buf[c]);
	}
	return size * nmemb; // tell curl how many bytes we handled
}
QString urlToString(QString url) {
	html = "";
	CURL* curl;
	curl_global_init(CURL_GLOBAL_ALL);
	curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, FALSE);
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
	curl_easy_setopt(curl, CURLOPT_TIMEOUT, 20L);
	curl_easy_setopt(curl, CURLOPT_URL, url.toStdString().c_str());
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &writeCallback);
	curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L); // tell curl to output its progress
	curl_easy_perform(curl);
	curl_easy_cleanup(curl);
	curl_global_cleanup();
	return QString::fromLocal8Bit(html.c_str());
}

QString decodeHtml(QString html) {
	html = html.replace("&lsquo;", "‘");
	html = html.replace("&rsquo;", "’");
	html = html.replace("&ldquo;", "“");
	html = html.replace("&rdquo;", "”");
	html = html.replace("&amp;", "&");
	html = html.replace("â€“", "–");
	html = html.replace("âˆš", "v");
	html = html.replace("&#33;", "!");
	html = html.replace("&#033;", "!");
	html = html.replace("&#38;", "&");
	html = html.replace("&#038;", "&");
	html = html.replace("&#39;", "'");
	html = html.replace("&#039;", "'");
	html = html.replace("&#333;", "ō");
	html = html.replace("&#8730;", "√");
	return html;
}

} // namspace MyCurl