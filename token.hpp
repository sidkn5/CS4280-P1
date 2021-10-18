// Student: Sean Dela Pena
// token.hpp
//


#ifndef TOKEN_HPP
#define TOKEN_HPP
#include <string>

enum class tokenType {
	//identifier, integer and eof
	IDTK, INTEGERTK, EOFTK,

	/*not sure if needed yet, fall into id then determine if it's a reserved word
	//reserved keywords
	STARTTK, STOPTK, LOOPTK, WHILETK, FORTK, LABELTK, EXITTK, LISTENTK, TALKTK,
	PROGRAMTK, IFTK, THENTK, ASSIGNTK, DECLARETK, JUMPTK, ELSETK,
	*/

	//operators and delimiters
	EQUALTK, GREATERTHANTK, LESSTHANTK, EQEQTK, COLONTK,
	COLONEQTK, PLUSTK, MINUSTK, MULTIPLYTK, DIVIDETK, MODULUSTK, DOTTK, LEFTPARENTK, RIGHTPARENTK,
	COMMATK, LEFTBRACETK, RIGHTBRACETK, SEMICOLONTK, LEFTBRACKETTK, RIGHTBRACKETTK
};

struct token{
	tokenType type;
	std::string tokenString;
	int lineNum;

};


#endif