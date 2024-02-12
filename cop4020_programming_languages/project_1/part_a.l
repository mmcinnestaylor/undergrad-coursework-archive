%{
  //Marlan McInnes-Taylor
     int numWords = 0;
%}
%%
[^ \t\n\r\f\v]+             {/*printf("Matched word: %s\n", yytext);*/ numWords++;}
%%
int main(){
  	yylex();
 	  printf("The number of words in the file: %d \n", numWords);
  	return 0;
}
