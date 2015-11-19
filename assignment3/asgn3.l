%{
#include "y.tab.h"
extern int yylval;
void yyerror (char *a);
%}
%%
"if"			{ printf("<%s>\n", yytext);return IF; }
"else"			{ printf("<%s>\n", yytext);return ELSE; }
"while"			{ printf("<%s>\n", yytext);return WHILE; }
"int"			{ printf("<%s>\n", yytext);return INT; }
"bool"			{ printf("<%s>\n", yytext);return BOOL; }
"main"			{ printf("<%s>\n", yytext);return MAIN; }
"return"		{ printf("<%s>\n", yytext);return RETURN; }
"true"			{ printf("<%s>\n", yytext);return TRUE; }
"void"			{ printf("<%s>\n", yytext);return VOID; }
"false"			{ printf("<%s>\n", yytext);return FALSE; }
">="			{ printf("<%s>\n", yytext);return GE; }
"<="			{ printf("<%s>\n", yytext);return LE; }
"=="			{ printf("<%s>\n", yytext);return EQ; }
"!="			{ printf("<%s>\n", yytext);return NE; }
"&&"			{ printf("<%s>\n", yytext);return AND; }
"||"			{ printf("<%s>\n", yytext);return OR; }
[a-zA-Z_][a-zA-Z0-9_]*  { printf("<%s>\n", yytext);return IDENTIFIER; }
([1-9][0-9]*|0)		{ printf("<%s>\n", yytext);return CONSTANT; }
[+(){}<>=*/;-]		{ printf("<%s>\n", yytext);return *yytext; }
[ \t\n]			;
.			printf("Unkown Character %s\n",yytext);
%%


void yyerror (char *a)
{
	printf("%s\n",a);
}
