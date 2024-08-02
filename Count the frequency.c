#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 1000

// Function to convert a string to lowercase
void to_lowercase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

// Function to count the frequency of a word in a sentence
int count_word_frequency(const char *sentence, const char *word) {
    char sentence_copy[MAX_LEN];
    char *token;
    int count = 0;

    // Copy the sentence to avoid modifying the original
    strncpy(sentence_copy, sentence, MAX_LEN - 1);
    sentence_copy[MAX_LEN - 1] = '\0'; // Ensure null-termination

    // Convert both sentence and word to lowercase for case-insensitive comparison
    to_lowercase(sentence_copy);
    char word_copy[MAX_LEN];
    strncpy(word_copy, word, MAX_LEN - 1);
    word_copy[MAX_LEN - 1] = '\0';
    to_lowercase(word_copy);

    // Tokenize the sentence and count occurrences of the word
    token = strtok(sentence_copy, " \t\n");
    while (token != NULL) {
        if (strcmp(token, word_copy) == 0) {
            count++;
        }
        token = strtok(NULL, " \t\n");
    }

    return count;
}

int main() {
    char sentence[MAX_LEN];
    char word[MAX_LEN];

    printf("Enter a sentence: ");
    fgets(sentence, sizeof(sentence), stdin);

    // Remove the newline character from the end of the sentence
    size_t len = strlen(sentence);
    if (len > 0 && sentence[len - 1] == '\n') {
        sentence[len - 1] = '\0';
    }

    printf("Enter the word to search for: ");
    fgets(word, sizeof(word), stdin);

    // Remove the newline character from the end of the word
    len = strlen(word);
    if (len > 0 && word[len - 1] == '\n') {
        word[len - 1] = '\0';
    }

    int frequency = count_word_frequency(sentence, word);
    printf("The word '%s' appears %d times in the sentence.\n", word, frequency);

    return 0;
}
