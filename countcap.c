#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_LENGTH 1000

void findCapitalWords(char *input) {
    char word[MAX_LENGTH];
    int i = 0, j = 0;
    
    while (input[i] != '\0') {
        // Skip non-alphabetical characters
        while (input[i] != '\0' && !isalpha(input[i])) {
            i++;
        }
        
        j = 0;
        // Collect characters of the word
        while (input[i] != '\0' && isalpha(input[i])) {
            word[j++] = input[i++];
        }
        
        word[j] = '\0'; // Null-terminate the word
        
        // Check if the word is in capital letters
        int isCapital = 1;
        for (int k = 0; k < j; k++) {
            if (!isupper(word[k])) {
                isCapital = 0;
                break;
            }
        }
        
        if (isCapital && j > 0) {
            printf("%s\n", word);
        }
    }
}

int main() {
    char input[MAX_LENGTH];
    
    printf("Enter a string: ");
    fgets(input, MAX_LENGTH, stdin);
    
    // Remove the newline character if present
    input[strcspn(input, "\n")] = 0;
    
    printf("Capital words in the input are:\n");
    findCapitalWords(input);
    
    return 0;
}
