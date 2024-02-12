%{
  //Marlan McInnes-Taylor
     char* longestWord = 0; int firstRun = 1;
%}
%%
[^ \t\n\r\f\v]+         {//printf("Matched word: %s\n", yytext);
                          if(firstRun){
                            longestWord = (char*) malloc (strlen(yytext)+1);
                            strcpy(longestWord, yytext);
                            firstRun = 0;
                          }
                          /*printf("The current longest word is: %s with length: %d\n",
                                  longestWord,strlen(longestWord));*/
                          if(strlen(yytext) > strlen(longestWord)){
                            free(longestWord);
                            longestWord = (char*) malloc (strlen(yytext)+1);
                            strcpy(longestWord, yytext);
                          }
                          /*printf("The new longest word is: %s with length: %d\n",
                                  longestWord,strlen(longestWord));*/
                        }
%%
int main(){
  	yylex();
 	  printf("Longest word in the file: %s\n", longestWord);
    printf("Number of charcters in the word: %d\n", strlen(longestWord));
  	return 0;
}
