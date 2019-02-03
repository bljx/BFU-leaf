#include <yacc.h>

#line 1 "E:\\compiler\\teaching\\03\\\312\265\321\351\\\312\265\321\3512\\\320\302\275\250\316\304\274\376\274\320\\p2.y"

typedef char* string;
#define YYSTYPE string

#line 9 "E:\\compiler\\teaching\\03\\\312\265\321\351\\\312\265\321\3512\\\320\302\275\250\316\304\274\376\274\320\\p2.c"
/* repeated because of possible precompiled header */
#include <yacc.h>

#include "p2.h"

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
#line 10 "E:\\compiler\\teaching\\03\\\312\265\321\351\\\312\265\321\3512\\\320\302\275\250\316\304\274\376\274\320\\p2.y"
 printf("%s is %s yuan!\n", yyattribute(1 - 3), yyattribute(3 - 3)); 
#line 121 "E:\\compiler\\teaching\\03\\\312\265\321\351\\\312\265\321\3512\\\320\302\275\250\316\304\274\376\274\320\\p2.c"
			}
		}
		break;
	default:
		yyassert(0);
		break;
	}
}
#line 12 "E:\\compiler\\teaching\\03\\\312\265\321\351\\\312\265\321\3512\\\320\302\275\250\316\304\274\376\274\320\\p2.y"

int main() 
{      
  yyparse(); 
  return 0;    
}        
void yyerror(char *msg)
{ 
  printf("Error encountered: %s \n", msg);
}

#line 142 "E:\\compiler\\teaching\\03\\\312\265\321\351\\\312\265\321\3512\\\320\302\275\250\316\304\274\376\274\320\\p2.c"
#ifdef YYDEBUG
YYCONST yysymbol_t YYNEARFAR YYBASED_CODE YYDCDECL yysymbol[] = {
	{ "$end", 0 },
	{ "error", 256 },
	{ "NAME", 257 },
	{ "EQ", 258 },
	{ "PRICE", 259 },
	{ NULL, 0 }
};

YYCONST char *YYCONST YYNEARFAR YYBASED_CODE YYDCDECL yyrule[] = {
	"$accept: file",
	"file: record file",
	"file: record",
	"record: NAME EQ PRICE"
};
#endif

YYCONST yyreduction_t YYNEARFAR YYBASED_CODE YYDCDECL yyreduction[] = {
	{ 0, 1, -1 },
	{ 1, 2, -1 },
	{ 1, 1, -1 },
	{ 2, 3, 0 }
};

YYCONST yytokenaction_t YYNEARFAR YYBASED_CODE YYDCDECL yytokenaction[] = {
	{ 4, YYAT_SHIFT, 6 },
	{ 3, YYAT_SHIFT, 1 },
	{ 2, YYAT_ACCEPT, 0 },
	{ 1, YYAT_SHIFT, 4 },
	{ 0, YYAT_SHIFT, 1 }
};
int YYNEAR YYDCDECL yytokenaction_size = 5;

YYCONST yystateaction_t YYNEARFAR YYBASED_CODE YYDCDECL yystateaction[] = {
	{ -253, 1, YYAT_ERROR, 0 },
	{ -255, 1, YYAT_ERROR, 0 },
	{ 2, 1, YYAT_ERROR, 0 },
	{ -256, 1, YYAT_REDUCE, 2 },
	{ -259, 1, YYAT_ERROR, 0 },
	{ 0, 0, YYAT_REDUCE, 1 },
	{ 0, 0, YYAT_REDUCE, 3 }
};

YYCONST yystategoto_t YYNEARFAR YYBASED_CODE YYDCDECL yystategoto[] = {
	{ 1, 5 }
};
int YYNEAR YYDCDECL yystategoto_size = 1;

YYCONST yynontermgoto_t YYNEARFAR YYBASED_CODE YYDCDECL yynontermgoto[] = {
	{ 0, -1 },
	{ -3, 2 },
	{ 0, 3 }
};

YYCONST yydestructor_t YYNEARFAR *YYNEAR YYDCDECL yydestructorptr = NULL;

