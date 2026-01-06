#include <http.hpp>
#include <WiFi.h>
#include <HTTPClient.h>

Http::Http(const char* baseUrl) : baseUrl(baseUrl) {}

bool Http::getRoute(const char* stop, String& response) {
    if (WiFi.status() != WL_CONNECTED) {
        return false;
    }

    HTTPClient http;
    String url = String(baseUrl) + "/route/" + stop;
    http.begin(url);
    int code = http.GET();

    if (code <= 0) {
        http.end();
        return false;
    }

    response = http.getString();
    http.end();
    return true;
}