#pragma once
#include <string.h>

class Event
{
private:
    String eventName;
    unsigned long lastOccuredAtTime;
    unsigned long shouldHappenEvery;

public:
    Event();

    Event(unsigned long lastOccuredAt, unsigned long shouldHappenEveryXMillis)
    {
        lastOccuredAtTime = lastOccuredAt;
        shouldHappenEvery = shouldHappenEveryXMillis;
    };

    Event(unsigned long lastOccuredAt, unsigned long shouldHappenEveryXMillis, String eventNameStr)
    {
        lastOccuredAtTime = lastOccuredAt;
        eventName = eventNameStr;
        shouldHappenEvery = shouldHappenEveryXMillis;
    };

    unsigned long getLastOccuredAtTime();
    unsigned long getShouldHappenEvery();
    unsigned long getEventName();

    void setLastOccuredAtTime();
    void setShouldHappenEvery();

    void occured()
    {
        if (eventName != NULL)
        {
            Serial.println(eventName + " has occured");
        }
        lastOccuredAtTime = millis();
    };

    bool isDueToOccur()
    {
        if ((millis() - lastOccuredAtTime) > shouldHappenEvery)
        {
            return true;
        }
        return false;
    };
};