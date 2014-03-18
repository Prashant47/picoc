#ifndef STDIO_H
#define STDIO_H
#include"fcntl.h"

extern FILE *stdout,*stdin,*stderr;
#define size_t int
/*getting some things from stdio.h that are required here */
#ifndef EOF
# define EOF (-1)
#endif

#ifndef BUFSIZ
# define BUFSIZ 256
#endif

#ifndef FILENAME_MAX
# define FILENAME_MAX 32
#endif

/* The possibilities for the third argument to `setvbuf'.  */
#define _IOFBF 0		/* Fully buffered.  */
#define _IOLBF 1		/* Line buffered.  */
#define _IONBF 2		/* No buffering.  */

/*definations for stdout,stdin */
int checkmode( const char *mode, int *seek);
FILE *fopen(const char *path, const char* mode);
int fread( void *ptr, size_t size, size_t nmemb, FILE *stream); 
int fwrite(const void *ptr, size_t size , size_t nmemb, FILE *stream);
int fclose(FILE *fp);
extern char getchar (void);
extern int printf (char *, ...);
#endif
