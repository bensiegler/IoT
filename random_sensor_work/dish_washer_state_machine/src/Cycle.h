#pragma once

#include <WasherStates.h>

class Cycle
{
private:
    WasherStates washType;
    WasherStates dryType;
    int washTime;
    int dryTime;

public:
    Cycle(WasherStates washType, WasherStates dryType, int washTime, int dryTime)
    {
        this->washType = washType;
        this->dryType = dryType;
        this->washTime = washTime;
        this->dryTime = dryTime;
    };

    WasherStates getWashType()
    {
        return washType;
    };

    WasherStates getDryType()
    {
        return dryType;
    }

    int getWashTime()
    {
        return washTime;
    }

    int getDryTime()
    {
        return dryTime;
    }
};