%{
/*
 * We now build a lexical analyzer to be used by a higher-level parser.
 */

#include "Óï·¨.h"	/* token codes from the parser */

#define LOOKUP 0 /* default - not a defined word type. */

int state; 

%}

%%

\n	{ state = LOOKUP; }

\.\n	{	state = LOOKUP;
		return 0; /* end of sentence */
	}

^verb	{ state = VERB; }
^adj	{ state = ADJECTIVE; }
^adv	{ state = ADVERB; }
^noun	{ state = NOUN; }
^prep	{ state = PREPOSITION; }
^pron	{ state = PRONOUN; }
^conj	{ state = CONJUNCTION; }

[a-zA-Z]+ { 
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
          }

.	; 

%%
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
