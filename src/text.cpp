#include <text.hpp>

Text::Text(String response, int size) :response(response), error(deserializeJson(json, response)), size(size), curr(0) {
    firstBuffer = new char[size + 1];
    secondBuffer = new char[size + 1];
    bottomBuffer = new char[size + 1];

    if (json["upcoming"].size() == 0) {
        const char* first = "No Scheduled";
        const char* second = "Departures";
        strcpy(firstBuffer, first);
        strcpy(secondBuffer, second);
        bottomBuffer[0] = '\0';
        return;
    }

    const char* bus = json["upcoming"][0]["BusName"] | "";
    const char* destination = json["upcoming"][0]["Destination"] | "";
    const char* timeFromNow = json["upcoming"][0]["TimeFromNow"] | "";


    snprintf(firstBuffer, size + 1, "%-*s%*s", size - (int)strlen(timeFromNow), bus, (int)strlen(timeFromNow), timeFromNow);
    
    strncpy(secondBuffer, destination, size);
    secondBuffer[size] = '\0';

    bottomBuffer[0] = '\0';
}

Text::~Text() {
    delete[] firstBuffer;
    delete[] secondBuffer;
    delete[] bottomBuffer;
}

const char* Text::getFirstBuffer() {
    return firstBuffer;
}

const char* Text::getSecondBuffer() {
    return secondBuffer;
}

const char* Text::getBottomBuffer() {
    return bottomBuffer;
}

DeserializationError Text::getError() {
    return error;
}

