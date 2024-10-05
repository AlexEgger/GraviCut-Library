#ifndef MYSTRUCTS_H
#define MYSTRUCTS_H

#include <Arduino.h> // Für byte und Serial
#include "myList.h" // Angenommene Header-Datei für GenericList

class MyStructs {
public:
    // Definition der Structs
    struct Lagerplatz {
        byte produkt;           // Produkttyp
        int verbleibendeLaenge; // Verbleibende Länge des Produktes in 1/100 cm
        bool isOccupied;        // Gibt an, ob der Lagerplatz belegt ist

        // Standardkonstruktor
        Lagerplatz()
            : produkt(0), verbleibendeLaenge(0), isOccupied(false) {}

        // Konstruktor mit Parametern
        Lagerplatz(int produktTyp, int laenge)
            : produkt(produktTyp), verbleibendeLaenge(laenge), isOccupied(true) {}

        // Kopierkonstruktor
        Lagerplatz(const Lagerplatz &other)
            : produkt(other.produkt), verbleibendeLaenge(other.verbleibendeLaenge), isOccupied(other.isOccupied) {}

        // Zuweisungsoperator
        Lagerplatz &operator=(const Lagerplatz &other) {
            if (this != &other) {
                produkt = other.produkt;
                verbleibendeLaenge = other.verbleibendeLaenge;
                isOccupied = other.isOccupied;
            }
            return *this;
        }

        // Vergleichsoperator ==
        bool operator==(const Lagerplatz &other) {
            return (produkt == other.produkt &&
                    verbleibendeLaenge == other.verbleibendeLaenge &&
                    isOccupied == other.isOccupied);
        }

        // Print-Funktion
        void print() const {
            Serial.print(F("Belegt: "));
            Serial.println(isOccupied ? F("Ja") : F("Nein"));

            // Nur drucken, wenn isOccupied wahr ist
            if (isOccupied) {
                Serial.print(F("Produkt: "));
                Serial.println(produkt);
                Serial.print(F("Verbleibende Länge (1/100 cm): "));
                Serial.println(verbleibendeLaenge);
            }
            Serial.println();
        }
    };

    struct Layout { // Layout der GUI, wird bei jedem View-Wechsel geaendert
        byte currentView;             // Index der aktuellen View
        GenericList<int> xPositionen; // x-Positionen der Elemente
        GenericList<int> yPositionen; // y-Positionen der Elemente
        int hButton;                  // Hoehe der Buttons
        int wButton;                  // Breite der Buttons
        int randAbstand;              // Abstand der Elemente vom Rand
        int zwischenAbstand;          // Abstand zwischen den Elementen
        byte schriftGroesse;          // Groesse der Schrift
    };

    struct Produkt {
        byte produktTyp;         // Typ des Produktes (von 1 bis 3)
        int produktMenge;        // aktuelle Anzahl der Produkte
        byte startProduktAnzahl; // Anfangsanzahl der Produkte
        int produktLaenge;       // Laenge in 1/100 cm

        Produkt() : produktTyp(0), produktMenge(0), produktLaenge(0), startProduktAnzahl(0) {}

        Produkt(int typ, int anzahl, int laenge) 
            : produktTyp(typ), produktMenge(anzahl), produktLaenge(laenge), startProduktAnzahl(anzahl) {}

        Produkt(const Produkt &other) 
            : produktTyp(other.produktTyp),
              produktMenge(other.produktMenge),
              startProduktAnzahl(other.startProduktAnzahl),
              produktLaenge(other.produktLaenge) {}

        Produkt &operator=(const Produkt &other) {
            if (this != &other) {
                produktTyp = other.produktTyp;
                produktMenge = other.produktMenge;
                startProduktAnzahl = other.startProduktAnzahl;
                produktLaenge = other.produktLaenge;
            }
            return *this;
        }

        void reduceCurrentProductAmount() {
            if (produktMenge > 0) {
                Serial.print(F("Produktmenge vorher = "));
                Serial.println(produktMenge);
                produktMenge--;
                Serial.print(F("Produktmenge nachher = "));
                Serial.println(produktMenge);
            }
        }

        void print() const {
            Serial.print(F("    Produkt Typ: "));
            Serial.println(produktTyp);
            Serial.print(F("    Produkt Menge: "));
            Serial.print(produktMenge);
            Serial.print(F("/"));
            Serial.println(startProduktAnzahl);
            Serial.print(F("    Produkt Laenge: "));
            Serial.println(produktLaenge);
        }
    };

    struct Auftrag {
        GenericList<Produkt> produkte; // Liste der Produkte im Auftrag
        byte gesamtProdukteAnzahl;      // Anfangsanzahl aller Produkte in diesem Auftrag

        Auftrag() : gesamtProdukteAnzahl(0) {}

        void addProdukt(const Produkt &produkt) {
            produkte.add(produkt);
            gesamtProdukteAnzahl++;
        }

        // Kopierkonstruktor
        Auftrag(const Auftrag &other)
            : produkte(other.produkte), gesamtProdukteAnzahl(other.gesamtProdukteAnzahl) {}

        // Zuweisungsoperator
        Auftrag &operator=(const Auftrag &other) {
            if (this != &other) {
                produkte = other.produkte;
                gesamtProdukteAnzahl = other.gesamtProdukteAnzahl;
            }
            return *this;
        }

        // Reduziert die Menge des ersten Produktes in der Liste
        void reduceCurrentProductAmount() {
            if (produkte.get(0).produktMenge > 0) {
                produkte.get(0).reduceCurrentProductAmount();
            }
        }

        void printAll() {
            for (byte i = 0; i < produkte.getSize(); i++) {
                Serial.print(F("Produkt: "));
                Serial.println(i + 1);
                produkte.get(i).print();
            }
        }
    };
};

#endif // MYSTRUCTS_H
