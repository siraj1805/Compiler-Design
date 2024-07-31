#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Function to check if the URL starts with a valid scheme
bool hasValidScheme(const char *url) {
    return strncmp(url, "http://", 7) == 0 || strncmp(url, "https://", 8) == 0;
}

// Function to check if the URL contains a valid domain
bool hasValidDomain(const char *url) {
    const char *domainStart = strstr(url, "://");
    if (!domainStart) {
        return false;
    }
    domainStart += 3; // Skip "://"

    // Check if domain is not empty and does not start with '/'
    if (*domainStart == '\0' || *domainStart == '/') {
        return false;
    }

    return true;
}

// Function to validate the URL
bool isValidURL(const char *url) {
    return hasValidScheme(url) && hasValidDomain(url);
}

int main() {
    char url[256];

    printf("Enter the URL to validate: ");
    if (fgets(url, sizeof(url), stdin) == NULL) {
        printf("Error reading input.\n");
        return 1;
    }

    // Remove newline character if present
    url[strcspn(url, "\n")] = '\0';

    if (isValidURL(url)) {
        printf("The URL \"%s\" is valid.\n", url);
    } else {
        printf("The URL \"%s\" is invalid.\n", url);
    }

    return 0;
}