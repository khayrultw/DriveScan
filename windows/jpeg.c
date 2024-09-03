#include <stdbool.h>
#include "jpeg.h"
#include "reader.h"

int check_for_jpg(const uint8_t *buffer) {
    for (size_t i = 0; i < BUFFER_SIZE-10; ++i) {
        if(buffer[i] == 0xFF && buffer[i+1] == 0xD8) {
            //printf("%c%c%c%c\n", buffer[i+6], buffer[i+7], buffer[i+8], buffer[i+9]);
            if (buffer[i+2] == 0xFF && (buffer[i+3] == 0xE0 || buffer[i+3] == 0xE1)) {
                if (buffer[i+6] == 'J' && buffer[i+7] == 'F' &&
                    buffer[i+8] == 'I' && buffer[i+9] == 'F') {
                    return i;
                } else if (buffer[i+6] == 'E' && buffer[i+7] == 'x' &&
                           buffer[i+8] == 'i' && buffer[i+9] == 'f') {
                    return i;
                }
            }
        }
    }
   // printf("\n");

    return -1;
}

long extract_jpeg_file(uint8_t* buffer, int start) {
    char file_name[50];
    static int file_counter = 0;
    sprintf(file_name, "out/extracted_image%d.jpg", file_counter++);

    FILE* outFile = fopen(file_name, "wb");

    if (!outFile) {
        fprintf(stderr, "Failed to open output file.\n");
        return -1;
    }

    uint16_t prevByte = 0;
    bool endOfJPEGFound = false;
    long file_size = BUFFER_SIZE - start;

    fwrite(buffer+start, 1, file_size, outFile);


    for(int k = 0; k < 128; k++) {
        read_next_block(buffer, BUFFER_SIZE);
        for (int i = 0; i < BUFFER_SIZE; i++) {
            file_size++;
            if (prevByte == 0xFF && buffer[i] == 0xD9) {
                endOfJPEGFound = true;
                fwrite(buffer, 1, i+1, outFile);
                break;
            }
            prevByte = buffer[i];
        }
        if (endOfJPEGFound) break;
        fwrite(buffer, 1, BUFFER_SIZE, outFile);
    }

    if (!endOfJPEGFound) {
        fprintf(stderr, "End of JPEG file not found, file might be incomplete.\n");
    } else {
        printf("\nExtracted successfully as '%s'.\n", file_name);
    }

    fclose(outFile);
    return file_size;
}

