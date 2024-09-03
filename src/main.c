#include<time.h>
#include "reader.h"
#include "jpeg.h"

int main(int argc, char *argv[]) {
    if(argc <= 1) {
        printf("No device path found.\nEnter device path like /dev/sda4, or /dev/sdb1\n");
        return 0;
    }

    const char* device = argv[1];  // Replace with the actual device

    printf("Trying to scan %s\n", device);
    if (init(device) != 0) {
        return -1;
    }

    time_t initial = time(NULL);

    uint8_t buffer[BUFFER_SIZE]; // Buffer to read data in chunks
    long jpeg_offset = -1;
    int parcen = 0;

   while (read_next_block(buffer, BUFFER_SIZE) == 0) {
        int buffer_pos = check_for_jpg(buffer);
        if(buffer_pos != -1) {
            long file_size = extract_jpeg_file(buffer, buffer_pos);
            //break;
        }
        go_back(512);
        int temp_parcen = get_parcentage();
        if(temp_parcen != parcen) {
            printf("%d%% done, time took: %ds\n", parcen, time(NULL) - initial);
        }
        parcen = temp_parcen;

    }

    printf("\rScanning 100%%\n");

    if (jpeg_offset == -1) {
        printf("No JPEG file signature found.\n");
    }
    
    close_reader();
    return 0;
}
