#include <string.h>

class Trigger
{
private:
    String eventName;
    unsigned long shouldHappenEvery;
    bool isActive = true;
    void (*foo)();

public:
    Trigger();

    Trigger(unsigned long lastOccuredAt, unsigned long shouldHappenEveryXMillis, void (*foop)())
    {
        lastOccuredAtTime = lastOccuredAt;
        shouldHappenEvery = shouldHappenEveryXMillis;
        foo = foop;
    };

    Trigger(unsigned long lastOccuredAt, unsigned long shouldHappenEveryXMillis, String eventNameStr, void (*foop)())
    {
        lastOccuredAtTime = lastOccuredAt;
        eventName = eventNameStr;
        shouldHappenEvery = shouldHappenEveryXMillis;
        foo = foop;
    };

    Trigger(unsigned long lastOccuredAt, unsigned long shouldHappenEveryXMillis, String eventNameStr, void (*foop)(), bool active)
    {
        lastOccuredAtTime = lastOccuredAt;
        eventName = eventNameStr;
        shouldHappenEvery = shouldHappenEveryXMillis;
        foo = foop;
        isActive = active;
    };

    unsigned long getLastOccuredAtTime()
    {
        return lastOccuredAtTime;
    };
    unsigned long getShouldHappenEvery()
    {
        return shouldHappenEvery;
    };
    String getEventName()
    {
        return eventName;
    };
    bool getIsActive()
    {
        return isActive;
    };

    void setIsActive(bool active)
    {
        isActive = active;
    };
    void setLastOccuredAtTime(unsigned long lastOccuredAt)
    {
        lastOccuredAtTime = lastOccuredAt;
    };
    void setShouldHappenEvery(unsigned long shouldHappenEveryX)
    {
        shouldHappenEvery = shouldHappenEveryX;
    };

    void occured()
    {
        if (eventName != NULL)
        {
            Serial.println(eventName + " has occured");
        }
        lastOccuredAtTime = millis();
    };

    void check()
    {
        if (((millis() - lastOccuredAtTime) > shouldHappenEvery) && isActive)
        {
            foo();
            occured();
        }
    };
};