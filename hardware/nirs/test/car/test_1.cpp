#include <ArduinoFake.h>
#include <unity.h>
#include <cmd/car.cpp>
//#include <cmd/car_scheduller.cpp>
#include <car/Chassis/pins.h>
#include <modules/Communicator/SerialCommunicator.h>
#include <string>
#include <unistd.h>
//#define UNIT_TEST

using namespace fakeit;

void test_setup(void)
{
    When(Method(ArduinoFake(), millis)).AlwaysReturn(10000);
    When(Method(ArduinoFake(), pinMode).Using(13, 1)).AlwaysReturn();
    for(Pin pin : motorPins) {
        When(Method(ArduinoFake(), pinMode).Using((byte)pin, 1)).AlwaysReturn();
    }

    setup();
}

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

void test_setup_scheduller(void)
{
    for(Pin pin : motorPins) {
        When(Method(ArduinoFake(), pinMode).Using((byte)pin, 1)).AlwaysReturn();
    }
    int values[] = {13, 214};
    int val = 0b0101;
    init_pinmodes(val, values);

    String data = "K|13 214$";
    Log = new Logger();
    serial_->WillReturnRead(data.c_str(), data.length());
    controller->os.setNowMode(true);

    setup();

    Verify(
            Method(ArduinoFake(), digitalWrite).Using((byte)motorPins[0], byteAt(val, 0))
            + Method(ArduinoFake(), digitalWrite).Using((byte)motorPins[1], byteAt(val, 1))
            + Method(ArduinoFake(), digitalWrite).Using((byte)motorPins[2], byteAt(val, 2))
            + Method(ArduinoFake(), digitalWrite).Using((byte)motorPins[3], byteAt(val, 3))
    ).Once();

    Verify(
            Method(ArduinoFake(), analogWrite).Using((byte)motorPinsPWM[0], 13)
            + Method(ArduinoFake(), analogWrite).Using((byte)motorPinsPWM[1], 214)
    ).Once();
}

void test_loop(void)
{
    Controller* controller = new Controller();
    When(Method(ArduinoFake(), delay)).AlwaysReturn();
    When(Method(ArduinoFake(), digitalWrite)).AlwaysReturn();
//    iteratons = 3;
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

void test_movement_listener() {
    String payload = String("123 212");
    Message msg = Message('K', (Load)payload.c_str());

    MovementListener listener;
    Mock<Controller> ctrlMock;
    Mock<Chassis> chassisMock;
    Chassis *chassis = &(chassisMock.get());
    When(Method(ctrlMock, getChassis)).AlwaysDo([chassis]()->Chassis*{
        return chassis;
    });
    When(Method(chassisMock, setValue2)).AlwaysReturn();

    controller = &(ctrlMock.get());
    listener(msg);
    Verify(Method(ctrlMock, getChassis)).Once();
    Verify(Method(chassisMock, setValue2).Using(123, 212)).Once();
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
//    RUN_TEST(test_movement_listener);
    RUN_TEST(test_setup_scheduller);

    UNITY_END();

    return 0;
}