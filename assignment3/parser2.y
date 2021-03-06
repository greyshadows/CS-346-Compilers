%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define yacc_header 1
#include "lex_yacc_def.h"

int yylex(void);
void yyerror (char *);
void debug(char *msg) {
	#ifdef DEBUG
		printf("%s\n", msg);
	#endif
}

%}

%union 
{
	int constant;
	char identifier[255];
	char keyword[255];
	char literal[255];
	struct Node *node;
};

%token <constant> CONSTANT
%token <identifier> IDENTIFIER
%token <literal> STRING_LITERAL
%token <keyword> INT BOOL MAIN IF ELSE WHILE RETURN TRUE FALSE GE LE NE EQ AND OR VOID PRINT INPUT INCLUDE
%nonassoc NO_ELSE
%nonassoc ELSE
%type <node> begin start declarations declaration type block variable_declaration function_declaration RETURN_statement statements argument_list argument statement function_call_statement parameters IF_statement WHILE_statement all_expression expression assignment_expression expression_unit unary_expression additive_expression multiplicative_expression logical_expression conditional_expression include_statement input_statement output_statement
%error-verbose
%%
begin: start 		{ print_tree($1); exit(0); }

start : declarations VOID  MAIN  '('  argument_list ')'  block 	{ $$ = mk_start($1, $5, $7); }
	| VOID  MAIN  '('  argument_list ')'  block 				{ $$ = mk_start(NULL, $4, $6); }
	| declarations VOID  MAIN  '('  ')'  block 					{ $$ = mk_start($1, NULL, $6); }
	| VOID  MAIN  '('  ')'  block 								{ $$ = mk_start(NULL, NULL, $5); }
	;

declarations: declaration 					{ $$ = $1; }
	| declaration declarations 				{ $$ = mk_statement_list($1, $2); }
	;

declaration: variable_declaration 			{ $$ = $1; }
	| function_declaration					{ $$ = $1; }
	| include_statement						{ $$ = $1; }
	;

include_statement: INCLUDE STRING_LITERAL ';'	{ $$ = mk_function_call(mk_keyword($1), mk_literal($2)); }

type: INT 						{ $$ = mk_keyword($1); }
	| BOOL						{ $$ = mk_keyword($1); }
	;

block: '{' statements '}'		{ $$ = $2; } 
	| '{' '}'					{ $$ = NULL;}
	;

variable_declaration :   type IDENTIFIER ';'   { $$ = mk_variable_declaration($1, mk_identifier($2), NULL); }
	|  type IDENTIFIER '=' all_expression ';'  { $$ = mk_variable_declaration($1, mk_identifier($2), $4); }
	;

function_declaration :   type IDENTIFIER '('  ')' '{' statements '}' { $$ = mk_function_declaration($1, mk_identifier($2), NULL, $6, NULL); }
	|  type IDENTIFIER '('  argument_list ')' '{' statements '}'	  { $$ = mk_function_declaration($1, mk_identifier($2), $4, $7, NULL); }
	;

RETURN_statement :  RETURN all_expression ';' { $$ = mk_return($2); }
	;

statements :  statement 		{ $$ = $1; }
	| statement statements 		{ $$ = mk_statement_list($1, $2); }
	;

argument_list :  argument  		  { $$ = $1; }
	| argument ','  argument_list { $$ = mk_argument_list($3, $1); }
	;

argument :  type  IDENTIFIER 	{ $$ = mk_argument($1, mk_identifier($2)); }
	;

statement :   ';' 				{ $$=NULL; }
	| variable_declaration 		{ $$=$1;}
	| expression ';' 			{ $$=$1;}
	| assignment_expression ';' { $$=$1;}
	| IF_statement 				{ $$=$1;}
	| WHILE_statement 			{ $$=$1;}
	| function_call_statement 	{ $$=$1;}
	| RETURN_statement			{ $$=$1;}
	| block						{ $$=$1;}
	| input_statement 			{ $$=$1;}
	| output_statement 			{ $$=$1;}
	| error ';'					{ yyclearin; yyerrok; }
	| error '}'					{ yyclearin; yyerrok; }
	| error '\n'				{ yyclearin; yyerrok; }
	;

input_statement: INPUT '~' IDENTIFIER ';'  { $$ = mk_function_call(mk_keyword($1), mk_identifier($3));}

output_statement: PRINT '~' all_expression ';'  { $$ = mk_function_call(mk_keyword($1), $3);}

function_call_statement :   IDENTIFIER '(' parameters ')' ';' { $$ = mk_function_call(mk_identifier($1), $3); }
	| IDENTIFIER '(' ')' ';'								 { $$ = mk_function_call(mk_identifier($1), NULL); }	
	;

parameters :  all_expression 			{ $$ = $1; }
	| parameters ',' all_expression 	{ $$ = mk_parameter_list($1, $3); }
	;

IF_statement :  IF  '(' conditional_expression ')' statement  %prec NO_ELSE		{ $$ = mk_if($3, $5, NULL); }
	| IF '(' conditional_expression ')' statement ELSE statement 				{ $$ = mk_if($3, $5, $7); }
	;

WHILE_statement :  WHILE '(' conditional_expression ')' statement { $$ = mk_while($3,$5);}
	;

all_expression :  expression 	{ $$ = $1;}
	| conditional_expression	{ $$ = $1;}
	;

expression :  additive_expression	{ $$ = $1;}
	;

assignment_expression :  IDENTIFIER '=' all_expression	{$$ = mk_operator('=', 2, mk_identifier($1), $3); }
	;

expression_unit :  CONSTANT 	{ $$ = mk_constant($1);}
	| IDENTIFIER 		{ $$ = mk_identifier($1);}
	| '(' expression ')'	{ $$ =$2; }
	;
unary_expression :  expression_unit { $$ = $1;}
	| '-' expression_unit	    { $$ = mk_operator('-',1,$2);}
	;

additive_expression :  multiplicative_expression 		{ $$ = $1;}
	| additive_expression '+' multiplicative_expression 	{ $$ = mk_operator('+',2,$1,$3);}
	| additive_expression '-' multiplicative_expression	{ $$ = mk_operator('-',2,$1,$3);}
	;

multiplicative_expression :  unary_expression 			{ $$ = $1;}
	| multiplicative_expression '*' unary_expression 	{ $$ = mk_operator('*',2,$1,$3);}
	| multiplicative_expression '/' unary_expression	{ $$ = mk_operator('/',2,$1,$3);}
	;

logical_expression :  expression_unit '<' expression_unit 	{ $$ = mk_operator('<',2,$1,$3);}
	| expression_unit '>' expression_unit			{ $$ = mk_operator('>',2,$1,$3);}
	| expression_unit LE expression_unit			{ $$ = mk_operator(LE,2,$1,$3);}
	| expression_unit GE expression_unit			{ $$ = mk_operator(GE,2,$1,$3);}
	| expression_unit EQ expression_unit			{ $$ = mk_operator(EQ,2,$1,$3);}
	| expression_unit NE expression_unit			{ $$ = mk_operator(NE,2,$1,$3);}
	| TRUE											{ $$ = mk_keyword($1);}
	| FALSE											{ $$ = mk_keyword($1);}
	| '(' logical_expression ')'				    { $$ = $2;}
	;

conditional_expression : logical_expression			{ $$ = $1;}
	| conditional_expression AND logical_expression		{ $$ = mk_operator(AND,2,$1,$3);}
	| conditional_expression OR logical_expression		{ $$ = mk_operator(OR,2,$1,$3);}
	;
%%

int main(void) {
	yyparse();
	return 0;
}
