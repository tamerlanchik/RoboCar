#include <ArduinoFake.h>
#include <unity.h>
//#include <cmd/car.cpp>
#include <cmd/car_scheduller.cpp>
#include <car/Chassis/pins.h>
#include <modules/Communicator/SerialCommunicator.h>
#include <string>
#include <unistd.h>

using namespace fakeit;

void test_setup(void)
{
    When(Method(ArduinoFake(), millis)).AlwaysReturn(10000);
    When(Method(ArduinoFake(), pinMode).Using(13, 1)).AlwaysReturn();
    for(byte pin : motorPins) {
        When(Method(ArduinoFake(), pinMode).Using(pin, 1)).AlwaysReturn();
    }

    setup();
}

void test_loop(void)
{
    When(Method(ArduinoFake(), delay)).AlwaysReturn();
    When(Method(ArduinoFake(), digitalWrite)).AlwaysReturn();
    iteratons = 3;
    serial_->WillReturnRead("L|Fuck$", 10);
    controller->getCommunicator()->read(true);
    Verify(Method(ArduinoFake(), digitalWrite).Using(13, 1)).Once();

    serial_->WillReturnRead("L|Coc$", 10);
    controller->getCommunicator()->read(true);
    Verify(Method(ArduinoFake(), digitalWrite).Using(13, 0)).Once();

    String val3 = "L|Fucqqqqqk$";
    serial_->WillReturnRead(val3.c_str(), val3.length());
    controller->getCommunicator()->read(true);
    Verify(Method(ArduinoFake(), digitalWrite).Using(13, 1)).Twice();
//    loop();
//    Verify(Method(ArduinoFake(), digitalWrite).Using(13, 1)).Once();
//    Verify(Method(ArduinoFake(), digitalWrite).Using(13, 0)).Once();
//    Verify(Method(ArduinoFake(), digitalWrite).Using(LED_BUILTIN, HIGH)).Once();
//    Verify(Method(ArduinoFake(), digitalWrite).Using(LED_BUILTIN, LOW)).Once();
//    Verify(Method(ArduinoFake(), delay).Using(100)).Exactly(2_Times);
}

void test_sceduller() {
    When(Method(ArduinoFake(), pinMode)).AlwaysReturn();
    setup();
    String val3 = "L|Fucqqqqqk$";
    serial_->WillReturnRead(val3.c_str(), val3.length());
    Verify(Method(ArduinoFake(), pinMode).Using(13, OUTPUT)).Once();
//    car_scheduller::iteratons = 3;
//    car_scheduller::loop();
//    When(Method(ArduinoFake(), digitalWrite)).AlwaysReturn();
//    sleep(4);
    while(1) {}
//    Verify(Method(ArduinoFake(), digitalWrite).Using(13, 1)).Twice();
//    Verify(Method(ArduinoFake(), digitalWrite).Using(13, 0)).Once();
}

void setUp(void)
{
    ArduinoFakeReset();
}

int main(int argc, char **argv)
{
    UNITY_BEGIN();

//    RUN_TEST(test_setup);
//    RUN_TEST(test_loop);
    RUN_TEST(test_sceduller);

    UNITY_END();

    return 0;
}