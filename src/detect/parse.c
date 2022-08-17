/* Driver template for the LEMON parser generator.
** The author disclaims copyright to this source code.
*/
/* First off, code is include which follows the "include" declaration
** in the input file. */
#include <stdio.h>
#line 54 "parse.y"

#include "sqliteInt.h"
#include "parse.h"

/*
** An instance of this structure holds information about the
** LIMIT clause of a SELECT statement.
*/
struct LimitVal {
  Expr *pLimit;    /* The LIMIT expression.  NULL if there is no limit */
  Expr *pOffset;   /* The OFFSET expression.  NULL if there is none */
};

/*
** An instance of this structure is used to store the LIKE,
** GLOB, NOT LIKE, and NOT GLOB operators.
*/
struct LikeOp {
  Token eOperator;  /* "like" or "glob" or "regexp" */
  int not;         /* True if the NOT keyword is present */
};

/*
** An instance of the following structure describes the event of a
** TRIGGER.  "a" is the event type, one of TK_UPDATE, TK_INSERT,
** TK_DELETE, or TK_INSTEAD.  If the event is of the form
**
**      UPDATE ON (a,b,c)
**
** Then the "b" IdList records the list "a,b,c".
*/
struct TrigEvent { int a; IdList * b; };

/*
** An instance of this structure holds the ATTACH key and the key type.
*/
struct AttachKey { int type;  Token key; };

#line 48 "parse.c"
/* Next is all token values, in a form suitable for use by makeheaders.
** This section will be null unless lemon is run with the -m switch.
*/
/* 
** These constants (all generated automatically by the parser generator)
** specify the various kinds of tokens (terminals) that the parser
** understands. 
**
** Each symbol here is a terminal symbol in the grammar.
*/
/* Make sure the INTERFACE macro is defined.
*/
#ifndef INTERFACE
# define INTERFACE 1
#endif
/* The next thing included is series of defines which control
** various aspects of the generated parser.
**    YYCODETYPE         is the data type used for storing terminal
**                       and nonterminal numbers.  "unsigned char" is
**                       used if there are fewer than 250 terminals
**                       and nonterminals.  "int" is used otherwise.
**    YYNOCODE           is a number of type YYCODETYPE which corresponds
**                       to no legal terminal or nonterminal number.  This
**                       number is used to fill in empty slots of the hash 
**                       table.
**    YYFALLBACK         If defined, this indicates that one or more tokens
**                       have fall-back values which should be used if the
**                       original value of the token will not parse.
**    YYACTIONTYPE       is the data type used for storing terminal
**                       and nonterminal numbers.  "unsigned char" is
**                       used if there are fewer than 250 rules and
**                       states combined.  "int" is used otherwise.
**    ParserTOKENTYPE     is the data type used for minor tokens given 
**                       directly to the parser from the tokenizer.
**    YYMINORTYPE        is the data type used for all minor tokens.
**                       This is typically a union of many types, one of
**                       which is ParserTOKENTYPE.  The entry in the union
**                       for base tokens is called "yy0".
**    YYSTACKDEPTH       is the maximum depth of the parser's stack.
**    ParserARG_SDECL     A static variable declaration for the %extra_argument
**    ParserARG_PDECL     A parameter declaration for the %extra_argument
**    ParserARG_STORE     Code to store %extra_argument into yypParser
**    ParserARG_FETCH     Code to extract %extra_argument from yypParser
**    YYNSTATE           the combined number of states.
**    YYNRULE            the number of rules in the grammar
**    YYERRORSYMBOL      is the code number of the error symbol.  If not
**                       defined, then do no error processing.
*/
#define YYCODETYPE unsigned short int
#define YYNOCODE 253
#define YYACTIONTYPE unsigned short int
#define ParserTOKENTYPE Token
typedef union {
  ParserTOKENTYPE yy0;
  int yy4;
  struct {int value; int mask;} yy215;
  SrcList* yy259;
  ValuesList* yy287;
  struct LimitVal yy292;
  Expr* yy314;
  ExprList* yy322;
  struct LikeOp yy342;
  Token yy378;
  IdList* yy384;
  Select* yy387;
  int yy505;
} YYMINORTYPE;
#define YYSTACKDEPTH 100
#define ParserARG_SDECL Parse *pParse;
#define ParserARG_PDECL ,Parse *pParse
#define ParserARG_FETCH Parse *pParse = yypParser->pParse
#define ParserARG_STORE yypParser->pParse = pParse
#define YYNSTATE 512
#define YYNRULE 281
#define YYERRORSYMBOL 148
#define YYERRSYMDT yy505
#define YYFALLBACK 1
#define YY_NO_ACTION      (YYNSTATE+YYNRULE+2)
#define YY_ACCEPT_ACTION  (YYNSTATE+YYNRULE+1)
#define YY_ERROR_ACTION   (YYNSTATE+YYNRULE)

/* Next are that tables used to determine what action to take based on the
** current state and lookahead token.  These tables are used to implement
** functions that take a state number and lookahead value and return an
** action integer.  
**
** Suppose the action integer is N.  Then the action is determined as
** follows
**
**   0 <= N < YYNSTATE                  Shift N.  That is, push the lookahead
**                                      token onto the stack and goto state N.
**
**   YYNSTATE <= N < YYNSTATE+YYNRULE   Reduce by rule N-YYNSTATE.
**
**   N == YYNSTATE+YYNRULE              A syntax error has occurred.
**
**   N == YYNSTATE+YYNRULE+1            The parser accepts its input.
**
**   N == YYNSTATE+YYNRULE+2            No such action.  Denotes unused
**                                      slots in the yy_action[] table.
**
** The action table is constructed as a single large table named yy_action[].
** Given state S and lookahead X, the action is computed as
**
**      yy_action[ yy_shift_ofst[S] + X ]
**
** If the index value yy_shift_ofst[S]+X is out of range or if the value
** yy_lookahead[yy_shift_ofst[S]+X] is not equal to X or if yy_shift_ofst[S]
** is equal to YY_SHIFT_USE_DFLT, it means that the action is not in the table
** and that yy_default[S] should be used instead.  
**
** The formula above is for computing the action when the lookahead is
** a terminal symbol.  If the lookahead is a non-terminal (as occurs after
** a reduce action) then the yy_reduce_ofst[] array is used in place of
** the yy_shift_ofst[] array and YY_REDUCE_USE_DFLT is used in place of
** YY_SHIFT_USE_DFLT.
**
** The following are the tables generated in this section:
**
**  yy_action[]        A single table containing all actions.
**  yy_lookahead[]     A table containing the lookahead for each entry in
**                     yy_action.  Used to detect hash collisions.
**  yy_shift_ofst[]    For each state, the offset into yy_action for
**                     shifting terminals.
**  yy_reduce_ofst[]   For each state, the offset into yy_action for
**                     shifting non-terminals after a reduce.
**  yy_default[]       Default action for each state.
*/
static const YYACTIONTYPE yy_action[] = {
 /*     0 */   240,  259,  290,  152,  273,  375,   57,   56,   56,   56,
 /*    10 */    56,  273,   59,   59,   59,   59,   60,   60,   61,   61,
 /*    20 */    61,   62,  365,    4,  365,   31,  323,  328,   62,  317,
 /*    30 */   169,  365,   26,  388,  185,  318,  489,  490,  491,  165,
 /*    40 */    59,   59,   59,   59,   60,   60,   61,   61,   61,   62,
 /*    50 */    55,   53,  248,  396,  399,  393,  393,   58,   56,   56,
 /*    60 */    56,   56,  171,   59,   59,   59,   59,   60,   60,   61,
 /*    70 */    61,   61,   62,  240,  366,   75,  375,   73,  206,   57,
 /*    80 */   383,  174,   64,   59,   59,   59,   59,   60,   60,   61,
 /*    90 */    61,   61,   62,  244,  341,  452,  794,  108,  511,  106,
 /*   100 */   101,    1,  449,  219,  321,  244,  388,   63,  422,  175,
 /*   110 */    52,  137,   63,  410,  175,  219,  137,   17,  495,  496,
 /*   120 */   497,  498,  499,   55,   53,  248,  396,  399,  393,  393,
 /*   130 */    58,   56,   56,   56,   56,  129,   59,   59,   59,   59,
 /*   140 */    60,   60,   61,   61,   61,   62,  240,  428,  260,   96,
 /*   150 */   455,  169,   57,   60,   60,   61,   61,   61,   62,  237,
 /*   160 */   165,  345,  385,  459,  149,   63,  457,  175,  449,  137,
 /*   170 */   273,  145,  346,  195,  269,  199,  270,  156,  152,  388,
 /*   180 */   375,  135,  220,  508,  346,  195,  269,  199,  270,  156,
 /*   190 */   365,   43,  375,  397,  220,  366,   55,   53,  248,  396,
 /*   200 */   399,  393,  393,   58,   56,   56,   56,   56,  417,   59,
 /*   210 */    59,   59,   59,   60,   60,   61,   61,   61,   62,  240,
 /*   220 */   106,  317,  385,  277,  149,   57,  273,  397,  489,  490,
 /*   230 */   491,  136,  123,  123,  342,  447,  774,  127,  257,  495,
 /*   240 */   496,  497,  498,  499,   77,   19,  365,   25,  460,  322,
 /*   250 */   192,  375,  388,  375,  471,  161,   18,  320,  292,  295,
 /*   260 */   296,  315,  122,  375,  412,  375,  366,  297,  253,   55,
 /*   270 */    53,  248,  396,  399,  393,  393,   58,   56,   56,   56,
 /*   280 */    56,  140,   59,   59,   59,   59,   60,   60,   61,   61,
 /*   290 */    61,   62,  240,   61,   61,   61,   62,  273,   57,  364,
 /*   300 */   273,  488,  273,  363,  417,  343,  344,  161,  387,  273,
 /*   310 */   292,  295,  296,  218,  247,  378,  379,  365,   21,  297,
 /*   320 */   365,   30,  365,   30,  375,  388,  132,  133,  161,  365,
 /*   330 */    30,  292,  295,  296,  342,  456,  375,   69,  426,  369,
 /*   340 */   297,  154,   55,   53,  248,  396,  399,  393,  393,   58,
 /*   350 */    56,   56,   56,   56,  432,   59,   59,   59,   59,   60,
 /*   360 */    60,   61,   61,   61,   62,  251,  469,  460,  240,  371,
 /*   370 */   371,  371,  286,  340,   57,   18,  366,  406,  173,  407,
 /*   380 */   300,  342,  273,  431,    3,  387,  407,  273,  155,  142,
 /*   390 */   276,  378,  379,  289,  461,  342,  483,  258,  134,  470,
 /*   400 */   458,  388,  365,   36,  342,  343,  344,  365,   43,  453,
 /*   410 */    72,   68,  456,   70,  157,  342,  369,  487,   55,   53,
 /*   420 */   248,  396,  399,  393,  393,   58,   56,   56,   56,   56,
 /*   430 */   435,   59,   59,   59,   59,   60,   60,   61,   61,   61,
 /*   440 */    62,  352,  284,  210,  240,  119,  371,  371,  371,  402,
 /*   450 */    57,   10,  343,  344,  173,  256,  353,  403,  273,  342,
 /*   460 */   468,  273,  436,  342,  200,  241,  343,  344,  467,  220,
 /*   470 */   326,  342,  354,    1,  350,  343,  344,  388,  365,   29,
 /*   480 */   121,  365,   36,  207,  117,  351,  343,  344,  316,  280,
 /*   490 */   418,  401,  401,  141,   55,   53,  248,  396,  399,  393,
 /*   500 */   393,   58,   56,   56,   56,   56,  454,   59,   59,   59,
 /*   510 */    59,   60,   60,   61,   61,   61,   62,  389,  327,  324,
 /*   520 */   240,  512,  208,  229,  327,  324,   57,  430,  422,  273,
 /*   530 */   343,  344,  171,  360,  343,  344,  252,  391,  392,  317,
 /*   540 */   273,  361,  343,  344,  441,  234,  489,  490,  491,  365,
 /*   550 */    48,  348,  349,  388,  419,  280,  487,  401,  401,  422,
 /*   560 */   365,   22,  235,  280,  390,  401,  401,  212,  442,  426,
 /*   570 */    55,   53,  248,  396,  399,  393,  393,   58,   56,   56,
 /*   580 */    56,   56,  223,   59,   59,   59,   59,   60,   60,   61,
 /*   590 */    61,   61,   62,  273,  229,  273,  240,  273,  214,  273,
 /*   600 */   138,  273,   57,  273,  447,  273,  447,    6,  447,  287,
 /*   610 */   291,  273,  211,  365,   46,  365,   30,  365,   87,  365,
 /*   620 */    84,  365,   85,  365,   89,  365,   90,  319,  250,  388,
 /*   630 */   501,  365,   97,  475,  364,  366,  309,  183,  363,  167,
 /*   640 */   229,  254,  158,  159,  160,  309,   55,   53,  248,  396,
 /*   650 */   399,  393,  393,   58,   56,   56,   56,   56,  249,   59,
 /*   660 */    59,   59,   59,   60,   60,   61,   61,   61,   62,  240,
 /*   670 */   273,  139,  407,  273,  366,   57,  273,  447,  273,  230,
 /*   680 */   357,  172,  218,  273,  217,  166,  218,  273,   49,  358,
 /*   690 */   365,   98,  273,  365,   16,  273,  365,   88,  365,   47,
 /*   700 */   184,  501,  388,  365,   99,  229,  366,  365,  100,  312,
 /*   710 */   255,  229,  365,   23,  274,  365,   32,  502,  146,   55,
 /*   720 */    53,  248,  396,  399,  393,  393,   58,   56,   56,   56,
 /*   730 */    56,  273,   59,   59,   59,   59,   60,   60,   61,   61,
 /*   740 */    61,   62,  240,  273,  307,  273,  502,  273,   57,  273,
 /*   750 */   233,  365,   33,  273,  415,  218,  273,  163,  273,  309,
 /*   760 */   273,  500,  273,  365,   24,  365,   34,  365,   35,  365,
 /*   770 */    37,  151,  142,  365,   38,  388,  365,   39,  365,   27,
 /*   780 */   365,   28,  365,   40,  280,  112,  401,  401,   75,  502,
 /*   790 */   503,  502,  366,   53,  248,  396,  399,  393,  393,   58,
 /*   800 */    56,   56,   56,   56,  157,   59,   59,   59,   59,   60,
 /*   810 */    60,   61,   61,   61,   62,  240,  273,  502,  273,  168,
 /*   820 */   273,   57,  273,  314,  381,  381,  263,  265,  243,  194,
 /*   830 */   103,  549,  376,  505,  278,  506,  365,   41,  365,   42,
 /*   840 */   365,   44,  365,   45,  196,  405,  440,  424,  388,  131,
 /*   850 */    20,  370,  384,  197,  408,  241,  416,  421,  438,  425,
 /*   860 */   463,  507,  216,   13,  168,  153,  437,  248,  396,  399,
 /*   870 */   393,  393,   58,   56,   56,   56,   56,    5,   59,   59,
 /*   880 */    59,   59,   60,   60,   61,   61,   61,   62,    5,  482,
 /*   890 */   443,  433,   65,  281,  445,  222,  444,  246,  299,  462,
 /*   900 */   480,  224,  227,   65,  281,  308,  481,  484,  246,   13,
 /*   910 */   275,  504,  112,  112,  394,  335,  112,  130,   81,  439,
 /*   920 */   198,  275,  201,  380,   81,  153,  382,  279,  398,  282,
 /*   930 */   411,  436,  232,  414,  493,  446,  448,  331,  494,  124,
 /*   940 */   125,  387,  294,  330,  333,  334,    9,  262,  266,  267,
 /*   950 */   338,  268,  387,  347,  355,  245,  359,  356,  362,   67,
 /*   960 */    66,    5,   75,  367,  202,   74,  285,   65,  271,  272,
 /*   970 */    67,   66,  369,  283,  203,   51,   65,  281,   65,  271,
 /*   980 */   272,  246,  204,  369,   71,  205,  150,  368,  171,  409,
 /*   990 */   209,  177,  178,  412,  275,  413,  109,  288,   76,  423,
 /*  1000 */   213,  179,  371,  371,  371,  372,  373,  374,   12,  215,
 /*  1010 */    92,  427,  450,  371,  371,  371,  372,  373,  374,   12,
 /*  1020 */   238,    5,  181,    2,  182,  387,  239,  451,  474,  189,
 /*  1030 */   261,  464,  301,  190,  191,  225,   65,  281,  465,  466,
 /*  1040 */   302,  246,  164,   67,   66,  429,  472,  104,  305,  476,
 /*  1050 */   113,   65,  271,  272,  275,  107,  369,  478,  118,  189,
 /*  1060 */   261,   11,  180,  190,  191,  225,  231,  479,  329,   86,
 /*  1070 */   242,   91,  332,  236,  310,  264,  336,  104,  486,  337,
 /*  1080 */   313,  193,  339,  105,   50,  387,  371,  371,  371,  372,
 /*  1090 */   373,  374,   12,  170,  550,  551,  147,  148,   54,  395,
 /*  1100 */   377,  386,  176,   67,   66,  400,  128,    7,  486,  404,
 /*  1110 */    14,   65,  271,  272,    8,   13,  369,  420,  110,  143,
 /*  1120 */   111,  434,   93,  293,  306,  115,  485,  221,   94,  304,
 /*  1130 */    78,  298,   95,  197,  171,  116,  162,  226,  303,  114,
 /*  1140 */   228,  473,   79,   15,  492,  477,  371,  371,  371,  372,
 /*  1150 */   373,  374,   12,  311,  306,  115,  485,   80,  166,  304,
 /*  1160 */   144,  120,  186,  102,  171,   82,   83,  187,  509,  325,
 /*  1170 */   535,  188,  510,  126,  535,  535,  535,  535,  535,  535,
 /*  1180 */   535,  535,  535,  535,  535,  535,  535,  535,  535,  535,
 /*  1190 */   535,  535,  535,  102,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */    16,   49,  160,   19,  160,   21,   22,   74,   75,   76,
 /*    10 */    77,  160,   79,   80,   81,   82,   83,   84,   85,   86,
 /*    20 */    87,   88,  180,  181,  180,  181,  152,  153,   88,  131,
 /*    30 */   156,  180,  181,   49,  136,  137,  138,  139,  140,  165,
 /*    40 */    79,   80,   81,   82,   83,   84,   85,   86,   87,   88,
 /*    50 */    66,   67,   68,   69,   70,   71,   72,   73,   74,   75,
 /*    60 */    76,   77,  112,   79,   80,   81,   82,   83,   84,   85,
 /*    70 */    86,   87,   88,   16,  200,  123,   92,   20,  234,   22,
 /*    80 */    83,   84,   78,   79,   80,   81,   82,   83,   84,   85,
 /*    90 */    86,   87,   88,   16,  178,  179,  149,  150,  151,  225,
 /*   100 */    23,  154,  186,   26,   14,   16,   49,  229,  172,  231,
 /*   110 */    53,  233,  229,  230,  231,   26,  233,    1,  244,  245,
 /*   120 */   246,  247,  248,   66,   67,   68,   69,   70,   71,   72,
 /*   130 */    73,   74,   75,   76,   77,   19,   79,   80,   81,   82,
 /*   140 */    83,   84,   85,   86,   87,   88,   16,  211,  153,   19,
 /*   150 */   180,  156,   22,   83,   84,   85,   86,   87,   88,  169,
 /*   160 */   165,  179,  172,  173,  174,  229,  180,  231,  186,  233,
 /*   170 */   160,   94,   95,   96,   97,   98,   99,  100,   19,   49,
 /*   180 */    21,   20,  105,   93,   95,   96,   97,   98,   99,  100,
 /*   190 */   180,  181,   21,   92,  105,  200,   66,   67,   68,   69,
 /*   200 */    70,   71,   72,   73,   74,   75,   76,   77,   20,   79,
 /*   210 */    80,   81,   82,   83,   84,   85,   86,   87,   88,   16,
 /*   220 */   225,  131,  172,  173,  174,   22,  160,  126,  138,  139,
 /*   230 */   140,  165,  142,  143,   21,  160,  146,  147,  228,  244,
 /*   240 */   245,  246,  247,  248,    1,    1,  180,  181,  160,  242,
 /*   250 */   162,   92,   49,   21,  166,   94,  168,  250,   97,   98,
 /*   260 */    99,  241,  242,   92,   21,   21,  200,  106,  193,   66,
 /*   270 */    67,   68,   69,   70,   71,   72,   73,   74,   75,   76,
 /*   280 */    77,   93,   79,   80,   81,   82,   83,   84,   85,   86,
 /*   290 */    87,   88,   16,   85,   86,   87,   88,  160,   22,  109,
 /*   300 */   160,  130,  160,  113,  116,   92,   93,   94,   65,  160,
 /*   310 */    97,   98,   99,  238,  175,  176,  177,  180,  181,  106,
 /*   320 */   180,  181,  180,  181,   92,   49,   83,   84,   94,  180,
 /*   330 */   181,   97,   98,   99,   21,   92,   92,  134,  160,   96,
 /*   340 */   106,  165,   66,   67,   68,   69,   70,   71,   72,   73,
 /*   350 */    74,   75,   76,   77,    2,   79,   80,   81,   82,   83,
 /*   360 */    84,   85,   86,   87,   88,  223,  192,  160,   16,  126,
 /*   370 */   127,  128,  223,  166,   22,  168,  200,  237,  239,  237,
 /*   380 */    16,   21,  160,    2,    1,   65,  237,  160,  212,  213,
 /*   390 */   175,  176,  177,  217,  192,   21,    2,  219,  191,  192,
 /*   400 */   171,   49,  180,  181,   21,   92,   93,  180,  181,  180,
 /*   410 */   134,  133,   92,  135,   50,   21,   96,  172,   66,   67,
 /*   420 */    68,   69,   70,   71,   72,   73,   74,   75,   76,   77,
 /*   430 */     2,   79,   80,   81,   82,   83,   84,   85,   86,   87,
 /*   440 */    88,   12,  220,  221,   16,   25,  126,  127,  128,    2,
 /*   450 */    22,    1,   92,   93,  239,  228,   27,    2,  160,   21,
 /*   460 */   186,  160,  188,   21,  201,  101,   92,   93,  194,  105,
 /*   470 */   151,   21,   43,  154,   45,   92,   93,   49,  180,  181,
 /*   480 */   242,  180,  181,  160,  124,   56,   92,   93,  243,  108,
 /*   490 */   116,  110,  111,  160,   66,   67,   68,   69,   70,   71,
 /*   500 */    72,   73,   74,   75,   76,   77,    2,   79,   80,   81,
 /*   510 */    82,   83,   84,   85,   86,   87,   88,   49,    3,    4,
 /*   520 */    16,    0,  221,  160,    3,    4,   22,   85,  172,  160,
 /*   530 */    92,   93,  112,   30,   92,   93,   25,   69,   70,  131,
 /*   540 */   160,   38,   92,   93,   33,  125,  138,  139,  140,  180,
 /*   550 */   181,  196,  197,   49,  116,  108,  172,  110,  111,  172,
 /*   560 */   180,  181,  199,  108,   96,  110,  111,  211,   57,  160,
 /*   570 */    66,   67,   68,   69,   70,   71,   72,   73,   74,   75,
 /*   580 */    76,   77,    2,   79,   80,   81,   82,   83,   84,   85,
 /*   590 */    86,   87,   88,  160,  160,  160,   16,  160,  211,  160,
 /*   600 */   165,  160,   22,  160,  160,  160,  160,  202,  160,  160,
 /*   610 */    85,  160,  160,  180,  181,  180,  181,  180,  181,  180,
 /*   620 */   181,  180,  181,  180,  181,  180,  181,  243,  219,   49,
 /*   630 */    21,  180,  181,  199,  109,  200,  160,  193,  113,  165,
 /*   640 */   160,  193,  102,  103,  104,  160,   66,   67,   68,   69,
 /*   650 */    70,   71,   72,   73,   74,   75,   76,   77,  223,   79,
 /*   660 */    80,   81,   82,   83,   84,   85,   86,   87,   88,   16,
 /*   670 */   160,  165,  237,  160,  200,   22,  160,  160,  160,  199,
 /*   680 */    37,  203,  238,  160,  238,   20,  238,  160,  210,   46,
 /*   690 */   180,  181,  160,  180,  181,  160,  180,  181,  180,  181,
 /*   700 */   224,   92,   49,  180,  181,  160,  200,  180,  181,  224,
 /*   710 */   193,  160,  180,  181,  160,  180,  181,  205,    1,   66,
 /*   720 */    67,   68,   69,   70,   71,   72,   73,   74,   75,   76,
 /*   730 */    77,  160,   79,   80,   81,   82,   83,   84,   85,   86,
 /*   740 */    87,   88,   16,  160,  199,  160,  205,  160,   22,  160,
 /*   750 */   199,  180,  181,  160,   20,  238,  160,  165,  160,  160,
 /*   760 */   160,  249,  160,  180,  181,  180,  181,  180,  181,  180,
 /*   770 */   181,  212,  213,  180,  181,   49,  180,  181,  180,  181,
 /*   780 */   180,  181,  180,  181,  108,   20,  110,  111,  123,  205,
 /*   790 */   249,  205,  200,   67,   68,   69,   70,   71,   72,   73,
 /*   800 */    74,   75,   76,   77,   50,   79,   80,   81,   82,   83,
 /*   810 */    84,   85,   86,   87,   88,   16,  160,  205,  160,   70,
 /*   820 */   160,   22,  160,  224,  126,  127,   21,   24,   23,   26,
 /*   830 */   160,  114,    2,  249,   16,  249,  180,  181,  180,  181,
 /*   840 */   180,  181,  180,  181,   96,    2,   23,    2,   49,  115,
 /*   850 */    20,  160,  172,  105,  160,  101,  214,  160,  189,  160,
 /*   860 */    95,  249,  160,   20,  115,   20,  160,   68,   69,   70,
 /*   870 */    71,   72,   73,   74,   75,   76,   77,    1,   79,   80,
 /*   880 */    81,   82,   83,   84,   85,   86,   87,   88,    1,    2,
 /*   890 */   189,    2,   16,   17,    2,    2,  189,   21,    2,  160,
 /*   900 */     2,  160,  160,   16,   17,  160,    2,    2,   21,   20,
 /*   910 */    34,  160,   20,   20,   96,  157,   20,  202,   20,   96,
 /*   920 */   183,   34,  204,  240,   20,   20,  240,  232,  232,  236,
 /*   930 */   183,  188,  205,  183,  172,  183,  183,   10,  172,  251,
 /*   940 */   251,   65,  187,  155,  155,  155,   20,  163,  167,  167,
 /*   950 */    22,  101,   65,  182,  182,   47,  182,  190,  182,   83,
 /*   960 */    84,    1,  123,  200,  205,  121,  120,   91,   92,   93,
 /*   970 */    83,   84,   96,  118,  206,  122,   16,   17,   91,   92,
 /*   980 */    93,   21,  207,   96,  133,  208,  114,  209,  112,  161,
 /*   990 */    26,  235,  222,   21,   34,  171,  161,  117,  101,  216,
 /*  1000 */   215,  222,  126,  127,  128,  129,  130,  131,  132,  215,
 /*  1010 */     1,  216,  171,  126,  127,  128,  129,  130,  131,  132,
 /*  1020 */   184,    1,  222,    1,  222,   65,  184,  190,   18,    7,
 /*  1030 */     8,  182,  158,   11,   12,   13,   16,   17,  182,  182,
 /*  1040 */    15,   21,  159,   83,   84,   85,  161,   25,   15,  161,
 /*  1050 */   198,   91,   92,   93,   34,    1,   96,  209,  226,    7,
 /*  1060 */     8,    1,  185,   11,   12,   13,  205,  209,    2,  170,
 /*  1070 */   164,  185,    9,    2,  227,   22,   21,   25,   56,   21,
 /*  1080 */   226,   25,   21,   35,    1,   65,  126,  127,  128,  129,
 /*  1090 */   130,  131,  132,   51,  114,  114,  114,  114,    1,   96,
 /*  1100 */     2,    2,   67,   83,   84,  109,    1,  119,   56,   41,
 /*  1110 */    20,   91,   92,   93,  119,   20,   96,  116,    1,  114,
 /*  1120 */     2,    2,    1,   51,  102,  103,  104,    2,    1,  107,
 /*  1130 */     1,   51,    1,  105,  112,   25,  100,   14,   16,  115,
 /*  1140 */    14,   17,   22,    1,  114,   17,  126,  127,  128,  129,
 /*  1150 */   130,  131,  132,   20,  102,  103,  104,   22,   20,  107,
 /*  1160 */    20,   25,   25,  141,  112,   22,   22,  144,    3,    5,
 /*  1170 */   252,  145,    6,  146,  252,  252,  252,  252,  252,  252,
 /*  1180 */   252,  252,  252,  252,  252,  252,  252,  252,  252,  252,
 /*  1190 */   252,  252,  252,  141,
};
#define YY_SHIFT_USE_DFLT (-103)
#define YY_SHIFT_MAX 325
static const short yy_shift_ofst[] = {
 /*     0 */   515, 1022, 1052,  876,  -16,  876, 1020, 1020, 1020,  213,
 /*    10 */   -50,  887, 1020, 1020, 1020, 1020,    4,  313,  232,   -3,
 /*    20 */    -3,   57,  130,  203,  276,  352,  428,  504,  580,  653,
 /*    30 */   653,  653,  653,  653,  653,  653,  653,  653,  653,  653,
 /*    40 */   653,  653,  653,  653,  653,  653,  726,  799,  799,  960,
 /*    50 */  1020, 1020, 1020, 1020, 1020, 1020, 1020, 1020, 1020, 1020,
 /*    60 */  1020, 1020, 1020, 1020, 1020, 1020, 1020, 1020, 1020, 1020,
 /*    70 */  1020, 1020, 1020, 1020, 1020, 1020, 1020, 1020, 1020, 1020,
 /*    80 */  1020, 1020, 1020, 1020,  -67,  -67,   77,  -39,  -39,   70,
 /*    90 */   208,  364,  313,  313,  313,  313,  232,  -60, -103, -103,
 /*   100 */  -103,  243,   90,   89, -102,  429,  360,  394,  521,  159,
 /*   110 */   313,  159,  313,  313,  313,  313,  313,  313,  420,  313,
 /*   120 */   313,  171,  171,  -48,  -48,  -48,  -48,  -48,  -50,  -50,
 /*   130 */  -103, -103,  320,  320,  161,  234,  381,  383,  447,  455,
 /*   140 */   374,  438,  450,  442,  408,  313,  525,  313,  313,  244,
 /*   150 */   313,  188,  313,  313,  676,  188,  313,  313,  511,  511,
 /*   160 */   511,  313,  313,  676,  313,  676,  313,  676,  313,  116,
 /*   170 */   503,  190,  734,  698,  698,  101,  101,  278,  503,  503,
 /*   180 */   754,  503,  503,  765,  665,  232,  232,  749,  749,  927,
 /*   190 */   927,  927,  926,  928,  928,  850,  850,  908,  850,  850,
 /*   200 */   -50,  839,  846,  844,  855,  853,  851,  872,  964,  972,
 /*   210 */   964,  872,  897,  880,  897,  880, 1009,  964,  964,  972,
 /*   220 */   908,  850,  850,  850, 1009, 1010, 1025,  872, 1033,  872,
 /*   230 */   839,  853,  853, 1054, 1060, 1054, -103, -103, -103, -103,
 /*   240 */   468,  540,  805,  803,  748,  643,  717,  830,  818,  843,
 /*   250 */   845,  889,  823,  892,  893,  896,  898,  904,  905,  609,
 /*   260 */  1066, 1063, 1071, 1053, 1055, 1056, 1058, 1061, 1048, 1042,
 /*   270 */  1083,  980,  981,  982,  983, 1097, 1098, 1099, 1003, 1035,
 /*   280 */   996, 1105, 1068,  988, 1090,  995, 1095, 1001, 1117, 1118,
 /*   290 */  1005, 1119, 1072, 1121, 1125, 1127, 1129, 1080, 1131, 1036,
 /*   300 */  1028, 1123, 1122, 1124, 1126, 1128, 1024, 1110, 1120, 1135,
 /*   310 */  1133, 1142, 1138, 1136, 1138, 1140, 1143, 1030, 1137, 1144,
 /*   320 */  1023, 1026, 1027, 1165, 1164, 1166,
};
#define YY_REDUCE_USE_DFLT (-159)
#define YY_REDUCE_MAX 239
static const short yy_reduce_ofst[] = {
 /*     0 */   -53, -126,   -5,  435,  -64,   66,  142,  222,  149,  207,
 /*    10 */   176,   10, -156,  140,  301,  227, -117,   88,  -10,  139,
 /*    20 */   215, -122, -122, -122, -122, -122, -122, -122, -122, -122,
 /*    30 */  -122, -122, -122, -122, -122, -122, -122, -122, -122, -122,
 /*    40 */  -122, -122, -122, -122, -122, -122, -122, -122, -122, -158,
 /*    50 */  -149,  137,  298,  369,  380,  433,  437,  439,  441,  443,
 /*    60 */   445,  451,  510,  513,  516,  518,  523,  527,  532,  535,
 /*    70 */   571,  583,  585,  587,  589,  593,  596,  598,  600,  602,
 /*    80 */   656,  658,  660,  662, -122, -122,  -84, -122, -122, -122,
 /*    90 */  -122,  274,   75,  444,  448,  517,   50, -122, -122, -122,
 /*   100 */  -122,  229,    7,  -18,   20,  355,  363,  178,  319,  356,
 /*   110 */   409,  387,  446,  434,  480,  545,  476,  551,  474,  485,
 /*   120 */   599,  245,  384,  512,  541,  584,  586,  612,  506,  592,
 /*   130 */   478,  559,  -30,  -14,  174,  202,  263,  323,  263,  263,
 /*   140 */   333,  449,  452,  554,  238,  670,  405,  554,  691,  680,
 /*   150 */   694,  642,  697,  699,  263,  642,  702,  706,  669,  701,
 /*   160 */   707,  739,  741,  263,  742,  263,  745,  263,  751,  758,
 /*   170 */   737,  715,  718,  683,  686,  695,  696,  693,  747,  750,
 /*   180 */   743,  752,  753,  755,  727,  762,  766,  688,  689,  788,
 /*   190 */   789,  790,  784,  781,  782,  771,  772,  767,  774,  776,
 /*   200 */   763,  759,  768,  775,  777,  778,  756,  828,  770,  824,
 /*   210 */   779,  835,  785,  783,  794,  795,  836,  800,  802,  841,
 /*   220 */   837,  849,  856,  857,  842,  874,  883,  885,  852,  888,
 /*   230 */   861,  848,  858,  832,  847,  854,  906,  899,  877,  886,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   519,  793,  793,  751,  633,  793,  751,  793,  751,  793,
 /*    10 */   637,  793,  747,  751,  793,  793,  721,  793,  552,  761,
 /*    20 */   761,  668,  793,  793,  793,  793,  793,  793,  793,  669,
 /*    30 */   750,  746,  742,  744,  743,  670,  657,  666,  673,  649,
 /*    40 */   675,  676,  686,  687,  768,  769,  710,  727,  709,  793,
 /*    50 */   793,  793,  793,  793,  793,  793,  793,  793,  793,  793,
 /*    60 */   793,  793,  793,  793,  793,  793,  793,  793,  793,  793,
 /*    70 */   793,  793,  793,  793,  793,  793,  793,  793,  793,  793,
 /*    80 */   793,  793,  793,  793,  712,  713,  545,  711,  720,  714,
 /*    90 */   715,  606,  793,  793,  793,  793,  793,  716,  717,  728,
 /*   100 */   729,  793,  788,  793,  774,  793,  793,  793,  519,  633,
 /*   110 */   793,  633,  793,  793,  793,  793,  793,  793,  793,  793,
 /*   120 */   793,  793,  793,  672,  672,  672,  672,  672,  793,  793,
 /*   130 */   627,  637,  793,  793,  597,  793,  793,  793,  793,  793,
 /*   140 */   793,  793,  793,  793,  774,  793,  625,  793,  793,  554,
 /*   150 */   793,  635,  793,  793,  640,  641,  793,  793,  793,  793,
 /*   160 */   793,  793,  793,  535,  793,  616,  793,  680,  793,  793,
 /*   170 */   660,  625,  634,  793,  793,  793,  793,  745,  660,  660,
 /*   180 */   576,  660,  660,  579,  672,  793,  793,  791,  791,  524,
 /*   190 */   524,  524,  596,  543,  543,  608,  608,  593,  608,  608,
 /*   200 */   793,  672,  663,  665,  653,  667,  793,  642,  661,  793,
 /*   210 */   661,  642,  650,  652,  650,  652,  752,  661,  661,  793,
 /*   220 */   593,  608,  608,  608,  752,  533,  530,  642,  615,  642,
 /*   230 */   672,  667,  667,  688,  793,  688,  538,  562,  581,  581,
 /*   240 */   793,  793,  534,  793,  793,  793,  696,  793,  793,  793,
 /*   250 */   793,  793,  793,  793,  793,  793,  793,  793,  793,  793,
 /*   260 */   793,  793,  793,  539,  793,  793,  793,  793,  793,  793,
 /*   270 */   793,  701,  697,  793,  698,  793,  793,  793,  793,  793,
 /*   280 */   619,  793,  793,  793,  654,  793,  664,  793,  793,  793,
 /*   290 */   793,  793,  793,  793,  793,  793,  793,  793,  793,  793,
 /*   300 */   793,  793,  793,  793,  793,  793,  793,  793,  793,  793,
 /*   310 */   677,  793,  678,  793,  679,  765,  793,  793,  793,  793,
 /*   320 */   793,  793,  793,  793,  520,  793,  513,  517,  515,  516,
 /*   330 */   522,  525,  523,  526,  527,  528,  540,  541,  544,  542,
 /*   340 */   536,  561,  549,  550,  551,  563,  570,  571,  609,  610,
 /*   350 */   611,  612,  762,  763,  764,  572,  591,  594,  595,  573,
 /*   360 */   658,  659,  574,  623,  624,  693,  617,  618,  622,  695,
 /*   370 */   699,  700,  702,  703,  704,  548,  555,  556,  559,  560,
 /*   380 */   757,  759,  758,  760,  558,  557,  705,  708,  718,  719,
 /*   390 */   725,  731,  735,  723,  724,  726,  730,  732,  733,  734,
 /*   400 */   620,  621,  738,  740,  741,  736,  748,  749,  643,  739,
 /*   410 */   722,  655,  547,  662,  656,  626,  636,  645,  646,  647,
 /*   420 */   648,  631,  632,  638,  651,  691,  692,  639,  628,  629,
 /*   430 */   630,  737,  694,  706,  707,  575,  582,  583,  584,  587,
 /*   440 */   588,  589,  590,  585,  586,  753,  754,  756,  755,  577,
 /*   450 */   578,  592,  564,  565,  566,  567,  701,  568,  569,  553,
 /*   460 */   546,  598,  601,  580,  602,  603,  604,  605,  607,  599,
 /*   470 */   600,  537,  529,  531,  532,  613,  644,  614,  671,  674,
 /*   480 */   683,  684,  685,  689,  690,  681,  682,  775,  776,  770,
 /*   490 */   771,  772,  773,  766,  767,  777,  778,  779,  780,  781,
 /*   500 */   782,  789,  790,  783,  792,  784,  785,  786,  787,  518,
 /*   510 */   521,  514,
};
#define YY_SZ_ACTTAB (sizeof(yy_action)/sizeof(yy_action[0]))

/* The next table maps tokens into fallback tokens.  If a construct
** like the following:
** 
**      %fallback ID X Y Z.
**
** appears in the grammer, then ID becomes a fallback token for X, Y,
** and Z.  Whenever one of the tokens X, Y, or Z is input to the parser
** but it does not parse, the type of the token is changed to ID and
** the parse is retried before an error is thrown.
*/
#ifdef YYFALLBACK
static const YYCODETYPE yyFallback[] = {
    0,  /*          $ => nothing */
    0,  /*         LP => nothing */
    0,  /*         RP => nothing */
    0,  /*       SEMI => nothing */
   21,  /*    EXPLAIN => ID */
   21,  /*      QUERY => ID */
   21,  /*       PLAN => ID */
   21,  /*      BEGIN => ID */
    0,  /*      START => nothing */
    0,  /* TRANSACTION => nothing */
    0,  /*       WORK => nothing */
    0,  /*     COMMIT => nothing */
    0,  /*   ROLLBACK => nothing */
    0,  /*     CREATE => nothing */
    0,  /*      TABLE => nothing */
   21,  /*         IF => ID */
    0,  /*        NOT => nothing */
    0,  /*     EXISTS => nothing */
   21,  /*       TEMP => ID */
    0,  /*         AS => nothing */
    0,  /*      COMMA => nothing */
    0,  /*         ID => nothing */
    0,  /*         EQ => nothing */
    0,  /*    DEFAULT => nothing */
    0,  /*    CHARSET => nothing */
    0,  /*        SET => nothing */
    0,  /*    COLLATE => nothing */
   21,  /*      ABORT => ID */
   21,  /*      AFTER => ID */
   21,  /*    ANALYZE => ID */
   21,  /*        ASC => ID */
   21,  /*     ATTACH => ID */
   21,  /*     BEFORE => ID */
   21,  /*    CASCADE => ID */
   21,  /*       CAST => ID */
   21,  /*   CONFLICT => ID */
   21,  /*   DATABASE => ID */
   21,  /*   DEFERRED => ID */
   21,  /*       DESC => ID */
   21,  /*     DETACH => ID */
   21,  /*       EACH => ID */
   21,  /*        END => ID */
   21,  /*  EXCLUSIVE => ID */
   21,  /*       FAIL => ID */
   21,  /*        FOR => ID */
   21,  /*     IGNORE => ID */
   21,  /*  IMMEDIATE => ID */
   21,  /*  INITIALLY => ID */
   21,  /*    INSTEAD => ID */
   21,  /*    LIKE_KW => ID */
   21,  /*      MATCH => ID */
   21,  /*        KEY => ID */
   21,  /*         OF => ID */
   21,  /*     OFFSET => ID */
   21,  /*     PRAGMA => ID */
   21,  /*      RAISE => ID */
   21,  /*    REPLACE => ID */
   21,  /*   RESTRICT => ID */
   21,  /*        ROW => ID */
   21,  /*  STATEMENT => ID */
   21,  /*    TRIGGER => ID */
   21,  /*     VACUUM => ID */
   21,  /*       VIEW => ID */
   21,  /*    REINDEX => ID */
   21,  /*     RENAME => ID */
   21,  /*   CTIME_KW => ID */
    0,  /*         OR => nothing */
    0,  /*        AND => nothing */
    0,  /*         IS => nothing */
    0,  /*    BETWEEN => nothing */
    0,  /*         IN => nothing */
    0,  /*     ISNULL => nothing */
    0,  /*    NOTNULL => nothing */
    0,  /*         NE => nothing */
    0,  /*         GT => nothing */
    0,  /*         LE => nothing */
    0,  /*         LT => nothing */
    0,  /*         GE => nothing */
    0,  /*     ESCAPE => nothing */
    0,  /*     BITAND => nothing */
    0,  /*      BITOR => nothing */
    0,  /*     LSHIFT => nothing */
    0,  /*     RSHIFT => nothing */
    0,  /*       PLUS => nothing */
    0,  /*      MINUS => nothing */
    0,  /*       STAR => nothing */
    0,  /*      SLASH => nothing */
    0,  /*        REM => nothing */
    0,  /*     CONCAT => nothing */
    0,  /*     UMINUS => nothing */
    0,  /*      UPLUS => nothing */
    0,  /*     BITNOT => nothing */
    0,  /*     STRING => nothing */
    0,  /*    JOIN_KW => nothing */
    0,  /* CONSTRAINT => nothing */
    0,  /*   AUTOINCR => nothing */
    0,  /*       NULL => nothing */
    0,  /*    PRIMARY => nothing */
    0,  /*     UNIQUE => nothing */
    0,  /*      CHECK => nothing */
    0,  /* REFERENCES => nothing */
    0,  /*         ON => nothing */
    0,  /*     DELETE => nothing */
    0,  /*     UPDATE => nothing */
    0,  /*     INSERT => nothing */
    0,  /* DEFERRABLE => nothing */
    0,  /*    FOREIGN => nothing */
    0,  /*       DROP => nothing */
    0,  /*      UNION => nothing */
    0,  /*        ALL => nothing */
    0,  /*     EXCEPT => nothing */
    0,  /*  INTERSECT => nothing */
    0,  /*     SELECT => nothing */
    0,  /*   DISTINCT => nothing */
    0,  /*        DOT => nothing */
    0,  /*       FROM => nothing */
    0,  /*       JOIN => nothing */
    0,  /*      USING => nothing */
    0,  /*      ORDER => nothing */
    0,  /*         BY => nothing */
    0,  /*      GROUP => nothing */
    0,  /*     HAVING => nothing */
    0,  /*      LIMIT => nothing */
    0,  /*      WHERE => nothing */
    0,  /*       INTO => nothing */
    0,  /*     VALUES => nothing */
    0,  /*    INTEGER => nothing */
    0,  /*      FLOAT => nothing */
    0,  /*       BLOB => nothing */
    0,  /*   REGISTER => nothing */
    0,  /*   VARIABLE => nothing */
    0,  /*  VARIABLE1 => nothing */
    0,  /*       CASE => nothing */
    0,  /*       WHEN => nothing */
    0,  /*       THEN => nothing */
    0,  /*       ELSE => nothing */
    0,  /*      NAMES => nothing */
    0,  /*  CHARACTER => nothing */
    0,  /*     GLOBAL => nothing */
    0,  /*      LOCAL => nothing */
    0,  /*    SESSION => nothing */
    0,  /*       SHOW => nothing */
    0,  /*  DATABASES => nothing */
    0,  /*    SCHEMAS => nothing */
    0,  /*     TABLES => nothing */
    0,  /*     STATUS => nothing */
    0,  /*  VARIABLES => nothing */
    0,  /*  COLLATION => nothing */
};
#endif /* YYFALLBACK */

/* The following structure represents a single element of the
** parser's stack.  Information stored includes:
**
**   +  The state number for the parser at this level of the stack.
**
**   +  The value of the token stored at this level of the stack.
**      (In other words, the "major" token.)
**
**   +  The semantic value stored at this level of the stack.  This is
**      the information used by the action routines in the grammar.
**      It is sometimes called the "minor" token.
*/
struct yyStackEntry {
  int stateno;       /* The state-number */
  int major;         /* The major token value.  This is the code
                     ** number for the token at this stack level */
  YYMINORTYPE minor; /* The user-supplied minor token value.  This
                     ** is the value of the token  */
};
typedef struct yyStackEntry yyStackEntry;

/* The state of the parser is completely contained in an instance of
** the following structure */
struct yyParser {
  int yyidx;                    /* Index of top element in stack */
  int yyerrcnt;                 /* Shifts left before out of the error */
  ParserARG_SDECL                /* A place to hold %extra_argument */
  yyStackEntry yystack[YYSTACKDEPTH];  /* The parser's stack */
};
typedef struct yyParser yyParser;

#ifndef NDEBUG
#include <stdio.h>
static FILE *yyTraceFILE = 0;
static char *yyTracePrompt = 0;
#endif /* NDEBUG */

#ifndef NDEBUG
/* 
** Turn parser tracing on by giving a stream to which to write the trace
** and a prompt to preface each trace message.  Tracing is turned off
** by making either argument NULL 
**
** Inputs:
** <ul>
** <li> A FILE* to which trace output should be written.
**      If NULL, then tracing is turned off.
** <li> A prefix string written at the beginning of every
**      line of trace output.  If NULL, then tracing is
**      turned off.
** </ul>
**
** Outputs:
** None.
*/
void ParserTrace(FILE *TraceFILE, char *zTracePrompt){
  yyTraceFILE = TraceFILE;
  yyTracePrompt = zTracePrompt;
  if( yyTraceFILE==0 ) yyTracePrompt = 0;
  else if( yyTracePrompt==0 ) yyTraceFILE = 0;
}
#endif /* NDEBUG */

#ifndef NDEBUG
/* For tracing shifts, the names of all terminals and nonterminals
** are required.  The following table supplies these names */
static const char *const yyTokenName[] = { 
  "$",             "LP",            "RP",            "SEMI",        
  "EXPLAIN",       "QUERY",         "PLAN",          "BEGIN",       
  "START",         "TRANSACTION",   "WORK",          "COMMIT",      
  "ROLLBACK",      "CREATE",        "TABLE",         "IF",          
  "NOT",           "EXISTS",        "TEMP",          "AS",          
  "COMMA",         "ID",            "EQ",            "DEFAULT",     
  "CHARSET",       "SET",           "COLLATE",       "ABORT",       
  "AFTER",         "ANALYZE",       "ASC",           "ATTACH",      
  "BEFORE",        "CASCADE",       "CAST",          "CONFLICT",    
  "DATABASE",      "DEFERRED",      "DESC",          "DETACH",      
  "EACH",          "END",           "EXCLUSIVE",     "FAIL",        
  "FOR",           "IGNORE",        "IMMEDIATE",     "INITIALLY",   
  "INSTEAD",       "LIKE_KW",       "MATCH",         "KEY",         
  "OF",            "OFFSET",        "PRAGMA",        "RAISE",       
  "REPLACE",       "RESTRICT",      "ROW",           "STATEMENT",   
  "TRIGGER",       "VACUUM",        "VIEW",          "REINDEX",     
  "RENAME",        "CTIME_KW",      "OR",            "AND",         
  "IS",            "BETWEEN",       "IN",            "ISNULL",      
  "NOTNULL",       "NE",            "GT",            "LE",          
  "LT",            "GE",            "ESCAPE",        "BITAND",      
  "BITOR",         "LSHIFT",        "RSHIFT",        "PLUS",        
  "MINUS",         "STAR",          "SLASH",         "REM",         
  "CONCAT",        "UMINUS",        "UPLUS",         "BITNOT",      
  "STRING",        "JOIN_KW",       "CONSTRAINT",    "AUTOINCR",    
  "NULL",          "PRIMARY",       "UNIQUE",        "CHECK",       
  "REFERENCES",    "ON",            "DELETE",        "UPDATE",      
  "INSERT",        "DEFERRABLE",    "FOREIGN",       "DROP",        
  "UNION",         "ALL",           "EXCEPT",        "INTERSECT",   
  "SELECT",        "DISTINCT",      "DOT",           "FROM",        
  "JOIN",          "USING",         "ORDER",         "BY",          
  "GROUP",         "HAVING",        "LIMIT",         "WHERE",       
  "INTO",          "VALUES",        "INTEGER",       "FLOAT",       
  "BLOB",          "REGISTER",      "VARIABLE",      "VARIABLE1",   
  "CASE",          "WHEN",          "THEN",          "ELSE",        
  "NAMES",         "CHARACTER",     "GLOBAL",        "LOCAL",       
  "SESSION",       "SHOW",          "DATABASES",     "SCHEMAS",     
  "TABLES",        "STATUS",        "VARIABLES",     "COLLATION",   
  "error",         "input",         "cmdlist",       "ecmd",        
  "cmdx",          "cmd",           "explain",       "trans_opt",   
  "create_table",  "create_table_args",  "temp",          "ifnotexists", 
  "nm",            "dbnm",          "columnlist",    "conslist_opt",
  "table_opt",     "select",        "column",        "eq_or_null",  
  "columnid",      "type",          "carglist",      "id",          
  "ids",           "typetoken",     "typename",      "signed",      
  "plus_num",      "minus_num",     "carg",          "ccons",       
  "term",          "expr",          "onconf",        "sortorder",   
  "idxlist_opt",   "refargs",       "defer_subclause",  "autoinc",     
  "refarg",        "refact",        "init_deferred_pred_opt",  "conslist",    
  "tcons",         "idxlist",       "defer_subclause_opt",  "orconf",      
  "resolvetype",   "raisetype",     "ifexists",      "fullname",    
  "oneselect",     "multiselect_op",  "distinct",      "selcollist",  
  "from",          "where_opt",     "groupby_opt",   "having_opt",  
  "orderby_opt",   "limit_opt",     "sclp",          "as",          
  "seltablist",    "stl_prefix",    "joinop",        "on_opt",      
  "using_opt",     "seltablist_paren",  "joinop2",       "inscollist",  
  "sortlist",      "sortitem",      "collate",       "exprlist",    
  "setlist",       "insert_cmd",    "inscollist_opt",  "valueslist",  
  "itemlist",      "likeop",        "escape",        "between_op",  
  "between_elem",  "in_op",         "case_operand",  "case_exprlist",
  "case_else",     "expritem",      "idxitem",       "plus_opt",    
  "number",        "variable_assignment_list",  "scope_qualifier",  "user_var_name",
  "show_databes",  "show_tables",   "show_table_status",  "show_variables",
  "show_collation",  "show_statement_pattern",  "full_keyword",  "from_db",     
};
#endif /* NDEBUG */

#ifndef NDEBUG
/* For tracing reduce actions, the names of all rules are required.
*/
static const char *const yyRuleName[] = {
 /*   0 */ "input ::= cmdlist",
 /*   1 */ "cmdlist ::= cmdlist ecmd",
 /*   2 */ "cmdlist ::= ecmd",
 /*   3 */ "cmdx ::= cmd",
 /*   4 */ "cmdx ::= LP cmd RP",
 /*   5 */ "ecmd ::= SEMI",
 /*   6 */ "ecmd ::= explain cmdx SEMI",
 /*   7 */ "explain ::=",
 /*   8 */ "explain ::= EXPLAIN",
 /*   9 */ "explain ::= EXPLAIN QUERY PLAN",
 /*  10 */ "cmd ::= BEGIN trans_opt",
 /*  11 */ "cmd ::= START TRANSACTION",
 /*  12 */ "trans_opt ::=",
 /*  13 */ "trans_opt ::= WORK",
 /*  14 */ "cmd ::= COMMIT trans_opt",
 /*  15 */ "cmd ::= ROLLBACK trans_opt",
 /*  16 */ "cmd ::= create_table create_table_args",
 /*  17 */ "create_table ::= CREATE temp TABLE ifnotexists nm dbnm",
 /*  18 */ "ifnotexists ::=",
 /*  19 */ "ifnotexists ::= IF NOT EXISTS",
 /*  20 */ "temp ::= TEMP",
 /*  21 */ "temp ::=",
 /*  22 */ "create_table_args ::= LP columnlist conslist_opt RP table_opt",
 /*  23 */ "create_table_args ::= AS select",
 /*  24 */ "columnlist ::= columnlist COMMA column",
 /*  25 */ "columnlist ::= column",
 /*  26 */ "table_opt ::=",
 /*  27 */ "table_opt ::= table_opt ID",
 /*  28 */ "table_opt ::= table_opt ID EQ ID",
 /*  29 */ "table_opt ::= table_opt DEFAULT CHARSET SET eq_or_null ID",
 /*  30 */ "table_opt ::= table_opt DEFAULT COLLATE eq_or_null ID",
 /*  31 */ "eq_or_null ::=",
 /*  32 */ "eq_or_null ::= EQ",
 /*  33 */ "column ::= columnid type carglist",
 /*  34 */ "columnid ::= nm",
 /*  35 */ "id ::= ID",
 /*  36 */ "ids ::= ID|STRING",
 /*  37 */ "nm ::= ID",
 /*  38 */ "nm ::= STRING",
 /*  39 */ "nm ::= JOIN_KW",
 /*  40 */ "type ::=",
 /*  41 */ "type ::= typetoken",
 /*  42 */ "typetoken ::= typename",
 /*  43 */ "typetoken ::= typename LP signed RP",
 /*  44 */ "typetoken ::= typename LP signed COMMA signed RP",
 /*  45 */ "typename ::= ids",
 /*  46 */ "typename ::= typename ids",
 /*  47 */ "signed ::= plus_num",
 /*  48 */ "signed ::= minus_num",
 /*  49 */ "carglist ::= carglist carg",
 /*  50 */ "carglist ::=",
 /*  51 */ "carg ::= CONSTRAINT nm ccons",
 /*  52 */ "carg ::= ccons",
 /*  53 */ "carg ::= DEFAULT term",
 /*  54 */ "carg ::= DEFAULT LP expr RP",
 /*  55 */ "carg ::= DEFAULT PLUS term",
 /*  56 */ "carg ::= DEFAULT MINUS term",
 /*  57 */ "carg ::= DEFAULT id",
 /*  58 */ "ccons ::= AUTOINCR",
 /*  59 */ "ccons ::= NULL onconf",
 /*  60 */ "ccons ::= NOT NULL onconf",
 /*  61 */ "ccons ::= PRIMARY KEY sortorder onconf",
 /*  62 */ "ccons ::= UNIQUE onconf",
 /*  63 */ "ccons ::= CHECK LP expr RP",
 /*  64 */ "ccons ::= REFERENCES nm idxlist_opt refargs",
 /*  65 */ "ccons ::= defer_subclause",
 /*  66 */ "ccons ::= COLLATE id",
 /*  67 */ "autoinc ::=",
 /*  68 */ "autoinc ::= AUTOINCR",
 /*  69 */ "refargs ::=",
 /*  70 */ "refargs ::= refargs refarg",
 /*  71 */ "refarg ::= MATCH nm",
 /*  72 */ "refarg ::= ON DELETE refact",
 /*  73 */ "refarg ::= ON UPDATE refact",
 /*  74 */ "refarg ::= ON INSERT refact",
 /*  75 */ "refact ::= SET NULL",
 /*  76 */ "refact ::= SET DEFAULT",
 /*  77 */ "refact ::= CASCADE",
 /*  78 */ "refact ::= RESTRICT",
 /*  79 */ "defer_subclause ::= NOT DEFERRABLE init_deferred_pred_opt",
 /*  80 */ "defer_subclause ::= DEFERRABLE init_deferred_pred_opt",
 /*  81 */ "init_deferred_pred_opt ::=",
 /*  82 */ "init_deferred_pred_opt ::= INITIALLY DEFERRED",
 /*  83 */ "init_deferred_pred_opt ::= INITIALLY IMMEDIATE",
 /*  84 */ "conslist_opt ::=",
 /*  85 */ "conslist_opt ::= COMMA conslist",
 /*  86 */ "conslist ::= conslist COMMA tcons",
 /*  87 */ "conslist ::= conslist tcons",
 /*  88 */ "conslist ::= tcons",
 /*  89 */ "tcons ::= CONSTRAINT nm",
 /*  90 */ "tcons ::= PRIMARY KEY LP idxlist autoinc RP onconf",
 /*  91 */ "tcons ::= UNIQUE LP idxlist RP onconf",
 /*  92 */ "tcons ::= CHECK LP expr RP onconf",
 /*  93 */ "tcons ::= FOREIGN KEY LP idxlist RP REFERENCES nm idxlist_opt refargs defer_subclause_opt",
 /*  94 */ "defer_subclause_opt ::=",
 /*  95 */ "defer_subclause_opt ::= defer_subclause",
 /*  96 */ "onconf ::=",
 /*  97 */ "onconf ::= ON CONFLICT resolvetype",
 /*  98 */ "resolvetype ::= raisetype",
 /*  99 */ "resolvetype ::= IGNORE",
 /* 100 */ "resolvetype ::= REPLACE",
 /* 101 */ "cmd ::= DROP TABLE ifexists fullname",
 /* 102 */ "ifexists ::= IF EXISTS",
 /* 103 */ "ifexists ::=",
 /* 104 */ "cmd ::= select",
 /* 105 */ "select ::= oneselect",
 /* 106 */ "select ::= select multiselect_op oneselect",
 /* 107 */ "multiselect_op ::= UNION",
 /* 108 */ "multiselect_op ::= UNION ALL",
 /* 109 */ "multiselect_op ::= EXCEPT|INTERSECT",
 /* 110 */ "oneselect ::= SELECT distinct selcollist from where_opt groupby_opt having_opt orderby_opt limit_opt",
 /* 111 */ "distinct ::= DISTINCT",
 /* 112 */ "distinct ::= ALL",
 /* 113 */ "distinct ::=",
 /* 114 */ "sclp ::= selcollist COMMA",
 /* 115 */ "sclp ::=",
 /* 116 */ "selcollist ::= sclp expr as",
 /* 117 */ "selcollist ::= sclp STAR",
 /* 118 */ "selcollist ::= sclp nm DOT STAR",
 /* 119 */ "as ::= AS nm",
 /* 120 */ "as ::= ids",
 /* 121 */ "as ::=",
 /* 122 */ "from ::=",
 /* 123 */ "from ::= FROM seltablist",
 /* 124 */ "stl_prefix ::= seltablist joinop",
 /* 125 */ "stl_prefix ::=",
 /* 126 */ "seltablist ::= stl_prefix nm dbnm as on_opt using_opt",
 /* 127 */ "seltablist ::= stl_prefix LP seltablist_paren RP as on_opt using_opt",
 /* 128 */ "seltablist_paren ::= select",
 /* 129 */ "seltablist_paren ::= seltablist",
 /* 130 */ "dbnm ::=",
 /* 131 */ "dbnm ::= DOT nm",
 /* 132 */ "fullname ::= nm dbnm",
 /* 133 */ "joinop ::= COMMA|JOIN",
 /* 134 */ "joinop ::= JOIN_KW JOIN",
 /* 135 */ "joinop ::= JOIN_KW nm JOIN",
 /* 136 */ "joinop ::= JOIN_KW nm nm JOIN",
 /* 137 */ "on_opt ::= ON expr",
 /* 138 */ "on_opt ::=",
 /* 139 */ "using_opt ::= USING LP inscollist RP",
 /* 140 */ "using_opt ::=",
 /* 141 */ "orderby_opt ::=",
 /* 142 */ "orderby_opt ::= ORDER BY sortlist",
 /* 143 */ "sortlist ::= sortlist COMMA sortitem collate sortorder",
 /* 144 */ "sortlist ::= sortitem collate sortorder",
 /* 145 */ "sortitem ::= expr",
 /* 146 */ "sortorder ::= ASC",
 /* 147 */ "sortorder ::= DESC",
 /* 148 */ "sortorder ::=",
 /* 149 */ "collate ::=",
 /* 150 */ "collate ::= COLLATE id",
 /* 151 */ "groupby_opt ::=",
 /* 152 */ "groupby_opt ::= GROUP BY exprlist",
 /* 153 */ "having_opt ::=",
 /* 154 */ "having_opt ::= HAVING expr",
 /* 155 */ "limit_opt ::=",
 /* 156 */ "limit_opt ::= LIMIT expr",
 /* 157 */ "limit_opt ::= LIMIT expr OFFSET expr",
 /* 158 */ "limit_opt ::= LIMIT expr COMMA expr",
 /* 159 */ "cmd ::= DELETE FROM fullname where_opt limit_opt",
 /* 160 */ "where_opt ::=",
 /* 161 */ "where_opt ::= WHERE expr",
 /* 162 */ "cmd ::= UPDATE fullname SET setlist where_opt limit_opt",
 /* 163 */ "setlist ::= setlist COMMA nm EQ expr",
 /* 164 */ "setlist ::= nm EQ expr",
 /* 165 */ "cmd ::= insert_cmd INTO fullname inscollist_opt VALUES valueslist",
 /* 166 */ "cmd ::= insert_cmd INTO fullname inscollist_opt SET setlist",
 /* 167 */ "cmd ::= insert_cmd fullname inscollist_opt SET setlist",
 /* 168 */ "cmd ::= insert_cmd INTO fullname inscollist_opt select",
 /* 169 */ "insert_cmd ::= INSERT",
 /* 170 */ "insert_cmd ::= REPLACE",
 /* 171 */ "valueslist ::= valueslist COMMA LP itemlist RP",
 /* 172 */ "valueslist ::= LP itemlist RP",
 /* 173 */ "valueslist ::= LP RP",
 /* 174 */ "itemlist ::= itemlist COMMA expr",
 /* 175 */ "itemlist ::= expr",
 /* 176 */ "inscollist_opt ::=",
 /* 177 */ "inscollist_opt ::= LP RP",
 /* 178 */ "inscollist_opt ::= LP inscollist RP",
 /* 179 */ "inscollist ::= inscollist COMMA nm",
 /* 180 */ "inscollist ::= nm",
 /* 181 */ "expr ::= term",
 /* 182 */ "expr ::= LP expr RP",
 /* 183 */ "term ::= NULL",
 /* 184 */ "expr ::= ID",
 /* 185 */ "expr ::= JOIN_KW",
 /* 186 */ "expr ::= nm DOT nm",
 /* 187 */ "expr ::= nm DOT nm DOT nm",
 /* 188 */ "term ::= INTEGER|FLOAT|BLOB",
 /* 189 */ "term ::= STRING",
 /* 190 */ "expr ::= REGISTER",
 /* 191 */ "expr ::= VARIABLE",
 /* 192 */ "expr ::= VARIABLE1",
 /* 193 */ "expr ::= CAST LP expr AS typetoken RP",
 /* 194 */ "expr ::= ID LP distinct exprlist RP",
 /* 195 */ "expr ::= ID LP STAR RP",
 /* 196 */ "term ::= CTIME_KW",
 /* 197 */ "expr ::= expr AND expr",
 /* 198 */ "expr ::= expr OR expr",
 /* 199 */ "expr ::= expr LT|GT|GE|LE expr",
 /* 200 */ "expr ::= expr EQ expr",
 /* 201 */ "expr ::= expr NE expr",
 /* 202 */ "expr ::= expr BITAND|BITOR|LSHIFT|RSHIFT expr",
 /* 203 */ "expr ::= expr PLUS|MINUS expr",
 /* 204 */ "expr ::= expr STAR|SLASH|REM expr",
 /* 205 */ "expr ::= expr CONCAT expr",
 /* 206 */ "likeop ::= LIKE_KW",
 /* 207 */ "likeop ::= NOT LIKE_KW",
 /* 208 */ "escape ::= ESCAPE expr",
 /* 209 */ "escape ::=",
 /* 210 */ "expr ::= expr likeop expr escape",
 /* 211 */ "expr ::= expr ISNULL|NOTNULL",
 /* 212 */ "expr ::= expr IS NULL",
 /* 213 */ "expr ::= expr NOT NULL",
 /* 214 */ "expr ::= expr IS NOT NULL",
 /* 215 */ "expr ::= NOT|BITNOT expr",
 /* 216 */ "expr ::= MINUS expr",
 /* 217 */ "expr ::= PLUS expr",
 /* 218 */ "between_op ::= BETWEEN",
 /* 219 */ "between_op ::= NOT BETWEEN",
 /* 220 */ "between_elem ::= INTEGER|STRING",
 /* 221 */ "expr ::= expr between_op between_elem AND between_elem",
 /* 222 */ "in_op ::= IN",
 /* 223 */ "in_op ::= NOT IN",
 /* 224 */ "expr ::= expr in_op LP exprlist RP",
 /* 225 */ "expr ::= LP select RP",
 /* 226 */ "expr ::= expr in_op LP select RP",
 /* 227 */ "expr ::= expr in_op nm dbnm",
 /* 228 */ "expr ::= EXISTS LP select RP",
 /* 229 */ "expr ::= CASE case_operand case_exprlist case_else END",
 /* 230 */ "case_exprlist ::= case_exprlist WHEN expr THEN expr",
 /* 231 */ "case_exprlist ::= WHEN expr THEN expr",
 /* 232 */ "case_else ::= ELSE expr",
 /* 233 */ "case_else ::=",
 /* 234 */ "case_operand ::= expr",
 /* 235 */ "case_operand ::=",
 /* 236 */ "exprlist ::= exprlist COMMA expritem",
 /* 237 */ "exprlist ::= expritem",
 /* 238 */ "expritem ::= expr",
 /* 239 */ "expritem ::=",
 /* 240 */ "idxlist_opt ::=",
 /* 241 */ "idxlist_opt ::= LP idxlist RP",
 /* 242 */ "idxlist ::= idxlist COMMA idxitem collate sortorder",
 /* 243 */ "idxlist ::= idxitem collate sortorder",
 /* 244 */ "idxitem ::= nm",
 /* 245 */ "plus_num ::= plus_opt number",
 /* 246 */ "minus_num ::= MINUS number",
 /* 247 */ "number ::= INTEGER|FLOAT",
 /* 248 */ "plus_opt ::= PLUS",
 /* 249 */ "plus_opt ::=",
 /* 250 */ "raisetype ::= ROLLBACK",
 /* 251 */ "raisetype ::= ABORT",
 /* 252 */ "raisetype ::= FAIL",
 /* 253 */ "cmd ::= SET variable_assignment_list",
 /* 254 */ "cmd ::= SET NAMES ids",
 /* 255 */ "cmd ::= SET CHARACTER SET ids",
 /* 256 */ "variable_assignment_list ::= variable_assignment_list COMMA scope_qualifier user_var_name EQ expr",
 /* 257 */ "variable_assignment_list ::= scope_qualifier user_var_name EQ expr",
 /* 258 */ "scope_qualifier ::= GLOBAL",
 /* 259 */ "scope_qualifier ::= LOCAL",
 /* 260 */ "scope_qualifier ::= SESSION",
 /* 261 */ "scope_qualifier ::= VARIABLE1 DOT",
 /* 262 */ "scope_qualifier ::=",
 /* 263 */ "user_var_name ::= ids",
 /* 264 */ "user_var_name ::= VARIABLE",
 /* 265 */ "cmd ::= show_databes",
 /* 266 */ "cmd ::= show_tables",
 /* 267 */ "cmd ::= show_table_status",
 /* 268 */ "cmd ::= show_variables",
 /* 269 */ "cmd ::= show_collation",
 /* 270 */ "show_databes ::= SHOW DATABASES|SCHEMAS show_statement_pattern",
 /* 271 */ "show_tables ::= SHOW full_keyword TABLES from_db show_statement_pattern",
 /* 272 */ "show_table_status ::= SHOW TABLE STATUS from_db show_statement_pattern",
 /* 273 */ "show_variables ::= SHOW scope_qualifier VARIABLES show_statement_pattern",
 /* 274 */ "show_collation ::= SHOW COLLATION show_statement_pattern",
 /* 275 */ "full_keyword ::= JOIN_KW",
 /* 276 */ "full_keyword ::=",
 /* 277 */ "show_statement_pattern ::= LIKE_KW STRING|ID",
 /* 278 */ "show_statement_pattern ::= where_opt",
 /* 279 */ "from_db ::=",
 /* 280 */ "from_db ::= FROM|IN nm",
};
#endif /* NDEBUG */

/*
** This function returns the symbolic name associated with a token
** value.
*/
const char *ParserTokenName(int tokenType){
#ifndef NDEBUG
  if( tokenType>0 && tokenType<(sizeof(yyTokenName)/sizeof(yyTokenName[0])) ){
    return yyTokenName[tokenType];
  }else{
    return "Unknown";
  }
#else
  return "";
#endif
}

/* 
** This function allocates a new parser.
** The only argument is a pointer to a function which works like
** malloc.
**
** Inputs:
** A pointer to the function used to allocate memory.
**
** Outputs:
** A pointer to a parser.  This pointer is used in subsequent calls
** to Parser and ParserFree.
*/
void *ParserAlloc(void *(*mallocProc)(size_t)){
  yyParser *pParser;
  pParser = (yyParser*)(*mallocProc)( (size_t)sizeof(yyParser) );
  if( pParser ){
    pParser->yyidx = -1;
  }
  return pParser;
}

/* The following function deletes the value associated with a
** symbol.  The symbol can be either a terminal or nonterminal.
** "yymajor" is the symbol code, and "yypminor" is a pointer to
** the value.
*/
static void yy_destructor(YYCODETYPE yymajor, YYMINORTYPE *yypminor){
  switch( yymajor ){
    /* Here is inserted the actions which take place when a
    ** terminal or non-terminal is destroyed.  This can happen
    ** when the symbol is popped from the stack during a
    ** reduce or during error processing or when a parser is 
    ** being destroyed before it is finished parsing.
    **
    ** Note: during a reduce, the only symbols destroyed are those
    ** which appear on the RHS of the rule, but which are not used
    ** inside the C code.
    */
    case 180:
    case 181:
    case 207:
    case 230:
    case 232:
    case 234:
    case 236:
#line 639 "parse.y"
{}
#line 1189 "parse.c"
      break;
    case 184:
#line 800 "parse.y"
{}
#line 1194 "parse.c"
      break;
    case 193:
    case 203:
    case 206:
    case 208:
    case 210:
    case 220:
    case 223:
    case 224:
    case 228:
    case 235:
    case 241:
#line 798 "parse.y"
{ }
#line 1209 "parse.c"
      break;
    case 199:
    case 204:
    case 212:
    case 213:
#line 493 "parse.y"
{}
#line 1217 "parse.c"
      break;
    case 205:
    case 215:
    case 221:
    case 237:
#line 566 "parse.y"
{ }
#line 1225 "parse.c"
      break;
    case 209:
#line 552 "parse.y"
{
}
#line 1231 "parse.c"
      break;
    case 216:
#line 510 "parse.y"
{ }
#line 1236 "parse.c"
      break;
    case 217:
#line 481 "parse.y"
{ }
#line 1241 "parse.c"
      break;
    case 219:
    case 226:
#line 625 "parse.y"
{}
#line 1247 "parse.c"
      break;
    case 227:
#line 610 "parse.y"
{ }
#line 1252 "parse.c"
      break;
    default:  break;   /* If no destructor action specified: do nothing */
  }
}

/*
** Pop the parser's stack once.
**
** If there is a destructor routine associated with the token which
** is popped from the stack, then call it.
**
** Return the major token number for the symbol popped.
*/
static int yy_pop_parser_stack(yyParser *pParser){
  YYCODETYPE yymajor;
  yyStackEntry *yytos = &pParser->yystack[pParser->yyidx];

  if( pParser->yyidx<0 ) return 0;
#ifndef NDEBUG
  if( yyTraceFILE && pParser->yyidx>=0 ){
    fprintf(yyTraceFILE,"%sPopping %s\n",
      yyTracePrompt,
      yyTokenName[yytos->major]);
  }
#endif
  yymajor = yytos->major;
  yy_destructor( yymajor, &yytos->minor);
  pParser->yyidx--;
  return yymajor;
}

/* 
** Deallocate and destroy a parser.  Destructors are all called for
** all stack elements before shutting the parser down.
**
** Inputs:
** <ul>
** <li>  A pointer to the parser.  This should be a pointer
**       obtained from ParserAlloc.
** <li>  A pointer to a function used to reclaim memory obtained
**       from malloc.
** </ul>
*/
void ParserFree(
  void *p,                    /* The parser to be deleted */
  void (*freeProc)(void*)     /* Function used to reclaim memory */
){
  yyParser *pParser = (yyParser*)p;
  if( pParser==0 ) return;
  while( pParser->yyidx>=0 ) yy_pop_parser_stack(pParser);
  (*freeProc)((void*)pParser);
}

/*
** Find the appropriate action for a parser given the terminal
** look-ahead token iLookAhead.
**
** If the look-ahead token is YYNOCODE, then check to see if the action is
** independent of the look-ahead.  If it is, return the action, otherwise
** return YY_NO_ACTION.
*/
static int yy_find_shift_action(
  yyParser *pParser,        /* The parser */
  int iLookAhead            /* The look-ahead token */
){
  int i;
  int stateno = pParser->yystack[pParser->yyidx].stateno;
 
  if( stateno>YY_SHIFT_MAX || (i = yy_shift_ofst[stateno])==YY_SHIFT_USE_DFLT ){
    return yy_default[stateno];
  }
  if( iLookAhead==YYNOCODE ){
    return YY_NO_ACTION;
  }
  i += iLookAhead;
  if( i<0 || i>=YY_SZ_ACTTAB || yy_lookahead[i]!=iLookAhead ){
#ifdef YYFALLBACK
    int iFallback;            /* Fallback token */
    if( iLookAhead<sizeof(yyFallback)/sizeof(yyFallback[0])
           && (iFallback = yyFallback[iLookAhead])!=0 ){
#ifndef NDEBUG
      if( yyTraceFILE ){
        fprintf(yyTraceFILE, "%sFALLBACK %s => %s\n",
           yyTracePrompt, yyTokenName[iLookAhead], yyTokenName[iFallback]);
      }
#endif
      return yy_find_shift_action(pParser, iFallback);
    }
#endif
    return yy_default[stateno];
  }else{
    return yy_action[i];
  }
}

/*
** Find the appropriate action for a parser given the non-terminal
** look-ahead token iLookAhead.
**
** If the look-ahead token is YYNOCODE, then check to see if the action is
** independent of the look-ahead.  If it is, return the action, otherwise
** return YY_NO_ACTION.
*/
static int yy_find_reduce_action(
  int stateno,              /* Current state number */
  int iLookAhead            /* The look-ahead token */
){
  int i;
  /* int stateno = pParser->yystack[pParser->yyidx].stateno; */
 
  if( stateno>YY_REDUCE_MAX ||
      (i = yy_reduce_ofst[stateno])==YY_REDUCE_USE_DFLT ){
    return yy_default[stateno];
  }
  if( iLookAhead==YYNOCODE ){
    return YY_NO_ACTION;
  }
  i += iLookAhead;
  if( i<0 || i>=YY_SZ_ACTTAB || yy_lookahead[i]!=iLookAhead ){
    return yy_default[stateno];
  }else{
    return yy_action[i];
  }
}

/*
** Perform a shift action.
*/
static void yy_shift(
  yyParser *yypParser,          /* The parser to be shifted */
  int yyNewState,               /* The new state to shift in */
  int yyMajor,                  /* The major token to shift in */
  YYMINORTYPE *yypMinor         /* Pointer ot the minor token to shift in */
){
  yyStackEntry *yytos;
  yypParser->yyidx++;
  if( yypParser->yyidx>=YYSTACKDEPTH ){
     ParserARG_FETCH;
     yypParser->yyidx--;
#ifndef NDEBUG
     if( yyTraceFILE ){
       fprintf(yyTraceFILE,"%sStack Overflow!\n",yyTracePrompt);
     }
#endif
     while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
     /* Here code is inserted which will execute if the parser
     ** stack every overflows */
#line 43 "parse.y"

  sqlite3ErrorMsg(pParse, "parser stack overflow");
#line 1404 "parse.c"
     ParserARG_STORE; /* Suppress warning about unused %extra_argument var */
     return;
  }
  yytos = &yypParser->yystack[yypParser->yyidx];
  yytos->stateno = yyNewState;
  yytos->major = yyMajor;
  yytos->minor = *yypMinor;
#ifndef NDEBUG
  if( yyTraceFILE && yypParser->yyidx>0 ){
    int i;
    fprintf(yyTraceFILE,"%sShift %d\n",yyTracePrompt,yyNewState);
    fprintf(yyTraceFILE,"%sStack:",yyTracePrompt);
    for(i=1; i<=yypParser->yyidx; i++)
      fprintf(yyTraceFILE," %s",yyTokenName[yypParser->yystack[i].major]);
    fprintf(yyTraceFILE,"\n");
  }
#endif
}

/* The following table contains information about every rule that
** is used during the reduce.
*/
static const struct {
  YYCODETYPE lhs;         /* Symbol on the left-hand side of the rule */
  unsigned char nrhs;     /* Number of right-hand side symbols in the rule */
} yyRuleInfo[] = {
  { 149, 1 },
  { 150, 2 },
  { 150, 1 },
  { 152, 1 },
  { 152, 3 },
  { 151, 1 },
  { 151, 3 },
  { 154, 0 },
  { 154, 1 },
  { 154, 3 },
  { 153, 2 },
  { 153, 2 },
  { 155, 0 },
  { 155, 1 },
  { 153, 2 },
  { 153, 2 },
  { 153, 2 },
  { 156, 6 },
  { 159, 0 },
  { 159, 3 },
  { 158, 1 },
  { 158, 0 },
  { 157, 5 },
  { 157, 2 },
  { 162, 3 },
  { 162, 1 },
  { 164, 0 },
  { 164, 2 },
  { 164, 4 },
  { 164, 6 },
  { 164, 5 },
  { 167, 0 },
  { 167, 1 },
  { 166, 3 },
  { 168, 1 },
  { 171, 1 },
  { 172, 1 },
  { 160, 1 },
  { 160, 1 },
  { 160, 1 },
  { 169, 0 },
  { 169, 1 },
  { 173, 1 },
  { 173, 4 },
  { 173, 6 },
  { 174, 1 },
  { 174, 2 },
  { 175, 1 },
  { 175, 1 },
  { 170, 2 },
  { 170, 0 },
  { 178, 3 },
  { 178, 1 },
  { 178, 2 },
  { 178, 4 },
  { 178, 3 },
  { 178, 3 },
  { 178, 2 },
  { 179, 1 },
  { 179, 2 },
  { 179, 3 },
  { 179, 4 },
  { 179, 2 },
  { 179, 4 },
  { 179, 4 },
  { 179, 1 },
  { 179, 2 },
  { 187, 0 },
  { 187, 1 },
  { 185, 0 },
  { 185, 2 },
  { 188, 2 },
  { 188, 3 },
  { 188, 3 },
  { 188, 3 },
  { 189, 2 },
  { 189, 2 },
  { 189, 1 },
  { 189, 1 },
  { 186, 3 },
  { 186, 2 },
  { 190, 0 },
  { 190, 2 },
  { 190, 2 },
  { 163, 0 },
  { 163, 2 },
  { 191, 3 },
  { 191, 2 },
  { 191, 1 },
  { 192, 2 },
  { 192, 7 },
  { 192, 5 },
  { 192, 5 },
  { 192, 10 },
  { 194, 0 },
  { 194, 1 },
  { 182, 0 },
  { 182, 3 },
  { 196, 1 },
  { 196, 1 },
  { 196, 1 },
  { 153, 4 },
  { 198, 2 },
  { 198, 0 },
  { 153, 1 },
  { 165, 1 },
  { 165, 3 },
  { 201, 1 },
  { 201, 2 },
  { 201, 1 },
  { 200, 9 },
  { 202, 1 },
  { 202, 1 },
  { 202, 0 },
  { 210, 2 },
  { 210, 0 },
  { 203, 3 },
  { 203, 2 },
  { 203, 4 },
  { 211, 2 },
  { 211, 1 },
  { 211, 0 },
  { 204, 0 },
  { 204, 2 },
  { 213, 2 },
  { 213, 0 },
  { 212, 6 },
  { 212, 7 },
  { 217, 1 },
  { 217, 1 },
  { 161, 0 },
  { 161, 2 },
  { 199, 2 },
  { 214, 1 },
  { 214, 2 },
  { 214, 3 },
  { 214, 4 },
  { 215, 2 },
  { 215, 0 },
  { 216, 4 },
  { 216, 0 },
  { 208, 0 },
  { 208, 3 },
  { 220, 5 },
  { 220, 3 },
  { 221, 1 },
  { 183, 1 },
  { 183, 1 },
  { 183, 0 },
  { 222, 0 },
  { 222, 2 },
  { 206, 0 },
  { 206, 3 },
  { 207, 0 },
  { 207, 2 },
  { 209, 0 },
  { 209, 2 },
  { 209, 4 },
  { 209, 4 },
  { 153, 5 },
  { 205, 0 },
  { 205, 2 },
  { 153, 6 },
  { 224, 5 },
  { 224, 3 },
  { 153, 6 },
  { 153, 6 },
  { 153, 5 },
  { 153, 5 },
  { 225, 1 },
  { 225, 1 },
  { 227, 5 },
  { 227, 3 },
  { 227, 2 },
  { 228, 3 },
  { 228, 1 },
  { 226, 0 },
  { 226, 2 },
  { 226, 3 },
  { 219, 3 },
  { 219, 1 },
  { 181, 1 },
  { 181, 3 },
  { 180, 1 },
  { 181, 1 },
  { 181, 1 },
  { 181, 3 },
  { 181, 5 },
  { 180, 1 },
  { 180, 1 },
  { 181, 1 },
  { 181, 1 },
  { 181, 1 },
  { 181, 6 },
  { 181, 5 },
  { 181, 4 },
  { 180, 1 },
  { 181, 3 },
  { 181, 3 },
  { 181, 3 },
  { 181, 3 },
  { 181, 3 },
  { 181, 3 },
  { 181, 3 },
  { 181, 3 },
  { 181, 3 },
  { 229, 1 },
  { 229, 2 },
  { 230, 2 },
  { 230, 0 },
  { 181, 4 },
  { 181, 2 },
  { 181, 3 },
  { 181, 3 },
  { 181, 4 },
  { 181, 2 },
  { 181, 2 },
  { 181, 2 },
  { 231, 1 },
  { 231, 2 },
  { 232, 1 },
  { 181, 5 },
  { 233, 1 },
  { 233, 2 },
  { 181, 5 },
  { 181, 3 },
  { 181, 5 },
  { 181, 4 },
  { 181, 4 },
  { 181, 5 },
  { 235, 5 },
  { 235, 4 },
  { 236, 2 },
  { 236, 0 },
  { 234, 1 },
  { 234, 0 },
  { 223, 3 },
  { 223, 1 },
  { 237, 1 },
  { 237, 0 },
  { 184, 0 },
  { 184, 3 },
  { 193, 5 },
  { 193, 3 },
  { 238, 1 },
  { 176, 2 },
  { 177, 2 },
  { 240, 1 },
  { 239, 1 },
  { 239, 0 },
  { 197, 1 },
  { 197, 1 },
  { 197, 1 },
  { 153, 2 },
  { 153, 3 },
  { 153, 4 },
  { 241, 6 },
  { 241, 4 },
  { 242, 1 },
  { 242, 1 },
  { 242, 1 },
  { 242, 2 },
  { 242, 0 },
  { 243, 1 },
  { 243, 1 },
  { 153, 1 },
  { 153, 1 },
  { 153, 1 },
  { 153, 1 },
  { 153, 1 },
  { 244, 3 },
  { 245, 5 },
  { 246, 5 },
  { 247, 4 },
  { 248, 3 },
  { 250, 1 },
  { 250, 0 },
  { 249, 2 },
  { 249, 1 },
  { 251, 0 },
  { 251, 2 },
};

static void yy_accept(yyParser*);  /* Forward Declaration */

/*
** Perform a reduce action and the shift that must immediately
** follow the reduce.
*/
static void yy_reduce(
  yyParser *yypParser,         /* The parser */
  int yyruleno                 /* Number of the rule by which to reduce */
){
  int yygoto;                     /* The next state */
  int yyact;                      /* The next action */
  YYMINORTYPE yygotominor;        /* The LHS of the rule reduced */
  yyStackEntry *yymsp;            /* The top of the parser's stack */
  int yysize;                     /* Amount to pop the stack */
  ParserARG_FETCH;
  yymsp = &yypParser->yystack[yypParser->yyidx];
#ifndef NDEBUG
  if( yyTraceFILE && yyruleno>=0 
        && yyruleno<sizeof(yyRuleName)/sizeof(yyRuleName[0]) ){
    fprintf(yyTraceFILE, "%sReduce [%s].\n", yyTracePrompt,
      yyRuleName[yyruleno]);
  }
#endif /* NDEBUG */

#ifndef NDEBUG
  /* Silence complaints from purify about yygotominor being uninitialized
  ** in some cases when it is copied into the stack after the following
  ** switch.  yygotominor is uninitialized when a rule reduces that does
  ** not set the value of its left-hand side nonterminal.  Leaving the
  ** value of the nonterminal uninitialized is utterly harmless as long
  ** as the value is never used.  So really the only thing this code
  ** accomplishes is to quieten purify.  
  */
  memset(&yygotominor, 0, sizeof(yygotominor));
#endif

  switch( yyruleno ){
  /* Beginning here are the reduction cases.  A typical example
  ** follows:
  **   case 0:
  **  #line <lineno> <grammarfile>
  **     { ... }           // User supplied code
  **  #line <lineno> <thisfile>
  **     break;
  */
      case 3:
      case 7:
      case 63:
      case 92:
#line 98 "parse.y"
{ }
#line 1766 "parse.c"
        break;
      case 4:
#line 99 "parse.y"
{ pParse->sflag |= SQL_FLAG_CODING;}
#line 1771 "parse.c"
        break;
      case 8:
      case 9:
#line 104 "parse.y"
{ pParse->sflag |= SQL_FLAG_PARSE; }
#line 1777 "parse.c"
        break;
      case 10:
      case 11:
#line 112 "parse.y"
{ pParse->sflag |= SQL_FLAG_TR;}
#line 1783 "parse.c"
        break;
      case 14:
      case 15:
#line 124 "parse.y"
{ pParse->sflag |= SQL_FLAG_TR; }
#line 1789 "parse.c"
        break;
      case 17:
#line 131 "parse.y"
{
   pParse->sflag |= SQL_FLAG_TABLE;
}
#line 1796 "parse.c"
        break;
      case 18:
      case 21:
      case 67:
      case 81:
      case 83:
      case 94:
      case 103:
      case 112:
      case 113:
      case 218:
      case 222:
#line 136 "parse.y"
{yygotominor.yy4 = 0;}
#line 1811 "parse.c"
        break;
      case 19:
      case 20:
      case 68:
      case 82:
      case 102:
      case 111:
      case 219:
      case 223:
#line 137 "parse.y"
{yygotominor.yy4 = 1;}
#line 1823 "parse.c"
        break;
      case 22:
#line 143 "parse.y"
{
  //sqlite3EndTable(pParse,&X,&Y,0);
}
#line 1830 "parse.c"
        break;
      case 23:
#line 146 "parse.y"
{
	pParse->sflag |= SQL_FLAG_TABLE;
}
#line 1837 "parse.c"
        break;
      case 33:
#line 167 "parse.y"
{
  //A.z = X.z;
  //A.n = (pParse->sLastToken.z-X.z) + pParse->sLastToken.n;
}
#line 1845 "parse.c"
        break;
      case 34:
#line 171 "parse.y"
{
  //sqlite3AddColumn(pParse,&X);
  //A = X;
}
#line 1853 "parse.c"
        break;
      case 35:
      case 36:
      case 37:
      case 38:
      case 39:
      case 247:
#line 181 "parse.y"
{yygotominor.yy378 = yymsp[0].minor.yy0;}
#line 1863 "parse.c"
        break;
      case 41:
#line 240 "parse.y"
{ /*sqlite3AddColumnType(pParse,&X);*/ }
#line 1868 "parse.c"
        break;
      case 42:
      case 45:
      case 119:
      case 120:
      case 131:
      case 150:
      case 244:
      case 245:
      case 246:
#line 241 "parse.y"
{yygotominor.yy378 = yymsp[0].minor.yy378;}
#line 1881 "parse.c"
        break;
      case 43:
#line 242 "parse.y"
{
  yygotominor.yy378.z = yymsp[-3].minor.yy378.z;
  yygotominor.yy378.n = &yymsp[0].minor.yy0.z[yymsp[0].minor.yy0.n] - yymsp[-3].minor.yy378.z;
}
#line 1889 "parse.c"
        break;
      case 44:
#line 246 "parse.y"
{
  yygotominor.yy378.z = yymsp[-5].minor.yy378.z;
  yygotominor.yy378.n = &yymsp[0].minor.yy0.z[yymsp[0].minor.yy0.n] - yymsp[-5].minor.yy378.z;
}
#line 1897 "parse.c"
        break;
      case 46:
#line 252 "parse.y"
{yygotominor.yy378.z=yymsp[-1].minor.yy378.z; yygotominor.yy378.n=yymsp[0].minor.yy378.n+(yymsp[0].minor.yy378.z-yymsp[-1].minor.yy378.z);}
#line 1902 "parse.c"
        break;
      case 47:
#line 254 "parse.y"
{ yygotominor.yy4 = atoi((char*)yymsp[0].minor.yy378.z); }
#line 1907 "parse.c"
        break;
      case 48:
#line 255 "parse.y"
{ yygotominor.yy4 = -atoi((char*)yymsp[0].minor.yy378.z); }
#line 1912 "parse.c"
        break;
      case 53:
#line 264 "parse.y"
{ /*sqlite3AddDefaultValue(pParse,X);*/   yy_destructor(180,&yymsp[0].minor);
}
#line 1918 "parse.c"
        break;
      case 54:
#line 265 "parse.y"
{ /*sqlite3AddDefaultValue(pParse,X);*/ }
#line 1923 "parse.c"
        break;
      case 55:
#line 266 "parse.y"
{ /*sqlite3AddDefaultValue(pParse,X);*/  yy_destructor(180,&yymsp[0].minor);
}
#line 1929 "parse.c"
        break;
      case 56:
#line 267 "parse.y"
{
  //Expr *p = sqlite3Expr(TK_UMINUS, X, 0, 0);
  //sqlite3AddDefaultValue(pParse,p);
  yy_destructor(180,&yymsp[0].minor);
}
#line 1938 "parse.c"
        break;
      case 57:
#line 271 "parse.y"
{
  //Expr *p = sqlite3Expr(TK_STRING, 0, 0, &X);
  //sqlite3AddDefaultValue(pParse,p);
}
#line 1946 "parse.c"
        break;
      case 60:
#line 281 "parse.y"
{/*sqlite3AddNotNull(pParse, R);*/}
#line 1951 "parse.c"
        break;
      case 61:
#line 283 "parse.y"
{/*sqlite3AddPrimaryKey(pParse,0,R,I,Z);*/}
#line 1956 "parse.c"
        break;
      case 62:
#line 284 "parse.y"
{/*sqlite3CreateIndex(pParse,0,0,0,0,R,0,0,0,0);*/}
#line 1961 "parse.c"
        break;
      case 64:
#line 287 "parse.y"
{   yy_destructor(184,&yymsp[-1].minor);
}
#line 1967 "parse.c"
        break;
      case 65:
#line 288 "parse.y"
{/*sqlite3DeferForeignKey(pParse,D);*/}
#line 1972 "parse.c"
        break;
      case 66:
#line 289 "parse.y"
{/*sqlite3AddCollateType(pParse, (char*)C.z, C.n);*/}
#line 1977 "parse.c"
        break;
      case 69:
#line 302 "parse.y"
{ yygotominor.yy4 = OE_Restrict * 0x010101; }
#line 1982 "parse.c"
        break;
      case 70:
#line 303 "parse.y"
{ yygotominor.yy4 = (yymsp[-1].minor.yy4 & yymsp[0].minor.yy215.mask) | yymsp[0].minor.yy215.value; }
#line 1987 "parse.c"
        break;
      case 71:
#line 305 "parse.y"
{ yygotominor.yy215.value = 0;     yygotominor.yy215.mask = 0x000000; }
#line 1992 "parse.c"
        break;
      case 72:
#line 306 "parse.y"
{ yygotominor.yy215.value = yymsp[0].minor.yy4;     yygotominor.yy215.mask = 0x0000ff; }
#line 1997 "parse.c"
        break;
      case 73:
#line 307 "parse.y"
{ yygotominor.yy215.value = yymsp[0].minor.yy4<<8;  yygotominor.yy215.mask = 0x00ff00; }
#line 2002 "parse.c"
        break;
      case 74:
#line 308 "parse.y"
{ yygotominor.yy215.value = yymsp[0].minor.yy4<<16; yygotominor.yy215.mask = 0xff0000; }
#line 2007 "parse.c"
        break;
      case 75:
#line 310 "parse.y"
{ yygotominor.yy4 = OE_SetNull; }
#line 2012 "parse.c"
        break;
      case 76:
#line 311 "parse.y"
{ yygotominor.yy4 = OE_SetDflt; }
#line 2017 "parse.c"
        break;
      case 77:
#line 312 "parse.y"
{ yygotominor.yy4 = OE_Cascade; }
#line 2022 "parse.c"
        break;
      case 78:
#line 313 "parse.y"
{ yygotominor.yy4 = OE_Restrict; }
#line 2027 "parse.c"
        break;
      case 79:
      case 80:
      case 95:
      case 97:
      case 98:
#line 315 "parse.y"
{yygotominor.yy4 = yymsp[0].minor.yy4;}
#line 2036 "parse.c"
        break;
      case 90:
#line 334 "parse.y"
{   yy_destructor(193,&yymsp[-3].minor);
}
#line 2042 "parse.c"
        break;
      case 91:
#line 336 "parse.y"
{   yy_destructor(193,&yymsp[-2].minor);
}
#line 2048 "parse.c"
        break;
      case 93:
#line 339 "parse.y"
{ 
   yy_destructor(193,&yymsp[-6].minor);
  yy_destructor(184,&yymsp[-2].minor);
}
#line 2056 "parse.c"
        break;
      case 96:
#line 352 "parse.y"
{yygotominor.yy4 = OE_Default;}
#line 2061 "parse.c"
        break;
      case 99:
#line 357 "parse.y"
{yygotominor.yy4 = OE_Ignore;}
#line 2066 "parse.c"
        break;
      case 100:
      case 170:
#line 358 "parse.y"
{yygotominor.yy4 = OE_Replace;}
#line 2072 "parse.c"
        break;
      case 101:
#line 362 "parse.y"
{
  pParse->sflag |= SQL_FLAG_TABLE;
  yy_destructor(199,&yymsp[0].minor);
}
#line 2080 "parse.c"
        break;
      case 104:
#line 382 "parse.y"
{
}
#line 2086 "parse.c"
        break;
      case 105:
      case 128:
#line 390 "parse.y"
{yygotominor.yy387 = yymsp[0].minor.yy387;}
#line 2092 "parse.c"
        break;
      case 106:
#line 392 "parse.y"
{
  if( yymsp[0].minor.yy387 ){
    yymsp[0].minor.yy387->op = yymsp[-1].minor.yy4;
    yymsp[0].minor.yy387->pPrior = yymsp[-2].minor.yy387;
  }
  yygotominor.yy387 = yymsp[0].minor.yy387;
}
#line 2103 "parse.c"
        break;
      case 107:
      case 109:
#line 400 "parse.y"
{yygotominor.yy4 = yymsp[0].major;}
#line 2109 "parse.c"
        break;
      case 108:
#line 401 "parse.y"
{yygotominor.yy4 = TK_ALL;}
#line 2114 "parse.c"
        break;
      case 110:
#line 405 "parse.y"
{
  pParse->select_num++;
  yy_destructor(205,&yymsp[-4].minor);
  yy_destructor(209,&yymsp[0].minor);
}
#line 2123 "parse.c"
        break;
      case 114:
      case 241:
#line 426 "parse.y"
{yygotominor.yy322 = yymsp[-1].minor.yy322;}
#line 2129 "parse.c"
        break;
      case 115:
      case 141:
      case 151:
      case 240:
#line 427 "parse.y"
{yygotominor.yy322 = 0;}
#line 2137 "parse.c"
        break;
      case 116:
      case 117:
      case 118:
      case 229:
      case 230:
      case 231:
#line 428 "parse.y"
{
  pParse->sflag |= SQL_FLAG_EXPR;
}
#line 2149 "parse.c"
        break;
      case 121:
#line 444 "parse.y"
{yygotominor.yy378.n = 0;}
#line 2154 "parse.c"
        break;
      case 122:
#line 456 "parse.y"
{yygotominor.yy259 = sqliteMalloc(sizeof(*yygotominor.yy259));}
#line 2159 "parse.c"
        break;
      case 123:
#line 457 "parse.y"
{yygotominor.yy259 = yymsp[0].minor.yy259;}
#line 2164 "parse.c"
        break;
      case 124:
#line 462 "parse.y"
{
   yygotominor.yy259 = yymsp[-1].minor.yy259;
   if( yygotominor.yy259 && yygotominor.yy259->nSrc>0 ) yygotominor.yy259->a[yygotominor.yy259->nSrc-1].jointype = yymsp[0].minor.yy4;
}
#line 2172 "parse.c"
        break;
      case 125:
#line 466 "parse.y"
{yygotominor.yy259 = 0;}
#line 2177 "parse.c"
        break;
      case 126:
#line 467 "parse.y"
{
  pParse->sflag |= SQL_FLAG_EXPR;
  yy_destructor(216,&yymsp[0].minor);
}
#line 2185 "parse.c"
        break;
      case 127:
#line 472 "parse.y"
{
  pParse->sflag |= SQL_FLAG_EXPR;
  yy_destructor(217,&yymsp[-4].minor);
  yy_destructor(216,&yymsp[0].minor);
}
#line 2194 "parse.c"
        break;
      case 129:
#line 483 "parse.y"
{
     pParse->select_num++;
  }
#line 2201 "parse.c"
        break;
      case 130:
#line 489 "parse.y"
{yygotominor.yy378.z=0; yygotominor.yy378.n=0;}
#line 2206 "parse.c"
        break;
      case 132:
#line 494 "parse.y"
{  pParse->sflag |= SQL_FLAG_LIST; }
#line 2211 "parse.c"
        break;
      case 133:
#line 498 "parse.y"
{ yygotominor.yy4 = JT_INNER; }
#line 2216 "parse.c"
        break;
      case 134:
      case 135:
      case 136:
#line 499 "parse.y"
{ pParse->sflag |= SQL_FLAG_JOIN; }
#line 2223 "parse.c"
        break;
      case 137:
      case 145:
      case 154:
      case 161:
      case 181:
      case 208:
      case 232:
      case 234:
      case 238:
#line 506 "parse.y"
{yygotominor.yy314 = yymsp[0].minor.yy314;}
#line 2236 "parse.c"
        break;
      case 138:
      case 153:
      case 160:
      case 209:
      case 233:
      case 235:
      case 239:
#line 507 "parse.y"
{yygotominor.yy314 = 0;}
#line 2247 "parse.c"
        break;
      case 139:
      case 178:
#line 511 "parse.y"
{yygotominor.yy384 = yymsp[-1].minor.yy384;}
#line 2253 "parse.c"
        break;
      case 140:
      case 176:
      case 177:
#line 512 "parse.y"
{yygotominor.yy384 = 0;}
#line 2260 "parse.c"
        break;
      case 142:
      case 152:
#line 523 "parse.y"
{yygotominor.yy322 = yymsp[0].minor.yy322;}
#line 2266 "parse.c"
        break;
      case 143:
      case 144:
      case 186:
      case 187:
      case 191:
      case 192:
      case 193:
      case 194:
      case 195:
      case 210:
      case 211:
      case 212:
      case 213:
      case 214:
      case 215:
      case 216:
      case 217:
      case 221:
      case 243:
#line 524 "parse.y"
{
	pParse->sflag |= SQL_FLAG_EXPR;
}
#line 2291 "parse.c"
        break;
      case 146:
      case 148:
#line 535 "parse.y"
{yygotominor.yy4 = SQLITE_SO_ASC;}
#line 2297 "parse.c"
        break;
      case 147:
#line 536 "parse.y"
{yygotominor.yy4 = SQLITE_SO_DESC;}
#line 2302 "parse.c"
        break;
      case 149:
#line 538 "parse.y"
{yygotominor.yy378.z = 0; yygotominor.yy378.n = 0;}
#line 2307 "parse.c"
        break;
      case 155:
#line 554 "parse.y"
{yygotominor.yy292.pLimit = 0; yygotominor.yy292.pOffset = 0;}
#line 2312 "parse.c"
        break;
      case 156:
#line 555 "parse.y"
{yygotominor.yy292.pLimit = yymsp[0].minor.yy314; yygotominor.yy292.pOffset = 0;}
#line 2317 "parse.c"
        break;
      case 157:
#line 557 "parse.y"
{yygotominor.yy292.pLimit = yymsp[-2].minor.yy314; yygotominor.yy292.pOffset = yymsp[0].minor.yy314;}
#line 2322 "parse.c"
        break;
      case 158:
#line 559 "parse.y"
{yygotominor.yy292.pOffset = yymsp[-2].minor.yy314; yygotominor.yy292.pLimit = yymsp[0].minor.yy314;}
#line 2327 "parse.c"
        break;
      case 159:
#line 563 "parse.y"
{pParse->sflag |= SQL_FLAG_DELETE;  yy_destructor(199,&yymsp[-2].minor);
  yy_destructor(205,&yymsp[-1].minor);
  yy_destructor(209,&yymsp[0].minor);
}
#line 2335 "parse.c"
        break;
      case 162:
#line 575 "parse.y"
{pParse->sflag |= SQL_FLAG_UPDATE;  yy_destructor(199,&yymsp[-4].minor);
  yy_destructor(205,&yymsp[-1].minor);
  yy_destructor(209,&yymsp[0].minor);
}
#line 2343 "parse.c"
        break;
      case 163:
      case 164:
      case 174:
      case 175:
      case 182:
      case 183:
      case 184:
      case 185:
      case 188:
      case 189:
      case 190:
      case 200:
      case 220:
      case 236:
      case 237:
#line 581 "parse.y"
{pParse->sflag |= SQL_FLAG_EXPR;}
#line 2362 "parse.c"
        break;
      case 165:
#line 591 "parse.y"
{pParse->sflag |= SQL_FLAG_INSERT;  yy_destructor(199,&yymsp[-3].minor);
  yy_destructor(227,&yymsp[0].minor);
}
#line 2369 "parse.c"
        break;
      case 166:
      case 167:
#line 595 "parse.y"
{pParse->sflag |= SQL_FLAG_INSERT;  yy_destructor(199,&yymsp[-3].minor);
}
#line 2376 "parse.c"
        break;
      case 168:
#line 602 "parse.y"
{pParse->sflag |= SQL_FLAG_INSERT;  yy_destructor(199,&yymsp[-2].minor);
}
#line 2382 "parse.c"
        break;
      case 169:
#line 606 "parse.y"
{ yygotominor.yy4 = OE_Default; }
#line 2387 "parse.c"
        break;
      case 171:
#line 612 "parse.y"
{ pParse->sflag |= SQL_FLAG_EXPR;   yy_destructor(227,&yymsp[-4].minor);
}
#line 2393 "parse.c"
        break;
      case 172:
#line 613 "parse.y"
{ pParse->sflag |= SQL_FLAG_EXPR; }
#line 2398 "parse.c"
        break;
      case 173:
#line 614 "parse.y"
{ yygotominor.yy287 = 0; }
#line 2403 "parse.c"
        break;
      case 179:
#line 630 "parse.y"
{ pParse->sflag |= SQL_FLAG_LIST;  yy_destructor(219,&yymsp[-2].minor);
}
#line 2409 "parse.c"
        break;
      case 180:
#line 631 "parse.y"
{ pParse->sflag |= SQL_FLAG_LIST;}
#line 2414 "parse.c"
        break;
      case 196:
#line 672 "parse.y"
{
  /* The CURRENT_TIME, CURRENT_DATE, and CURRENT_TIMESTAMP values are
  ** treated as functions that return constants */
	pParse->sflag |= SQL_FLAG_EXPR;
}
#line 2423 "parse.c"
        break;
      case 197:
      case 198:
      case 199:
      case 201:
      case 202:
      case 203:
      case 204:
      case 205:
#line 677 "parse.y"
{pParse->sflag |= SQL_FLAG_OPT;}
#line 2435 "parse.c"
        break;
      case 206:
#line 688 "parse.y"
{yygotominor.yy342.eOperator = yymsp[0].minor.yy0; yygotominor.yy342.not = 0;}
#line 2440 "parse.c"
        break;
      case 207:
#line 689 "parse.y"
{yygotominor.yy342.eOperator = yymsp[0].minor.yy0; yygotominor.yy342.not = 1;}
#line 2445 "parse.c"
        break;
      case 224:
      case 225:
      case 226:
      case 227:
      case 228:
#line 736 "parse.y"
{
	  pParse->sflag |= SQL_FLAG_EXPR;
  }
#line 2456 "parse.c"
        break;
      case 242:
#line 805 "parse.y"
{
	pParse->sflag |= SQL_FLAG_EXPR;
  yy_destructor(193,&yymsp[-4].minor);
}
#line 2464 "parse.c"
        break;
      case 250:
#line 933 "parse.y"
{yygotominor.yy4 = OE_Rollback;}
#line 2469 "parse.c"
        break;
      case 251:
#line 934 "parse.y"
{yygotominor.yy4 = OE_Abort;}
#line 2474 "parse.c"
        break;
      case 252:
#line 935 "parse.y"
{yygotominor.yy4 = OE_Fail;}
#line 2479 "parse.c"
        break;
      case 253:
      case 254:
      case 255:
#line 991 "parse.y"
{
	  pParse->sflag |= SQL_FLAG_STMT;
}
#line 2488 "parse.c"
        break;
      case 256:
      case 257:
#line 1005 "parse.y"
{
	  pParse->sflag |= SQL_FLAG_EXPR;
}
#line 2496 "parse.c"
        break;
      case 261:
#line 1017 "parse.y"
{ pParse->sflag |= SQL_FLAG_SCOPE; }
#line 2501 "parse.c"
        break;
      case 263:
#line 1021 "parse.y"
{ yygotominor.yy378 = yymsp[0].minor.yy378; }
#line 2506 "parse.c"
        break;
      case 264:
#line 1022 "parse.y"
{ yygotominor.yy378 = yymsp[0].minor.yy0; }
#line 2511 "parse.c"
        break;
      case 270:
      case 271:
      case 272:
      case 273:
      case 274:
#line 1031 "parse.y"
{
		pParse->sflag |= SQL_FLAG_SHOW;
}
#line 2522 "parse.c"
        break;
      case 278:
#line 1055 "parse.y"
{
  yy_destructor(205,&yymsp[0].minor);
}
#line 2529 "parse.c"
        break;
  };
  yygoto = yyRuleInfo[yyruleno].lhs;
  yysize = yyRuleInfo[yyruleno].nrhs;
  yypParser->yyidx -= yysize;
  yyact = yy_find_reduce_action(yymsp[-yysize].stateno,yygoto);
  if( yyact < YYNSTATE ){
#ifdef NDEBUG
    /* If we are not debugging and the reduce action popped at least
    ** one element off the stack, then we can push the new element back
    ** onto the stack here, and skip the stack overflow test in yy_shift().
    ** That gives a significant speed improvement. */
    if( yysize ){
      yypParser->yyidx++;
      yymsp -= yysize-1;
      yymsp->stateno = yyact;
      yymsp->major = yygoto;
      yymsp->minor = yygotominor;
    }else
#endif
    {
      yy_shift(yypParser,yyact,yygoto,&yygotominor);
    }
  }else if( yyact == YYNSTATE + YYNRULE + 1 ){
    yy_accept(yypParser);
  }
}

/*
** The following code executes when the parse fails
*/
static void yy_parse_failed(
  yyParser *yypParser           /* The parser */
){
  ParserARG_FETCH;
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sFail!\n",yyTracePrompt);
  }
#endif
  while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
  /* Here code is inserted which will be executed whenever the
  ** parser fails */
  ParserARG_STORE; /* Suppress warning about unused %extra_argument variable */
}

/*
** The following code executes when a syntax error first occurs.
*/
static void yy_syntax_error(
  yyParser *yypParser,           /* The parser */
  int yymajor,                   /* The major type of the error token */
  YYMINORTYPE yyminor            /* The minor type of the error token */
){
  ParserARG_FETCH;
#define TOKEN (yyminor.yy0)
#line 34 "parse.y"

  if( pParse->zErrMsg==0 ){
    if( TOKEN.z[0] ){
      sqlite3ErrorMsg(pParse, "near \"%T\": syntax error", &TOKEN);
    }else{
      sqlite3ErrorMsg(pParse, "incomplete SQL statement");
    }
  }
#line 2596 "parse.c"
  ParserARG_STORE; /* Suppress warning about unused %extra_argument variable */
}

/*
** The following is executed when the parser accepts
*/
static void yy_accept(
  yyParser *yypParser           /* The parser */
){
  ParserARG_FETCH;
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sAccept!\n",yyTracePrompt);
  }
#endif
  while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
  /* Here code is inserted which will be executed whenever the
  ** parser accepts */
  ParserARG_STORE; /* Suppress warning about unused %extra_argument variable */
}

/* The main parser program.
** The first argument is a pointer to a structure obtained from
** "ParserAlloc" which describes the current state of the parser.
** The second argument is the major token number.  The third is
** the minor token.  The fourth optional argument is whatever the
** user wants (and specified in the grammar) and is available for
** use by the action routines.
**
** Inputs:
** <ul>
** <li> A pointer to the parser (an opaque structure.)
** <li> The major token number.
** <li> The minor token number.
** <li> An option argument of a grammar-specified type.
** </ul>
**
** Outputs:
** None.
*/
void Parser(
  void *yyp,                   /* The parser */
  int yymajor,                 /* The major token code number */
  ParserTOKENTYPE yyminor       /* The value for the token */
  ParserARG_PDECL               /* Optional %extra_argument parameter */
){
  YYMINORTYPE yyminorunion;
  int yyact;            /* The parser action. */
  int yyendofinput;     /* True if we are at the end of input */
  int yyerrorhit = 0;   /* True if yymajor has invoked an error */
  yyParser *yypParser;  /* The parser */

  /* (re)initialize the parser, if necessary */
  yypParser = (yyParser*)yyp;
  if( yypParser->yyidx<0 ){
    /* if( yymajor==0 ) return; // not sure why this was here... */
    yypParser->yyidx = 0;
    yypParser->yyerrcnt = -1;
    yypParser->yystack[0].stateno = 0;
    yypParser->yystack[0].major = 0;
  }
  yyminorunion.yy0 = yyminor;
  yyendofinput = (yymajor==0);
  ParserARG_STORE;

#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sInput %s\n",yyTracePrompt,yyTokenName[yymajor]);
  }
#endif

  do{
    yyact = yy_find_shift_action(yypParser,yymajor);
    if( yyact<YYNSTATE ){
      yy_shift(yypParser,yyact,yymajor,&yyminorunion);
      yypParser->yyerrcnt--;
      if( yyendofinput && yypParser->yyidx>=0 ){
        yymajor = 0;
      }else{
        yymajor = YYNOCODE;
      }
    }else if( yyact < YYNSTATE + YYNRULE ){
      yy_reduce(yypParser,yyact-YYNSTATE);
    }else if( yyact == YY_ERROR_ACTION ){
      int yymx;
#ifndef NDEBUG
      if( yyTraceFILE ){
        fprintf(yyTraceFILE,"%sSyntax Error!\n",yyTracePrompt);
      }
#endif
#ifdef YYERRORSYMBOL
      /* A syntax error has occurred.
      ** The response to an error depends upon whether or not the
      ** grammar defines an error token "ERROR".  
      **
      ** This is what we do if the grammar does define ERROR:
      **
      **  * Call the %syntax_error function.
      **
      **  * Begin popping the stack until we enter a state where
      **    it is legal to shift the error symbol, then shift
      **    the error symbol.
      **
      **  * Set the error count to three.
      **
      **  * Begin accepting and shifting new tokens.  No new error
      **    processing will occur until three tokens have been
      **    shifted successfully.
      **
      */
      if( yypParser->yyerrcnt<0 ){
        yy_syntax_error(yypParser,yymajor,yyminorunion);
      }
      yymx = yypParser->yystack[yypParser->yyidx].major;
      if( yymx==YYERRORSYMBOL || yyerrorhit ){
#ifndef NDEBUG
        if( yyTraceFILE ){
          fprintf(yyTraceFILE,"%sDiscard input token %s\n",
             yyTracePrompt,yyTokenName[yymajor]);
        }
#endif
        yy_destructor(yymajor,&yyminorunion);
        yymajor = YYNOCODE;
      }else{
         while(
          yypParser->yyidx >= 0 &&
          yymx != YYERRORSYMBOL &&
          (yyact = yy_find_shift_action(yypParser,YYERRORSYMBOL)) >= YYNSTATE
        ){
          yy_pop_parser_stack(yypParser);
        }
        if( yypParser->yyidx < 0 || yymajor==0 ){
          yy_destructor(yymajor,&yyminorunion);
          yy_parse_failed(yypParser);
          yymajor = YYNOCODE;
        }else if( yymx!=YYERRORSYMBOL ){
          YYMINORTYPE u2;
          u2.YYERRSYMDT = 0;
          yy_shift(yypParser,yyact,YYERRORSYMBOL,&u2);
        }
      }
      yypParser->yyerrcnt = 3;
      yyerrorhit = 1;
#else  /* YYERRORSYMBOL is not defined */
      /* This is what we do if the grammar does not define ERROR:
      **
      **  * Report an error message, and throw away the input token.
      **
      **  * If the input token is $, then fail the parse.
      **
      ** As before, subsequent error messages are suppressed until
      ** three input tokens have been successfully shifted.
      */
      if( yypParser->yyerrcnt<=0 ){
        yy_syntax_error(yypParser,yymajor,yyminorunion);
      }
      yypParser->yyerrcnt = 3;
      yy_destructor(yymajor,&yyminorunion);
      if( yyendofinput ){
        yy_parse_failed(yypParser);
      }
      yymajor = YYNOCODE;
#endif
    }else{
      yy_accept(yypParser);
      yymajor = YYNOCODE;
    }
  }while( yymajor!=YYNOCODE && yypParser->yyidx>=0 );
  return;
}
