#include "Magazin.h"

// Parameterloser Konstruktor: Initialisiert die Solenoids und Zeiten
Magazin::Magazin()
    : _pairs{
          SolenoidSensorPair(D7, A0), // Paar 0: Solenoid und Sensor
          SolenoidSensorPair(D6, A1), // Paar 1: Solenoid und Sensor
          SolenoidSensorPair(D5, A2)  // Paar 2: Solenoid und Sensor
      },
      _activateDuration(1000),   // Definierte Aktivierungsdauer (1 Sekunde)
      _deactivateDuration(1000), // Definierte Deaktivierungsdauer (1 Sekunde)
      _isActivated(false)        // Anfangszustand: Solenoid ist nicht aktiviert
{
    // Timer starten
    _timer.start();
}

// Interne Logik zur Steuerung der Solenoids und zum Auslesen der Sensoren
int Magazin::activateControl(int index)
{
    if (!_isActivated) // Wenn der Solenoid noch nicht aktiviert ist
    {
        _pairs[index].solenoidPin = 1; // Solenoid einschalten
        _timer.reset();                // Timer zurücksetzen
        _isActivated = true;           // Aktivierungsstatus setzen
        return 0;                      // Noch nicht fertig, Zeit läuft
    }

    // Solenoid ist aktiviert, Zeit prüfen
    if (_timer.read_ms() >= _activateDuration && _timer.read_ms() < _activateDuration + _deactivateDuration)
    {
        _pairs[index].solenoidPin = 0; // Solenoid ausschalten
    }

    // Prüfen, ob die gesamte Zeit (Aktivierungs- und Deaktivierungsdauer) abgelaufen ist
    if (_timer.read_ms() >= _activateDuration + _deactivateDuration)
    {
        // Sensorwert lesen
        float sensorValue = _pairs[index].sensorPin.read();

        _isActivated = false; // Aktivierungsstatus zurücksetzen

        // Wenn der Sensor anschlägt, Rückgabewert 2
        if (sensorValue > 0.5f)
        {
            return 2; // Sensorwert erkannt
        }
        return 1; // Vorgang abgeschlossen, aber Sensor nicht ausgelöst
    }

    return 0; // Vorgang läuft noch
}

// Verarbeitung der Eingabe, ruft activateControl basierend auf inputValue auf
int Magazin::parseInput(int inputValue)
{
    int motorIndex = inputValue - 1; // Index des Solenoids (0-2)
    if (motorIndex >= 0 && motorIndex < 3)
    {
        return activateControl(motorIndex); // Rufe activateControl mit dem entsprechenden Index auf
    }
    return -1; // Ungültige Eingabe
}
