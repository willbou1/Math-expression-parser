This is a simple parser for math expressions. It can do:
	-Simple verification of the expression including:
		-Parentesis matching
		-Impossibility of two operator or number following each other
		-Impossibility of beginning or ending an expression with an operator
	-Negative numbers
	-These operators:
		- +
		- -
		- *
		- /
		- ^
		- %
	-Parentesis
	-Operators are performed on long double
	-Convert infix to postfix

This is a simple C++ project that can open your mind to the universe of parser. 
I hope it can help some people to start doing parser.

Here's how it works:
1. It separatesthe expression into tokens
2. It verifies the tokens for mistakes
3. It converts the infix expression to postfix
4. It resolves the postfix expression

The code is heavily commented for easy understanding. 
Also, if you need this codde for your software you can take it and modify it as you need.
If you don't like comment you can check the "main - nc.cpp".