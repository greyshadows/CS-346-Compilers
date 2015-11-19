/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     CONSTANT = 258,
     IDENTIFIER = 259,
     STRING_LITERAL = 260,
     INT = 261,
     BOOL = 262,
     MAIN = 263,
     IF = 264,
     ELSE = 265,
     WHILE = 266,
     RETURN = 267,
     TRUE = 268,
     FALSE = 269,
     GE = 270,
     LE = 271,
     NE = 272,
     EQ = 273,
     AND = 274,
     OR = 275,
     VOID = 276,
     PRINT = 277,
     INPUT = 278,
     INCLUDE = 279,
     NO_ELSE = 280
   };
#endif
/* Tokens.  */
#define CONSTANT 258
#define IDENTIFIER 259
#define STRING_LITERAL 260
#define INT 261
#define BOOL 262
#define MAIN 263
#define IF 264
#define ELSE 265
#define WHILE 266
#define RETURN 267
#define TRUE 268
#define FALSE 269
#define GE 270
#define LE 271
#define NE 272
#define EQ 273
#define AND 274
#define OR 275
#define VOID 276
#define PRINT 277
#define INPUT 278
#define INCLUDE 279
#define NO_ELSE 280




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 19 "parser2.y"
{
	int constant;
	char identifier[255];
	char keyword[255];
	char literal[255];
	struct Node *node;
}
/* Line 1529 of yacc.c.  */
#line 107 "y.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

