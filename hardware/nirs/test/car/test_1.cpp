#include <ArduinoFake.h>
#include <unity.h>
#include <cmd/car.cpp>
#include <car/Chassis/pins.h>

using namespace fakeit;

void test_setup(void)
{
    When(Method(ArduinoFake(), millis)).AlwaysReturn(10000);
    When(Method(ArduinoFake(), pinMode).Using(9, 1)).AlwaysReturn();
    for(byte pin : motorPins) {
        When(Method(ArduinoFake(), pinMode).Using(pin, 1)).AlwaysReturn();
    }

    setup();

    Verify(Method(ArduinoFake(), pinMode).Using(9, OUTPUT)).Once();
}

void test_loop(void)
{
//    When(Method(ArduinoFake(), digitalWrite)).AlwaysReturn();
//    When(Method(ArduinoFake(), delay)).AlwaysReturn();]
    When(Method(ArduinoFake(), millis)).AlwaysReturn(10010);
//    When(Method(ArduinoFake(Serial), print)).Return();
//    When(getArduinoFakeContext()->Mocks->Serial.template stub<1>(
//            &std::remove_reference<decltype(getArduinoFakeContext()->Mocks->Serial.get())>::type::print).setMethodDetails(
//            "ArduinoFake(Serial)", "print"))

    loop();

//    Verify(Method(ArduinoFake(), digitalWrite).Using(LED_BUILTIN, HIGH)).Once();
//    Verify(Method(ArduinoFake(), digitalWrite).Using(LED_BUILTIN, LOW)).Once();
//    Verify(Method(ArduinoFake(), delay).Using(100)).Exactly(2_Times);
}

void setUp(void)
{
    ArduinoFakeReset();
}

int main(int argc, char **argv)
{
    UNITY_BEGIN();

    RUN_TEST(test_setup);
//    RUN_TEST(test_loop);

    UNITY_END();

    return 0;
}