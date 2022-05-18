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
typedef union
{
    Expr    *expr;
    ExprList    *list;
} YYSTYPE;
extern YYSTYPE yylval;
