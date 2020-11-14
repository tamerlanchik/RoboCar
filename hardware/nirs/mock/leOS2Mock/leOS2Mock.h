//
// Created by andrey on 04.11.2020.
//

#ifndef ROBOCAR_LEOS2MOCK_H
#define ROBOCAR_LEOS2MOCK_H
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>

//constants
const uint8_t PAUSED = 0;
const uint8_t SCHEDULED = 1; //0b00000001
const uint8_t SCHEDULED_IMMEDIATESTART = 5; //0b00000101
const uint8_t IMMEDIATESTART = SCHEDULED_IMMEDIATESTART; //alias for previous
const uint8_t ONETIME = 2;
const uint8_t NOW = 10;

class scheduller;

class leOS2Mock {
public:
    //public methods
    leOS2Mock();
    void begin(uint16_t resetTimeout = 0);
    uint8_t addTask(void (*)(void), unsigned long, uint8_t taskStatus = SCHEDULED);
    uint8_t removeTask(void (*)(void));
    uint8_t pauseTask(void (*)(void));
    uint8_t restartTask(void (*)(void));
    uint8_t modifyTask(void (*)(void), unsigned long, uint8_t oneTimeTask = 0);
    uint8_t getTaskStatus(void (*)(void));
    uint32_t convertMs(uint32_t);
    void haltScheduler(void);
    void restartScheduler(void);
    void reset(void);
    void setNowMode(bool);
//    scheduller* getScheduller();
private:
    //private methods
    void setWDT();
    uint8_t setTask(void (*)(void), uint8_t, unsigned long taskInterval = 0);
    bool need_now;
};

class scheduler {
public:
    void init(void (*)(int));
    void halt();
    void restart();
    void needTime(bool);
private:
    struct itimerval timer;
    struct timeval start;
    struct timeval interval;
    bool needTime();
};


#endif //ROBOCAR_LEOS2MOCK_H
