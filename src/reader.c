#include "reader.h"
#include <stdio.h>

static FILE* disk = NULL;
static long long disk_size = -1;


int init(const char* path) {
    disk = fopen(path, "rb");
    if (!disk) {
        fprintf(stderr, "Failed to open device: %s\n", path);
        return -1;
    }

    fseek(disk, 0, SEEK_END);
    disk_size = ftell(disk);
    fseek(disk, 0, SEEK_SET);

    return 0;
}

int read_next_block(uint8_t* buffer, long long buffer_size) {
    if (disk == NULL) {
        fprintf(stderr, "Disk not initialized.\n");
        return -1;
    }

    if (fread(buffer, 1, buffer_size, disk) != buffer_size) {
        if (feof(disk)) {
            printf("End of file reached.\n");
            return 1;
        } else {
            fprintf(stderr, "Error reading from disk.\n");
            return -1;
        }
    }

    return 0;
}

long long get_position() {
    return ftell(disk);
}

int get_parcentage() {
    return 100 * get_position() / disk_size;
}

void go_back(int jmp) {
    long long current = ftell(disk);
    fseek(disk, current-jmp, SEEK_SET);
}

void close_reader() {
    if (disk != NULL) {
        fclose(disk);
        disk = NULL;
    }
}


/*
   fseek(disk, 0, SEEK_END);
    long disk_size = ftell(disk);
    fseek(disk, 0, SEEK_SET);
    long current_pos = 0; 
*/
