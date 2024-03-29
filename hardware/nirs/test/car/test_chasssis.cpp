#include <ArduinoFake.h>
#include <unity.h>
#include <car/Chassis/pins.h>
#include <car/Chassis/Chassis.h>
#include <string>
#include <modules/Logger/Logger.hpp>
#include <lib.h>

using namespace fakeit;

Logger* Log;

void init() {
    Log = new Logger();
}

// пишем в 4 цифровых и 2 аналоговых пина (опционльно)
void init_pinmodes(int digital, int* analog = nullptr) {
    for (size_t i = 0; i < 4; i++) {
        When(Method(ArduinoFake(), digitalWrite).Using((byte)motorPins[i], byteAt(digital, i))).AlwaysReturn();
    }
    if (!analog) {
        return;
    }
//    printf("L=%d|%d, R=%d|%d\n", motorPinsPWM[(int)Pins::AL], abs(analog[0]), motorPinsPWM[(int)Pins::AR], abs(analog[1]));
    When(Method(ArduinoFake(), analogWrite).Using((byte)motorPinsPWM[(int)Pin::AL], abs(analog[0]))).AlwaysReturn();
    When(Method(ArduinoFake(), analogWrite).Using((byte)motorPinsPWM[(int)Pin::AR], abs(analog[1]))).AlwaysReturn();
}

void test_init(void)
{
    for(Pin pin : motorPins) {
        When(Method(ArduinoFake(), pinMode).Using((byte)pin, 1)).AlwaysReturn();
    }
    auto chassis = new Chassis();
    chassis->init();
    for (auto pin : motorPins)
        Verify(Method(ArduinoFake(), pinMode).Using((byte)pin, OUTPUT)).Once();
}

void test_write_values() {
    for(int val = 0; val < 16; ++val) {
        ArduinoFakeReset();
        init_pinmodes(val);

        Chassis().setMotorValues(static_cast<Movement>(val));

        Verify(
                Method(ArduinoFake(), digitalWrite).Using((byte)motorPins[0], byteAt(val, 0))
                + Method(ArduinoFake(), digitalWrite).Using((byte)motorPins[1], byteAt(val, 1))
                + Method(ArduinoFake(), digitalWrite).Using((byte)motorPins[2], byteAt(val, 2))
                + Method(ArduinoFake(), digitalWrite).Using((byte)motorPins[3], byteAt(val, 3))
        ).Once();
    }
}

void test_set_value() {
    struct Case {
        const char* name;
        int val[2];
        int analogRes[2];
        int digitalRes;
    };
//    const Case cases[] = {
//        {
//            "Forward 1",
//            {100, 0},
//            {100, 100},
//            {Chassis::movements[Forward]}
//        },
//        {
//            "Right",
//            {10, 50},
//            {50, 50},
//            {Chassis::movements[Right]}
//        },
//    };
    const Case cases[] = {
            {
                    "Forward 1",
                    {100, 0},
                    {100, 0},
                    {add((char)Chassis::MotorMov::FORWARD, 0)}
            },
            {
                    "Right 1",
                    {100, -70},
                    {100, 70},
                    {add((char)Chassis::MotorMov::FORWARD, (char)Chassis::MotorMov::BACKWARD)}
            },
    };
    for(auto test : cases) {
        std::cout << "Case: " << test.name << std::endl;
        ArduinoFakeReset();
        // setup
        init_pinmodes(test.digitalRes, test.analogRes);

        // call
        Chassis().setValue2(test.val[0], test.val[1]);

        //verify
        // порядок неважен
        Verify(
                Method(ArduinoFake(), digitalWrite).Using((byte)motorPins[0], byteAt(test.digitalRes, 0))
                + Method(ArduinoFake(), digitalWrite).Using((byte)motorPins[1], byteAt(test.digitalRes, 1))
                + Method(ArduinoFake(), digitalWrite).Using((byte)motorPins[2], byteAt(test.digitalRes, 2))
                + Method(ArduinoFake(), digitalWrite).Using((byte)motorPins[3], byteAt(test.digitalRes, 3))
        ).Once();
        Verify(
                Method(ArduinoFake(), analogWrite).Using((byte)motorPins[4], test.analogRes[0])
                + Method(ArduinoFake(), analogWrite).Using((byte)motorPins[5], test.analogRes[1])
        ).Once();
    }
}

void test_byteAt() {
    struct Case {
        int input[2];
        byte res;
    };
    const Case tests[] = {
        {1, 0, 1},
        {0b100, 1, 0},
        {0b01000, 3, 1},
    };
    for(auto test : tests) {
        auto res = byteAt(test.input[0], test.input[1]);
        TEST_ASSERT_EQUAL(test.res, res);
    }
}

//void test_add() {
//    int res = (int)Pins::AL;
//    res = (int)Pins::AR;
//    res = (int)Pins::D1;
//    res=(int)Pins::D2;
//    res = (int)Pins::D3;
//    int r = 1;
//}

void setUp(void)
{
    ArduinoFakeReset();
    init();
}

int main(int argc, char **argv)
{
//    test_add();
//    return 0;
    UNITY_BEGIN();

//    RUN_TEST(test_byteAt);
//    RUN_TEST(test_init);
//    RUN_TEST(test_write_values);
    RUN_TEST(test_set_value);


    UNITY_END();

    return 0;
}