#ifndef TEXT_HPP
#define TEXT_HPP

#include <ArduinoJson.h>

class Text {
    private:
        String response;
        JsonDocument json;
        DeserializationError error;
        int size;
        char* firstBuffer;
        char* secondBuffer;
        char* bottomBuffer;
        int curr;
        
    public:
        Text(String response, int size);
        ~Text();
        const char* getFirstBuffer();
        const char* getSecondBuffer();
        const char* getBottomBuffer();
        DeserializationError getError();
};

#endif
