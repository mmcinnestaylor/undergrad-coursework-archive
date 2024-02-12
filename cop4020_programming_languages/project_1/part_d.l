%{
  //Marlan McInnes-Taylor
     int numInts = 0, numNegInts = 0, numDoubles = 0, numNegDoubles = 0;
%}
inttoken ([1-9][0-9]*)|0
%%
"+"?[ ]*{inttoken}            {/*printf("Matched integer: %s\n", yytext);*/ numInts++;}
-[ ]*{inttoken}               {/*printf("Matched neg integer: %s\n", yytext);*/ numNegInts++;}
("+"?[ ]*{inttoken})\.[0-9]+  {/*printf("Matched real: %s\n", yytext);*/ numDoubles++;}
(-[ ]*{inttoken})\.[0-9]+     {/*printf("Matched neg real: %s\n", yytext);*/ numNegDoubles++;}
%%
int main(){
  	yylex();
 	  printf("Number of positive integers: %d\n", numInts);
    printf("Number of negative integers: %d\n", numNegInts);
	  printf("Number of positive reals: %d\n", numDoubles);
    printf("Number of negative reals: %d\n", numNegDoubles);
  	return 0;
}
