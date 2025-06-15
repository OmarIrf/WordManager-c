#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_WORDS 1000
#define MAX_LENGTH 50

// Function Prototypes
void loadWords(char words[][MAX_LENGTH], int *count);
void saveWords(char words[][MAX_LENGTH], int count);
void addWords(char words[][MAX_LENGTH], int *count);
void viewWords(char words[][MAX_LENGTH], int count);
void removeWord(char words[][MAX_LENGTH], int *count, int *deletedCount);
void showMenu();

int main() {
    char words[MAX_WORDS][MAX_LENGTH];
    int wordCount = 0;
    int deletedCount = 0;
    int choice;

    loadWords(words, &wordCount);

    do {
        showMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addWords(words, &wordCount);
                break;
            case 2:
                viewWords(words, wordCount);
                break;
            case 3:
                saveWords(words, wordCount);
                printf("Words saved. Exiting.
");
                printf("Words deleted this session: %d\n", deletedCount);
                break;
            case 4:
                removeWord(words, &wordCount, &deletedCount);
                break;
            case 5:
                printf("Words deleted this session: %d\n", deletedCount);
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 3);

    return 0;
}

void loadWords(char words[][MAX_LENGTH], int *count) {
    FILE *file = fopen("words.bin", "rb");
    if (file == NULL) {
        printf("No existing word file found. Starting fresh.\n");
        return;
    }
    fread(count, sizeof(int), 1, file);
    fread(words, sizeof(char), (*count) * MAX_LENGTH, file);
    fclose(file);
    printf("%d word(s) loaded from binary file.\n", *count);
}

void saveWords(char words[][MAX_LENGTH], int count) {
    FILE *file = fopen("words.bin", "wb");
    if (file == NULL) {
        printf("Error: Could not save to binary file.\n");
        return;
    }
    fwrite(&count, sizeof(int), 1, file);
    fwrite(words, sizeof(char), count * MAX_LENGTH, file);
    fclose(file);
    printf("Words successfully saved to binary file.\n");
}

void addWords(char words[][MAX_LENGTH], int *count) {
    int remaining = MAX_WORDS - *count;
    int num;
    if (remaining == 0) {
        printf("Word limit reached.\n");
        return;
    }

    printf("How many words do you want to add? (Max %d): ", remaining);
    scanf("%d", &num);

    if (num <= 0 || num > remaining) {
        printf("Invalid number of words.\n");
        return;
    }

    for (int i = 0; i < num; i++) {
        printf("Enter word #%d: ", *count + 1);
        scanf("%s", words[*count]);
        (*count)++;
    }

    printf("%d word(s) added successfully.\n", num);
}

void viewWords(char words[][MAX_LENGTH], int count) {
    if (count == 0) {
        printf("No words to show.\n");
        return;
    }

    printf("Current words:\n");
    for (int i = 0; i < count; i++) {
        printf("%d: %s\n", i, words[i]);
    }
}

void removeWord(char words[][MAX_LENGTH], int *count, int *deletedCount) {
    int index;
    char confirm;

    if (*count == 0) {
        printf("No words to remove.\n");
        return;
    }

    viewWords(words, *count);
    printf("Enter index of word to delete (0 to %d): ", *count - 1);
    scanf("%d", &index);

    if (index < 0 || index >= *count) {
        printf("Invalid index.\n");
        return;
    }

    printf("You selected: '%s'\n", words[index]);
    printf("Are you sure you want to delete this word? (Y/N): ");
    scanf(" %c", &confirm);

    if (confirm != 'Y' && confirm != 'y') {
        printf("Deletion cancelled.\n");
        return;
    }

    FILE *logFile = fopen("deleted_log.txt", "a");
    if (logFile != NULL) {
        time_t now = time(NULL);
        char *timestamp = ctime(&now);
        timestamp[strcspn(timestamp, "\n")] = 0;
        fprintf(logFile, "[%s] Deleted word: %s\n", timestamp, words[index]);
        fclose(logFile);
    }

    for (int i = index; i < *count - 1; i++) {
        strcpy(words[i], words[i + 1]);
    }

    (*count)--;
    (*deletedCount)++;
    printf("Word successfully removed and logged.\n");
}

void showMenu() {
    printf("\n--- WORD MANAGER MENU ---\n");
    printf("1) Add word(s)\n");
    printf("2) View all words\n");
    printf("3) Exit & Save\n");
    printf("4) Remove a word\n");
    printf("5) View how many words were deleted\n");
}
