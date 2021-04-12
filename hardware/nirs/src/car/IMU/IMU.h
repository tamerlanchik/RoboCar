#ifndef NIRS_IMU_H
#define NIRS_IMU_H

#include <Filter3.hpp>
#include "Wire.h"
#include "I2Cdev.h"
#include "MPU6050.h"
#include "Math3D.h"

//enum class AccelRangeParam {
//    x1 = MPU6050_ACCEL_FS_2,
//    x2 = MPU6050_ACCEL_FS_4,
//    x3 = MPU6050_ACCEL_FS_8,
//    x4 = MPU6050_ACCEL_FS_16,
//};
//
//enum class GyroRangeParam {
//    x1 = MPU6050_GYRO_FS_250,
//    x2 = MPU6050_GYRO_FS_500,
//    x3 = MPU6050_GYRO_FS_1000,
//    x4 = MPU6050_GYRO_FS_2000,
//};

class IMU : public MPU6050 {
public:
    const static uint8_t DEFAULT_ADDRESS = MPU6050_ADDRESS_AD0_LOW;
    const static uint8_t RESERVE_ADDRESS = MPU6050_ADDRESS_AD0_HIGH;
    typedef uint8_t AccelRangeParam;
    typedef uint8_t GyroRangeParam;

    struct IMUData {
        Math3D::Vector a;
        Math3D::Vector g;
    };

    struct Config {
        uint8_t address;
        AccelRangeParam accel_range;
        GyroRangeParam gyro_range;
        static Config get_default() {
            return Config{DEFAULT_ADDRESS, 1, 1};
        }
    };

    IMU(const uint8_t address);

    IMU(const Config cfg);

    bool init();

    IMUData read();

    IMUData get();

    IMUData readRaw();

    void setFilters(Filter3<Math3D::Vector>*,Filter3<Math3D::Vector>*);

    static const Config getDefaultConfig() {
        return Config::get_default();
    }

private:
    Config _cfg;
    uint16_t _accel_factor;
    uint16_t _gyro_factor;
    Filter3<Math3D::Vector>* _filter_gyro;
    Filter3<Math3D::Vector>* _filter_accel;
};


#endif //NIRS_IMU_H
