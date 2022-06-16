#pragma once
#include <string>

/*
 * Description: The Timer class behaves simply as a timer. When it is created
 * Author:
 * Date:
 */

namespace Timing
{
    class Timer
    {
    protected:
        unsigned long setAtTime;
        unsigned long timerLength;
        bool goneOff;
        String name;
        String msg;

        void goOff()
        {
            String output = "";
            if (name != NULL)
            {
                output += name + " has gone off with message: { \n";
                if (msg != NULL)
                {
                    output += msg + "\n }";
                }
            }
            goneOff = true;
        };

    public:
        Timer(unsigned long setAtTime, unsigned long timerLength)
        {
            this->timerLength = timerLength;
            this->setAtTime = setAtTime;
        };
        Timer(unsigned long setAtTime, unsigned long timerLength, String name)
        {
            this->timerLength = timerLength;
            this->name = name;
            this->setAtTime = setAtTime;
        };
        Timer(unsigned long setAtTime, unsigned long timerLength, String name, String msg)
        {
            this->timerLength = timerLength;
            this->name = name;
            this->msg = msg;
            this->setAtTime = setAtTime;
        };

        String getMessage()
        {
            return msg;
        };
        String getName()
        {
            return name;
        };
        unsigned long getTimerLength()
        {
            return timerLength;
        };
        bool hasGoneOff()
        {
            return goneOff;
        };

        void check()
        {
            if ((millis() - setAtTime) >= timerLength && !goneOff)
            {
                goOff();
            }
        };

        void reset()
        {
            goneOff = false;
            setAtTime = millis();
        }
    };
};
