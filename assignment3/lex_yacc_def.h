#ifndef lex_yacc_header
#define lex_yacc_header

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "y.tab.h"

struct Node;

#ifdef yacc_header

struct Node *root;

typedef enum { 
	E_CONSTANT,
	E_LITERAL,
	E_IDENTIFIER,
	E_KEYWORD,
	E_OPERATOR,
	E_WHILE, 
	E_IF, 
	E_PARAMETER_LIST,
	E_FUNCTION_CALL, 
	E_ARGUMENT, 
	E_ARGUMENT_LIST,
	E_STATEMENT,
	E_STATEMENT_LIST, 
	E_RETURN,
	E_FUNCTION_DECLARATION,
	E_VARIABLE_DECLARATION,
	E_START
} NodeType;

void * get(struct Node *) ;

/**
 * struct Constant 
**/
typedef struct
{
	int value;
} Constant;
const char *Constant_val(const Constant obj) {
	static char val[11];
	sprintf(val, "%d", obj.value);
	return (const char *)(&val);
}

typedef struct
{
	char *value;
} Literal;
const char *Literal_val(const Literal obj) {
	return (const char *)obj.value;
}

/**
 * struct Identifier
**/
typedef struct
{
	char * name;
} Identifier;
const char *Identifier_val(const Identifier obj) {
	return (const char *)obj.name;
}

/**
 * struct Operator
**/
typedef struct
{
	int operator;
	char *name;
	int size;
	struct Node **operands; 
} Operator;
struct Node *Operator_next(const Operator obj, int n) {
	if (n < obj.size) {
		return obj.operands[n];
	}
	return NULL;
}
int Operator_size(const Operator obj) {
	return obj.size;
}
const char *Operator_val(const Operator obj) {
	return (const char *)obj.name;
}

/**
 * struct Keyword
**/
typedef struct
{
	char * name;
} Keyword;
const char *Keyword_val(const Keyword obj) {
	return (const char *)obj.name;
}

/**
 * struct While
**/
typedef struct 
{ 
	struct Node *condition;
	struct Node *statement;
} While;
struct Node *While_next(const While obj, int n) {
	switch(n) {
		case 0: return obj.condition;
		case 1: return obj.statement;
		default: return NULL;
	}
}
int While_size(const While obj) {
	return 2;
}
const char *While_val(const While obj) {
	return "[while statement]";
}

typedef struct 
{ 
	struct Node *condition;
	struct Node *if_statement;
	struct Node *else_statement;
} If;
struct Node *If_next(const If obj, int n) {
	switch(n) {
		case 0: return obj.condition;
		case 1: return obj.if_statement;
		case 2: return obj.else_statement;
		default: return NULL;
	}
}
int If_size(const If obj) {
	return obj.else_statement == NULL ? 2 : 3;
}
const char *If_val(const If obj) {
	return "[if statement]";
}

typedef struct 
{ 
	struct Node *type;
	struct Node *name;
} Argument;
struct Node *Argument_next(const Argument obj, int n) {
	switch(n) {
		case 0: return obj.type;
		case 1: return obj.name;
		default: return NULL;
	}
}
int Argument_size(const Argument obj) {
	return 2;
}
const char *Argument_val(const Argument obj) {
	return "[parameter]";
}

typedef struct 
{
	struct Node *list;
	struct Node *argument;
} ArgumentList;
struct Node *ArgumentList_next(const ArgumentList obj, int n) {
	switch(n) {
		case 0: return obj.argument;
		case 1: return obj.list;
		default: return NULL;
	}
}
int ArgumentList_size(const ArgumentList obj) {
	return 2;
}
const char *ArgumentList_val(const ArgumentList obj) {
	return "[parameters]";
}

typedef struct 
{
	struct Node *name;
	struct Node *parameters;
} FunctionCall;
struct Node *FunctionCall_next(const FunctionCall obj, int n) {
	switch(n) {
		case 0: return obj.name;
		case 1: return obj.parameters;
		default: return NULL;
	}
}
int FunctionCall_size(const FunctionCall obj) {
	return 2;
}
const char *FunctionCall_val(const FunctionCall obj) {
	return "[function call]";
}

typedef struct 
{ 
	struct Node *list;
	struct Node *parameter;
} ParameterList;
struct Node *ParameterList_next(const ParameterList obj, int n) {
	switch(n) {
		case 0: return obj.list;
		case 1: return obj.parameter;
		default: return NULL;
	}
}
int ParameterList_size(const ParameterList obj) {
	return 2;
}
const char *ParameterList_val(const ParameterList obj) {
	return "[arguments]";
}

typedef struct 
{ 
	struct Node *list;
	struct Node *statement;
} StatementList;
struct Node *StatementList_next(const StatementList obj, int n) {
	switch(n) {
		case 0: return obj.list;
		case 1: return obj.statement;
		default: return NULL;
	}
}
int StatementList_size(const StatementList obj) {
	return 2;
}
const char *StatementList_val(const StatementList obj) {
	return "[statements]";
}

typedef struct 
{ 
	struct Node *value;
} Return;
struct Node *Return_next(const Return obj, int n) {
	switch(n) {
		case 0: return obj.value;
		default: return NULL;
	}
}
int Return_size(const Return obj){
	return 1;
}
const char *Return_val(const Return obj) {
	return "[return]";
}

typedef struct 
{
	struct Node *return_type;
	struct Node *name;
	struct Node *arguments;
	struct Node *body;
	struct Node *return_statement;
} FunctionDeclaration;
struct Node *FunctionDeclaration_next(const FunctionDeclaration obj, int n) {
	switch(n) {
		case 0: return obj.return_type;
		case 1: return obj.name;
		case 2: return obj.arguments;
		case 3: return obj.body;
		case 4: return obj.return_statement;
		default: return NULL;
	}
}
int FunctionDeclaration_size(const FunctionDeclaration obj) {
	return 5;
}
const char *FunctionDeclaration_val(const FunctionDeclaration obj) {
	return "[func dec]";
}

typedef struct 
{
	struct Node *type;
	struct Node *name;
	struct Node *value;
} VariableDeclartion;
struct Node *VariableDeclartion_next(const VariableDeclartion obj, int n) {
	switch(n) {
		case 0: return obj.type;
		case 1: return obj.name;
		case 2: return obj.value;
		default: return NULL;
	}
}
int VariableDeclartion_size(const VariableDeclartion obj) {
	return 3;
}
const char *VariableDeclartion_val(const VariableDeclartion obj) {
	return "[var dec]";
}

typedef struct 
{ 
	struct Node *declarations;
	struct Node *arguments;
	struct Node *body;
} Start;
struct Node *Start_next(const Start obj, int n) {
	switch(n) {
		case 0: return obj.declarations;
		case 1: return obj.arguments;
		case 2: return obj.body;
	}
	return NULL;
}
int Start_size(const Start obj) {
	return 3;
}
const char *Start_val(const Start obj) {
	return "[start]";
}

struct Node
{ 
	NodeType type;
	union
	{
		Constant con;
		Literal lit;
		Identifier id;
		Operator op;
		Keyword key;
		Start st;
		VariableDeclartion vd;
		FunctionDeclaration fd;
		Return ret;
		StatementList sl;
		ParameterList pl;
		FunctionCall fc;
		ArgumentList al;
		Argument arg;
		If _if;
		While wh;
	};
};

void * get(struct Node *n) {
	switch(n->type) {
		case E_CONSTANT: return &(n->con); break;
		case E_LITERAL: return &(n->lit); break;
		case E_IDENTIFIER: return &(n->id); break;
		case E_OPERATOR: return &(n->op); break;
		case E_KEYWORD: return &(n->key); break;
		case E_START: return &(n->st); break;
		case E_VARIABLE_DECLARATION: return &(n->vd); break;
		case E_FUNCTION_DECLARATION: return &(n->fd); break;
		case E_RETURN: return &(n->ret); break;
		case E_STATEMENT_LIST: return &(n->sl); break;
		case E_PARAMETER_LIST: return &(n->pl); break;
		case E_FUNCTION_CALL: return &(n->fc); break;
		case E_ARGUMENT_LIST: return &(n->al); break;
		case E_ARGUMENT: return &(n->arg); break;
		case E_IF: return &(n->_if); break;
		case E_WHILE: return &(n->wh); break;
		default: return NULL; break;
	}
}

const char *value(struct Node *n) {
	switch(n->type) {
		case E_CONSTANT: return Constant_val(n->con); break;
		case E_LITERAL: return Literal_val(n->lit); break;
		case E_IDENTIFIER: return Identifier_val(n->id); break;
		case E_OPERATOR: return Operator_val(n->op); break;
		case E_KEYWORD: return Keyword_val(n->key); break;
		case E_START: return Start_val(n->st); break;
		case E_VARIABLE_DECLARATION: return VariableDeclartion_val(n->vd); break;
		case E_FUNCTION_DECLARATION: return FunctionDeclaration_val(n->fd); break;
		case E_RETURN: return Return_val(n->ret); break;
		case E_STATEMENT_LIST: return StatementList_val(n->sl); break;
		case E_PARAMETER_LIST: return ParameterList_val(n->pl); break;
		case E_FUNCTION_CALL: return FunctionCall_val(n->fc); break;
		case E_ARGUMENT_LIST: return ArgumentList_val(n->al); break;
		case E_ARGUMENT: return Argument_val(n->arg); break;
		case E_IF: return If_val(n->_if); break;
		case E_WHILE: return While_val(n->wh); break;
		default: return "not valid"; break;
	}
}

struct Node *next(struct Node *n, int num) {
	switch(n->type) {
		// case E_CONSTANT: Constant_next(n->con);
		// case E_IDENTIFIER: Identifier_next(n->id);
		case E_OPERATOR: return Operator_next(n->op, num); break;
		case E_START: return Start_next(n->st, num); break;
		case E_VARIABLE_DECLARATION: return VariableDeclartion_next(n->vd, num); break;
		case E_FUNCTION_DECLARATION: return FunctionDeclaration_next(n->fd, num); break;
		case E_RETURN: return Return_next(n->ret, num); break;
		case E_STATEMENT_LIST: return StatementList_next(n->sl, num); break;
		case E_PARAMETER_LIST: return ParameterList_next(n->pl, num); break;
		case E_FUNCTION_CALL: return FunctionCall_next(n->fc, num); break;
		case E_ARGUMENT_LIST: return ArgumentList_next(n->al, num); break;
		case E_ARGUMENT: return Argument_next(n->arg, num); break;
		case E_IF: return If_next(n->_if, num); break;
		case E_WHILE: return While_next(n->wh, num); break;
		default: return NULL; break;
	}
}

int size(struct Node *n) {
	switch(n->type) {
		case E_OPERATOR: return Operator_size(n->op); break;
		case E_START: return Start_size(n->st); break;
		case E_VARIABLE_DECLARATION: return VariableDeclartion_size(n->vd); break;
		case E_FUNCTION_DECLARATION: return FunctionDeclaration_size(n->fd); break;
		case E_RETURN: return Return_size(n->ret); break;
		case E_STATEMENT_LIST: return StatementList_size(n->sl); break;
		case E_PARAMETER_LIST: return ParameterList_size(n->pl); break;
		case E_FUNCTION_CALL: return FunctionCall_size(n->fc); break;
		case E_ARGUMENT_LIST: return ArgumentList_size(n->al); break;
		case E_ARGUMENT: return Argument_size(n->arg); break;
		case E_IF: return If_size(n->_if); break;
		case E_WHILE: return While_size(n->wh); break;
		default: return 0; break;
	}
}

const char * operator_from_yacc_id(int id) {
	switch(id) {
		case '>': return ">"; break;
		case '<': return ">"; break;
		case '=': return "="; break;
		case '+': return "+"; break;
		case '-': return "-"; break;
		case '*': return "*"; break;
		case '/': return "/"; break;
		case NE: return "!="; break;
		case EQ: return "=="; break;
		case LE: return "<="; break;
		case GE: return ">="; break;
		case AND: return "&&"; break;
		case OR: return "||"; break;
		default: return "xx"; break;
	}
}
struct Node *mk_operator(int oper, int nops, ...)
{
	va_list vlist;
        struct Node *n;
    	int i;

    /* allocate struct Node */
	n = (struct Node *)malloc(sizeof(struct Node));
	n->op.operands = (struct Node **)malloc(sizeof(struct Node*) * nops);
	n->op.name = (char *)malloc(3);
    /* copy information */
    n->type = E_OPERATOR;
    n->op.operator = oper;
    n->op.size = nops;
    strncpy(n->op.name, operator_from_yacc_id(oper), 3);
    va_start(vlist, nops);
    for (i = 0; i < nops; i++)
        n->op.operands[i] = va_arg(vlist, struct Node*);
    va_end(vlist);
    #ifdef DEBUG
		printf("making: operator(%s)\n", n->op.name);
		fflush(stdout);
	#endif
    
    return n;

}

struct Node *mk_identifier(const char * name)
{
	#ifdef DEBUG
		printf("making: Identifier(%s)\n", name);
		fflush(stdout);
	#endif
	struct Node *n;
	int len = strlen(name);

	n = (struct Node *)malloc(sizeof(struct Node));

	n->type = E_IDENTIFIER;
	n->id.name = malloc(len);
	strncpy(n->id.name, name, len);

	return n;
}

struct Node *mk_constant(int value)
{
	#ifdef DEBUG
		printf("making: Constant(%d)\n", value);
		fflush(stdout);
	#endif
	struct Node *n;
	n = (struct Node *)malloc(sizeof(struct Node));
	n->type = E_CONSTANT;
	n->con.value = value;

	return n;
}
struct Node *mk_keyword(const char * name)
{
	#ifdef DEBUG
		printf("making: Keyword(%s)\n", name);
		fflush(stdout);
	#endif
	struct Node *n;
	int len = strlen(name);

	n = (struct Node *)malloc(sizeof(struct Node));

	n->type = E_KEYWORD;
	n->key.name = (char *)malloc(len);

	strcpy(n->key.name, name);

	return n;
}

struct Node *mk_while(struct Node *ex, struct Node *st) {
	#ifdef DEBUG
		printf("making: while\n");
		fflush(stdout);
	#endif
	struct Node *n;
	n = (struct Node *)malloc(sizeof(struct Node));
	n->type = E_WHILE;
	n->wh.condition = ex;
	n->wh.statement = st;

	return n;
}

struct Node *mk_if(struct Node *ex, struct Node *st1, struct Node *st2) {
	#ifdef DEBUG
		printf("making: if\n");
		fflush(stdout);
	#endif
	struct Node *n;
	n = (struct Node *)malloc(sizeof(struct Node));
	n->type = E_IF;
	n->_if.condition = ex;
	n->_if.if_statement = st1;
	n->_if.else_statement = st2;

	return n;
}

struct Node *mk_argument(struct Node *type, struct Node *name) {
	#ifdef DEBUG
		printf("making: argument\n");
		fflush(stdout);
	#endif
	struct Node *n;
	n = (struct Node *)malloc(sizeof(struct Node));
	n->type = E_ARGUMENT;
	n->arg.type = type;
	n->arg.name = name;

	return n;
}

struct Node *mk_argument_list(struct Node *list, struct Node *arg) {
	#ifdef DEBUG
		printf("making: ArgumentList\n");
		fflush(stdout);
	#endif
	struct Node *n;
	n = (struct Node *)malloc(sizeof(struct Node));
	n->type = E_ARGUMENT_LIST;
	n->al.list = list;
	n->al.argument = arg;

	return n;
}

struct Node *mk_function_call(struct Node *name, struct Node *prmtrs) {
	#ifdef DEBUG
		printf("making: FunctionCall\n");
		fflush(stdout);
	#endif
	struct Node *n;

	n = (struct Node *)malloc(sizeof(struct Node));

	n->type = E_FUNCTION_CALL;
	n->fc.name = name;
	n->fc.parameters = prmtrs;

	return n;
}

struct Node *mk_parameter_list(struct Node *list, struct Node *val) {
	#ifdef DEBUG
		printf("making: ParameterList\n");
		fflush(stdout);
	#endif
	struct Node *n;
	n = (struct Node *)malloc(sizeof(struct Node));
	n->type = E_PARAMETER_LIST;
	n->pl.list = list;
	n->pl.parameter = val;

	return n;
}

struct Node *mk_literal(const char *value) {
	int len = strlen(value);

	#ifdef DEBUG
		printf("making: Literal(%s)\n", value);
		fflush(stdout);
	#endif
	struct Node *n;

	n = (struct Node *)malloc(sizeof(struct Node));

	n->type = E_LITERAL;
	n->lit.value = (char *)malloc(len);
	strncpy(n->lit.value, value, len);

	return n;
}

struct Node *mk_statement_list(struct Node *list, struct Node *statement) {
	#ifdef DEBUG
		printf("making: StatementList\n");
		fflush(stdout);
	#endif
	struct Node *n;
	n = (struct Node *)malloc(sizeof(struct Node));
	n->type = E_STATEMENT_LIST;
	n->sl.list = list;
	n->sl.statement = statement;

	return n;
}

struct Node *mk_return(struct Node *value) {
	#ifdef DEBUG
		printf("making: Return\n");
		fflush(stdout);
	#endif
	struct Node *n;
	n = (struct Node *)malloc(sizeof(struct Node));
	n->type = E_RETURN;
	n->ret.value = value;

	return n;
}

struct Node *mk_function_declaration(struct Node *type, struct Node *name, struct Node *arguments, struct Node *body, struct Node *return_statement) {
	#ifdef DEBUG
		printf("making: FunctionDeclaration\n");
		fflush(stdout);
	#endif
	struct Node *n;
	n = (struct Node *)malloc(sizeof(struct Node));
	n->type = E_FUNCTION_DECLARATION;
	n->fd.return_type = type;
	n->fd.name = name;
	n->fd.arguments = arguments;
	n->fd.body = body;
	n->fd.return_statement = return_statement;

	return n;
}

struct Node *mk_variable_declaration(struct Node *type, struct Node *name, struct Node *value) {
	#ifdef DEBUG
		printf("making: VariableDeclartion\n");
		fflush(stdout);
	#endif
	struct Node *n;
	n = (struct Node *)malloc(sizeof(struct Node));
	n->type = E_VARIABLE_DECLARATION;
	n->vd.type = type;
	n->vd.name = name;
	n->vd.value = value;

	return n;
}

struct Node *mk_start(struct Node *declarations, struct Node *arguments, struct Node *body) {
	#ifdef DEBUG
		printf("making: Start\n");
		fflush(stdout);
	#endif
	struct Node *n;
	n = (struct Node *)malloc(sizeof(struct Node));
	n->type = E_START;
	n->st.declarations = declarations;
	n->st.arguments = arguments;
	n->st.body = body;

	return n;
}

int del = 1; /* distance of graph columns */
int eps = 3; /* distance of graph lines */

/* interface for drawing (can be replaced by "real" graphic using GD or other) */
void graphInit (void);
void graphFinish();
void graphBox (char *s, int *w, int *h);
void graphDrawBox (char *s, int c, int l);
void graphDrawArrow (int c1, int l1, int c2, int l2);

/* recursive drawing of the syntax tree */
void exNode (struct Node *p, int c, int l, int *ce, int *cm);

/*****************************************************************************/

/* main entry point of the manipulation of the syntax tree */
int ex (struct Node *p) {
    int rte, rtm;

    graphInit ();
    exNode (p, 0, 0, &rte, &rtm);
    graphFinish();
    return 0;
}

/*c----cm---ce---->                       drawing of leaf-nodes
 l leaf-info
 */

/*c---------------cm--------------ce----> drawing of non-leaf-nodes
 l            node-info
 *                |
 *    -------------     ...----
 *    |       |               |
 *    v       v               v
 * child1  child2  ...     child-n
 *        che     che             che
 *cs      cs      cs              cs
 *
 */

void exNode
    (   struct Node *p,
        int c, int l,        /* start column and line of node */
        int *ce, int *cm     /* resulting end column and mid of node */
    )
{
    int w, h;           /* node width and height */
    char *s;            /* node text */
    int cbar;           /* "real" start column of node (centred above subnodes) */
    int k;              /* child number */
    int che, chm;       /* end column and mid of children */
    int cs;             /* start column of children */
    char word[255];      /* extended node text */

    if (NULL == p) return;

    strcpy (word, value(p)); /* should never appear */
    s = word;

    /* construct node text box */
    graphBox (s, &w, &h);
    cbar = c;
    *ce = c + w;
    *cm = c + w / 2;

    /* node is leaf */
    if (0 == size(p)) {
        graphDrawBox (s, cbar, l);
        return;
    }

    /* node has children */
    cs = c;
    for (k = 0; k < size(p); k++) {
        if(next(p, k)){
        	exNode (next(p, k), cs, l+h+eps, &che, &chm);
        	cs = che;
        }
    }

    /* total node width */
    if (w < che - c) {
        cbar += (che - c - w) / 2;
        *ce = che;
        *cm = (c + che) / 2;
    }

    /* draw node */
    graphDrawBox (s, cbar, l);

    /* draw arrows (not optimal: children are drawn a second time) */
    cs = c;
    for (k = 0; k < size(p); k++) {
    	if (next(p, k)) {
        	exNode (next(p, k), cs, l+h+eps, &che, &chm);
        	graphDrawArrow (*cm, l+h, chm, l+h+eps-1);
        	cs = che;
    	}
    }
}

/* interface for drawing */

#define lmax 200
#define cmax 2000

char graph[lmax][cmax]; /* array for ASCII-Graphic */
int graphNumber = 0;

void graphTest (int l, int c)
{   int ok;
    ok = 1;
    if (l < 0) ok = 0;
    if (l >= lmax) ok = 0;
    if (c < 0) ok = 0;
    if (c >= cmax) ok = 0;
    if (ok) return;
    printf ("\n+++error: l=%d, c=%d not in drawing rectangle 0, 0 ... %d, %d", 
        l, c, lmax, cmax);
    exit(1);
}

void graphInit (void) {
    int i, j;
    for (i = 0; i < lmax; i++) {
        for (j = 0; j < cmax; j++) {
            graph[i][j] = ' ';
        }
    }
}

void graphFinish() {
    int i, j;
    for (i = 0; i < lmax; i++) {
        for (j = cmax-1; j > 0 && graph[i][j] == ' '; j--);
        graph[i][cmax-1] = 0;
        if (j < cmax-1) graph[i][j+1] = 0;
        if (graph[i][j] == ' ') graph[i][j] = 0;
    }
    for (i = lmax-1; i > 0 && graph[i][0] == 0; i--);
    printf ("\n\nGraph %d:\n", graphNumber++);
    for (j = 0; j <= i; j++) printf ("\n%s", graph[j]);
    printf("\n");
}

void graphBox (char *s, int *w, int *h) {
    *w = strlen (s) + del;
    *h = 1;
}

void graphDrawBox (char *s, int c, int l) {
    int i;
    graphTest (l, c+strlen(s)-1+del);
    for (i = 0; i < strlen (s); i++) {
        graph[l][c+i+del] = s[i];
    }
}

void graphDrawArrow (int c1, int l1, int c2, int l2) {
    int m;
    graphTest (l1, c1);
    graphTest (l2, c2);
    m = (l1 + l2) / 2;
    while (l1 != m) { graph[l1][c1] = '|'; if (l1 < l2) l1++; else l1--; }
    while (c1 != c2) { graph[l1][c1] = '-'; if (c1 < c2) c1++; else c1--; }
    while (l1 != l2) { graph[l1][c1] = '|'; if (l1 < l2) l1++; else l1--; }
    graph[l1][c1] = '|';
}

void print_tree(struct Node *node) {
	printf("First: %s %d\n", value(node), node->type);
	ex(node);
}
#endif
#endif