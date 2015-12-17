grammar ArrayInt;
init: '{' value (',' value)* '}';
value: init
	| INT
	;	
INT: [a-z]+;
WS: [ \t\r\n]+ -> skip;

