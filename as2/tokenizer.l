%{
	#define keyword 	1
	#define identifier 	2
	#define numliteral 	3
	#define	boolliteral 4
	#define operator	5
	#define line		6
	#define others		7
%}

NUMBER		[0-9]+
IDENTIFIER	[a-zA-Z_][a-zA-Z0-9_]*
BOOL		(true|false)
CMP_SYM		([<>]|[<>]=|==|!=)
LOG_SYM 	([&]{2}|[|]{2})
MAT_SYM		[+/*-=]

%%
\;										{ return line; }
(if|else|while|main|int|bool|return)	{ return keyword; }
{BOOL}									{ return boolliteral; }
{NUMBER}								{ return numliteral; }
({CMP_SYM}|{LOG_SYM}|{MAT_SYM})			{ return operator; }
{IDENTIFIER}							{ return identifier; }
<<EOF>>				                    { exit(0); }
[\(\)\{\}\,]							{ return others; }	
.										{ return -1;}
%%

int main( argc, argv )
int argc;
char **argv;
    {
    	int code;
    	const char *tags[] = {
    		"",
    		"keyword", 
    		"identifier",
    		"numliteral",
    		"boolliteral",
    		"operator",
    		"line_terminator",
    		"other_symbols"
    	};
	    for(;(code = yylex());) {
	    	if (0 < code && code < 8) {
	    		printf("<%s,%s>\n", yytext, tags[code]);
	    	}
	    }
    }