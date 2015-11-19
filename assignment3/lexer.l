%option yylineno
%{
#include "lex_yacc_def.h"
#include "y.tab.h"

static int column = 0;
void debug_print(int type, char *value) {
	column += strlen(value);
	#ifdef DEBUG
	if (DEBUG > 1)
		printf(":: TOKEN <%d:%s>\n", type, value);
	#endif
}

void yyerror(const char *);
%}
%%
"if"					{ debug_print(IF,yytext); strcpy(yylval.keyword, yytext); return IF; }
"else"					{ debug_print(ELSE,yytext); strcpy(yylval.keyword, yytext); return ELSE; }
"while"					{ debug_print(WHILE,yytext); strcpy(yylval.keyword, yytext); return WHILE; }
"int"					{ debug_print(INT,yytext); strcpy(yylval.keyword, yytext); return INT; }
"bool"					{ debug_print(BOOL,yytext); strcpy(yylval.keyword, yytext); return BOOL; }
"main"					{ debug_print(MAIN,yytext); strcpy(yylval.keyword, yytext); return MAIN; }
"return"				{ debug_print(RETURN,yytext); strcpy(yylval.keyword, yytext); return RETURN; }
"true"					{ debug_print(TRUE,yytext); strcpy(yylval.keyword, yytext); return TRUE; }
"void"					{ debug_print(VOID,yytext); strcpy(yylval.keyword, yytext); return VOID; }
"false"					{ debug_print(FALSE,yytext); strcpy(yylval.keyword, yytext); return FALSE; }
"print"					{ debug_print(PRINT,yytext); strcpy(yylval.keyword, yytext); return PRINT; }
"input"					{ debug_print(INPUT,yytext); strcpy(yylval.keyword, yytext); return INPUT; }
"include"				{ debug_print(INCLUDE,yytext); strcpy(yylval.keyword, yytext); return INCLUDE; }
">="					{ debug_print(GE,yytext); return GE; }
"<="					{ debug_print(LE,yytext); return LE; }
"=="					{ debug_print(EQ,yytext); return EQ; }
"!="					{ debug_print(NE,yytext); return NE; }
"&&"					{ debug_print(AND,yytext); return AND; }
"||"					{ debug_print(OR,yytext); return OR; }
[a-zA-Z_][a-zA-Z0-9_]*  { debug_print(IDENTIFIER,yytext); strcpy(yylval.identifier, yytext); return IDENTIFIER; }
(-[1-9][0-9]*)			{ debug_print(CONSTANT,yytext); yylval.constant = atoi(yytext); return CONSTANT; }
([1-9][0-9]*|0)			{ debug_print(CONSTANT,yytext); yylval.constant = atoi(yytext); return CONSTANT; }
\"[^"\n]*\"			{ debug_print(STRING_LITERAL,yytext); strcpy(yylval.literal, yytext); return STRING_LITERAL; }
[-+(){}<>=*/;~]			{ debug_print(yytext[0],yytext); return *yytext; }
[ \t]					{ debug_print(yytext[0], yytext); }
[\n]					{ column = 0; }
.						{ debug_print(yytext[0],yytext); return yytext[0]; }
%%

int yywrap(void) {
	return 1;
}

void yyerror(const char *err) {
	printf("line %d::%d %s, found %s\n", yylineno, column, err, yytext);
}