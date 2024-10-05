#include "PosServo.h"

// Constructor: initializes the motors and their tolerance value
PosServo::PosServo(uint16_t tolerance)
    : motors{
          Motor(PA_2, PA_3, PA_1), // Motor 0: Schere
          Motor(PC_8, PC_9, PB_0), // Motor 1: Schieber
          Motor(PB_5, PB_6, PB_1)  // Motor 2: Anschlag
      },
      tol(tolerance) // Set common tolerance for all motors
{
    // Initialize all motor pins to the off state
    for (int i = 0; i < 3; ++i)
    {
        motors[i].posPin = 0;
        motors[i].negPin = 0;
        motors[i].position = 0; // Initial position for each motor
    }
}

// Convert from ADC value to a decimal value
uint16_t PosServo::mapADC(float x, float in_min, float in_max, uint16_t out_min, uint16_t out_max)
{
    return (uint16_t)((x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min);
}

// Update the current position of a specific motor
void PosServo::updatePosition(int motorIndex)
{
    float adcValue = motors[motorIndex].adcPin.read();                 // Read ADC value (range: 0.0 to 1.0)
    motors[motorIndex].position = mapADC(adcValue, 0.0, 1.0, 10, 520); // Map from 0-1 to 10-520 (Position in 1/100 cm)
}

// Motor 0: Move actuator to the open position
int PosServo::Open()
{
    updatePosition(0);            // Update current position for Motor 0
    if (motors[0].position < 500) // Continue moving until the target position is reached
    {
        motors[0].negPin = 0; // Motor negative terminal off
        motors[0].posPin = 1; // Motor positive terminal on
        return 0;             // Still running
    }
    else
    {
        motors[0].posPin = 0; // Motor positive terminal off
        motors[0].negPin = 0; // Motor negative terminal off
        return 1;             // Operation completed
    }
}

// Motor 0: Move actuator to the close position
int PosServo::Close()
{
    updatePosition(0);           // Update current position for Motor 0
    if (motors[0].position > 30) // Continue moving until the target position is reached
    {
        motors[0].posPin = 0; // Motor positive terminal off
        motors[0].negPin = 1; // Motor negative terminal on
        return 0;             // Still running
    }
    else
    {
        motors[0].posPin = 0; // Motor positive terminal off
        motors[0].negPin = 0; // Motor negative terminal off
        return 1;             // Operation completed
    }
}

// Motor 1: Move to Position A
int PosServo::PosA()
{
    updatePosition(1);            // Update current position for Motor 1
    if (motors[1].position < 200) // Move upward until Position A is reached
    {
        motors[1].posPin = 1; // Motor positive terminal on
        motors[1].negPin = 0; // Motor negative terminal off
        return 0;             // Still running
    }
    else
    {
        motors[1].posPin = 0; // Motor positive terminal off
        motors[1].negPin = 0; // Motor negative terminal off
        return 1;             // Operation completed
    }
}

// Motor 1: Move to Position B
int PosServo::PosB()
{
    updatePosition(1);            // Update current position for Motor 1
    if (motors[1].position > 400) // Move downward until Position B is reached
    {
        motors[1].posPin = 1; // Motor positive terminal on
        motors[1].negPin = 0; // Motor negative terminal off
        return 0;             // Still running
    }
    else
    {
        motors[1].posPin = 0; // Motor positive terminal off
        motors[1].negPin = 0; // Motor negative terminal off
        return 1;             // Operation completed
    }
}

// Motor 2: Move actuator to a specific position
int PosServo::Position(uint16_t x)
{
    updatePosition(2);                // Update current position for Motor 2
    if (motors[2].position < x - tol) // Move upward until within tolerance
    {
        motors[2].posPin = 1; // Motor positive terminal on
        motors[2].negPin = 0; // Motor negative terminal off
        return 0;             // Still running
    }
    else if (motors[2].position > x + tol) // Move downward until within tolerance
    {
        motors[2].posPin = 0; // Motor positive terminal off
        motors[2].negPin = 1; // Motor negative terminal on
        return 0;             // Still running
    }
    else // Position is within the tolerance range
    {
        motors[2].posPin = 0; // Motor positive terminal off
        motors[2].negPin = 0; // Motor negative terminal off
        return 1;             // Operation completed
    }
}

// Parse input commands from the master and trigger the corresponding function
int PosServo::parseInput(uint16_t inputValue)
{
    if (inputValue == 0)
    {
        return Open(); // Motor 0: Open
    }
    else if (inputValue == 1)
    {
        return Close(); // Motor 0: Close
    }
    else if (inputValue == 2)
    {
        return PosA(); // Motor 1: Move to Position A
    }
    else if (inputValue == 3)
    {
        return PosB(); // Motor 1: Move to Position B
    }
    else
    {
        return Position(inputValue); // Motor 2: Move to specific position
    }
}
