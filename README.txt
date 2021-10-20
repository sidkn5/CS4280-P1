Student: Sean Dela Pena 
Professor: Mark Hauschild
Assignment: Project 1 - CS 4280
	Scanner that tokenize.
Date: 10/19/21

USAGE: make		(makefile to compile, creates a scanner executable)
	./P0 [somefile] [keyboard input]
	make clean	

Two example invocations:
	./scanner somefile.txt [enter]

	./scanner [enter]
	this 
	is an 
	example
	of keyboard
	input
	[ctrl + d]

Any other invocations will result in an error.

Notes:
	The token structure is as shown
	[token, "string", line num:charNum]
	["IDTk, "example, line 1:1]

Important:
	The testScanner can be found in scanner.cpp file. The way the program works
	is that main processes the arguments, then calls the testScanner function. The
	testScanner function then calls the fsaDriver to get the tokens and calls the
	printTokenVector to print out the tokens.