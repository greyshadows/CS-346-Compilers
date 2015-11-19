%{
#define KEYWORD 1
#define IDENTIFIER 2
#define STRING 3
#define CONSTANT 4
#define OPERATOR 5
#define SPECIAL 6
%}
%%
[ \t]+	;
main |
if |
when |
else |
do |
return |
returns |
epsilon |
takes |
int |
float |
bool |
function |
in |
out 			{return KEYWORD;} 
\+ |
\- |
\* |
\/ |
= |
\< |
\> |
! |
and |
or 			{return OPERATOR;} 
[0-9]+	|
[0-9]+\.[0-9]+	|
\.[0-9]+		{return CONSTANT;}
\"[^\"\n]*\"		{return STRING; }
\( |
\) |
\{ |
\} |
; |
, |
: 			{return SPECIAL ;}
[a-zA-Z][a-zA-Z0-9]*	{return IDENTIFIER;}
\n			{return '\n';}
%%

int yywrap(void){
	return 1;
}
#include<stdio.h>
main(argc,argv)
int argc;
char *argv[];
{
int val;

while(val = yylex()){
	 switch(val){
		case 1: printf("<%s,Keyword> ",yytext);
			break;
		case 5: printf("<%s,Operator> ",yytext);
			break;
		case 4: printf("<%s,Constant> ",yytext);
			break;
		case 3: printf("<%s,String> ",yytext);
			break;
		case 6: printf("<%s,Special> ",yytext);
			break;
		case 2: printf("<%s,Indentifier> ",yytext);
			break;
		case 10: printf("\n");
	}
}
}
