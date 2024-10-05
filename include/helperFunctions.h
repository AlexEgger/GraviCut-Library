#ifndef HELPERFUNCTIONS_H
#define HELPERFUNCTIONS_H

#include <stdint.h> // Für int32_t und int16_t
#include <string.h> // Für strlen, strcat
#include "myList.h" // Für GenericList
#include "myStructs.h" // Für Auftrag und Produkt

// Helper API to convert decimal to ASCII
int32_t Dec2Ascii(char *pSrc, int32_t value);

// Fills an existing list with test data
void TestDatenBefuellen(GenericList<Auftrag> &auftraege);

// Converts the given product to a string
void AddProductToStringArray(const Produkt &affectedProduct);

// Converts the given length into a suitable string for the view
void AddLengthToStringArray(const int &affectedInteger);

#endif // HELPERFUNCTIONS_H
