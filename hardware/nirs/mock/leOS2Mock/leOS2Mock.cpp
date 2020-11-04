/* This file is part of leOS2 library.
   Please check the README file and the notes
   inside the leOS2.h file
*/

//include required libraries
#include <cstdint>
#include "leOS2Mock.h"

//global settings - modify them to change the leOS characteristics
const uint8_t MAX_TASKS = 9; //max allowed tasks -1 (i.e.: 9 = 10-1)
#ifdef SIXTYFOUR_MATH
volatile unsigned long long _ticksCounter = 0; //use a 64-bit counter so it will overflow after 584,942,417 years!
#else
volatile unsigned long _ticksCounter = 0; //use a 32bit counter, so max intervals cannot exceed 49.7 days
#endif
//set your max interval here (max 2^32-1) - default 225000 ticks (1 hour)
#define MAX_TASK_INTERVAL 225000UL


//tasks variables
struct leOS_core {
    void (*taskPointer)(void); //used to store the pointers to user's tasks
    volatile unsigned long userTasksInterval; //used to store the interval between each task's run
//used to store the next time a task will have to be executed
#ifdef SIXTYFOUR_MATH
    volatile unsigned long long plannedTask;
#else
    volatile unsigned long plannedTask;
#endif
    volatile uint8_t taskIsActive; //used to store the status of the tasks
};
leOS_core tasks[MAX_TASKS];
volatile uint8_t _numTasks; //the number of current running tasks
volatile uint8_t _initialized;
volatile uint16_t _wdtResetTimeout;
volatile uint8_t _taskIsRunning;
volatile uint16_t _maxTimeouts;

scheduler sced;

void ISR(int);

//class constructor
leOS2Mock::leOS2Mock(void) {
    _initialized = 0;
}


//class initialization
void leOS2Mock::begin(uint16_t resetTimeout) {
    //store the # of timeouts before to reset the chip
    _wdtResetTimeout = resetTimeout;
    setWDT(); //initialize the WDT
    _initialized = 1;
    _numTasks = 0;
    _taskIsRunning = 0;
}


//add a task to the scheduler
uint8_t leOS2Mock::addTask(void (*userTask)(void), unsigned long taskInterval, uint8_t taskStatus) {
    if ((_initialized == 0) || (_numTasks == MAX_TASKS)) { //max number of allowed tasks reached
        return 1;
    }

    if ((taskInterval < 1) || (taskInterval > MAX_TASK_INTERVAL)) {
        taskInterval = 1; //1 tick/16 ms by default
    }
    //check if taskStatus is valid
    if (taskStatus > SCHEDULED_IMMEDIATESTART) {
        taskStatus = SCHEDULED;
    }
    //add the task to the scheduler
    sced.halt();
//    SREG &= ~(1<<SREG_I); //halt the scheduler
    tasks[_numTasks].taskPointer = *userTask;
    tasks[_numTasks].taskIsActive = taskStatus & 0b00000011; //I get only the first 2 bits - I don't need the IMMEDIATESTART bit
    tasks[_numTasks].userTasksInterval = taskInterval;
    //no wait if the user wants the task up and running once added...
    //...otherwise we wait for the interval before to run the task
    tasks[_numTasks].plannedTask = _ticksCounter + ((taskStatus & 0b00000100)? 0 : taskInterval);
    _numTasks++;
    sced.restart();
//    SREG |= (1<<SREG_I); //restart the scheduler
    return 0;
}


//pause a specific task
uint8_t leOS2Mock::pauseTask(void (*userTask)(void)) {
    return (setTask(userTask, 0));
}


//restart a specific task
uint8_t leOS2Mock::restartTask(void (*userTask)(void)) {
    return (setTask(userTask, 1));
}


//modify an existing task
uint8_t leOS2Mock::modifyTask(void (*userTask)(void), unsigned long taskInterval, uint8_t oneTimeTask) {
    if ((oneTimeTask < SCHEDULED) && (oneTimeTask > ONETIME)) {
        oneTimeTask = 0;
    }

    if ((taskInterval < 1) || (taskInterval > MAX_TASK_INTERVAL)) {
        taskInterval = 1; //1 tick/16 ms by default
    }

    //modify the task into the scheduler
    sced.halt();
//    SREG &= ~(1<<SREG_I); //halt the scheduler
    uint8_t tempI = 0;
    uint8_t _done = 1;
    do {
        if (tasks[tempI].taskPointer == *userTask) { //found the task
            tasks[tempI].userTasksInterval = taskInterval;
            if (oneTimeTask != 0) {
                tasks[tempI].taskIsActive = oneTimeTask;
            }
            tasks[tempI].plannedTask = _ticksCounter + taskInterval;
            _done = 0;
            break;
        }
        tempI++;
    } while (tempI < _numTasks);
    sced.restart();
//    SREG |= (1<<SREG_I); //restart the scheduler
    return _done;

}


//manage the tasks' status
uint8_t leOS2Mock::setTask(void (*userTask)(void), uint8_t tempStatus, unsigned long taskInterval) {
    if ((_initialized == 0) || (_numTasks == 0)) {
        return 1;
    }

    sced.halt();
//    SREG &= ~(1<<SREG_I); //halt the scheduler
    uint8_t tempI = 0;
    do {
        if (tasks[tempI].taskPointer == *userTask) {
            tasks[tempI].taskIsActive = tempStatus;
            if (tempStatus == SCHEDULED) {
                if (taskInterval == 0) {
                    tasks[tempI].plannedTask = _ticksCounter + tasks[tempI].userTasksInterval;
                } else {
                    tasks[tempI].plannedTask = _ticksCounter + taskInterval;
                }
            }
            break;
        } else {
            tempI++;
        }
    } while (tempI < _numTasks);
    sced.restart();
//    SREG |= (1<<SREG_I); //restart the scheduler
    return 0;
}


//remove a task from the scheduler
uint8_t leOS2Mock::removeTask(void (*userTask)(void)) {
    if ((_initialized == 0) || (_numTasks == 0)) {
        return 1;
    }

    sced.halt();
//    SREG &= ~(1<<SREG_I); //halt the scheduler
    uint8_t tempI = 0;
    do {
        if (tasks[tempI].taskPointer == *userTask) {
            if ((tempI + 1) == _numTasks) {
                _numTasks--;
            } else if (_numTasks > 1) {
                for (uint8_t tempJ = tempI; tempJ < _numTasks; tempJ++) {
                    tasks[tempJ].taskPointer = tasks[tempJ + 1].taskPointer;
                    tasks[tempJ].taskIsActive = tasks[tempJ + 1].taskIsActive;
                    tasks[tempJ].userTasksInterval = tasks[tempJ + 1].userTasksInterval;
                    tasks[tempJ].plannedTask = tasks[tempJ + 1].plannedTask;
                }
                _numTasks -= 1;
            } else {
                _numTasks = 0;
            }
            break;
        } else {
            tempI++;
        }
    } while (tempI < _numTasks);
    sced.restart();
//    SREG |= (1<<SREG_I); //restart the scheduler
    return 0;
}


//check if a task is running
uint8_t leOS2Mock::getTaskStatus(void (*userTask)(void)) {
    if ((_initialized == 0) || (_numTasks == 0)) {
        return -1;
    }

    uint8_t tempJ = 255; //return 255 if the task was not found (almost impossible)
    sced.halt();
//    SREG &= ~(1<<SREG_I); //halt the scheduler
    uint8_t tempI = 0;
    //look for the task
    do {
        if (tasks[tempI].taskPointer == *userTask) {
            //return its current status
            tempJ = tasks[tempI].taskIsActive;
            break;
        }
        tempI++;
    } while (tempI < _numTasks);
    sced.restart();
//    SREG |= (1<<SREG_I); //restart the scheduler
    return tempJ; //return the task status
}


//convert milliseconds in ticks
uint32_t leOS2Mock::convertMs(uint32_t tempMs) {
    if (tempMs < 16) {
        return 1;
    }
    tempMs = tempMs >> 4;
    if (tempMs > MAX_TASK_INTERVAL) {
        return MAX_TASK_INTERVAL;
    } else {
        return tempMs;
    }
}


//reset the MCU
void leOS2Mock::reset(void) {
    sced.restart();
//    wdt_disable();
//    wdt_enable(WDTO_2S);
//    while(1){}; //wait for reset
}

/*
    **************************************************************
    * WARNING - The following code contains the core of leOS2:   *
    * do not modify it unless you exactly know what you're doing *
    **************************************************************
*/

//ISR (Interrupt Service Routine) called by the timer's overflow:
//interrupt-driven routine to run the tasks - this ISR is not atomic
//so other ISRs can interrupt it
void ISR(int signum) {

    _ticksCounter++; //increment the ticks counter

    //check if the next timeout of the WDT an interrupt should be
    //called or a reset should be executed
    if (_wdtResetTimeout ) {
//        _WD_CONTROL_REG |= (1<<WDIE); //another interrupt, please...
        //check if a task is already running
        if (_taskIsRunning) {
            //check if the maximum # of timeouts has been reached
            _maxTimeouts--;
            return;
        }
    }

    //THIS IS THE SCHEDULER!
    uint8_t tempI = 0; //set the pointer to the tasks to 0
    void (*savedJobPointer)(void); //create a task pointer
    while (tempI < _numTasks) {
        if (tasks[tempI].taskIsActive > 0 ) { //the task is running
            //check if it's time to execute the task
#ifdef SIXTYFOUR_MATH
            if (_ticksCounter > tasks[tempI].plannedTask) {
#else
            if ((long)(_ticksCounter - tasks[tempI].plannedTask) >=0) { //this trick overruns the overflow of _ticksCounter
#endif
                //prepare the counters to monitor if a task will freeze
                _maxTimeouts = _wdtResetTimeout;
                _taskIsRunning = 1;
                savedJobPointer = tasks[tempI].taskPointer; //store its pointer
                savedJobPointer(); //call the task
                //reset the counters
                _taskIsRunning = 0;

                if (tasks[tempI].taskIsActive == ONETIME) {
                    //re-determine the task's position in case it's changed
                    tempI = 0;
                    do {
                        if (tasks[tempI].taskPointer == savedJobPointer) { //found the task
                            break;
                        } else {
                            tempI++;
                        }
                    } while (tempI <= _numTasks);
                    //remove it from the scheduler
                    if (tempI == _numTasks) {
                        _numTasks--;
                    } else if (_numTasks > 1) {
                        for (uint8_t tempJ = tempI; tempJ < _numTasks; tempJ++) {
                            tasks[tempJ].taskPointer = tasks[tempJ + 1].taskPointer;
                            tasks[tempJ].taskIsActive = tasks[tempJ + 1].taskIsActive;
                            tasks[tempJ].userTasksInterval = tasks[tempJ + 1].userTasksInterval;
                            tasks[tempJ].plannedTask = tasks[tempJ + 1].plannedTask;
                        }
                        _numTasks -= 1;
                    } else {
                        _numTasks = 0;
                    }
                } else {
                    //let's schedule next start
                    tasks[tempI].plannedTask = _ticksCounter + tasks[tempI].userTasksInterval;
                }
            }
        }
        tempI++;
    }
}



//
//private methods
//

/*
************************************************************пре
WARNING!! DO NOT MODIFY THE FOLLOWING CODE IF YOU DON'T KNOW
WHAT YOU'RE DOING! YOU COULD PUT YOUR MICROCONTROLLER IN A
NEVERENDING RESET!!
************************************************************
*/

//set the WatchDog Timer
void leOS2Mock::setWDT() {
    sced.init(ISR);
}


//halt the scheduler
void leOS2Mock::haltScheduler() {
    sced.halt();
}


//restart the scheduler
void leOS2Mock::restartScheduler() {
    if (_initialized) {
        setWDT();
    }
}

//-------------------

void scheduler::init(void (*timer_handler)(int)) {
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = timer_handler;
    sigaction(SIGALRM, &sa, NULL);

    // 16 ms for AVR uses WatchDog timer
    const int us_interval = 16*1000;

    this->start = {0, us_interval};
    this->interval = {0, us_interval};

    this->restart();
}
void scheduler::halt() {
    this->timer.it_value.tv_sec = 0;
    this->timer.it_value.tv_usec = 0;

    setitimer(ITIMER_REAL, &timer, NULL);
}

void scheduler::restart() {
    this->timer.it_value = this->start;
    this->timer.it_interval = this->interval;

    setitimer(ITIMER_REAL, &timer, NULL);
}

