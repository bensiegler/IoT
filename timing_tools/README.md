# timing_tools

## Intro

This is a set of classes to abstract away & simplify a host of Timing & Trigger structures for the argon microprocessor. At this time, there is a glitch in the argon software that causes an Assertion Error when the TimingManager is used. However, each timer class can still be used be used individually, avoiding the TimerManager class. I'm working on a solution. 

## With TimingManager (DEV)

To create and manage timers/triggers using the TimingManager, create an instance of said class and call the `update()` method on each iteration of the `loop()`. From this point on the TimingManager is ready to handle external requests for timers and triggers. 

## Without TimingManager

Without the timing manager, you must declare & `update()` each timer individually.

## EventChain

I'm working on getting pre-defined & mutible event chains to work with the TimingManager. Each trigger or timer would be followed by a another creating a chain of events and behavior, stored in an elegant way, ready to be called whenever.

Standby while I work on this stuff. I'm hoping that once I get it all working I can add it as a Particle library.  




