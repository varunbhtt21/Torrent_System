#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
    char buffer[1024];
    int files[2];
    ssize_t count;
    struct stat st;

    int ret ;
    /* Check for insufficient parameters */
    if (argc < 3)
        return -1;
    files[0] = open(argv[1], O_RDONLY);
    if (files[0] == -1) /* Check if file opened */
        return -1;
    files[1] = open(argv[2], O_WRONLY | O_CREAT | O_EXCL | S_IRUSR | S_IWUSR );
    if (files[1] == -1) /* Check if file opened (permissions problems ...) */
    {
        close(files[0]);
        return -1;
    }

    while ((count = read(files[0], buffer, sizeof(buffer))) != 0)
        write(files[1], buffer, count);

    ret=stat(files[1], &st);


    return 0;
}


/*
if(ret != 0) {
    return false;
}
if((st.st_mode & S_IWOTH) == S_IWOTH) {

} else {

} */
