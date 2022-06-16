#pragma once
#include "Timer.h"

namespace Timing {
    class PausableTimer: public Timer {
        private:
            bool paused;
            unsigned long pauseStartedAt;

        public:
            PausableTimer(unsigned long timerLength) : Timer(millis(), timerLength){};
            PausableTimer(unsigned long timerLength, String name) : Timer(millis(), timerLength, name){};
            PausableTimer(unsigned long timerLength, String name, String msg) : Timer(millis(), timerLength, name, msg){};

            //want to get rid of this method but cant bcs Trigger cant seem to access Timer::goOff
            void goOff() {
                if(!paused) {
                    Timer::goOff();
                }
            };
            void check() {
                if(!paused) {
                    Timer::check();
                }
            };
            void pause() {
                pauseStartedAt = millis();
                paused = true;
            };
            void resume() {
                Timer::timerLength += millis() - pauseStartedAt;
                paused = false;
            };
    };
};