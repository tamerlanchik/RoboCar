#include <Arduino.h>
#include <leOS2.h>
#include <IMU.h>
#include <Logger.h>
#include <Listener.h>

leOS2 myOS;
IMU* mpu;
Logger* Log;
CommunicatorConfig communicatorConfig;

void setup() {
    Log = Log ? Log : new Logger();
    communicatorConfig = {17, 'K', true, 57600};
    Serial.begin(57600);
    mpu = new IMU(IMU::getDefaultConfig());
    if (mpu->init()) {
        delay(100000);
    }
//    mpu->setFilters(
//        new AverageFilter<Math3D::Vector>(0.5, Math3D::Vector()),
//        new AverageFilter<Math3D::Vector>(0.5, Math3D::Vector())
//    );
    myOS.begin();
//    myOS.addTask([](){
//        Serial.println("Hello");
//    }, myOS.convertMs(1000));

    myOS.addTask([](){
        auto data = mpu->read();
        char str[100];
//        sprintf(str, "%6d %6d %6d %6d %6d %6d", (int)data.a.x, (int)data.a.y, (int)data.a.z, (int)data.g.x, (int)data.g.y,(int) data.g.z);
//        sprintf(str, "%6d %6d %6d", (int)data.g.x, (int)data.g.y,(int) data.g.z);
        sprintf(str, "%6d", (int)data.g.z);
        Serial.println(str);
    }, myOS.convertMs(30));
}

void loop() {
}