%{
  //Marlan McInnes-Taylor
     int numVowels = 0, numConsonants = 0;
%}
vowel     A|a|E|e|I|i|O|o|U|u|Y|y
consonant B|b|C|c|D|d|F|f|G|g|H|h|J|j|K|k|L|l|M|m|N|n|P|p|Q|q|R|r|S|s|T|t|V|v|W|w|X|x|Z|z
%%
{vowel}         {/*printf("Matched vowel: %s\n", yytext);*/ numVowels++;}
{consonant}     {/*printf("Matched consonant: %s\n", yytext);*/ numConsonants++;}
%%
int main(){
  	yylex();
 	  printf("Number of vowels: %d\n", numVowels);
	  printf("Number of consonants: %d\n", numConsonants);
  	return 0;
}
