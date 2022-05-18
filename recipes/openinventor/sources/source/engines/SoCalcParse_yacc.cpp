#ifndef lint
static char yysccsid[] = "@(#)yaccpar   1.9 (Berkeley) 02/21/93";
#endif
#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define yyclearin (yychar=(-1))
#define yyerrok (yyerrflag=0)
#define YYRECOVERING (yyerrflag!=0)
#define YYPREFIX "yy"
#line 19 "lib\database\src\so\engines\SoCalcParse.y"
#include <Inventor/misc/SoBasic.h>
#include <Inventor/errors/SoDebugError.h>
#include "SoCalcExpr.h"
#include <stdio.h>
#ifdef WIN32
#include <float.h>
#define drand48() (((double)rand())/double(RAND_MAX))
#elif defined(__APPLE__)
#include <float.h>
#include <limits.h>
#else
#include <values.h>
#endif
#include <math.h>
#include <ctype.h>
#ifndef WIN32
#include <strings.h>
#endif
#include <stdlib.h>

void yyerror(const char *);
extern "C" int  yylex();
int yyparse();

static const char *In;
static ExprList *EList;

static const struct {
    const char *name;
    float   val;
} Constants[] = {
    { "MAXFLOAT",   MAXFLOAT },
#if defined(__APPLE__) || defined(WIN32)
    { "MINFLOAT",   FLT_MIN },
#else
    { "MINFLOAT",   MINFLOAT },
#endif
    { "M_E",        M_E },
    { "M_LOG2E",    M_LOG2E },
    { "M_LOG10E",   M_LOG10E },
    { "M_LN2",      M_LN2 },
    { "M_LN10",     M_LN10 },
    { "M_PI",       M_PI },
    { "M_SQRT2",    M_SQRT2 },
    { "M_SQRT1_2",  M_SQRT1_2 },
};
#define NCONSTANTS (sizeof(Constants)/sizeof(Constants[0]))

static const struct {
    const char *name;
    Expr::Type  type;
} Inputs[] = {
    { "a", Expr::FLOAT}, { "b", Expr::FLOAT},
    { "c", Expr::FLOAT}, { "d", Expr::FLOAT},
    { "e", Expr::FLOAT}, { "f", Expr::FLOAT},
    { "g", Expr::FLOAT}, { "h", Expr::FLOAT},
    { "A", Expr::VEC3F}, { "B", Expr::VEC3F},
    { "C", Expr::VEC3F}, { "D", Expr::VEC3F},
    { "E", Expr::VEC3F}, { "F", Expr::VEC3F},
    { "G", Expr::VEC3F}, { "H", Expr::VEC3F},
}, Outputs[] = {
    { "oa", Expr::FLOAT}, { "ob", Expr::FLOAT},
    { "oc", Expr::FLOAT}, { "od", Expr::FLOAT},
    { "oA", Expr::VEC3F}, { "oB", Expr::VEC3F},
    { "oC", Expr::VEC3F}, { "oD", Expr::VEC3F},
}, Vars[] = {
    { "ta", Expr::FLOAT}, { "tb", Expr::FLOAT},
    { "tc", Expr::FLOAT}, { "td", Expr::FLOAT},
    { "te", Expr::FLOAT}, { "tf", Expr::FLOAT},
    { "tg", Expr::FLOAT}, { "th", Expr::FLOAT},
    { "tA", Expr::VEC3F}, { "tB", Expr::VEC3F},
    { "tC", Expr::VEC3F}, { "tD", Expr::VEC3F},
    { "tE", Expr::VEC3F}, { "tF", Expr::VEC3F},
    { "tG", Expr::VEC3F}, { "tH", Expr::VEC3F},
};
#define NINPUTS (sizeof(Inputs)/sizeof(Inputs[0]))
#define NOUTPUTS (sizeof(Outputs)/sizeof(Outputs[0]))
#define NVARS (sizeof(Vars)/sizeof(Vars[0]))

static double rand(double max) { return max * drand48(); }
static SbVec3f cross(const SbVec3f &a, const SbVec3f &b) { return a.cross(b); }
static double dot(const SbVec3f &a, const SbVec3f &b) { return a.dot(b); }
static double length(const SbVec3f &a) { return a.length(); }
static SbVec3f normalize(const SbVec3f &v) { SbVec3f t=v; t.normalize(); return t; }
static SbVec3f vec3f(double a, double b, double c) { return SbVec3f(a,b,c); }

/* Keep this up to date with the info in initFuncs()*/
#define NFUNCS 25

static struct {
    const Func *func;
} Funcs[NFUNCS];

#line 118 "lib\database\src\so\engines\SoCalcParse.y"
typedef union
{
    Expr    *expr;
    ExprList    *list;
} YYSTYPE;
#line 112 "y.tab.c"
#define LEXERR 257
#define CONST 258
#define FUNC 259
#define INPUT 260
#define OUTPUT 261
#define VAR 262
#define OROR 263
#define ANDAND 264
#define GEQ 265
#define LEQ 266
#define EQEQ 267
#define NEQ 268
#define YYERRCODE 256
short yylhs[] = {                                        -1,
    0,    0,    0,    1,    1,    1,    1,    2,    2,    2,
    2,    2,    3,    3,    3,   12,   12,    4,    4,    4,
    5,    5,    5,    5,    6,    6,    6,    7,    7,    7,
    7,    7,    8,    8,    8,    9,    9,   10,   10,   11,
   11,
};
short yylen[] = {                                         2,
    1,    3,    2,    3,    6,    3,    6,    1,    1,    1,
    1,    3,    1,    4,    4,    1,    3,    1,    2,    2,
    1,    3,    3,    3,    1,    3,    3,    1,    3,    3,
    3,    3,    1,    3,    3,    1,    3,    1,    3,    1,
    5,
};
short yydefred[] = {                                      0,
    0,    0,    0,    1,    0,    0,    0,    0,    0,    8,
    0,    9,   10,   11,    0,    0,    0,   13,    0,   21,
    0,    0,    0,    0,    0,    0,    4,    0,    6,    0,
    2,    0,    0,   19,   20,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   16,    0,   12,    0,   22,   23,   24,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   15,    0,   14,    0,    5,    7,   17,   41,
};
short yydgoto[] = {                                       3,
    4,   18,   19,   20,   21,   22,   23,   24,   25,   26,
   27,   54,
};
short yysindex[] = {                                   -245,
  -61,  -56,  -46,    0,  -21,  -21,  -21,  -21, -245,    0,
  -22,    0,    0,    0,  -21,  -21,  -21,    0,  -68,    0,
  -27,  -36,  -58, -246, -235,  -57,    0,  -59,    0,  -54,
    0,  -21,    6,    0,    0,  -21,  -21,  -21,  -21,  -21,
  -21,  -21,  -21,  -21,  -21,  -21,  -21,  -21,  -21,  -21,
  -20,  -11,    0,  -30,    0,  -39,    0,    0,    0,  -27,
  -27,  -36,  -36,  -36,  -36,  -58,  -58, -246, -235,   -3,
  -21,  -21,    0,  -21,    0,  -21,    0,    0,    0,    0,
};
short yyrindex[] = {                                      0,
    0,    0,    0,    0,    0,    0,    0,    0,    3,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    1,    0,
    8,   65,  136,  184,  349,  343,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   33,
   40,   72,   97,  104,  110,  142,  152,  192,  380,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
};
short yygindex[] = {                                      0,
   47,    0,    0,  215,   -9,  -17,  -10,    9,   20,    0,
  212,    0,
};
#define YYTABLESIZE 643
short yytable[] = {                                       5,
   18,   44,    3,   45,    7,   50,   41,   25,   40,   39,
   73,   17,    9,   74,   37,    1,    2,   32,   15,   38,
   46,   47,   36,   16,   62,   63,   64,   65,   48,    6,
   60,   61,   27,   51,    8,   66,   67,   18,   52,   26,
   71,   18,   18,   18,   18,   18,   55,   18,   25,   72,
   25,   25,   25,   75,   76,   31,   68,    0,   18,   18,
   18,    3,   18,   18,   28,   25,   25,   25,   69,   25,
   25,   32,    0,   27,    0,   27,   27,   27,    0,    0,
   26,    0,   26,   26,   26,    0,    0,    0,    0,    0,
   27,   27,   27,   18,   27,   27,   31,   26,   26,   26,
   25,   26,   26,   29,    0,   28,    0,    0,   28,   30,
    0,    0,   32,    0,    0,   32,    0,    0,    0,    0,
    0,    0,   28,   28,   28,   27,   28,   28,    0,   32,
   32,   32,   26,   32,   32,   33,    0,   31,    0,    0,
   31,   34,    0,    0,   29,    0,    0,   29,    0,    0,
   30,   35,    0,   30,   31,   31,   31,   28,   31,   31,
    0,   29,   29,   29,   32,   29,   29,   30,   30,   30,
    0,   30,   30,    0,    0,    0,   33,    0,    0,   33,
    0,    0,   34,   36,    0,   34,    0,    0,    0,   31,
    0,   37,   35,   33,   33,   35,   29,    0,   33,   34,
   34,    0,   30,    0,   34,   49,   42,   43,    0,   35,
   35,    0,    0,    0,   35,    0,    0,   28,   29,   30,
    0,    0,    0,    0,   36,    0,   33,   36,   33,    0,
   34,   35,   37,    0,   34,   37,   10,   11,   12,   13,
   14,   36,   36,   53,   35,    0,   36,   56,    0,   37,
   37,   57,   58,   59,   37,    0,    0,    0,    0,    0,
    0,   70,    0,   18,   18,   18,   18,   18,   18,    0,
   25,   25,   25,   25,   25,   25,   36,    0,    0,    0,
    0,    0,   77,   78,   37,   79,    0,   80,    0,    0,
    0,    0,    0,    0,    0,   27,   27,   27,   27,   27,
   27,    0,   26,   26,   26,   26,   26,   26,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   28,   28,   28,
   28,   28,   28,    0,   32,   32,   32,   32,   32,   32,
    0,    0,   40,    0,    0,    0,    0,    0,   38,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   31,
   31,   31,   31,   31,   31,    0,   29,   29,   29,   29,
   29,   29,   30,   30,   30,   30,   30,   30,    0,   39,
    0,    0,    0,   40,    0,    0,   40,    0,    0,   38,
    0,    0,   38,    0,    0,    0,    0,    0,   33,   33,
   40,   40,   33,   33,   34,   34,   38,   38,   34,   34,
    0,   38,    0,    0,   35,   35,    0,    0,   35,   35,
   39,    0,    0,   39,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   40,    0,   39,   39,    0,
    0,   38,   39,    0,    0,    0,   36,   36,    0,    0,
    0,    0,    0,    0,   37,   37,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   39,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   38,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   39,
};
short yycheck[] = {                                      61,
    0,   60,    0,   62,   61,   63,   43,    0,   45,   37,
   41,   33,   59,   44,   42,  261,  262,   40,   40,   47,
  267,  268,   91,   45,   42,   43,   44,   45,  264,   91,
   40,   41,    0,   93,   91,   46,   47,   37,   93,    0,
   61,   41,   42,   43,   44,   45,   41,   47,   41,   61,
   43,   44,   45,   93,   58,    9,   48,   -1,   58,   59,
   60,   59,   62,   63,    0,   58,   59,   60,   49,   62,
   63,    0,   -1,   41,   -1,   43,   44,   45,   -1,   -1,
   41,   -1,   43,   44,   45,   -1,   -1,   -1,   -1,   -1,
   58,   59,   60,   93,   62,   63,    0,   58,   59,   60,
   93,   62,   63,    0,   -1,   41,   -1,   -1,   44,    0,
   -1,   -1,   41,   -1,   -1,   44,   -1,   -1,   -1,   -1,
   -1,   -1,   58,   59,   60,   93,   62,   63,   -1,   58,
   59,   60,   93,   62,   63,    0,   -1,   41,   -1,   -1,
   44,    0,   -1,   -1,   41,   -1,   -1,   44,   -1,   -1,
   41,    0,   -1,   44,   58,   59,   60,   93,   62,   63,
   -1,   58,   59,   60,   93,   62,   63,   58,   59,   60,
   -1,   62,   63,   -1,   -1,   -1,   41,   -1,   -1,   44,
   -1,   -1,   41,    0,   -1,   44,   -1,   -1,   -1,   93,
   -1,    0,   41,   58,   59,   44,   93,   -1,   63,   58,
   59,   -1,   93,   -1,   63,  263,  265,  266,   -1,   58,
   59,   -1,   -1,   -1,   63,   -1,   -1,    6,    7,    8,
   -1,   -1,   -1,   -1,   41,   -1,   15,   44,   93,   -1,
   16,   17,   41,   -1,   93,   44,  258,  259,  260,  261,
  262,   58,   59,   32,   93,   -1,   63,   36,   -1,   58,
   59,   37,   38,   39,   63,   -1,   -1,   -1,   -1,   -1,
   -1,   50,   -1,  263,  264,  265,  266,  267,  268,   -1,
  263,  264,  265,  266,  267,  268,   93,   -1,   -1,   -1,
   -1,   -1,   71,   72,   93,   74,   -1,   76,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  263,  264,  265,  266,  267,
  268,   -1,  263,  264,  265,  266,  267,  268,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  263,  264,  265,
  266,  267,  268,   -1,  263,  264,  265,  266,  267,  268,
   -1,   -1,    0,   -1,   -1,   -1,   -1,   -1,    0,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  263,
  264,  265,  266,  267,  268,   -1,  263,  264,  265,  266,
  267,  268,  263,  264,  265,  266,  267,  268,   -1,    0,
   -1,   -1,   -1,   41,   -1,   -1,   44,   -1,   -1,   41,
   -1,   -1,   44,   -1,   -1,   -1,   -1,   -1,  263,  264,
   58,   59,  267,  268,  263,  264,   58,   59,  267,  268,
   -1,   63,   -1,   -1,  263,  264,   -1,   -1,  267,  268,
   41,   -1,   -1,   44,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   93,   -1,   58,   59,   -1,
   -1,   93,   63,   -1,   -1,   -1,  263,  264,   -1,   -1,
   -1,   -1,   -1,   -1,  263,  264,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   93,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  263,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  263,
};
#define YYFINAL 3
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 268
#if YYDEBUG
char *yyname[] = {
"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
"'!'",0,0,0,"'%'",0,0,"'('","')'","'*'","'+'","','","'-'",0,"'/'",0,0,0,0,0,0,0,
0,0,0,"':'","';'","'<'","'='","'>'","'?'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,"'['",0,"']'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"LEXERR","CONST","FUNC","INPUT","OUTPUT",
"VAR","OROR","ANDAND","GEQ","LEQ","EQEQ","NEQ",
};
char *yyrule[] = {
"$accept : asgnlist",
"asgnlist : asgn",
"asgnlist : asgnlist ';' asgn",
"asgnlist : asgnlist ';'",
"asgn : OUTPUT '=' conditional_expression",
"asgn : OUTPUT '[' conditional_expression ']' '=' conditional_expression",
"asgn : VAR '=' conditional_expression",
"asgn : VAR '[' conditional_expression ']' '=' conditional_expression",
"primary_expression : CONST",
"primary_expression : INPUT",
"primary_expression : OUTPUT",
"primary_expression : VAR",
"primary_expression : '(' conditional_expression ')'",
"postfix_expression : primary_expression",
"postfix_expression : postfix_expression '[' conditional_expression ']'",
"postfix_expression : FUNC '(' args ')'",
"args : conditional_expression",
"args : args ',' conditional_expression",
"unary_expression : postfix_expression",
"unary_expression : '-' unary_expression",
"unary_expression : '!' unary_expression",
"multiplicative_expression : unary_expression",
"multiplicative_expression : multiplicative_expression '*' unary_expression",
"multiplicative_expression : multiplicative_expression '/' unary_expression",
"multiplicative_expression : multiplicative_expression '%' unary_expression",
"additive_expression : multiplicative_expression",
"additive_expression : additive_expression '+' multiplicative_expression",
"additive_expression : additive_expression '-' multiplicative_expression",
"relational_expression : additive_expression",
"relational_expression : relational_expression '<' additive_expression",
"relational_expression : relational_expression '>' additive_expression",
"relational_expression : relational_expression LEQ additive_expression",
"relational_expression : relational_expression GEQ additive_expression",
"equality_expression : relational_expression",
"equality_expression : equality_expression EQEQ relational_expression",
"equality_expression : equality_expression NEQ relational_expression",
"logical_AND_expression : equality_expression",
"logical_AND_expression : logical_AND_expression ANDAND equality_expression",
"logical_OR_expression : logical_AND_expression",
"logical_OR_expression : logical_OR_expression OROR logical_AND_expression",
"conditional_expression : logical_OR_expression",
"conditional_expression : logical_OR_expression '?' conditional_expression ':' conditional_expression",
};
#endif
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 500
#define YYMAXDEPTH 500
#endif
#endif
int yydebug;
int yynerrs;
int yyerrflag;
int yychar;
short *yyssp;
YYSTYPE *yyvsp;
YYSTYPE yyval;
YYSTYPE yylval;
short yyss[YYSTACKSIZE];
YYSTYPE yyvs[YYSTACKSIZE];
#define yystacksize YYSTACKSIZE
#line 235 "lib\database\src\so\engines\SoCalcParse.y"

//
// The static Funcs array contains instances of objects that have
// constructors. Since this wouldn't get set up correctly in a DSO, we
// have to initialize the array at run-time.
//

static void
initFuncs()
{
    int i = 0;

#define MAKEFUNC(CLASS, NAME)                             \
    Funcs[i++].func = new CLASS(SO__QUOTE(NAME),NAME)

    MAKEFUNC(Func_d, acos);
    MAKEFUNC(Func_d, asin);
    MAKEFUNC(Func_d, atan);
    MAKEFUNC(Func_dd, atan2);
    MAKEFUNC(Func_d, ceil);
    MAKEFUNC(Func_d, cos);
    MAKEFUNC(Func_d, cosh);
    MAKEFUNC(Funcv_vv, cross);
    MAKEFUNC(Func_vv, dot);
    MAKEFUNC(Func_d, exp);
    MAKEFUNC(Func_d, fabs);
    MAKEFUNC(Func_d, floor);
    MAKEFUNC(Func_dd, fmod);
    MAKEFUNC(Func_v, length);
    MAKEFUNC(Func_d, log);
    MAKEFUNC(Func_d, log10);
    MAKEFUNC(Funcv_v, normalize);
    MAKEFUNC(Func_dd, pow);
    MAKEFUNC(Func_d, rand);
    MAKEFUNC(Func_d, sin);
    MAKEFUNC(Func_d, sinh);
    MAKEFUNC(Func_d, sqrt);
    MAKEFUNC(Func_d, tan);
    MAKEFUNC(Func_d, tanh);
    MAKEFUNC(Funcv_ddd, vec3f);

#ifdef DEBUG
    // Sanity check
    if (i != NFUNCS)
    SoDebugError::post("SoCalcParse initFuncs (internal)",
               "Wrong number of functions declared");
#endif /* DEBUG */
}

static Const *
isConst(const char *nm)
{
    for (int i=0; i<NCONSTANTS; i++)
    if (strcmp(nm, Constants[i].name)==0)
        return new Const(Constants[i].val);
    return NULL;
}

static Func *
isFunc(const char *nm)
{
    for (int i=0; i<NFUNCS; i++) {
    const Func *f = Funcs[i].func;
    if (strcmp(nm, f->name)==0)
        return f->dup();
    }
    return NULL;
}

static Var *
isInput(const char *nm)
{
    for (int i=0; i<NINPUTS; i++) if (strcmp(nm, Inputs[i].name)==0)
    return new Var(nm, Inputs[i].type);
    return NULL;
}

static Var *
isOutput(const char *nm)
{
    for (int i=0; i<NOUTPUTS; i++) if (strcmp(nm, Outputs[i].name)==0)
    return new Var(nm, Outputs[i].type);
    return NULL;
}

static Var *
isVar(const char *nm)
{
    for (int i=0; i<NVARS; i++) if (strcmp(nm, Vars[i].name)==0)
    return new Var(nm, Vars[i].type);
    return NULL;
}

int yylex()
{
#define BSZ 100
    char c, buf[BSZ+1], *cp = buf;

    // skip over blanks
    while (isspace(*In))
    In++;

    if (!In[0])
    return EOF;

    if (isdigit(In[0]) || In[0] == '.') {

    // skip past a valid floating-point number
    // (don't need to compute the number, will
    // use atof() to do that).
    SbBool dot = FALSE;
    SbBool exp = FALSE;
    for (;;) {
        c = *In++;
        if (cp - buf < BSZ)
        *cp++ = c;
        *cp = c;
        if (isdigit(c))
        continue;
        if (c== '.') {
        if (dot || exp)
            return LEXERR;
        dot = TRUE;
        continue;
        }
        if (c == 'e' || c == 'E') {
        if (exp)
            return LEXERR;
        exp = TRUE;
        continue;
        }
        // Check for negative exponent
        if (c == '-' && exp && (In[-2] == 'e' || In[-2] == 'E')) {
        continue;
        }
        break;  // end of number
    }
    if (In[-1] == 'e')
        return LEXERR;

    *cp = 0;
    In--;   // push back last character "read"

    yylval.expr = new Const(atof(buf));
    return CONST;
    }

    if (isalpha(In[0])) {
    while (isalnum(In[0]) || In[0] == '_') {
        if (cp - buf < BSZ)
        *cp++ = *In++;
    }
    *cp = 0;

    if (yylval.expr = isConst(buf))
        return CONST;

    if (yylval.expr = isFunc(buf))
        return FUNC;

    if (yylval.expr = isInput(buf))
        return INPUT;

    if (yylval.expr = isOutput(buf))
        return OUTPUT;

    if (yylval.expr = isVar(buf))
        return VAR;

    }

#define EQ2(x,y)    (x[0]==y[0] && x[1]==y[1])
    if (EQ2(In, "==")) { In += 2; return EQEQ; }
    if (EQ2(In, "!=")) { In += 2; return NEQ; }
    if (EQ2(In, ">=")) { In += 2; return GEQ; }
    if (EQ2(In, "<=")) { In += 2; return LEQ; }
    if (EQ2(In, "&&")) { In += 2; return ANDAND; }
    if (EQ2(In, "||")) { In += 2; return OROR; }

    return *In++;
}

void
yyerror(const char *)
{
    // printf("parse error: %s\n", s);
}

SbBool
SoCalcParse(ExprList *elist, const char *buf)
{
    static SbBool initted = FALSE;

    if (! initted) {
    initFuncs();
    initted = TRUE;
    }

    In = buf;
    EList = elist;
    return(yyparse());
}

#ifdef TESTMAIN

void
main()
{
    char buf[1000];
#if YYDEBUG
    extern int yydebug;
    yydebug = 1;
#endif
    EList = new ExprList;

    while (gets(buf)) {
    In = buf;
    EList->truncate(0);
    if (yyparse())
        printf("Parse error.\n");
    else {
        EList->eval();
        for (int i=0; i<EList->length(); i++) {
        (*EList)[i]->pr();
        }
    }
    }
}

#endif
#line 628 "y.tab.c"
#define YYABORT goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR goto yyerrlab
int
yyparse()
{
    register int yym, yyn, yystate;
#if YYDEBUG
    register char *yys;
    extern char *getenv();

    if (yys = getenv("YYDEBUG"))
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = (-1);

    yyssp = yyss;
    yyvsp = yyvs;
    *yyssp = yystate = 0;

yyloop:
    if (yyn = yydefred[yystate]) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yyssp >= yyss + yystacksize - 1)
        {
            goto yyoverflow;
        }
        *++yyssp = yystate = yytable[yyn];
        *++yyvsp = yylval;
        yychar = (-1);
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;
#ifdef lint
    goto yynewerror;
#endif
yynewerror:
    yyerror("syntax error");
#ifdef lint
    goto yyerrlab;
#endif
yyerrlab:
    ++yynerrs;
yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yyssp]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yyssp, yytable[yyn]);
#endif
                if (yyssp >= yyss + yystacksize - 1)
                {
                    goto yyoverflow;
                }
                *++yyssp = yystate = yytable[yyn];
                *++yyvsp = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yyssp);
#endif
                if (yyssp <= yyss) goto yyabort;
                --yyssp;
                --yyvsp;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = (-1);
        goto yyloop;
    }
yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    yyval = yyvsp[1-yym];
    switch (yyn)
    {
case 1:
#line 135 "lib\database\src\so\engines\SoCalcParse.y"
{ EList->append(yyvsp[0].expr); }
break;
case 2:
#line 136 "lib\database\src\so\engines\SoCalcParse.y"
{ EList->append(yyvsp[0].expr); }
break;
case 4:
#line 142 "lib\database\src\so\engines\SoCalcParse.y"
{ yyval.expr = new Assign(yyvsp[-2].expr, yyvsp[0].expr); }
break;
case 5:
#line 144 "lib\database\src\so\engines\SoCalcParse.y"
{ yyval.expr = new AssignIndex(yyvsp[-5].expr, yyvsp[-3].expr, yyvsp[0].expr); }
break;
case 6:
#line 146 "lib\database\src\so\engines\SoCalcParse.y"
{ yyval.expr = new Assign(yyvsp[-2].expr, yyvsp[0].expr); }
break;
case 7:
#line 148 "lib\database\src\so\engines\SoCalcParse.y"
{ yyval.expr = new AssignIndex(yyvsp[-5].expr, yyvsp[-3].expr, yyvsp[0].expr); }
break;
case 8:
#line 152 "lib\database\src\so\engines\SoCalcParse.y"
{ yyval.expr = yyvsp[0].expr; }
break;
case 9:
#line 153 "lib\database\src\so\engines\SoCalcParse.y"
{ yyval.expr = yyvsp[0].expr; }
break;
case 10:
#line 154 "lib\database\src\so\engines\SoCalcParse.y"
{ yyval.expr = yyvsp[0].expr; }
break;
case 11:
#line 155 "lib\database\src\so\engines\SoCalcParse.y"
{ yyval.expr = yyvsp[0].expr; }
break;
case 12:
#line 156 "lib\database\src\so\engines\SoCalcParse.y"
{ yyval.expr = yyvsp[-1].expr; }
break;
case 13:
#line 160 "lib\database\src\so\engines\SoCalcParse.y"
{ yyval.expr = yyvsp[0].expr; }
break;
case 14:
#line 162 "lib\database\src\so\engines\SoCalcParse.y"
{ yyval.expr = new Index(yyvsp[-3].expr, yyvsp[-1].expr); }
break;
case 15:
#line 163 "lib\database\src\so\engines\SoCalcParse.y"
{ ((Func *)yyvsp[-3].expr)->setArgs(yyvsp[-1].list); yyval.expr = yyvsp[-3].expr; }
break;
case 16:
#line 167 "lib\database\src\so\engines\SoCalcParse.y"
{ (yyval.list = new ExprList)->append(yyvsp[0].expr); }
break;
case 17:
#line 168 "lib\database\src\so\engines\SoCalcParse.y"
{ yyvsp[-2].list->append(yyvsp[0].expr); yyval.list = yyvsp[-2].list; }
break;
case 19:
#line 173 "lib\database\src\so\engines\SoCalcParse.y"
{ yyval.expr = new Negate(yyvsp[0].expr); }
break;
case 20:
#line 174 "lib\database\src\so\engines\SoCalcParse.y"
{ yyval.expr = new Not(yyvsp[0].expr); }
break;
case 22:
#line 180 "lib\database\src\so\engines\SoCalcParse.y"
{ yyval.expr = new Mult(yyvsp[-2].expr, yyvsp[0].expr); }
break;
case 23:
#line 182 "lib\database\src\so\engines\SoCalcParse.y"
{ yyval.expr = new Divide(yyvsp[-2].expr, yyvsp[0].expr); }
break;
case 24:
#line 184 "lib\database\src\so\engines\SoCalcParse.y"
{ yyval.expr = new Mod(yyvsp[-2].expr, yyvsp[0].expr); }
break;
case 26:
#line 190 "lib\database\src\so\engines\SoCalcParse.y"
{ yyval.expr = new Plus(yyvsp[-2].expr, yyvsp[0].expr); }
break;
case 27:
#line 192 "lib\database\src\so\engines\SoCalcParse.y"
{ yyval.expr = new Minus(yyvsp[-2].expr, yyvsp[0].expr); }
break;
case 29:
#line 198 "lib\database\src\so\engines\SoCalcParse.y"
{ yyval.expr = new LessThan(yyvsp[-2].expr, yyvsp[0].expr); }
break;
case 30:
#line 200 "lib\database\src\so\engines\SoCalcParse.y"
{ yyval.expr = new GreaterThan(yyvsp[-2].expr, yyvsp[0].expr); }
break;
case 31:
#line 202 "lib\database\src\so\engines\SoCalcParse.y"
{ yyval.expr = new LessEQ(yyvsp[-2].expr, yyvsp[0].expr); }
break;
case 32:
#line 204 "lib\database\src\so\engines\SoCalcParse.y"
{ yyval.expr = new GreaterEQ(yyvsp[-2].expr, yyvsp[0].expr); }
break;
case 34:
#line 210 "lib\database\src\so\engines\SoCalcParse.y"
{ yyval.expr = new Equals(yyvsp[-2].expr, yyvsp[0].expr); }
break;
case 35:
#line 212 "lib\database\src\so\engines\SoCalcParse.y"
{ yyval.expr = new NotEquals(yyvsp[-2].expr, yyvsp[0].expr); }
break;
case 37:
#line 218 "lib\database\src\so\engines\SoCalcParse.y"
{ yyval.expr = new And(yyvsp[-2].expr, yyvsp[0].expr); }
break;
case 39:
#line 224 "lib\database\src\so\engines\SoCalcParse.y"
{ yyval.expr = new Or(yyvsp[-2].expr, yyvsp[0].expr); }
break;
case 41:
#line 231 "lib\database\src\so\engines\SoCalcParse.y"
{ yyval.expr = new Ternary(yyvsp[-4].expr, yyvsp[-2].expr, yyvsp[0].expr); }
break;
#line 897 "y.tab.c"
    }
    yyssp -= yym;
    yystate = *yyssp;
    yyvsp -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yyssp = YYFINAL;
        *++yyvsp = yyval;
        if (yychar < 0)
        {
            if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yyssp, yystate);
#endif
    if (yyssp >= yyss + yystacksize - 1)
    {
        goto yyoverflow;
    }
    *++yyssp = yystate;
    *++yyvsp = yyval;
    goto yyloop;
yyoverflow:
    yyerror("yacc stack overflow");
yyabort:
    return (1);
yyaccept:
    return (0);
}
