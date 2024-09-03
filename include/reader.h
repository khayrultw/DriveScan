#ifndef READER_H
#define READER_H
#include <stdint.h>

#define BUFFER_SIZE 1024*64

int init(const char* path);
int read_next_block(uint8_t* buffer, long long buffer_size);
long long get_position();
void update_prev_bytes(uint8_t* buffer);
void get_prev_byte(uint8_t* buffer);
void close_reader();
int get_parcentage();
void go_back(int jmp);

#endif