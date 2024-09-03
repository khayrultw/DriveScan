#ifndef JPEG_H
#define JPEG_H

#include <stdio.h>
#include <stdint.h>

int check_for_jpg(const uint8_t *buffer);
long extract_jpeg_file(uint8_t* buffer, int start);

#endif

