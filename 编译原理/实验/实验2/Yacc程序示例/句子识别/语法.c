#include <yacc.h>

#line 1 "E:\\compiler\\teaching\\07\\\312\265\321\351\\\312\265\321\3512\\Yacc\263\314\320\362\312\276\300\375\\\276\344\327\323\312\266\261\360\\\323\357\267\250.y"

/*
 * A lexer for the basic grammar to use for recognizing english sentences.
 */
#include <stdio.h>

#line 11 "E:\\compiler\\teaching\\07\\\312\265\321\351\\\312\265\321\3512\\Yacc\263\314\320\362\312\276\300\375\\\276\344\327\323\312\266\261\360\\\323\357\267\250.c"
/* repeated because of possible precompiled header */
#include <yacc.h>

#include "Óï·¨.h"

#ifndef YYSTYPE
#define YYSTYPE int
#endif
#ifndef YYSTACK_SIZE
#define YYSTACK_SIZE 100
#endif

/* (state) stack */
#if (YYSTACK_SIZE) != 0
static yystack_t YYNEAR yystack[(YYSTACK_SIZE)];
yystack_t YYFAR *YYNEAR YYDCDECL yysstackptr = yystack;
yystack_t YYFAR *YYNEAR YYDCDECL yystackptr = yystack;
#else
yystack_t YYFAR *YYNEAR YYDCDECL yysstackptr = NULL;
yystack_t YYFAR *YYNEAR YYDCDECL yystackptr = NULL;
#endif

/* attribute stack */
#if (YYSTACK_SIZE) != 0
static YYSTYPE YYNEAR yyattributestack[(YYSTACK_SIZE)];
#ifdef YYPROTOTYPE
void YYFAR *YYNEAR YYDCDECL yysattributestackptr = yyattributestack;
void YYFAR *YYNEAR YYDCDECL yyattributestackptr = yyattributestack;
#else
char YYFAR *YYNEAR YYDCDECL yysattributestackptr = (char YYFAR *) yyattributestack;
char YYFAR *YYNEAR YYDCDECL yyattributestackptr = (char YYFAR *) yyattributestack;
#endif
#else
#ifdef YYPROTOTYPE
void YYFAR *YYNEAR YYDCDECL yysattributestackptr = NULL;
void YYFAR *YYNEAR YYDCDECL yyattributestackptr = NULL;
#else
char YYFAR *YYNEAR YYDCDECL yysattributestackptr = NULL;
char YYFAR *YYNEAR YYDCDECL yyattributestackptr = NULL;
#endif
#endif

int YYNEAR YYDCDECL yysstack_size = (YYSTACK_SIZE);
int YYNEAR YYDCDECL yystack_size = (YYSTACK_SIZE);

/* attributes */
YYSTYPE YYNEAR yyval;
YYSTYPE YYNEAR yylval;
#ifdef YYPROTOTYPE
void YYFAR *YYNEAR YYDCDECL yyvalptr = &yyval;
void YYFAR *YYNEAR YYDCDECL yylvalptr = &yylval;
#else
char YYFAR *YYNEAR YYDCDECL yyvalptr = (char *) &yyval;
char YYFAR *YYNEAR YYDCDECL yylvalptr = (char *) &yylval;
#endif

size_t YYNEAR YYDCDECL yyattribute_size = sizeof(YYSTYPE);

/* yyattribute */
#ifdef YYDEBUG
#ifdef YYPROTOTYPE
static YYSTYPE YYFAR *yyattribute1(int index)
#else
static YYSTYPE YYFAR *yyattribute1(index)
int index;
#endif
{
	YYSTYPE YYFAR *p = &((YYSTYPE YYFAR *) yyattributestackptr)[yytop + index];
	return p;
}
#define yyattribute(index) (*yyattribute1(index))
#else
#define yyattribute(index) (((YYSTYPE YYFAR *) yyattributestackptr)[yytop + (index)])
#endif

#ifdef YYDEBUG
#ifdef YYPROTOTYPE
static void yyinitdebug(YYSTYPE YYFAR **p, int count)
#else
static void yyinitdebug(p, count)
YYSTYPE YYFAR **p;
int count;
#endif
{
	int i;
	yyassert(p != NULL);
	yyassert(count >= 1);

	for (i = 0; i < count; i++) {
		p[i] = &((YYSTYPE YYFAR *) yyattributestackptr)[yytop + i - (count - 1)];
	}
}
#endif

#ifdef YYPROTOTYPE
void YYCDECL yyparseaction(int action)
#else
void YYCDECL yyparseaction(action)
int action;
#endif
{
	switch (action) {
	case 0:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[4];
			yyinitdebug(yya, 4);
#endif
			{
#line 11 "E:\\compiler\\teaching\\07\\\312\265\321\351\\\312\265\321\3512\\Yacc\263\314\320\362\312\276\300\375\\\276\344\327\323\312\266\261\360\\\323\357\267\250.y"
 printf("Sentence is valid.\n"); 
#line 123 "E:\\compiler\\teaching\\07\\\312\265\321\351\\\312\265\321\3512\\Yacc\263\314\320\362\312\276\300\375\\\276\344\327\323\312\266\261\360\\\323\357\267\250.c"
			}
		}
		break;
	default:
		yyassert(0);
		break;
	}
}
#line 20 "E:\\compiler\\teaching\\07\\\312\265\321\351\\\312\265\321\3512\\Yacc\263\314\320\362\312\276\300\375\\\276\344\327\323\312\266\261\360\\\323\357\267\250.y"


extern FILE *yyin;

main()
{
	while(!feof(yyin)) {
		yyparse();
	}
}


#line 145 "E:\\compiler\\teaching\\07\\\312\265\321\351\\\312\265\321\3512\\Yacc\263\314\320\362\312\276\300\375\\\276\344\327\323\312\266\261\360\\\323\357\267\250.c"
#ifdef YYDEBUG
YYCONST yysymbol_t YYNEARFAR YYBASED_CODE YYDCDECL yysymbol[] = {
	{ "$end", 0 },
	{ "error", 256 },
	{ "NOUN", 257 },
	{ "PRONOUN", 258 },
	{ "VERB", 259 },
	{ NULL, 0 }
};

YYCONST char *YYCONST YYNEARFAR YYBASED_CODE YYDCDECL yyrule[] = {
	"$accept: sentence",
	"sentence: subject VERB object",
	"subject: NOUN",
	"subject: PRONOUN",
	"object: NOUN"
};
#endif

YYCONST yyreduction_t YYNEARFAR YYBASED_CODE YYDCDECL yyreduction[] = {
	{ 0, 1, -1 },
	{ 1, 3, 0 },
	{ 2, 1, -1 },
	{ 2, 1, -1 },
	{ 3, 1, -1 }
};

YYCONST yytokenaction_t YYNEARFAR YYBASED_CODE YYDCDECL yytokenaction[] = {
	{ 0, YYAT_SHIFT, 1 },
	{ 0, YYAT_SHIFT, 2 },
	{ 5, YYAT_SHIFT, 6 },
	{ 4, YYAT_SHIFT, 5 },
	{ 3, YYAT_ACCEPT, 0 }
};
int YYNEAR YYDCDECL yytokenaction_size = 5;

YYCONST yystateaction_t YYNEARFAR YYBASED_CODE YYDCDECL yystateaction[] = {
	{ -257, 1, YYAT_ERROR, 0 },
	{ 0, 0, YYAT_REDUCE, 2 },
	{ 0, 0, YYAT_REDUCE, 3 },
	{ 4, 1, YYAT_ERROR, 0 },
	{ -256, 1, YYAT_ERROR, 0 },
	{ -255, 1, YYAT_ERROR, 0 },
	{ 0, 0, YYAT_REDUCE, 4 },
	{ 0, 0, YYAT_REDUCE, 1 }
};

YYCONST yystategoto_t YYNEARFAR YYBASED_CODE YYDCDECL yystategoto[] = {
	{ 0, 0 }
};
int YYNEAR YYDCDECL yystategoto_size = 0;

YYCONST yynontermgoto_t YYNEARFAR YYBASED_CODE YYDCDECL yynontermgoto[] = {
	{ 0, -1 },
	{ 0, 3 },
	{ 0, 4 },
	{ 0, 7 }
};

YYCONST yydestructor_t YYNEARFAR *YYNEAR YYDCDECL yydestructorptr = NULL;

