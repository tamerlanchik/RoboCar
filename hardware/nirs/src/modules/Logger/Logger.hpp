#ifndef ROBOCAR_LOGGER_H
#define ROBOCAR_LOGGER_H

#ifdef UNIT_TEST
    #include <iostream>
    #include <cstdarg>
#else
    #include <Arduino.h>
#endif

class Logger {
public:
    Logger() : divider(" "), prev_divider(divider) {
#ifndef UNIT_TEST
        Serial.begin(115200);
        delay(200);
#endif
        println('i', "Init serial");
    }

    template<typename ...Params>
    void println(const char level, Params... params) {
        const char *prefix;
        switch (level) {
            case 'd':
                prefix = "D: ";
                break;
            case 'i':
                prefix = "I: ";
                break;
            case 'e':
                prefix = "E: ";
                break;
            default:
                prefix = "";
        }
        print_rec(prefix);
        print_rec(params...);
        print_rec("\n");
    }
    template<typename T, typename... Params>
    void print_rec(T value, Params... params) {
#ifdef UNIT_TEST
        std::cout << value << divider;
#else
        Serial.print(value);
        Serial.print(divider);
#endif
        print_rec(params...);
    }

    void print_rec(const char *value) {
#ifdef UNIT_TEST
        std::cout << value;
#else
        Serial.print(value);
#endif
    }

    void print_rec() {}
    void setDivider(const char* d) {
        prev_divider = divider;
        divider = d;
    }

    void rollbackDivider() {
        divider = prev_divider;
    }

private:
    const char* divider;
    const char* prev_divider;
};
//}

#endif
