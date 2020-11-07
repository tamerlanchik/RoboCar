//
// Created by andrey on 07.11.2020.
//

#ifndef ROBOCAR_LIB_H
#define ROBOCAR_LIB_H
#include <unistd.h>
#include <fcntl.h>

int supress_stdout() {
    fflush(stdout);

    int ret = dup(1);
    int nullfd = open("/dev/null", O_WRONLY);
    // check nullfd for error omitted
    dup2(nullfd, 1);
    close(nullfd);

    return ret;
}

void resume_stdout(int fd=STDOUT_FILENO) {
    fflush(stdout);
    dup2(fd, 1);
//    close(fd);
}

#endif //ROBOCAR_LIB_H
