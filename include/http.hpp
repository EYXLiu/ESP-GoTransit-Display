#ifndef HTTP_HPP
#define HTTP_HPP

#include <Arduino.h>

class Http {
    private:
        String baseUrl;
    public:
        Http(const char* baseUrl);
        bool getRoute(const char* stop, String& response);
};

#endif
