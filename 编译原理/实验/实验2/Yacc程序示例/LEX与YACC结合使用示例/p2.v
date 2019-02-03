    0  $accept : file $end

    1  file : record file
    2       | record

    3  record : NAME EQ PRICE


state 0
	$accept : . file $end

	NAME  shift 1

	file goto 2
	record goto 3


state 1
	record : NAME . EQ PRICE

	EQ  shift 4


state 2
	$accept : file . $end  (0)

	$end  accept


state 3
	file : record . file
	file : record .  (2)

	NAME  shift 1
	.  reduce 2

	file goto 5
	record goto 3


state 4
	record : NAME EQ . PRICE

	PRICE  shift 6


state 5
	file : record file .  (1)

	.  reduce 1


state 6
	record : NAME EQ PRICE .  (3)

	.  reduce 3


5 tokens, 3 nonterminals
4 grammar rules, 7 states
