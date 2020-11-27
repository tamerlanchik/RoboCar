#include <modules/CircularBuffer/CircularBuffer.h>
#include <ArduinoFake.h>
#include <unity.h>
#include <string>
#include <car/Tachometr/Tachometr.h>
#include <modules/Logger/Logger.hpp>

using namespace fakeit;
Logger* Log;

class NewTachometr : public Tachometr {
public:
    NewTachometr(int curr) : Tachometr(curr) {}
    void put(int val) {
        Tachometr::buffer.storage[curr].handleInterr(val);
    }
};

//int main() {
//    CircularBuffer<int, 5> buffer;
//    buffer.put(1);
//    buffer.put(2);
//    buffer.put(3);
//    buffer.put(4);
//    buffer.put(5);
//    buffer.put(6);
//    for(auto i = buffer.begin(); i != buffer.end(); ++i) {
//        printf("%d\n", *i);
//    }
//}

void test_1() {
    String s = "0.6";
    float d = atof(s.c_str());
    Log = new Logger();
    When(Method(ArduinoFake(), attachInterrupt)).AlwaysReturn();
    When(Method(ArduinoFake(), micros)).AlwaysReturn(10000000);
    When(Method(ArduinoFake(), cli)).AlwaysReturn();
    When(Method(ArduinoFake(), sei)).AlwaysReturn();
    NewTachometr* t = new NewTachometr(0);
    t->start<0>(2);
    const int times[] = {34887036, 34898000, 34905524, 34916944, 34924688, 34937172, 34958712, 34967368, 34981092, 34990292, 35006524};
    TachoData data[sizeof(times)];
    int i = 0;
    for(int time : times) {
        t->put(time);
        data[i++] = t->getData();
    }

//    Tachometr::buffer.mPath[0] = 132;
//    TachoData d = t->getData();
    int a = 0;

}


void setUp(void)
{
    ArduinoFakeReset();
}

int main(int argc, char **argv)
{
//    test_add();
//    return 0;
    UNITY_BEGIN();

//    RUN_TEST(test_byteAt);
//    RUN_TEST(test_init);
//    RUN_TEST(test_write_values);
    RUN_TEST(test_1);


    UNITY_END();

    return 0;
}