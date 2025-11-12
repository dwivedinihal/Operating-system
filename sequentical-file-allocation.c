#include <stdio.h>
#include <stdbool.h>

typedef struct file {
    char name;
    int no_blocks;
    int start_block;
} File;

int main() {
    bool blocks[1000];
    for (int i = 0; i < 1000; i++) {
        blocks[i] = true; // Initially, all blocks are free
    }

    int n;
    printf("Enter number of files: ");
    scanf("%d", &n);

    File files[n];

    // Input file details
    for (int i = 0; i < n; i++) {
        getchar(); // clear buffer

        printf("\nEnter name of file %d: ", i + 1);
        scanf("%c", &files[i].name);

        printf("Enter start block of file %d: ", i + 1);
        scanf("%d", &files[i].start_block);

        printf("Enter number of blocks for file %d: ", i + 1);
        scanf("%d", &files[i].no_blocks);

        int st = files[i].start_block;

        // Mark the required blocks as allocated
        for (int j = 0; j < files[i].no_blocks; j++) {
            if (st >= 1000) {
                printf("❌ Error: Block range exceeds memory space!\n");
                break;
            }
            blocks[st++] = false;
        }
    }

    // Search for a file
    char ch;
    getchar(); // clear input buffer
    printf("\nEnter file name to search for: ");
    scanf("%c", &ch);

    bool found = false;

    for (int i = 0; i < n; i++) {
        if (files[i].name == ch) {
            printf("\n✅ FILE FOUND\n");
            printf("----------------------------\n");
            printf("File Name              : %c\n", files[i].name);
            printf("Start Block Address    : %d\n", files[i].start_block);
            printf("Number of Blocks       : %d\n", files[i].no_blocks);
            printf("Blocks Occupied        : ");

            int st = files[i].start_block;
            for (int j = 0; j < files[i].no_blocks; j++) {
                printf("%d ", st++);
            }
            printf("\n----------------------------\n");

            found = true;
            break;
        }
    }

    if (!found) {
        printf("\n❌ File not found.\n");
    }

    return 0;
}
