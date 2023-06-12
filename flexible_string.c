/***************************************************
 * Written by...: Ning Liu
 * Date Written.: May 27, 2023
 * Purpose......: Resizable and expandable string in C. (Flexible String)
 ***************************************************/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "./flexible_string.h"

#define FDS_MAX_PREALLOC (1024 * 1024)

/**
 * Function: flexible_string_create
 * ---------------------------------
 * Creates a flexible string (fxs) object with the given initial string.
 *
 * @param string: Initial string to be assigned to the flexible string
 * @return: Pointer to the created flexible string object (fxs*)
 */
fxs* flexible_string_create(char* string) {
    int str_len = (int) strlen(string);
    fxs* fs;
    fs = (fxs*) malloc(sizeof(fxs) + str_len + 1);
    if (NULL == fs) {
        exit (1);
    }

    fs->len = str_len;
    fs->free = 0;
    fs->connect = &flexible_string_connect;
    fs->connect_f = &flexible_string_connect_f;
    fs->destructor = &flexible_string_destructor;
    fs->edit = &flexible_string_edit;
    fs->edit_f = &flexible_string_edit_f;
    memcpy(fs->string, string, str_len);
    fs->string[str_len] = '\0';

    return fs;
}

/**
 * Function: flexible_string_create_f
 * -----------------------------------
 * Creates a flexible string (fxs) object with the formatted string based on the provided format and arguments.
 *
 * @param buff_size: Size of the buffer used to hold the formatted string
 * @param format: Format string specifying the desired format
 * @param ...: Additional arguments to be formatted
 * @return: Pointer to the created flexible string object (fxs*)
 */
fxs* flexible_string_create_f(int buff_size, char* format, ...) {
    char buf[buff_size];
    va_list args;
    va_start(args, format);
    vsnprintf(buf, buff_size, format, args);
    va_end(args);
    return flexible_string_create(buf);
}

/**
 * Function: flexible_string_resize_memory
 * ---------------------------------------
 * Resizes the memory allocation for a flexible string (fxs) object to accommodate a new length.
 *
 * @param fs: Pointer to the flexible string object to be resized
 * @param len: New length to accommodate in the flexible string
 * @return: Pointer to the resized flexible string object (fxs*)
 */
static fxs* flexible_string_resize_memory(fxs* fs, int len) {
    if (fs->free >= len) {
        return fs;
    }

    int new_len = fs->len + len;
    if (new_len < FDS_MAX_PREALLOC) {
        new_len = new_len * 2;
    } else {
        new_len = new_len + FDS_MAX_PREALLOC;
    }

    fxs* tmp_fs = (fxs *) realloc(fs,  sizeof(fxs) + new_len + 1);
    if (NULL == tmp_fs) {
        exit (1);
    }

    fs = tmp_fs;
    fs->free = new_len - tmp_fs->len;

    return fs;
}

/**
 * Function: flexible_string_connect
 * ---------------------------------
 * Connects (appends) a given string to a flexible string (fxs) object.
 *
 * @param fs: Pointer to the flexible string object to which the string will be connected
 * @param append_string: String to be connected (appended) to the flexible string
 * @return: Pointer to the modified flexible string object (fxs*)
 */
static fxs* flexible_string_connect(fxs* fs, char* append_string) {
    int append_str_len = (int) strlen(append_string);
    fs = flexible_string_resize_memory(fs, append_str_len);
    memcpy(fs->string + fs->len, append_string, append_str_len);
    fs->string[fs->len + append_str_len] = '\0';
    fs->len = fs->len + append_str_len;
    fs->free = fs->free - append_str_len;

    return fs;
}

/**
 * Function: flexible_string_connect_f
 * -----------------------------------
 * Connects (appends) a formatted string to a flexible string (fxs) object.
 *
 * @param fs: Pointer to the flexible string object to which the formatted string will be connected
 * @param buff_size: Size of the buffer used to hold the formatted string
 * @param format: Format string specifying the desired format
 * @param ...: Additional arguments to be formatted
 * @return: Pointer to the modified flexible string object (fxs*)
 */
static fxs* flexible_string_connect_f(fxs* fs, int buff_size, char* format, ...) {
    va_list args;
    va_start(args, format);
    fs = __flexible_string_connect_f(fs, buff_size, format, args);
    va_end(args);

    return fs;
}

/**
 * Function: flexible_string_destructor
 * ------------------------------------
 * Destructor function for a flexible string (fxs) object.
 *
 * @param fs: Pointer to the flexible string object to be destroyed
 */
static void flexible_string_destructor(fxs* fs) {
    free(fs);
}

/**
 * Function: flexible_string_edit
 * ------------------------------
 * Edits the content of a flexible string (fxs) object with a new string.
 *
 * @param fs: Pointer to the flexible string object to be edited
 * @param new_string: New string to replace the content of the flexible string
 * @return: Pointer to the modified flexible string object (fxs*)
 */
static fxs* flexible_string_edit(fxs* fs, char* new_string) {
    int new_len = (int) strlen(new_string);
    int diff_len = new_len - fs->len;
    fs = flexible_string_resize_memory(fs, diff_len);
    memcpy(fs->string, new_string, new_len);
    fs->string[new_len] = '\0';
    fs->len = new_len;
    fs->free = fs->free - diff_len;

    return fs;
}

/**
 * Function: flexible_string_edit_f
 * --------------------------------
 * Edits the content of a flexible string (fxs) object with a formatted string.
 *
 * @param fs: Pointer to the flexible string object to be edited
 * @param buff_size: Size of the buffer used to hold the formatted string
 * @param format: Format string specifying the desired format
 * @param ...: Additional arguments to be formatted
 * @return: Pointer to the modified flexible string object (fxs*)
 */
static fxs* flexible_string_edit_f(fxs* fs, int buff_size, char* format, ...) {
    va_list args;
    va_start(args, format);
    fs = __flexible_string_edit_f(fs, buff_size, format, args);
    va_end(args);
    return fs;
}

/**
 * Function: __flexible_string_connect_f
 * -------------------------------------
 * Connects (appends) a formatted string to a flexible string (fxs) object using a variable argument list.
 *
 * @param fs: Pointer to the flexible string object to which the formatted string will be connected
 * @param buff_size: Size of the buffer used to hold the formatted string
 * @param format: Format string specifying the desired format
 * @param args: Variable argument list containing additional arguments to be formatted
 * @return: Pointer to the modified flexible string object (fxs*)
 */
fxs* __flexible_string_connect_f(fxs* fs, int buff_size, char* format, va_list args) {
    char buf[buff_size];
    vsnprintf(buf, buff_size, format, args);
    return flexible_string_connect(fs, buf);
}

/**
 * Function: __flexible_string_edit_f
 * ----------------------------------
 * Edits the content of a flexible string (fxs) object with a formatted string using a variable argument list.
 *
 * @param fs: Pointer to the flexible string object to be edited
 * @param buff_size: Size of the buffer used to hold the formatted string
 * @param format: Format string specifying the desired format
 * @param args: Variable argument list containing additional arguments to be formatted
 * @return: Pointer to the modified flexible string object (fxs*)
 */
fxs* __flexible_string_edit_f(fxs* fs, int buff_size, char* format, va_list args) {
    char buf[buff_size];
    vsnprintf(buf, buff_size, format, args);
    return flexible_string_edit(fs, buf);
}
