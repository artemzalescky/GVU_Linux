#ifndef PROTOCOLNAME_H
#define PROTOCOLNAME_H


#include "QByteArray"
#include <QString>

namespace protocolName {

#define MUSV_UAV 				2
#define MUSV_STATE_REQ 			4
#define MUSV_ANGLES 			6
#define MUSV_SETTINGS 			8
#define MUSV_ANGULAR_SPEED 		10
#define MUSV_PHOTO_VIDEO 		12
#define MSG_TYPE_SENSOR_ZERO 		0x0E
#define MSG_TYPE_SENSOR_ZERO_RESET	0x0F
#ifdef DEBUG
#define MUSV_SERVICE			0x55
#define MUSV_IN_ANGLES          6
#else
#define MUSV_SERVICE			0x54
#define MUSV_IN_ANGLES          3
#endif

#define MUSV_IN_STATE 			1
#define MUSV_IN_SERVICE         0x55

#define MSG_TYPE_OUT_BINS			0x33

#define MUSV_SETTINGS_POWER				1
#define MUSV_SETTINGS_POWER_ON			1
#define MUSV_SETTINGS_POWER_OFF			0
#define MUSV_SETTINGS_PHOTO				2
#define MUSV_SETTINGS_ZOOM				3
#define MUSV_SETTINGS_EXPOSURE			4
#define MUSV_SETTINGS_FREQUENCY			5
#define MUSV_SETTINGS_STABILISATION		6
#define MUSV_SETTINGS_CONTROL_PWM		7
#define MUSV_SETTINGS_COLOR				8
#define MUSV_SETTINGS_CAMERA			9
#define MUSV_SETTINGS_FOCUS				10
#define MUSV_SETTINGS_CALIBRATION		11
#define MUSV_SETTINGS_MOTOR     		12
#define MUSV_SETTINGS_FORMAT            13
#define MUSV_SETTINGS_TOGGLE_WIFI		14
#define MSG_DATA_CALIBRATION_DATA       0x0F
#define MSG_DATA_OUTPUT_RATE            0x10

#define MUSV_SETTINGS_STABILISATION_OFF	0
#define MUSV_SETTINGS_STABILISATION_ON	1

#define MSG_CALIBRATION_OFF			0x00
#define MSG_CALIBRATION_ELLIPSE		0x01
#define MSG_CALIBRATION_Z_ROTATE	0x02
#define MSG_CALIBRATION_Y_ROTATE	0x03
#define MSG_CALIBRATION_X_ROTATE	0x04

//Output date rate for MSG_DATA_OUTPUT_RATE
#define MSG_OUTPUT_RATE_OFF			0x00
#define MSG_OUTPUT_RATE_1HZ			0x01
#define MSG_OUTPUT_RATE_5HZ			0x02
#define MSG_OUTPUT_RATE_10HZ		0x03
#define MSG_OUTPUT_RATE_25HZ		0x04
#define MSG_OUTPUT_RATE_50HZ		0x05

#define MUSV_SETTINGS_CAMERA_TV			1
#define MUSV_SETTINGS_CAMERA_IR			2
#define MUSV_SETTINGS_CAMERA_PHOTO		4

#define MUSV_SETTINGS_FOCUS_OFF         0
#define MUSV_SETTINGS_FOCUS_ON          1

#define MUSV_SETTINGS_PHOTO_NO          0
#define MUSV_SETTINGS_PHOTO_TAKE_PHOTO  3
#define MUSV_SETTINGS_PHOTO_BURST       5
#define MUSV_SETTINGS_RECORD            7

#define MUSV_SETTINGS_MOTOR_OFF   		0
#define MUSV_SETTINGS_MOTOR_ON     		1


#define MUSV_SERVICE_PID_ROLL_REQ       0
#define MUSV_SERVICE_PID_ROLL_Kp		1
#define MUSV_SERVICE_PID_ROLL_Lp        2
#define MUSV_SERVICE_PID_ROLL_Ki		3
#define MUSV_SERVICE_PID_ROLL_Li        4
#define MUSV_SERVICE_PID_ROLL_Kd		5
#define MUSV_SERVICE_PID_ROLL_Ld        6
#define MUSV_SERVICE_PID_ROLL_L			7

#define MUSV_SERVICE_PID_PITCH_REQ   	8
#define MUSV_SERVICE_PID_PITCH_Kp		9
#define MUSV_SERVICE_PID_PITCH_Lp       10
#define MUSV_SERVICE_PID_PITCH_Ki		11
#define MUSV_SERVICE_PID_PITCH_Li       12
#define MUSV_SERVICE_PID_PITCH_Kd		13
#define MUSV_SERVICE_PID_PITCH_Ld       14
#define MUSV_SERVICE_PID_PITCH_L		15

#define MUSV_SERVICE_PID_YAW_REQ        16
#define MUSV_SERVICE_PID_YAW_Kp			17
#define MUSV_SERVICE_PID_YAW_Lp         18
#define MUSV_SERVICE_PID_YAW_Ki			19
#define MUSV_SERVICE_PID_YAW_Li         20
#define MUSV_SERVICE_PID_YAW_Kd			21
#define MUSV_SERVICE_PID_YAW_Ld         22
#define MUSV_SERVICE_PID_YAW_L			23

#define MUSV_SERVICE_CALIB_REQ			24
#define MUSV_SERVICE_CALIB_DATA			25

//******************
#define MUSV_SERVICE_CALIB_CLEAR       0x1A
#define MSG_DATA_SERVICE_TOGGLE_TERMINAL 0x1B

class protocol
{

private:
    static void ValueToArray(float value, char* array, u_int8_t* sum);
    static void ValueToArray(u_int16_t value, char* array, u_int8_t* sum);
    float ConvertValue(QString str, bool* ok);

public:

    static QByteArray GenerateMessage(u_int8_t typeMessage);
    static QByteArray GenerateAngles(float value1, float value2, float value3);
//    static QByteArray GenerateMessage(u_int8_t typeMessage, u_int8_t typeReg, QString str);
    static QByteArray GenerateMessage(u_int8_t typeMessage, u_int8_t typeReg, float value);
    static QByteArray GenerateMessage(u_int8_t typeMessage, u_int8_t typeReg, u_int8_t value);
    static QByteArray GenerateMessage(u_int8_t typeMessage, u_int8_t typeReg, u_int16_t value);
    static QByteArray GenerateMessage(u_int8_t typeMessage, u_int8_t typeReg, u_int8_t value1, u_int16_t value2);
    static QByteArray GenerateMessage(u_int8_t typeMessage, u_int8_t typeReg);
};

}

#endif // PROTOCOLNAME_H
