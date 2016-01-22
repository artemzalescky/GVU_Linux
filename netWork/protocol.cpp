#include "protocol.h"
using namespace protocolName;

void protocol::ValueToArray(float value, char* array, u_int8_t* sum)
{
    u_int8_t temp;
    char* data = (char*) &value;
    memcpy(array, data, 4);
    temp = array[0];
    *sum += array[0];
    array[0] = array[3];
    *sum += array[3];
    array[3] = temp;
    temp = array[1];
    *sum += array[1];
    array[1] = array[2];
    *sum += array[2];
    array[2] = temp;
}

void protocol::ValueToArray(u_int16_t value, char* array, u_int8_t* sum)
{
    u_int8_t temp;
    char* data = (char*) &value;
    memcpy(array, data, 2);
    temp = array[0];
    *sum += array[0];
    array[0] = array[1];
    *sum += array[1];
    array[1] = temp;
}

float protocol::ConvertValue(QString str, bool *ok)
{
    str.replace(",",".");
    float data = str.toFloat(ok);
    return data;
}



QByteArray protocol::GenerateMessage(u_int8_t typeMessage, u_int8_t typeReg, float value)
{
    u_int8_t size = 8;
    u_int8_t sum = 0;
    char data[size];
    QByteArray message;
    data[0] = typeMessage;
    sum += typeMessage;
    data[1] = size;
    sum += size;
    data[2] = typeReg;
    sum += typeReg;
    ValueToArray(value, data+3, &sum);
    data[7] = sum;
    message.append(data, size);
    return message;
}

QByteArray protocol::GenerateMessage(u_int8_t typeMessage, u_int8_t typeReg, u_int16_t value)
{
    u_int8_t size = 6;
    u_int8_t sum = 0;
    char data[size];
    QByteArray message;
    data[0] = typeMessage;
    sum += typeMessage;
    data[1] = size;
    sum += size;
    data[2] = typeReg;
    sum += typeReg;
    data[3] = value;
    sum += value;
    data[4] = sum;
    message.append(data, size);
    return message;
}

QByteArray protocol::GenerateMessage(u_int8_t typeMessage, u_int8_t typeReg, u_int8_t value)
{
    u_int8_t size = 5;
    u_int8_t sum = 0;
    char data[size];
    QByteArray message;
    data[0] = typeMessage;
    sum += typeMessage;
    data[1] = size;
    sum += size;
    data[2] = typeReg;
    sum += typeReg;
    data[3] = value;
    sum += value;
    data[4] = sum;
    message.append(data, size);
    return message;
}

QByteArray protocol::GenerateMessage(u_int8_t typeMessage, u_int8_t typeReg, u_int8_t value1, u_int16_t value2)
{
    u_int8_t size = 7;
    u_int8_t sum = 0;
    char data[size];
    QByteArray message;
    data[0] = typeMessage;
    sum += typeMessage;
    data[1] = size;
    sum += size;
    data[2] = typeReg;
    sum += typeReg;
    data[3] = value1;
    sum += value1;
    ValueToArray(value2, data+4, &sum);
    data[6] = sum;
    message.append(data, size);
    return message;
}



QByteArray protocol::GenerateMessage(u_int8_t typeMessage)
{
    u_int8_t size = 3;
    u_int8_t sum = 0;
    char data[size];
    QByteArray message;
    data[0] = typeMessage;
    sum += typeMessage;
    data[1] = size;
    sum += size;
    data[2] = sum;
    message.append(data, size);
    return message;
}

QByteArray protocol::GenerateAngles(float value1, float value2, float value3)
{
    u_int8_t size = 15;
    u_int8_t sum = 0;
    char data[size];
    QByteArray message;
    data[0] = MUSV_ANGLES;
    sum += MUSV_ANGLES;
    data[1] = size;
    sum += size;
    ValueToArray(value1, data+2, &sum);
    ValueToArray(value2, data+6, &sum);
    ValueToArray(value3, data+10, &sum);
    data[14] = sum;
    message.append(data, size);
    return message;
}

QByteArray protocol::GenerateMessage(u_int8_t typeMessage, u_int8_t typeReg)
{
    u_int8_t size = 4;
    u_int8_t sum = 0;
    char data[size];
    QByteArray message;
    data[0] = typeMessage;
    sum += typeMessage;
    data[1] = size;
    sum += size;
    data[2] = typeReg;
    sum += typeReg;
    data[3] = sum;
    message.append(data, size);
    return message;
}
