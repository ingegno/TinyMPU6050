/*
 *	Register map for the MPU6050 available at: https://www.invensense.com/wp-content/uploads/2015/02/MPU-6000-Register-Map1.pdf
 */
#ifndef TINY_MPU6050_H
#define TINY_MPU6050_H

/*
 *	Mandatory includes
 */
#include "Arduino.h"
#include "Wire.h"

/*
 *	Default MPU6050 address
 */
#define MPU6050_ADDRESS     	0x68

/*
 *	Configuration registers
 */
#define MPU6050_SMPLRT_DIV  	0x19
#define MPU6050_CONFIG      	0x1A
#define MPU6050_GYRO_CONFIG 	0x1B
#define MPU6050_ACCEL_CONFIG	0x1C
#define MPU6050_PWR_MGMT_1      0x6B

/*
 *	Data registers
 */
#define MPU6050_ACCEL_XOUT_H	0x3B	// Initial register address for accel data
#define MPU6050_GYRO_XOUT_H		0x43	// Initial register address for gyro data

/*
 *	Class
 */
class MPU6050 {

	/*
	 *	Public methods and attributes
	 */
	public:

		// Constructor
		MPU6050 (TwoWire &w);

		// Setup method
		void Initialize ();

		// Register write method
		void RegisterWrite (byte registerAddress, byte data);

		// Calibrating gyroscope offsets method
		void CalibrateGyro ();

		// Gets and sets
        float GetGyroXOffset () { return gyroXOffset };
        float GetGyroYOffset () { return gyroYOffset };
        float GetGyroZOffset () { return gyroZOffset };
        void SetGyroOffsets (float x, float y, float z);

        int16_t GetRawAccX () { return rawAccX };
        int16_t GetRawAccY () { return rawAccY };
        int16_t GetRawAccZ () { return rawAccZ };
        int16_t GetRawGyroX () { return rawGyroX };
        int16_t GetRawGyroY () { return rawGyroY };
        int16_t GetRawGyroZ () { return rawGyroZ };

        float GetAccX () { return accX };
        float GetAccY () { return accY };
        float GetAccZ () { return accZ };
        float GetGyroX () { return gyroX };
        float GetGyroY () { return gyroY };
        float GetGyroZ () { return gyroZ };

        float GetAngAccX () { return angAccX };
        float GetAngAccY () { return angAccY };
        float GetAngAccZ () { return angAccZ };
        float GetAngGyroX () { return angGyroX };
        float GetAngGyroY () { return angGyroY };
        float GetAngGyroZ () { return angGyroZ };

        float GetAngX () { return angX };
        float GetAngY () { return angY };
        float GetAngZ () { return angZ };

        float GetFilterAccCoeff () { return filterAccelCoeff };
        float GetFilterGyroCoeff () { return filterGyroCoeff };
        void SetFilterAccCoeff (float coeff);
        void SetFilterGyroCoeff (float coeff);

	/*
	 *	Private methods and attributes
	 */
	private:

		// I²C stuff
		TwoWire *wire;

		// Gyroscope offsets
		float gyroXOffset, gyroYOffset, gyroZOffset;

		// Raw accel and gyro data
		int16_t rawAccX, rawAccY, rawAccZ, rawGyroX, rawGyroY, rawGyroZ;

		// Readable accel and gyro data
		float accX, accY, accZ, gyroX, gyroY, gyroZ;

		// Integration interval stuff
		long intervalStart;
		float dt;

		// Angle data according to accel and gyro (separately)
		float angGyroX, angGyroY, angGyroZ, angAccX, angAccY, angAccZ;

		// Complememtary filter accel and gyro coefficients
		float filterAccelCoeff, filterGyroCoeff;

		// Angle data w/ complementary filter
		float angX, angY, angZ;
}