#include<stdio.h>



int file_size(size_t  size)
{                   
    static const char *SIZES[] = { "B", "kB", "MB", "GB" };
   
    size_t div = 0;
    size_t rem = 0;

    while (size >= 1024 && div < (sizeof SIZES / sizeof *SIZES)) {
        rem = (size % 1024);
        div++;   
        size /= 1024;
    }

    printf("%.1f %s\n", (float)size + (float)rem / 1024.0, SIZES[div]);
}