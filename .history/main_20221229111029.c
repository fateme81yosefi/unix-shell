#include <stdio.h>
#include <string.h>
#include <stdlib.h>  
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

#define MAX_TOOL_CMD 10000
#define MAX_LETTER_SUPP 10000 
#define MAX_COMMAND_SUPP 1000 
#define HISTORY_MAX_SIZE 100

void create_Shell(){

    printf("\n\n\n\n________________________________________");
    printf("\n\n\n\n\tWelcome To My SHELL");
    printf("\n\n\n\n"
           "________________________________________");
    char *username = getenv("USER");
    printf("\n\n\nYour UserName is: @%s", username);
    printf("\n");
    sleep(1);

}

int gettingInput(char* strInput){

    char* CmdBuffer;
  
    CmdBuffer = readline("\n>>> ");

    if (strlen(CmdBuffer) != 0) {
        add_history(CmdBuffer);
        strcpy(strInput, CmdBuffer);
        return 0;
    } else {
        return 1;
    }
}

void PrintCurrentPath(){
    char dir[1024];
    getcwd(dir, sizeof(dir));
    printf("\nCurrent Direction: %s", dir);
}

void getFirstWordInEachLine(){
    FILE *textfile;
    char word[30];
    textfile = fopen("text1.txt", "r");
    if (textfile == NULL) {
        printf("file does not exist!\n");
    } else {
    while (!feof(textfile)) {
        fscanf(textfile,"%s%*[^\n]",word);
        printf("first word : %s\n", word);
        strcpy(word,""); 
    }
    } 
    fclose(textfile);
}

void getMostRepeatedWord(){
   FILE *textfile;  
    char ch, *line;  
    size_t len = 0, read;  
    char words[1000][1000], word[20];  
    int i = 0, j, k, maxCount = 0, count;  
      
    //Opens file in read mode  
    textfile = fopen("text1.txt","r");  
      
    //If file doesn't exist  
    if (textfile == NULL){  
        printf("file does not exist!\n");
        exit(0);  
    }  
      
    //Since, C doesn't provide in-built function,   
    //following code will split content of file into words  
    while ((read = getline(&line, &len, textfile)) != -1) {  
          
        for(k=0; line[k]!='\0'; k++){  
            //Here, i represents row and j represents column of two-dimensional array words   
            if(line[k] != ' ' && line[k] != '\n' && line[k] != ',' && line[k] != '.' ){  
                words[i][j++] = tolower(line[k]);  
            }  
            else{  
                words[i][j] = '\0';  
                //Increment row count to store new word  
                i++;  
                //Set column count to 0  
                j = 0;  
            }  
        }  
    }  
      
    int length = i;  
      
    //Determine the most repeated word in a file  
    for(i = 0; i < length; i++){  
        count = 1;  
        //Count each word in the file and store it in variable count  
        for(j = i+1; j < length; j++){  
            if(strcmp(words[i], words[j]) == 0 && (strcmp(words[i]," ") != 0)){  
                count++;  
            }   
        }  
        //If maxCount is less than count then store value of count in maxCount   
        //and corresponding word to variable word  
        if(count > maxCount){  
            maxCount = count;  
            strcpy(word, words[i]);  
        }  
    }  
      
    printf("Most repeated word: %s", word);  
    fclose(textfile);  
      
}

void removeEmptySpace(){

  FILE * textfile;
    int a;
    
    textfile=fopen ("text1.txt","r");
    
    if (textfile)
    {
        do {
            a = fgetc (textfile);
            if ( isgraph(a) ) putchar (a);
        } while (a != EOF);
        fclose (textfile);
    }
}

void deleteComment(){

    FILE *textfile;
    int i=0;
    char str[80];
    textfile=fopen("text1.txt","r");

    if(textfile==NULL)
    {
        printf("file does not exist!\n");
        exit(EXIT_FAILURE);
    }

    printf("\n");

    while(!feof(textfile))
    {
        fgets(str,80,textfile);
         
        if(strstr(str,"#"))
        {

            while(str[i]!='\0')
            {
                if(str[i]!='#')
                {
                    i++;
                }
                else
                {
                    putc('\0',textfile);
                    i++;
                    break;
                }
            }   
        }
        else
        {
        printf("%s", str);
        }
    }

    fclose(textfile);
    printf("\n");
}

void countLine(){
    FILE *textfile;
    int lineNumber = 0;
    char characterfile;
 
    textfile = fopen("text1.txt", "r");
    characterfile = getc(textfile);
     while (1){
          if (characterfile == '\n'  || characterfile == EOF){    
            lineNumber=lineNumber+1;
        }
        if(characterfile==EOF) break;
        //take next character from file.
        characterfile = getc(textfile);
        } 
  
    fclose(textfile); 
    printf("There are %d lines in this file . ", lineNumber);
}

int readTenLine(){

    FILE *textfile;
    char line[MAX_TOOL_CMD];
    int lineCount=0;
     
    textfile = fopen("text1.txt", "r");

    if(textfile == NULL){
        printf("file does not exist!\n");
        return 0;
    }
     
    while(fgets(line, MAX_TOOL_CMD, textfile) && lineCount<10){
        printf("%s",line);
        lineCount=lineCount+1;
    }
    return 1;
    fclose(textfile);
}

void execArgs(char** parsed){

    // Forking a child
    pid_t p1 = fork(); 
  
    if (p1 < 0) {
        printf("\nForking problem occure...");
        return;
    } else if (p1 == 0) {
        if (execvp(parsed[0], parsed) < 0) {//
            printf("\n problem was Happend...");
        }
        exit(0);
    } else {
        // waiting for child to terminate
        wait(NULL); 
        return;
    }
}

int MyCmdHandle(char** parsed){

    int NumberMyCmd = 6, i, switchOwnArg = 0;
    char* MyCmdList[NumberMyCmd];
    char* username;
  
    MyCmdList[0] = "gfwl";
    MyCmdList[1] = "gmrw";
    MyCmdList[2] = "res";
    MyCmdList[3] = "dc";
    MyCmdList[4] = "cle";
    MyCmdList[5] = "rtle";
    MyCmdList[6] = "cd";

    for (i = 0; i < NumberMyCmd; i++) {
        if (strcmp(parsed[0], MyCmdList[i]) == 0) {
            switchOwnArg = i + 1;
            break;
        }
    }

     pid_t p1 = fork(); 

    if (p1 < 0) {
        printf("\nForking problem occure...");
        return 0;
    } else if (p1 == 0) {

      switch (switchOwnArg) {

          case 1:
              getFirstWordInEachLine();
              return 1;
          case 2:
              getMostRepeatedWord();
              return 1;
          case 3:
              removeEmptySpace();
              return 1;
          case 4:
              deleteComment();
              return 1;
          case 5:
              countLine();
              return 1;
          case 6:
              readTenLine();
              return 1;
          case 7:
              chdir(parsed[1]);
              return 1;
          default:
              break;
essString(char* str, char** parsed){
    parseSpace(str, parsed);//kalamato joda mikone

    if (MyCmdHandle(parsed)) return 0;

    else return 1;
}

int main() {

    char inputString[MAX_LETTER_SUPP], *parsedArgs[MAX_COMMAND_SUPP];
    int execFlag = 0;
    create_Shell();
    

  while (1) {
        PrintCurrentPath();
        if (gettingInput(inputString))
            continue;
        execFlag = processString(inputString,
        parsedArgs);
      
   if (execFlag == 1)
            execArgs(parsedArgs);
    }
    return 0;

}