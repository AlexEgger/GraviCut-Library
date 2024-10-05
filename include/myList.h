#ifndef MYLIST_H
#define MYLIST_H

// Template-Klasse für eine generische Liste
template <typename T>
class GenericList
{
private:
    int size;     // Aktuelle Anzahl der Elemente in der Liste
    int capacity; // Maximale Kapazität der Liste
    T *array;     // Dynamisches Array zur Speicherung der Elemente

    // Funktion zur Verdopplung der Kapazität des Arrays
    void resize();

public:
    // Konstruktor mit einer optionalen Anfangskapazität (Standard: 5)
    GenericList(int initialCapacity = 5);

    // Destruktor zum Freigeben des Speichers
    ~GenericList();

    // Kopierkonstruktor
    GenericList(const GenericList &other);

    // Zuweisungsoperator
    GenericList &operator=(const GenericList &other);

    // Methode zum Hinzufügen eines Wertes zur Liste
    void add(const T &value);

    // Methode zum Entfernen eines Elements an einem bestimmten Index
    void remove(int index);

    // Methode zum Abrufen eines Elements an einem bestimmten Index
    T &get(int index);

    // Methode zum Abrufen aller Elemente als konstantes Array
    const T *getAll() const;

    // Methode zum Setzen eines Wertes an einem bestimmten Index
    void set(int index, const T &value);

    // Methode zum Abrufen der aktuellen Größe der Liste
    int getSize() const;

    // Methode zum Löschen aller Elemente in der Liste
    void clear();
};

#endif // MYLIST_H
