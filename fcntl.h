#ifndef FCNTL_H
#define FCNTL_H
#include<stdlib.h>
#define O_RDONLY  0x000
#define O_WRONLY  0x001
#define O_RDWR    0x002
#define O_CREATE  0x200

struct FILEL {
  int desc;
};

#define size_t int
typedef struct FILEL FILE;
#endif
