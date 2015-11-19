#ifndef lex_yacc
#define lex_yacc

#include <vector>
#include <string>
typedef enum { 
	ctype,itype,ktype,otype,
	while_type, 
	if_type, 
	parameter_type,
	func_call_type, 
	arg_type, 
	arg_list_type,
	stmt_type,
	stmts_type, 
	return_statement_type,
	func_decl_type,
	var_dec_type,
	start_type
} ntype;

class node;

class cnst	//constant
{
public:
	int value;	// value
};

class idntfr	//identifier
{
public:
	int index;	//index in symbol table
};

class oprtr	//operator
{
public:
	int oper;
	int nop;
	node **oprnd; 
};

class keyword	//keyword
{
	public:
	int kword;
};

class whl
{ public:
	node *w_exp;
	node *w_stmt;
};

class ifelse
{ public:
	node *i_exp;
	node *i_stmt1;
	node *i_stmt2;
};

class argmnt
{ public:
	node *arg_type;
	node *arg_id;
};

class arg_list
{
public:
	node *al_list;
	node *al_arg;
};

class func_call
{
public:
	node *fc_id;
	node *fc_prmtrs;
};

class prmtr
{ public:
	node *p_value;
	node *p_prmtr;
};

class stmts
{ public:
	node *sts_stmts;
	node *sts_stmt;
};

class rtrn
{ public:
	node* r_exp;
};

class func_decl
{
public:
	node *fd_type;
	node *name;
	node *fd_aglist;
	node *fd_stmts;
	node *return_statement;
};

class var_decl
{
public:
	node *vd_type;
	node *vd_id;
	node *vd_value;
};

class strt
{ public:
	node* st_decl;
	node* st_arglist;
	node *st_block;
};

class node
{ public:
	ntype type;
	union
	{
		cnst con;
		idntfr id;
		oprtr op;
		keyword kw;
		strt st;
		var_decl vd;
		func_decl fd;
		rtrn rt;
		stmts sts;
		prmtr pm;
		func_call fc;
		arg_list arglst;
		argmnt arg;
		ifelse ifi;
		whl wh;
	};
};

node *mk_opr(int oper, int nops, ...)
{
	va_list vlist;
        node *n;
    	int i;

    /* allocate node */
	n=new node;
	n->op.oprnd = new node*[nops];
    /* copy information */
    n->type = otype;
    n->op.oper = oper;
    n->op.nop = nops;
    va_start(vlist, nops);
    for (i = 0; i < nops; i++)
        n->op.oprnd[i] = va_arg(vlist, node*);
    va_end(vlist);
    
    return n;

}

node *mk_id(int i)
{
	node *n;
	n= new node;
	n->type=itype;
	n->id.index=i;

	return n;
}

node *mk_con(int value)
{
	node *n;
	n = new node;
	n->type = ctype;
	n->con.value=value;

	return n;
}
node *mk_kw(int kword)
{
	node *n;
	n = new node;
	n->type = ktype;
	n->kw.kword = kword;

	return n;
}

node *mk_while(node *ex, node *st) {
	node *n;
	n = new node;
	n->type = while_type;
	n->wh.w_exp = ex;
	n->wh.w_stmt = st;

	return n;
}

node *mk_if(node *ex, node *st1, node *st2) {
	node *n;
	n = new node;
	n->type = if_type;
	n->ifi.i_exp = ex;
	n->ifi.i_stmt1 = st1;
	n->ifi.i_stmt2 = st2;

	return n;
}

node *mk_argument(node *type, node *id) {
	node *n;
	n = new node;
	n->type = arg_type;
	n->arg.arg_type = type;
	n->arg.arg_id = id;

	return n;
}

node *mk_argument_list(node *list, node *arg) {
	node *n;
	n = new node;
	n->type = arg_list_type;
	n->arglst.al_list = list;
	n->arglst.al_arg = arg;

	return n;
}

node *mk_function_call(node *name, node *prmtrs) {
	node *n;
	n = new node;
	n->type = func_call_type;
	n->fc.fc_id = name;
	n->fc.fc_prmtrs = prmtrs;

	return n;
}

node *mk_parameter(node *list, node *val) {
	node *n;
	n = new node;
	n->type = parameter_type;
	n->pm.p_value = val;
	n->pm.p_prmtr = list;

	return n;
}

node *mk_statements(node *list, node *statement) {
	node *n;
	n = new node;
	n->type = stmts_type;
	n->sts.sts_stmt = statement;
	n->sts.sts_stmts = list;

	return n;
}

node *mk_return(node *ex) {
	node *n;
	n = new node;
	n->type = return_statement_type;
	n->rt.r_exp = ex;

	return n;
}

node *mk_function_declaration(node *type, node *name, node *arguments, node *body, node *return_statement) {
	node *n;
	n = new node;
	n->type = func_decl_type;
	n->fd.fd_type = type;
	n->fd.name = name;
	n->fd.fd_aglist = arguments;
	n->fd.fd_stmts = body;
	n->fd.return_statement = return_statement;

	return n;
}

node *mk_variable_declaration(node *type, node *name, node *value) {
	node *n;
	n = new node;
	n->type = var_dec_type;
	n->vd.vd_type = type;
	n->vd.vd_id = name;
	n->vd.vd_value = value;

	return n;
}

node *mk_start(node *declarations, node *arguments, node *body) {
	node *n;
	n = new node;
	n->type = start_type;
	n->st.st_decl = declarations;
	n->st.st_arglist = arguments;
	n->st.st_block = body;

	return n;
}
#endif