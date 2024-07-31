#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_PARAGRAPH_LENGTH 1000
#define MAX_WORD_LENGTH 50
#define MAX_WORDS 500

void toLowerCase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

void removePunctuation(char *str) {
    char *src = str, *dst = str;
    while (*src) {
        if (ispunct((unsigned char)*src)) {
            src++;
        } else if (src == dst) {
            src++;
            dst++;
        } else {
            *dst++ = *src++;
        }
    }
    *dst = '\0';
}

int main() {
    char paragraph[MAX_PARAGRAPH_LENGTH];
    char *words[MAX_WORDS];
    int wordCount[MAX_WORDS] = {0};
    int numWords = 0;

    printf("Enter a paragraph: ");
    fgets(paragraph, MAX_PARAGRAPH_LENGTH, stdin);
    paragraph[strcspn(paragraph, "\n")] = '\0';

    toLowerCase(paragraph);
    removePunctuation(paragraph);

    char *token = strtok(paragraph, " ");
    while (token != NULL) {
        int found = 0;
        for (int i = 0; i < numWords; i++) {
            if (strcmp(words[i], token) == 0) {
                wordCount[i]++;
                found = 1;
                break;
            }
        }
        if (!found) {
            words[numWords] = strdup(token);
            wordCount[numWords] = 1;
            numWords++;
        }
        token = strtok(NULL, " ");
    }

    printf("Word frequencies:\n");
    for (int i = 0; i < numWords; i++) {
        printf("%s: %d\n", words[i], wordCount[i]);
        free(words[i]); 
    }

    return 0;
}
