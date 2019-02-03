#include <lex.h>

#line 1 "E:\\compiler\\teaching\\07\\\312\265\321\351\\\312\265\321\3512\\Yacc\263\314\320\362\312\276\300\375\\\276\344\327\323\312\266\261\360\\\264\312\267\250.l"

/*
 * We now build a lexical analyzer to be used by a higher-level parser.
 */

#include "”Ô∑®.h"	/* token codes from the parser */

#define LOOKUP 0 /* default - not a defined word type. */

int state; 


#line 17 "E:\\compiler\\teaching\\07\\\312\265\321\351\\\312\265\321\3512\\Yacc\263\314\320\362\312\276\300\375\\\276\344\327\323\312\266\261\360\\\264\312\267\250.c"
/* repeated because of possible precompiled header */
#include <lex.h>

#include "¥ ∑®.h"

#ifndef YYTEXT_SIZE
#define YYTEXT_SIZE 100
#endif
#ifndef YYUNPUT_SIZE
#define YYUNPUT_SIZE YYTEXT_SIZE
#endif

/* yytext */
static char YYNEAR yysatext[(YYTEXT_SIZE) + 1];		/* extra char for \0 */
char YYFAR *YYNEAR YYDCDECL yystext = yysatext;
char YYFAR *YYNEAR YYDCDECL yytext = yysatext;
int YYNEAR YYDCDECL yystext_size = (YYTEXT_SIZE);
int YYNEAR YYDCDECL yytext_size = (YYTEXT_SIZE);

/* yystatebuf */
#if (YYTEXT_SIZE) != 0
static int YYNEAR yysastatebuf[(YYTEXT_SIZE)];
int YYFAR *YYNEAR YYDCDECL yysstatebuf = yysastatebuf;
int YYFAR *YYNEAR YYDCDECL yystatebuf = yysastatebuf;
#else
int YYFAR *YYNEAR YYDCDECL yysstatebuf = NULL;
int YYFAR *YYNEAR YYDCDECL yystatebuf = NULL;
#endif

/* yyunputbuf */
#if (YYUNPUT_SIZE) != 0
static int YYNEAR yysaunputbuf[(YYUNPUT_SIZE)];
int YYFAR *YYNEAR YYDCDECL yysunputbufptr = yysaunputbuf;
int YYFAR *YYNEAR YYDCDECL yyunputbufptr = yysaunputbuf;
#else
int YYFAR *YYNEAR YYDCDECL yysunputbufptr = NULL;
int YYFAR *YYNEAR YYDCDECL yyunputbufptr = NULL;
#endif
int YYNEAR YYDCDECL yysunput_size = (YYUNPUT_SIZE);
int YYNEAR YYDCDECL yyunput_size = (YYUNPUT_SIZE);

/* backwards compatability with lex */
#ifdef input
#ifdef YYPROTOTYPE
int YYCDECL yyinput(void)
#else
int YYCDECL yyinput()
#endif
{
	return input();
}
#else
#define input yyinput
#endif

#ifdef output
#ifdef YYPROTOTYPE
void YYCDECL yyoutput(int ch)
#else
void YYCDECL yyoutput(ch)
int ch;
#endif
{
	output(ch);
}
#else
#define output yyoutput
#endif

#ifdef unput
#ifdef YYPROTOTYPE
void YYCDECL yyunput(int ch)
#else
void YYCDECL yyunput(ch)
int ch;
#endif
{
	unput(ch);
}
#else
#define unput yyunput
#endif

#ifndef YYNBORLANDWARN
#ifdef __BORLANDC__
#pragma warn -rch		/* <warning: unreachable code> off */
#endif
#endif

#ifdef YYPROTOTYPE
int YYCDECL yylexaction(int action)
#else
int YYCDECL yylexaction(action)
int action;
#endif
{
	yyreturnflg = 1;
	switch (action) {
	case 1:
		{
#line 16 "E:\\compiler\\teaching\\07\\\312\265\321\351\\\312\265\321\3512\\Yacc\263\314\320\362\312\276\300\375\\\276\344\327\323\312\266\261\360\\\264\312\267\250.l"
 state = LOOKUP; 
#line 120 "E:\\compiler\\teaching\\07\\\312\265\321\351\\\312\265\321\3512\\Yacc\263\314\320\362\312\276\300\375\\\276\344\327\323\312\266\261\360\\\264\312\267\250.c"
		}
		break;
	case 2:
		{
#line 18 "E:\\compiler\\teaching\\07\\\312\265\321\351\\\312\265\321\3512\\Yacc\263\314\320\362\312\276\300\375\\\276\344\327\323\312\266\261\360\\\264\312\267\250.l"
	state = LOOKUP;
		return 0; /* end of sentence */
	
#line 129 "E:\\compiler\\teaching\\07\\\312\265\321\351\\\312\265\321\3512\\Yacc\263\314\320\362\312\276\300\375\\\276\344\327\323\312\266\261\360\\\264\312\267\250.c"
		}
		break;
	case 3:
		{
#line 22 "E:\\compiler\\teaching\\07\\\312\265\321\351\\\312\265\321\3512\\Yacc\263\314\320\362\312\276\300\375\\\276\344\327\323\312\266\261\360\\\264\312\267\250.l"
 state = VERB; 
#line 136 "E:\\compiler\\teaching\\07\\\312\265\321\351\\\312\265\321\3512\\Yacc\263\314\320\362\312\276\300\375\\\276\344\327\323\312\266\261\360\\\264\312\267\250.c"
		}
		break;
	case 4:
		{
#line 23 "E:\\compiler\\teaching\\07\\\312\265\321\351\\\312\265\321\3512\\Yacc\263\314\320\362\312\276\300\375\\\276\344\327\323\312\266\261\360\\\264\312\267\250.l"
 state = ADJECTIVE; 
#line 143 "E:\\compiler\\teaching\\07\\\312\265\321\351\\\312\265\321\3512\\Yacc\263\314\320\362\312\276\300\375\\\276\344\327\323\312\266\261\360\\\264\312\267\250.c"
		}
		break;
	case 5:
		{
#line 24 "E:\\compiler\\teaching\\07\\\312\265\321\351\\\312\265\321\3512\\Yacc\263\314\320\362\312\276\300\375\\\276\344\327\323\312\266\261\360\\\264\312\267\250.l"
 state = ADVERB; 
#line 150 "E:\\compiler\\teaching\\07\\\312\265\321\351\\\312\265\321\3512\\Yacc\263\314\320\362\312\276\300\375\\\276\344\327\323\312\266\261\360\\\264\312\267\250.c"
		}
		break;
	case 6:
		{
#line 25 "E:\\compiler\\teaching\\07\\\312\265\321\351\\\312\265\321\3512\\Yacc\263\314\320\362\312\276\300\375\\\276\344\327\323\312\266\261\360\\\264\312\267\250.l"
 state = NOUN; 
#line 157 "E:\\compiler\\teaching\\07\\\312\265\321\351\\\312\265\321\3512\\Yacc\263\314\320\362\312\276\300\375\\\276\344\327\323\312\266\261\360\\\264\312\267\250.c"
		}
		break;
	case 7:
		{
#line 26 "E:\\compiler\\teaching\\07\\\312\265\321\351\\\312\265\321\3512\\Yacc\263\314\320\362\312\276\300\375\\\276\344\327\323\312\266\261\360\\\264\312\267\250.l"
 state = PREPOSITION; 
#line 164 "E:\\compiler\\teaching\\07\\\312\265\321\351\\\312\265\321\3512\\Yacc\263\314\320\362\312\276\300\375\\\276\344\327\323\312\266\261\360\\\264\312\267\250.c"
		}
		break;
	case 8:
		{
#line 27 "E:\\compiler\\teaching\\07\\\312\265\321\351\\\312\265\321\3512\\Yacc\263\314\320\362\312\276\300\375\\\276\344\327\323\312\266\261\360\\\264\312\267\250.l"
 state = PRONOUN; 
#line 171 "E:\\compiler\\teaching\\07\\\312\265\321\351\\\312\265\321\3512\\Yacc\263\314\320\362\312\276\300\375\\\276\344\327\323\312\266\261\360\\\264\312\267\250.c"
		}
		break;
	case 9:
		{
#line 28 "E:\\compiler\\teaching\\07\\\312\265\321\351\\\312\265\321\3512\\Yacc\263\314\320\362\312\276\300\375\\\276\344\327\323\312\266\261\360\\\264\312\267\250.l"
 state = CONJUNCTION; 
#line 178 "E:\\compiler\\teaching\\07\\\312\265\321\351\\\312\265\321\3512\\Yacc\263\314\320\362\312\276\300\375\\\276\344\327\323\312\266\261\360\\\264\312\267\250.c"
		}
		break;
	case 10:
		{
#line 30 "E:\\compiler\\teaching\\07\\\312\265\321\351\\\312\265\321\3512\\Yacc\263\314\320\362\312\276\300\375\\\276\344\327\323\312\266\261\360\\\264\312\267\250.l"
 
	     if(state != LOOKUP) {
	     	add_word(state, yytext);
	     } else {
		switch(lookup_word(yytext)) {
		case VERB:
		  return(VERB);
		case ADJECTIVE:
		  return(ADJECTIVE);
		case ADVERB:
		  return(ADVERB);
		case NOUN:
		  return(NOUN);
		case PREPOSITION:
		  return(PREPOSITION);
		case PRONOUN:
		  return(PRONOUN);
		case CONJUNCTION:
		  return(CONJUNCTION);
		default:
		  printf("%s:  don't recognize\n", yytext);
		  /* don't return, just ignore it */
		}
            }
          
#line 209 "E:\\compiler\\teaching\\07\\\312\265\321\351\\\312\265\321\3512\\Yacc\263\314\320\362\312\276\300\375\\\276\344\327\323\312\266\261\360\\\264\312\267\250.c"
		}
		break;
	case 11:
		{
#line 56 "E:\\compiler\\teaching\\07\\\312\265\321\351\\\312\265\321\3512\\Yacc\263\314\320\362\312\276\300\375\\\276\344\327\323\312\266\261\360\\\264\312\267\250.l"
;
#line 216 "E:\\compiler\\teaching\\07\\\312\265\321\351\\\312\265\321\3512\\Yacc\263\314\320\362\312\276\300\375\\\276\344\327\323\312\266\261\360\\\264\312\267\250.c"
		}
		break;
	default:
		yyassert(0);
		break;
	}
	yyreturnflg = 0;
	return 0;
}

#ifndef YYNBORLANDWARN
#ifdef __BORLANDC__
#pragma warn .rch		/* <warning: unreachable code> to the old state */
#endif
#endif
#line 58 "E:\\compiler\\teaching\\07\\\312\265\321\351\\\312\265\321\3512\\Yacc\263\314\320\362\312\276\300\375\\\276\344\327\323\312\266\261\360\\\264\312\267\250.l"

/* define a linked list of words and types */
struct word {
	char *word_name;
	int word_type;
	struct word *next;
};

struct word *word_list; /* first element in word list */

extern void *malloc();

int
add_word(int type, char *word)
{
	struct word *wp;	

	if(lookup_word(word) != LOOKUP) {
		printf("!!! warning: word %s already defined \n", word);
		return 0;
	}
	
	/* word not there, allocate a new entry and link it on the list */

	wp = (struct word *) malloc(sizeof(struct word));

	wp->next = word_list;

	/* have to copy the word itself as well */
	
	wp->word_name = (char *) malloc(strlen(word)+1);
	strcpy(wp->word_name, word);
	wp->word_type = type;
	word_list = wp;
	return 1;	/* it worked */
}

int
lookup_word(char *word)
{
	struct word *wp = word_list;

	/* search down the list looking for the word */
	for(; wp; wp = wp->next) {
		if(strcmp(wp->word_name, word) == 0)
			return wp->word_type;
	}

	return LOOKUP;	/* not found */
}

#line 284 "E:\\compiler\\teaching\\07\\\312\265\321\351\\\312\265\321\3512\\Yacc\263\314\320\362\312\276\300\375\\\276\344\327\323\312\266\261\360\\\264\312\267\250.c"
YYCONST yymatch_t YYNEARFAR YYBASED_CODE YYDCDECL yymatch[] = {
	0
};

int YYNEAR YYDCDECL yytransitionmax = 249;
YYCONST yytransition_t YYNEARFAR YYBASED_CODE YYDCDECL yytransition[] = {
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 7, 4 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 3, 2 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 5, 1 },
	{ 25, 18 },
	{ 5, 1 },
	{ 4, 2 },
	{ 5, 5 },
	{ 13, 8 },
	{ 14, 9 },
	{ 0, 0 },
	{ 0, 0 },
	{ 22, 16 },
	{ 29, 24 },
	{ 0, 0 },
	{ 0, 0 },
	{ 5, 1 },
	{ 15, 10 },
	{ 5, 1 },
	{ 17, 12 },
	{ 16, 11 },
	{ 18, 13 },
	{ 23, 16 },
	{ 21, 15 },
	{ 5, 1 },
	{ 5, 2 },
	{ 5, 2 },
	{ 5, 2 },
	{ 5, 2 },
	{ 5, 2 },
	{ 5, 2 },
	{ 5, 2 },
	{ 5, 2 },
	{ 5, 2 },
	{ 5, 2 },
	{ 5, 2 },
	{ 5, 2 },
	{ 5, 2 },
	{ 5, 2 },
	{ 5, 2 },
	{ 5, 2 },
	{ 5, 2 },
	{ 5, 2 },
	{ 5, 2 },
	{ 5, 2 },
	{ 5, 2 },
	{ 5, 2 },
	{ 5, 2 },
	{ 5, 2 },
	{ 5, 2 },
	{ 5, 2 },
	{ 24, 17 },
	{ 26, 21 },
	{ 27, 22 },
	{ 28, 23 },
	{ 0, 0 },
	{ 0, 0 },
	{ 9, 2 },
	{ 5, 2 },
	{ 12, 2 },
	{ 5, 2 },
	{ 5, 2 },
	{ 5, 2 },
	{ 5, 2 },
	{ 5, 2 },
	{ 5, 2 },
	{ 5, 2 },
	{ 5, 2 },
	{ 5, 2 },
	{ 5, 2 },
	{ 10, 2 },
	{ 5, 2 },
	{ 11, 2 },
	{ 5, 2 },
	{ 5, 2 },
	{ 5, 2 },
	{ 5, 2 },
	{ 5, 2 },
	{ 8, 2 },
	{ 5, 2 },
	{ 5, 2 },
	{ 5, 2 },
	{ 5, 2 },
	{ 19, 14 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 20, 14 },
	{ 5, 19 },
	{ 5, 19 },
	{ 5, 19 },
	{ 5, 19 },
	{ 5, 19 },
	{ 5, 19 },
	{ 5, 19 },
	{ 5, 19 },
	{ 5, 19 },
	{ 5, 19 },
	{ 5, 19 },
	{ 5, 19 },
	{ 5, 19 },
	{ 5, 19 },
	{ 5, 19 },
	{ 5, 19 },
	{ 5, 19 },
	{ 5, 19 },
	{ 5, 19 },
	{ 5, 19 },
	{ 5, 19 },
	{ 5, 19 },
	{ 5, 19 },
	{ 5, 19 },
	{ 5, 19 },
	{ 5, 19 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 5, 19 },
	{ 5, 19 },
	{ 5, 19 },
	{ 5, 19 },
	{ 5, 19 },
	{ 5, 19 },
	{ 5, 19 },
	{ 5, 19 },
	{ 5, 19 },
	{ 5, 19 },
	{ 5, 19 },
	{ 5, 19 },
	{ 5, 19 },
	{ 5, 19 },
	{ 5, 19 },
	{ 5, 19 },
	{ 5, 19 },
	{ 5, 19 },
	{ 5, 19 },
	{ 5, 19 },
	{ 5, 19 },
	{ 5, 19 },
	{ 5, 19 },
	{ 5, 19 },
	{ 5, 19 },
	{ 5, 19 }
};

YYCONST yystate_t YYNEARFAR YYBASED_CODE YYDCDECL yystate[] = {
	{ 0, 0, 0 },
	{ 2, 1, 0 },
	{ -6, 55, 0 },
	{ 0, 0, 1 },
	{ 0, 1, 11 },
	{ 8, 1, 10 },
	{ 0, 0, 11 },
	{ 0, 0, 2 },
	{ 19, 2, 10 },
	{ 19, 4, 10 },
	{ 19, 1, 10 },
	{ 19, 1, 10 },
	{ 19, 3, 10 },
	{ 19, 2, 10 },
	{ 19, 72, 10 },
	{ 19, 1, 10 },
	{ 8, 6, 10 },
	{ 19, 36, 10 },
	{ 19, 1, 10 },
	{ 0, 126, 4 },
	{ 19, 0, 5 },
	{ 19, 37, 10 },
	{ 19, 36, 10 },
	{ 19, 39, 10 },
	{ 19, 2, 10 },
	{ 19, 0, 3 },
	{ 19, 0, 6 },
	{ 19, 0, 7 },
	{ 19, 0, 8 },
	{ 19, 0, 9 }
};

YYCONST yybackup_t YYNEARFAR YYBASED_CODE YYDCDECL yybackup[] = {
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0
};

