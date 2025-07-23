#include "parser.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

char* getBuffer(char* path) {
    FILE* file = fopen(path, "r");

    if (!file) {
        printf("Error opening file");
        exit(1);
    }

    char* buffer = (char*) malloc(sizeof(char) * 65536);

    bool inString = false;

    int c;
    int i = 0;

    while ((c = fgetc(file)) != EOF) {
        if (c == '"') {
            inString = !inString;
        }

        if (c != ' ' && c != '\n' && !inString) {
            buffer[i++] = c;
        } else if (inString) {
            buffer[i++] = c;
        }
    }

    buffer[i] = '\0';

    return buffer;
}

HashTable* parseNodes() {
    HashTable* table = createHashTable(CAPACITY);

    char* buffer = getBuffer("tests/nodes.gdb");
    char* nodeData = NULL;

    int start = -1;
    int end = 0;
    int i = 0;

    
    while (buffer[i] != '\0') {
        if (buffer[i] == '{') {
            start = i + 1; 
        } else if (buffer[i] == '}' && start != -1) {
            end = i - 1;

            if (start <= end) {
                nodeData = (char*) malloc(end - start + 2);
                strncpy(nodeData, &buffer[start], end - start + 1);
                nodeData[end - start + 1] = '\0';

                // TODO: Parse nodeData, handle node creation and insertion into HashTable :3
                char* token = strtok(nodeData, ";");

                while (token != NULL) {
                    printf("%s\n", token);
                    token = strtok(NULL, ";");
                }

                free(nodeData);
                nodeData = NULL;
            }

            start = -1;
        }

        i++;
    }

    free(buffer);

    return table;
}
