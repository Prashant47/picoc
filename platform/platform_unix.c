#include "../picoc.h"
#include "../stdio.h"
#include "../interpreter.h"
/* mark where to end the program for platforms which require this */
jmp_buf PicocExitBuf;

void PlatformCleanup()
{
}
void putchar(char ch){
	write(1,&ch,sizeof(ch));
}
char *fgets(char *s,int size,FILE *stream){
	int i;
	char ch;
	for(i = 0 ; i < size -1 ; i++){
		fread(&ch,1,1,stream);
		if(ch == '\n' || ch == EOF ){
			break;
		}else{
			*(s+i) = ch;
		}
	}
	*(s+i) = '\0';
	return s;
}
/* get a line of interactive input */
char *PlatformGetLine(char *Buf, int MaxLen, const char *Prompt)
{
/*
#ifdef USE_READLINE
    if (Prompt != NULL)
    {
        // use GNU readline to read the line 
        char *InLine = readline(Prompt);
        if (InLine == NULL)
            return NULL;
    
        Buf[MaxLen] = '\0';
        strncpy(Buf, InLine, MaxLen-1);
        strncat(Buf, "\n", MaxLen-1);
        
        if (InLine[0] != '\0')
            add_history(InLine);
            
        free(InLine);
        return Buf;
    }
#endif
*/

    if (Prompt != NULL)
        printf("%s", Prompt);
        
    //fflush(stdout);
    return fgets(Buf, MaxLen, stdin);
}

/* get a character of interactive input */
int PlatformGetCharacter()
{
    //fflush(stdout);
    return getchar();
}

/* write a character to the console */
void PlatformPutc(unsigned char OutCh, union OutputStreamInfo *Stream)
{
    putchar(OutCh);
}

/* read a file into memory */
char *PlatformReadFile(const char *FileName)
{
    struct stat FileInfo;
    char *ReadText;
    FILE *InFile;
    int BytesRead;
    int tmpvar;
    if ( (tmpvar = stat(FileName, &FileInfo)) < 0 ){
        ProgramFail(NULL, "can't read file %s\n", FileName);
    }
    if(tmpvar > 0)
	    FileInfo.st_size = tmpvar;
    /*printf("%d %s\n",FileInfo.st_size, FileName); */

    ReadText = (char *)malloc(sizeof(char) * (FileInfo.st_size + 5));

    if (ReadText == NULL)
        ProgramFail(NULL, "out of memory\n");
        
    InFile = fopen(FileName, "r");
    if (InFile == NULL)
        ProgramFail(NULL, "can't read file %s\n", FileName);
 
    BytesRead = fread(ReadText, 1, FileInfo.st_size, InFile);
// printf("bytes read are %d\n ",BytesRead);   
    
    if (BytesRead == 0)
        ProgramFail(NULL, "can't read file %s\n", FileName);
	
    ReadText[BytesRead] = '\0';
//printf("%s\n",ReadText);
//    fclose(InFile);
    return ReadText;   
   printf("Here\n"); 
}

/* read and scan a file for definitions */
void PicocPlatformScanFile(const char *FileName)
{  
    char *SourceStr = PlatformReadFile(FileName);
    PicocParse(FileName, SourceStr, strlen(SourceStr), TRUE, FALSE, TRUE);
}

/* exit the program */
void PlatformExit(int RetVal)
{
    PicocExitValue = RetVal;
//    longjmp(PicocExitBuf, 1);
    exit(1);
}

