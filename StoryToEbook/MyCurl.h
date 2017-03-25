#pragma once

#include <iostream>
#include <QString>
#include "curl/curl.h"

namespace MyCurl {

size_t writeCallback(char* buf, size_t size, size_t nmemb, void* up);
QString urlToString(QString url);
QString decodeHtml(QString html);

} // namespace MyCurl