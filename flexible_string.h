/***************************************************
 * Written by...: Ning Liu
 * Date Written.: May 27, 2023
 * Purpose......: Resizable and expandable string in C. (Flexible String)
 ***************************************************/

#ifndef FLEXIBLE_STRING_H
#define FLEXIBLE_STRING_H

typedef struct fxs {
    int len;
    int free;
    struct fxs* (*connect)(struct fxs* fs, char* string);
    struct fxs* (*connect_f)(struct fxs* fs, int buff_size, char* format, ...);
    void (*destructor)(struct fxs* fs);
    struct fxs* (*edit)(struct fxs* fs, char* string);
    struct fxs* (*edit_f)(struct fxs* fs, int buff_size, char* format, ...);
    char string[];
} fxs;

fxs* flexible_string_create(char* string);

fxs* flexible_string_create_f(int buff_size, char* format, ...);

static fxs* flexible_string_resize_memory(fxs* fs, int len);

static fxs* flexible_string_connect(fxs* fs, char* string);

static fxs* flexible_string_connect_f(fxs* fs, int buff_size, char* format, ...);

static void flexible_string_destructor(fxs* fs);

static fxs* flexible_string_edit(fxs* fs, char* string);

static fxs* flexible_string_edit_f(fxs* fs, int buff_size, char* format, ...);

fxs* __flexible_string_connect_f(fxs* fs, int buff_size, char* format, va_list args);

fxs* __flexible_string_edit_f(fxs* fs, int buff_size, char* format, va_list args);

#endif
