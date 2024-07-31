#include <stdio.h>
#include <ctype.h>
#include <string.h>

void findCapitalWords(char *str) {
    int i = 0;
    char word[100];
    int wordIndex = 0;
    int isCapital = 1;

    while (str[i] != '\0') {
        if (isalpha(str[i])) {
            if (!isupper(str[i])) {
                isCapital = 0;
            }
            word[wordIndex++] = str[i];
        } else {
            if (wordIndex > 0) {
                word[wordIndex] = '\0';
                if (isCapital) {
                    printf("%s\n", word);
                }
                wordIndex = 0;
                isCapital = 1;
            }
        }
        i++;
    }

    // To handle the last word
    if (wordIndex > 0) {
        word[wordIndex] = '\0';
        if (isCapital) {
            printf("%s\n", word);
        }
    }
}

int main() {
    char str[1000];
    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = '\0'; // Remove the newline character at the end

    printf("Capital words:\n");
    findCapitalWords(str);

    return 0;
}
