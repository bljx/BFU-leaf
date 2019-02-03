    0  $accept : sentence $end

    1  sentence : subject VERB object

    2  subject : NOUN
    3          | PRONOUN

    4  object : NOUN


state 0
	$accept : . sentence $end

	NOUN  shift 1
	PRONOUN  shift 2

	sentence goto 3
	subject goto 4


state 1
	subject : NOUN .  (2)

	.  reduce 2


state 2
	subject : PRONOUN .  (3)

	.  reduce 3


state 3
	$accept : sentence . $end  (0)

	$end  accept


state 4
	sentence : subject . VERB object

	VERB  shift 5


state 5
	sentence : subject VERB . object

	NOUN  shift 6

	object goto 7


state 6
	object : NOUN .  (4)

	.  reduce 4


state 7
	sentence : subject VERB object .  (1)

	.  reduce 1


5 tokens, 4 nonterminals
5 grammar rules, 8 states
