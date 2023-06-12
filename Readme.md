Resizable and Expandable String Library
Introduction
The Resizable and Expandable String Library, also known as Flexible String Library, is a C library that provides a flexible string data structure. It allows you to dynamically resize and modify strings based on your needs. This library is useful when you need to work with strings that may change in length frequently.

Usage
### Including the Library
   To use the Flexible String Library in your C program, you need to include the header file "flexible_string.h" in your source code:

```c
#include "flexible_string.h"
```
### Creating a Flexible String
   You can create a flexible string object using the flexible_string_create function. This function takes an initial string as a parameter and returns a pointer to the created flexible string object:

```c
fxs* fs = flexible_string_create("Hello");
```
### Appending Strings
   You can append a string to a flexible string using the connect function. It takes a flexible string object and a string to be appended as parameters:

```c
fs = fs->connect(fs, " World!");
```
### Appending Formatted Strings
   You can also append a formatted string to a flexible string using the connect_f function. It takes a flexible string object, a buffer size, a format string, and additional arguments as parameters:

```c
fs = fs->connect_f(fs, 128, "The value is: %d", 42);
```
### Editing the Content
   You can edit the content of a flexible string object with a new string using the edit function. It takes a flexible string object and a new string as parameters:

```c
fs = fs->edit(fs, "New content");
```
### Editing with Formatted Strings
   You can also edit the content of a flexible string object with a formatted string using the edit_f function. It takes a flexible string object, a buffer size, a format string, and additional arguments as parameters:

```c
fs = fs->edit_f(fs, 128, "Updated value: %f", 3.14);
```
### Printing the String
You can use the standard C library function printf to print the content of the flexible string to the console:
```c
printf("%s\n", fs->string);
```


### Destroying a Flexible String
   When you are done with a flexible string object, you should destroy it to free the allocated memory using the destructor function:

```c
fs->destructor(fs);
```

### MIT License

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"),
to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

1. The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

2. The software is provided "as is", without warranty of any kind, express or implied, including but not limited to the warranties of merchantability,
   fitness for a particular purpose and noninfringement. In no event shall the authors or copyright holders be liable for any claim, damages or
   other liability, whether in an action of contract, tort or otherwise, arising from, out of or in connection with the software or the use or other
   dealings in the softwar
