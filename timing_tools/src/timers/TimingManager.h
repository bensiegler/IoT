#pragma once
#include <string>
#include <vector>
#include <typeinfo>
#include <optional>

#include "Timer.h"
#include "Trigger.h"
#include "InterruptableTrigger.h"
#include "PassiveTimer.h"

using namespace std;

namespace Timing
{
    class TimingManager
    {
    private:
        vector<Timer> activeTimers;
        // would like to merge this into active timers and differentiate by object type
        // in the update method. This would be a lot more elegant, but I need help with
        // with typeid()
        vector<PassiveTimer> passiveTimers;

    protected:
        // optional<Timer> getTimerByName(String name)
        // {
        //     optional<Timer> optionalTimer;
        //     for (auto i = activeTimers.begin(); i != activeTimers.end(); ++i)
        //     {
        //         if ((*i).getName() == name)
        //         {
        //             optionalTimer.emplace(*i);
        //         }
        //     }

        //     // for (auto i = passiveTimers.begin(); i != passiveTimers.end(); ++i)
        //     // {
        //     //     if ((*i).getName() == name)
        //     //     {
        //     //         return *i;
        //     //     }
        //     // }

        //     return optionalTimer;

        // };

        vector<Timer> getActiveTimers()
        {
            return activeTimers;
        }

        vector<PassiveTimer> getPassiveTimers()
        {
            return passiveTimers;
        }

    public:
        void update()
        {
            for (auto i = activeTimers.begin(); i != activeTimers.end(); ++i)
            {
                Timer t = *i;
                t.check();
                if (t.hasGoneOff())
                {
                    activeTimers.erase(i);
                }
            }
        }

        Timer* createNewTimer(unsigned long timerLength, String name, String msg)
        {
            Timer t = Timer(millis(), timerLength, name, msg);
            activeTimers.push_back(t);
            return &t;
        }

        Timer* createNewTimer(unsigned long timerLength, String name)
        {
            Timer t = Timer(millis(), timerLength, name);
            activeTimers.push_back(t);
            return &t;
        }

        Timer* createNewTimer(unsigned long timerLength)
        {
            Timer t = Timer(millis(), timerLength);
            activeTimers.push_back(t);
            return &t;
        }
    };
};
