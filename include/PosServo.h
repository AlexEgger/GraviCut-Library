#ifndef POSSERVO_H
#define POSSERVO_H

#include "mbed.h" // Include mbed header for pin and ADC handling

// Structure to represent a motor
struct Motor
{
    DigitalOut posPin; // Positive terminal pin
    DigitalOut negPin; // Negative terminal pin
    AnalogIn adcPin;   // ADC input pin for position feedback
    int16_t position;  // Current position in 1/100 cm

    // Constructor for Motor structure
    Motor(PinName pos, PinName neg, PinName adc)
        : posPin(pos), negPin(neg), adcPin(adc), position(0) {}
};

class PosServo
{
private:
    Motor motors[3];   // Array of motors
    const int16_t tol; // Tolerance value for the actuators in 1/100 cm

    // Convert from ADC value to a decimal value
    uint16_t mapADC(float x, float in_min, float in_max, uint16_t out_min, uint16_t out_max);

    // Update the current position of a specific motor
    void updatePosition(int motorIndex);

    // Motor 0: Move actuator to open position
    int Open();

    // Motor 0: Move actuator to close position
    int Close();

    // Motor 2: Move actuator to a specific position
    int Position(uint16_t x);

    // Motor 1: Move to Position A
    int PosA();

    // Motor 1: Move to Position B
    int PosB();

public:
    // Constructor: initializes the motors
    PosServo();

    // Parse input commands from the master and trigger the corresponding function
    // Returns whether the action is completed (1) or still running (0)
    int parseInput(uint16_t inputValue);
};

#endif // POSSERVO_H
