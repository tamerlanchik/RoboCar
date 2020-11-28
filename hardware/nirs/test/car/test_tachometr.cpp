#include <modules/CircularBuffer/CircularBuffer.h>
#include <ArduinoFake.h>
#include <unity.h>
#include <string>
#include <car/Tachometr/Tachometr.h>
#include <modules/Logger/Logger.hpp>
#include <fstream>

using namespace fakeit;
Logger* Log;

Config cfg;
TachometrConfig tachometrConfig;
CommunicatorConfig communicatorConfig;
ChassisConfig chassisConfig;

class NewTachometr : public Tachometr {
public:
    NewTachometr(int curr) : Tachometr(curr) {}
    void put(int val) {
        Tachometr::buffer.storage[curr].handleInterr(val);
    }
};

void init() {
    communicatorConfig = {17, 'K', true, 57600};
    tachometrConfig = {8, 1, 15, 4, 1, 20};
    chassisConfig = {10};

    String s = "0.6";
    float d = atof(s.c_str());
    Log = new Logger();
    When(Method(ArduinoFake(), attachInterrupt)).AlwaysReturn();
//    When(Method(ArduinoFake(), micros)).AlwaysReturn(10000000);
    When(Method(ArduinoFake(), cli)).AlwaysReturn();
    When(Method(ArduinoFake(), sei)).AlwaysReturn();
}

// Читаем данные времени из файла, результаты моделирования пишем в другой.
// Для MatLab.
void graph() {
    std::ifstream inputFile("fstreams/f1_input.txt");
    std::ofstream outputFile("fstreams/f1_output.txt");
    if (!inputFile.is_open() || !outputFile.is_open()) {
        TEST_FAIL_MESSAGE("Cannot open one of the files!");
    }
    init();
    unsigned long* time = new unsigned long(0);
    NewTachometr* sensor = new NewTachometr(0);
    When(Method(ArduinoFake(), micros)).AlwaysDo([&time]()->unsigned long{
        return *time;
    });
    unsigned long t;
    while(!inputFile.eof()) {
        inputFile >> t;
        *time = t;
        sensor->put(t);
        auto data = sensor->getLinearData(true);

        outputFile << t
            << " " << data.x
            << " " << data.v
            << " " << data.a
            << "\n";
    }
    inputFile.close();
    outputFile.close();
}

void test_1() {
    init();
    NewTachometr* t = new NewTachometr(0);
    t->start<0>(2);
//    const int times[] = {34887036, 34898000, 34905524, 34916944, 34924688, 34937172, 34958712, 34967368, 34981092, 34990292, 35006524};
//    const int times[] = {34000000, 34898000, 34905524, 34916944, 34924688, 34937172, 34958712, 34967368, 34981092, 34990292, 35006524};
    int times[10] = {34000000};
    int step = 100000;
    for(int i = 1; i < 10; ++i) {
        times[i] = times[i-1] + step;
        step *= 2;
    }
    TachoData data[sizeof(times)];
    int i = 0;
    for(int time : times) {
        t->put(time);
        data[i++] = t->getData();
    }

    for(int j = 0; j < i; ++j) {
        printf("%f ", data[j].x);
    }
    printf("\n\n");

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
//    RUN_TEST(test_1);
    RUN_TEST(graph);


    UNITY_END();

    return 0;
}