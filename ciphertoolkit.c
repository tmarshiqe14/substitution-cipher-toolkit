#include <cs50.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

// Function prototypes
bool is_valid_key(string key);
string substitute(string key, string plaintext);
void frequency_analysis(string text);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution KEY\n");
        return 1;
    }

    string key = argv[1];

    // Validate key
    if (!is_valid_key(key))
    {
        printf("Error: Key must contain 26 unique alphabetical characters.\n");
        return 1;
    }

    // Prompt user for mode
    char mode;
    do
    {
        mode = get_char("Encrypt (E) or Decrypt (D)? ");
        mode = toupper(mode);
    }
    while (mode != 'E' && mode != 'D');

    // Get input text
    string text = get_string("Enter text: ");

    // If decrypting, invert key
    if (mode == 'D')
    {
        string inverse_key = malloc(27);
        for (int i = 0; i < 26; i++)
        {
            int idx = toupper(key[i]) - 'A';
            inverse_key[idx] = 'A' + i;
        }
        inverse_key[26] = '\0';
        key = inverse_key;
    }

    // Perform substitution
    string result = substitute(key, text);
    printf("%s: %s\n", (mode == 'E') ? "Ciphertext" : "Plaintext", result);

    // Bonus: frequency analysis (basic cryptanalysis tool)
    frequency_analysis(result);

    return 0;
}

// Validate key: 26 unique alphabetic chars
bool is_valid_key(string key)
{
    if (strlen(key) != 26)
    {
        return false;
    }

    bool used[26] = {false};

    for (int i = 0; i < 26; i++)
    {
        if (!isalpha(key[i]))
        {
            return false;
        }

        int index = toupper(key[i]) - 'A';
        if (used[index])
        {
            return false;
        }
        used[index] = true;
    }
    return true;
}

// Substitution logic
string substitute(string key, string plaintext)
{
    int len = strlen(plaintext);
    string cipher_text = malloc(len + 1);

    for (int i = 0; i < len; i++)
    {
        if (isupper(plaintext[i]))
        {
            int index = plaintext[i] - 'A';
            cipher_text[i] = toupper(key[index]);
        }
        else if (islower(plaintext[i]))
        {
            int index = plaintext[i] - 'a';
            cipher_text[i] = tolower(key[index]);
        }
        else
        {
            cipher_text[i] = plaintext[i];
        }
    }
    cipher_text[len] = '\0';
    return cipher_text;
}

// Simple frequency analysis for cryptanalysis practice
void frequency_analysis(string text)
{
    int counts[26] = {0};
    int total = 0;

    for (int i = 0; text[i] != '\0'; i++)
    {
        if (isalpha(text[i]))
        {
            counts[toupper(text[i]) - 'A']++;
            total++;
        }
    }

    printf("\nLetter Frequency Analysis:\n");
    for (int i = 0; i < 26; i++)
    {
        if (counts[i] > 0)
        {
            printf("%c: %.2f%%\n", 'A' + i, (counts[i] * 100.0) / total);
        }
    }
}
