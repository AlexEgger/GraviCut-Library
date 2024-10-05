#include "MyList.h"

// Funktion zur Verdopplung der Kapazität des Arrays
template <typename T>
void GenericList<T>::resize()
{
    // Verdopplung der Kapazität
    capacity *= 2;

    // Erstellen eines neuen Arrays mit der neuen Kapazität
    T *newArray = new T[capacity];

    // Kopieren der vorhandenen Elemente in das neue Array
    for (int i = 0; i < size; ++i)
    {
        newArray[i] = array[i];
    }

    // Freigeben des alten Arrays
    delete[] array;

    // Zuweisen des neuen Arrays
    array = newArray;
}

// Konstruktor mit einer optionalen Anfangskapazität
template <typename T>
GenericList<T>::GenericList(int initialCapacity)
    : size(0), capacity(initialCapacity), array(new T[capacity]) {}

// Destruktor
template <typename T>
GenericList<T>::~GenericList()
{
    delete[] array; // Freigeben des Speichers
}

// Kopierkonstruktor
template <typename T>
GenericList<T>::GenericList(const GenericList &other)
    : size(other.size), capacity(other.capacity), array(new T[other.capacity])
{
    for (int i = 0; i < size; ++i)
    {
        array[i] = other.array[i]; // Kopieren der Elemente
    }
}

// Zuweisungsoperator
template <typename T>
GenericList<T> &GenericList<T>::operator=(const GenericList &other)
{
    if (this != &other)
    {
        // Freigeben des alten Speichers
        delete[] array;

        // Zuweisen neuer Werte
        array = new T[other.capacity];
        for (int i = 0; i < other.size; ++i)
        {
            array[i] = other.array[i]; // Kopieren der Elemente
        }
        size = other.size;
        capacity = other.capacity;
    }
    return *this; // Rückgabe des aktuellen Objekts
}

// Methode zum Hinzufügen eines Wertes zur Liste
template <typename T>
void GenericList<T>::add(const T &value)
{
    if (size >= capacity)
    {
        resize(); // Verdopplung der Kapazität, falls nötig
    }
    array[size++] = value; // Hinzufügen des Wertes
}

// Methode zum Entfernen eines Elements an einem bestimmten Index
template <typename T>
void GenericList<T>::remove(int index)
{
    if (index >= size || index < 0)
    {
        return; // Index außerhalb des gültigen Bereichs
    }
    for (int i = index; i < size - 1; ++i)
    {
        array[i] = array[i + 1]; // Verschieben der Elemente
    }
    --size; // Reduzieren der Größe
}

// Methode zum Abrufen eines Elements an einem bestimmten Index
template <typename T>
T &GenericList<T>::get(int index)
{
    if (index >= size || index < 0)
    {
        // Hier könnte eine Ausnahmebehandlung implementiert werden
        throw std::out_of_range("Index out of bounds"); // Beispiel für Ausnahmebehandlung
    }
    return array[index]; // Rückgabe des Elements
}

// Methode zum Abrufen aller Elemente als konstantes Array
template <typename T>
const T *GenericList<T>::getAll() const
{
    return array; // Rückgabe des Arrays
}

// Methode zum Setzen eines Wertes an einem bestimmten Index
template <typename T>
void GenericList<T>::set(int index, const T &value)
{
    if (index >= size || index < 0)
    {
        // Hier könnte eine Ausnahmebehandlung implementiert werden
        throw std::out_of_range("Index out of bounds"); // Beispiel für Ausnahmebehandlung
        return;
    }
    array[index] = value; // Setzen des Wertes
}

// Methode zum Abrufen der aktuellen Größe der Liste
template <typename T>
int GenericList<T>::getSize() const
{
    return size; // Rückgabe der Größe
}

// Methode zum Löschen aller Elemente in der Liste
template <typename T>
void GenericList<T>::clear()
{
    delete[] array;          // Freigeben des Speichers
    size = 0;                // Zurücksetzen der Größe
    capacity = 5;            // Zurücksetzen der Kapazität auf Standardwert
    array = new T[capacity]; // Neu Zuweisen des Arrays
}

// Die Implementierung muss in derselben Datei oder in einer spezialisierten CPP-Datei sein
// um Template-Funktionen korrekt zu kompilieren.
