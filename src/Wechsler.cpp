#include "Wechsler.h"
#include <cmath> // Include cmath for fabs function

/**
 * Constructor for Wechsler class
 * Hard-codes the PWM pin and rotation time per degree.
 */
Wechsler::Wechsler()
    : _pwmPin(D9),                    // Hard-coded PWM pin (change this to your desired pin)
      _rotationTimePerDegree(0.0035), // Hard-coded rotation time per degree
      _motorRunning(false),
      _timeCorrection(0),
      _targetTime(0),
      _elapsedTime(0)
{
    // Set the PWM period to 20ms for motor control (common for servo motors)
    _pwmPin.period_ms(20);

    _dutyCyclePWM = 0.75f; // Set the PWM duty cycle to 75% (example value)

    // Ensure the motor is stopped initially by setting the PWM duty cycle to 0
    _pwmPin.write(0.0f);
}

/**
 * Asynchronous function for controlling the motor based on input.
 * This function should be called cyclically.
 * @param inputValue: The input value that controls the motor.
 *                    When inputValue == 1, the motor will rotate 72 degrees.
 * @return int: Returns 0 if the motor is still rotating,
 *              and 1 when the motor has finished its rotation.
 */
int Wechsler::parseInput(uint16_t inputValue)
{
    // If inputValue is 1, start the motor rotation
    if (inputValue == 1)
    {
        // Start the motor to rotate 72 degrees
        return rotateDegrees(72); // Call rotateDegrees and return its result
    }

    return 1; // Return 1 if no rotation is initiated (inputValue is not 1)
}

/**
 * Initiates the rotation of the motor by a specified number of degrees.
 * This function manages the motor's state and timing.
 * @param degrees: The number of degrees to rotate the motor.
 * @return uint8_t: Returns 0 if the motor is still rotating,
 *                  and 1 when the motor has finished its rotation.
 */
uint8_t Wechsler::rotateDegrees(int degrees)
{
    // If the motor is not currently running, initiate rotation
    if (!_motorRunning)
    {
        // Calculate the time required to rotate the specified number of degrees
        _targetTime = degrees * _rotationTimePerDegree * 1000; // Convert seconds to milliseconds
        _targetTime += _timeCorrection;                        // Apply time correction to compensate for any previous timing issues

        // Reset the elapsed time and mark the motor as running
        _elapsedTime = 0;
        _motorRunning = true;

        // Start the motor by setting the PWM duty cycle (0.75 is an example value)
        _pwmPin.write(_dutyCyclePWM);

        // Reset and start the timer to measure the rotation time
        _timer.reset();
        _timer.start();
    }

    // If the motor is currently running, check the elapsed time
    if (_motorRunning)
    {
        // Get the elapsed time in milliseconds
        _elapsedTime = _timer.read_ms();

        // If the elapsed time has exceeded 99% of the target time
        if (_elapsedTime >= _targetTime * 0.99) // Check if elapsed time exceeds target time by more than 1%
        {
            // Stop the motor by setting the PWM duty cycle to 0
            _pwmPin.write(0.0f);

            // Mark the motor as stopped
            _motorRunning = false;

            // Stop the timer since the motor has completed its operation
            _timer.stop();

            // Calculate the discrepancy between the target and actual time
            _timeCorrection = _elapsedTime - _targetTime; // Store the excess time as correction for the next cycle

            return 1; // Motor rotation is complete, return 1
        }
        else
        {
            return 0; // Motor is still rotating, return 0
        }
    }

    return 1; // If no rotation was initiated or if the motor has stopped, return 1
}