#ifndef WECHSLER_H
#define WECHSLER_H

#include "mbed.h"

class Wechsler
{
public:
    /**
     * Constructor for Wechsler class
     * Hard-codes the PWM pin and rotation time per degree.
     */
    Wechsler();

    /**
     * Asynchronous motor control function that should be called cyclically.
     * Based on the input value, it will either rotate the motor or stop it.
     * @param inputValue: The input value that determines the motor operation.
     *                    If the value is 1, it rotates the motor by 72 degrees.
     * @return int: Returns 0 if the motor is still rotating,
     *              returns 1 if the motor has finished its rotation.
     */
    int parseInput(uint16_t inputValue);

private:
    PwmOut _pwmPin;               // The PWM output pin for motor control
    float _rotationTimePerDegree; // Time required for motor to rotate 1 degree
    float _dutyCyclePWM;          // PWM duty cycle for motor control
    float _targetTime;            // Target time in milliseconds to complete the rotation
    float _elapsedTime;           // Elapsed time since the motor started running
    Timer _timer;                 // Timer object to measure elapsed time
    bool _motorRunning;           // Flag indicating whether the motor is currently running
    float _timeCorrection;        // Variable to store time correction for compensating time discrepancies

    /**
     * Rotates the motor by a specific number of degrees.
     * This is a direct control function and operates synchronously.
     * @param degrees: The number of degrees to rotate the motor.
     */
    uint8_t rotateDegrees(int degrees);
};

#endif // WECHSLER_H
