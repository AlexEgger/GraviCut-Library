#ifndef MAGAZIN_H
#define MAGAZIN_H

#include "mbed.h" // Include mbed header for pin and ADC handling

// Struktur für einen Solenoid-Motor und einen zugehörigen Sensor
struct SolenoidSensorPair
{
    DigitalOut solenoidPin; // Pin zur Steuerung des Solenoids
    AnalogIn sensorPin;     // Pin zum Lesen des Sensors

    // Konstruktor für das Struct
    SolenoidSensorPair(PinName solPin, PinName senPin)
        : solenoidPin(solPin), sensorPin(senPin) {}
};

class Magazin
{
private:
    SolenoidSensorPair _pairs[3]; // Array von Solenoid-Sensor-Paaren
    uint32_t _activateDuration;   // Dauer, für die der Solenoid aktiv bleibt (in ms)
    uint32_t _deactivateDuration; // Dauer, bevor die Funktion 1 zurückgibt (in ms)
    Timer _timer;                 // Timer zur Messung der Zeit
    bool _isActivated;            // Flag, ob der Solenoid aktiviert wurde

    // Interne Logik für das Ansteuern und das Auslesen des Sensors
    int activateControl(int index);

public:
    // Konstruktor: Initialisiert die Solenoids, Sensoren und Zeiten
    Magazin();

    // Verarbeitung der Eingabe, ruft activateControl basierend auf inputValue auf
    int parseInput(int inputValue);
};

#endif // MAGAZIN_H
