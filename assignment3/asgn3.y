%token INT IDENTIFIER BOOL CONSTANT MAIN IF ELSE WHILE RETURN TRUE FALSE GE LE NE EQ AND OR VOID
%nonassoc NO_ELSE
%nonassoc ELSE
%%
start : declarations VOID  MAIN  '('  argument_list ')'  block 
	| VOID  MAIN  '('  argument_list ')'  block 
	| declarations VOID  MAIN  '('  ')'  block 
	| VOID  MAIN  '('  ')'  block 
	;

declarations: variable_declaration 
	| function_declaration
	;

type: INT 
	| BOOL
	;

block: '{' statements '}' 
	| '{' '}'
	;

variable_declaration :   type IDENTIFIER ';'  
	|  type IDENTIFIER '=' all_expression ';' 
	;

function_declaration :   type IDENTIFIER '('  ')' '{' statements RETURN_statement '}' 
	|  type IDENTIFIER '('  argument_list ')' '{' statements RETURN_statement '}'
	;

RETURN_statement :  RETURN all_expression ';'
	;

statements :  statement 
	| statement statements
	;

argument_list :  argument  
	| argument ','  argument_list
	;

argument :  type  IDENTIFIER
	;

statement :   ';' 
	| variable_declaration 
	| expression ';' 
	| assignment_expression ';' 
	| IF_statement 
	| WHILE_statement 
	| function_call_statement 
	| block
	| error ';'
	| error '}'
	;

function_call_statement :  IDENTIFIER '(' parameters ')' ';' 
	| IDENTIFIER '(' ')' ';'
	;

parameters :  all_expression 
	| parameters ',' all_expression
	;

IF_statement :  IF  '(' logical_expression ')' statement  %prec NO_ELSE
	| IF '(' logical_expression ')' statement ELSE statement
	;

WHILE_statement :  WHILE '(' logical_expression ')' statement
	;

all_expression :  expression 
	| logical_expression
	;

expression :  additive_expression
	;

assignment_expression :  IDENTIFIER '=' all_expression
	;

expression_unit :  CONSTANT 
	| IDENTIFIER 
	| '(' expression ')'
	;
unary_expression :  expression_unit 
	| '-' expression_unit
	;

additive_expression :  multiplicative_expression 
	| additive_expression '+' multiplicative_expression 
	| additive_expression '-' multiplicative_expression
	;

multiplicative_expression :  unary_expression 
	| multiplicative_expression '*' unary_expression 
	| multiplicative_expression '/' unary_expression
	;

logical_expression :  expression_unit '<' expression_unit 
	| expression_unit '>' expression_unit
	| expression_unit LE expression_unit
	| expression_unit GE expression_unit
	| expression_unit EQ expression_unit
	| expression_unit NE expression_unit
	| TRUE
	| FALSE
	| logical_expression AND expression_unit
	| logical_expression OR expression_unit
	;

