#ifndef PID_TUNER_H
#define PID_TUNER_H
#define PID_TUNER_DEBUG

#if ARDUINO > 22
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <HardwareSerial.h>

constexpr byte startMarker = 254;
constexpr byte endMarker = 255;
constexpr byte specialByte = 253;

class PIDTuner
{
    HardwareSerial &port;
    bool *power;
    float *xa;
    float *ya;

    void serialFlush();
    bool readBytes(byte[], byte, char);
    void decodeData(byte[], byte, byte &, byte[]);
    void debug(String);

public:
    // PIDTuner(byte *, float *, float *, float *, HardwareSerial &);
    PIDTuner(bool *_power, float *_xa, float *_ya, HardwareSerial &newPort = Serial1) : port(newPort)
    {
        port.begin(115200);
        power = _power;
        xa = _xa;
        ya = _ya;
    }
    bool update();
};
#endif