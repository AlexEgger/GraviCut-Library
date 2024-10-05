#include "helperFunctions.h"

/**
 * @brief Converts a decimal value to ASCII and appends it to the given null-terminated string.
 *
 * @param pSrc Pointer to the destination string.
 * @param value The integer value to convert.
 * @return int32_t Returns 0 on success.
 */
int32_t Dec2Ascii(char *pSrc, int32_t value)
{
    int16_t Length; // Variable to hold the length of the string
    char *pdst, charval;
    int32_t CurrVal = value, tmpval, i;
    char tmparray[16]; // Assumed that output string will not exceed 16 characters including null terminator
    char idx = 0;

    // Get the length of the string
    Length = strlen(pSrc);
    pdst = pSrc + Length;

    // Cross check whether 0 is sent
    if (0 == value)
    {
        *pdst++ = '0';
        *pdst++ = '\0';
        return 0;
    }

    // Handling of negative number
    if (CurrVal < 0)
    {
        *pdst++ = '-';
        CurrVal = -CurrVal;
    }

    // Insert the digits
    while (CurrVal > 0)
    {
        tmpval = CurrVal;
        CurrVal /= 10;
        tmpval = tmpval - CurrVal * 10;
        charval = '0' + tmpval;
        tmparray[idx++] = charval; // Store digits in reverse order
    }

    // Flip the digits to normal order and append to the destination string
    for (i = 0; i < idx; i++)
    {
        *pdst++ = tmparray[idx - i - 1];
    }
    *pdst++ = '\0'; // Null terminate the string

    return 0; // Indicate success
}

/**
 * @brief Fills a list with test data.
 *
 * @param auftraege Reference to the list of orders.
 */
void TestDatenBefuellen(GenericList<Auftrag> &auftraege)
{
    for (byte i = 0; i < testMengeAuftraege; i++)
    {
        Auftrag auftrag; // Use the default constructor

        for (int j = 0; j < testMengeProdukte; j++)
        {
            int produktTypBefuellen = ((j + i + 1) % 3) + 1;
            int produktMengeBefuellen = i + 1;
            int produktLaengeBefuellen = 200 + 20 * ((j + 1) * (i + 1));

            Produkt produktBefuellen(produktTypBefuellen, produktMengeBefuellen, produktLaengeBefuellen);
            auftrag.addProdukt(produktBefuellen);
        }

        auftraege.add(auftrag);
    }
}

/**
 * @brief Converts the given product to a string and appends it to StringArray.
 *
 * @param affectedProduct The product to convert.
 */
void AddProductToStringArray(const Produkt &affectedProduct)
{
    strcat(StringArray, "Produkt ");
    Dec2Ascii(StringArray, (int32_t)affectedProduct.produktTyp);
    strcat(StringArray, ", ");
    Dec2Ascii(StringArray, (int32_t)affectedProduct.produktMenge);
    strcat(StringArray, " x ");
    AddLengthToStringArray(affectedProduct.produktLaenge);
}

/**
 * @brief Converts the given length into a string suitable for the view.
 *
 * @param affectedInteger The integer length to convert.
 */
void AddLengthToStringArray(const int &affectedInteger)
{
    Dec2Ascii(StringArray, (int32_t)affectedInteger / 100); // Convert to whole cm
    strcat(StringArray, ",");

    // Append a leading zero if necessary for the decimal part
    if (affectedInteger % 100 < 10)
    {
        strcat(StringArray, "0");
    }

    Dec2Ascii(StringArray, (int32_t)affectedInteger % 100); // Convert to cm decimal part
    strcat(StringArray, "cm");
}
