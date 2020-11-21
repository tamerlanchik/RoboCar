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
        Tachometr::buffer.mTime[curr].put(val);
        Tachometr::buffer.mCoord[curr].put(Tachometr::buffer.mDirection[curr] * dL);
        Tachometr::buffer.changed[curr] = true;
        Tachometr::buffer.mPath[curr] += Tachometr::buffer.mDirection[curr] * dL;
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
    Log = new Logger();
    When(Method(ArduinoFake(), attachInterrupt)).AlwaysReturn();
    NewTachometr* t = new NewTachometr(0);
    t->start<0>(2);
//    unsigned long start = 1000000;
//    t->put(start + 1);
//
//    t->put(start + 2);
//    t->put(start + 10);
    t->put(19804688);
    t->put(19804704);
    t->put(19804724);
    When(Method(ArduinoFake(), micros)).AlwaysReturn(10000000);
    When(Method(ArduinoFake(), cli)).AlwaysReturn();
    When(Method(ArduinoFake(), sei)).AlwaysReturn();
    Tachometr::buffer.mPath[0] = 132;
    TachoData d = t->getData();
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