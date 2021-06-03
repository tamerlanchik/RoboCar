#include "IMU.h"
#include <Logger.h>

extern Logger* Log;

IMU::IMU(const Config cfg) : MPU6050(), _cfg(cfg) {
}


bool IMU::init() {
    if(_cfg.accel_range > 4) {
        Log->println('e', "Bad accel factor: ", _cfg.accel_range);
        return 1;
    }
    if(_cfg.gyro_range > 4) {
        Log->println('e', "Bad gyro factor: ", _cfg.gyro_range);
        return 1;
    }
    const uint8_t accel_base_factor=2, gyro_base_factor = 250;
    _accel_factor = accel_base_factor * _cfg.accel_range;
    _gyro_factor = gyro_base_factor * _cfg.gyro_range;

    Wire.begin();
    initialize();

//    MPU6050::setFullScaleAccelRange(static_cast<uint8_t>(_cfg.accel_range));
//    MPU6050::setFullScaleGyroRange(static_cast<uint8_t>(_cfg.gyro_range));
    Log->println('d', _cfg.accel_range, _cfg.gyro_range);

    if (!testConnection()) {
        Log->println('e', "No connection to IMU");
        return 1;
    }

//    setFilters(new DummyFilter<Math3D::Vector>, new DummyFilter<Math3D::Vector>);
    setFilters(
        new AverageFilter<Math3D::Vector>(0.5, Math3D::Vector(0, 0, 0)),
        new AverageFilter<Math3D::Vector>(0.5, Math3D::Vector(0, 0, 0))
    );

    Log->println('d', "Init MPU6050");
    return false;
}


IMU::IMUData IMU::read() {
    IMUData res = readRaw();
    res.a = _filter_accel->apply(res.a);
    res.g = _filter_gyro->apply(res.g);
    return res;
}

IMU::IMUData IMU::get() {
    return IMUData{
        _filter_accel->get(),
        _filter_gyro->get()
    };
}

IMU::IMUData IMU::readRaw() {
    int16_t raw[6];
    getMotion6(&raw[0], &raw[1], &raw[2], &raw[3], &raw[4], &raw[5]);

//    const int16_t MAX_INT16 = 32768;
    return IMUData{
        Math3D::Vector(raw[0], raw[1], raw[2]),
        Math3D::Vector(raw[3], raw[4], raw[5]),
    };
}

void IMU::setFilters(Filter3<Math3D::Vector>* filter_accel, Filter3<Math3D::Vector>* filter_gyro) {
    _filter_accel = filter_accel;
    _filter_gyro = filter_gyro;
}