//Student: Sean Dela Pena

#include "scanner.hpp"
#include "token.hpp"
#include "character.hpp"


const int rowSize = 25;
const int colSize = 25;

enum states {
	ERROR = -1, s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11,
	s12, s13, s14, s15, s16, s17, s18, s19, s20, s21, s22, s23,
	s24, s25,
	FINAL = 101
};

std::string keywords[] = {
	"start", "stop", "loop", "while", "for", "label", "exit", "listen", "talk", "program", "if", "then", "assign", "declare", "jump", "else"
};


std::string tokenNames[] = {
	"HolderTk", "IDTk", "INTEGERTk", "WSTk", "EQUALTk", "EQEQTk", "GREATERTHANTk", "LESSTHANTk", "COLONTk",
	"COLONEQTk", "PLUSTk", "MINUSTk", "MULTIPLYTk", "DIVIDETk", "MODULUSTk", "DOTTk", "LEFTPARENTK", 
	"RIGHTPARENTk", "COMMATk", "LEFTBRACETk", "RIGHTBRACETk", "SEMICOLONTk", "LEFTBRACKETTk", "RIGHTBRACKETTk",
	"EOFTk", "KEYWORDTk"
};

int fsaTable[rowSize][colSize] = {
	//  a-z   A-Z   0-9     $    WS     =     >     <     :     +	   -	  *      /	   %	   .	  (	     )	    ,	   {	  }	     ;     [       ]    EOF
	{   s2,	ERROR,   s3,   s2,   s4,   s5,   s7,   s8,   s9,  s11,   s12,   s13,   s14,   s15,   s16,   s17,   s18,   s19,   s20,   s21,   s22,   s23,   s24,   s25, FINAL},	//s1
	{   s2,    s2,   s2,FINAL,FINAL,FINAL,FINAL,FINAL,FINAL,FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL},	//s2
	{FINAL, FINAL,   s3,FINAL,FINAL,FINAL,FINAL,FINAL,FINAL,FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL},	//s3
	{FINAL, FINAL,FINAL,FINAL,FINAL,FINAL,FINAL,FINAL,FINAL,FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL},	//s4
	{FINAL, FINAL,FINAL,FINAL,FINAL,   s6,FINAL,FINAL,FINAL,FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL},	//s5
	{FINAL, FINAL,FINAL,FINAL,FINAL,FINAL,FINAL,FINAL,FINAL,FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL},	//s6
	{FINAL, FINAL,FINAL,FINAL,FINAL,FINAL,FINAL,FINAL,FINAL,FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL},	//s7
	{FINAL, FINAL,FINAL,FINAL,FINAL,FINAL,FINAL,FINAL,FINAL,FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL},	//s8
	{FINAL, FINAL,FINAL,FINAL,FINAL,  s10,FINAL,FINAL,FINAL,FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL},	//s9
	{FINAL, FINAL,FINAL,FINAL,FINAL,FINAL,FINAL,FINAL,FINAL,FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL},	//s10
	{FINAL, FINAL,FINAL,FINAL,FINAL,FINAL,FINAL,FINAL,FINAL,FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL},	//s11
	{FINAL, FINAL,FINAL,FINAL,FINAL,FINAL,FINAL,FINAL,FINAL,FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL},	//s12
	{FINAL, FINAL,FINAL,FINAL,FINAL,FINAL,FINAL,FINAL,FINAL,FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL},	//s13
	{FINAL, FINAL,FINAL,FINAL,FINAL,FINAL,FINAL,FINAL,FINAL,FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL},	//s14
	{FINAL, FINAL,FINAL,FINAL,FINAL,FINAL,FINAL,FINAL,FINAL,FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL},	//s15
	{FINAL, FINAL,FINAL,FINAL,FINAL,FINAL,FINAL,FINAL,FINAL,FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL},	//s16
	{FINAL, FINAL,FINAL,FINAL,FINAL,FINAL,FINAL,FINAL,FINAL,FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL},	//s17
	{FINAL, FINAL,FINAL,FINAL,FINAL,FINAL,FINAL,FINAL,FINAL,FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL},	//s18
	{FINAL, FINAL,FINAL,FINAL,FINAL,FINAL,FINAL,FINAL,FINAL,FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL},	//s19
	{FINAL, FINAL,FINAL,FINAL,FINAL,FINAL,FINAL,FINAL,FINAL,FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL},	//s20
	{FINAL, FINAL,FINAL,FINAL,FINAL,FINAL,FINAL,FINAL,FINAL,FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL},	//s21
	{FINAL, FINAL,FINAL,FINAL,FINAL,FINAL,FINAL,FINAL,FINAL,FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL},	//s22
	{FINAL, FINAL,FINAL,FINAL,FINAL,FINAL,FINAL,FINAL,FINAL,FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL},	//s23
	{FINAL, FINAL,FINAL,FINAL,FINAL,FINAL,FINAL,FINAL,FINAL,FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL},	//s24
	{FINAL, FINAL,FINAL,FINAL,FINAL,FINAL,FINAL,FINAL,FINAL,FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL},	//s25

};

std::map<char, int> columnInt = {
	{'a', LOWERCASE},       //a-z   lowercase
	{'A', UPPERCASE},       //A-Z   uppercase
	{'1', INTEGER},       //0-9 digit
	{'$', DOLLAR},
	{' ', WS},       //WS
	{'=', EQUAL},
	{'>', GREATERTHAN},
	{'<', LESSTHAN},
	{':', COLON},
	{'+', PLUS},
	{'-', MINUS},
	{'*', MULTIPLY},
	{'/', DIVIDE},
	{'%', MODULUS},
	{'.', DOT},
	{'(', LEFTPAREN},
	{')', RIGHTPAREN},
	{',', COMMA},
	{'{', LEFTBRACE},
	{'}', RIGHTBRACE},
	{';', SEMICOLON},
	{'[', LEFTBRACKET},
	{']', RIGHTBRACKET},
	{EOF, 23},      //EOF
	{'\0',24}
};


void testScanner(std::string filename) {
	std::vector <token> tks = fsaDriver(filename);
	printTokenVector(tks);
}

void printTokenVector(std::vector<token> &tks) {



	for (int i = 0; i < tks.size(); i++) {
		if (tks[i].type == 0 || tks[i].type == 3) {
			//these are holder tks, don't print
		}
		else {
			std::cout << "[" << tokenNames[tks[i].type] << ", \"" << tks[i].tokenString
				<< "\", line " << tks[i].lineNum << "]" << std::endl;
		}
	}
}


void printTest(std::string file) {
	//std::cout << keywords[1];
	//std::cout << file;
	//std::cout << filter(file);
	LinesContainer printThis;
	//printThis = filter(file);
	std::cout << printThis.value;
}

void printError() {
	std::cout << "This is an error state, terminating...\n";
	exit(1);
}


void filterComments(std::string line) {

	for (int i = 0; i <= line.length(); i++) {
		if (line[i] == '&' && line[i + 1] == '&') {

		}
	}
}

LinesContainer filter(std::string filename, int lineNumber) {
	std::ifstream file;
	LinesContainer buffer;
	int line = 0;

	file.open(filename);

	while (lineNumber) {
		
		if (std::getline(file, buffer.value)) {	
			line++;
			//std::cout << buffer.value << line << std::endl;
			lineNumber--;
			if (lineNumber <= 0) break;
		}
		else {
			//std::cout << "GOT HERE";
			buffer.endOfFile = true;
			break;
		}
	}

	buffer.lineNum = line;
	return buffer;
}


std::vector<token> fsaDriver(std::string filename) {
	LinesContainer currentLine;
	
	int tableColumn = 10;
	int currentLineNum = 1;
	int numOfLines = 0;

	std::vector <token> allTokens;

	//pseudo from powerpoint
	int state = s1;
	int nextState;
	token newToken;
	char nextChar;			//+1 lookahead
	int lookahead = 0;
	std::string word = "";
	int charColumn;
	int tokenIntType;

	

	//token test;
	
	while (!currentLine.endOfFile) {

		currentLine = filter(filename, currentLineNum);
		int length = currentLine.value.size();

		for (int i = 0; i < length; i++) {
			//std::cout << currentLine.value[i];
			charColumn = getIntFsa(currentLine.value[i]);
			nextState = fsaTable[state][charColumn];

			if (isspace(currentLine.value[i])) length++;

			if (nextState == ERROR) {
				printError();
			}
			else if (nextState == FINAL) {
				if (checkKeyword(word)) {

					//std::cout << word << " Key TOKEN" << " line Number " << currentLineNum << "\n";
					//tokenIntType = state;
					//std::cout << word << " Key TOKEN" << " line Number " << currentLineNum << "\n";
					std::cout << "value: " << word << " line Number: " << currentLineNum << " token: " << KEYWORDTK << "\n";
					allTokens.push_back(getToken(KEYWORDTK, word, currentLineNum));
					word = "";
					state = s1;
					nextState = fsaTable[state][charColumn];
					word.append(1, currentLine.value[i]);
					if (nextState != FINAL) {
						state = nextState;
					}
				} else {
					tokenIntType = state;
					
					//std::cout << "value: " << word << " line Number: " << currentLineNum << " token: " << tokenNames[tokenIntType] << "\n";
					allTokens.push_back(getToken(tokenType(tokenIntType), word, currentLineNum));
					word = "";
					state = s1;
					nextState = fsaTable[state][charColumn];
					word.append(1, currentLine.value[i]);
					if (nextState != FINAL) {
						state = nextState;
					}
				}
				
			}
			else {
				nextChar = currentLine.value[i];
				state = nextState;
				word.append(1, nextChar);
				nextChar = currentLine.value[i + 1];
				charColumn = getIntFsa(nextChar);
			}

		}
		//std::cout << "\n";

		currentLineNum++;
	}

	return allTokens;

}

int getIntFsa(char ch) {
	if (islower(ch)) {
		return LOWERCASE;
	}
	else if (isupper(ch)) {
		return UPPERCASE;
	}
	else if (isspace(ch)) {
		return WS;
	}
	else if (isdigit(ch)) {
		return INTEGER;
	}
	
	return columnInt[ch];
}

bool checkKeyword(std::string str) {
	int keywordNum = 16;
	token temp;
	std::string keywordStrings[keywordNum] = {
		"start", "stop", "loop", "while", "for", "label", "exit", "listen",
		"talk", "program", "if", "then", "assign", "declare", "jump", "else"
	};
	for (int i = 0; i < keywordNum; i++) {
		if (str == keywordStrings[i]) {
			
			return true;
		}
	}
	return false;
}

token getToken(tokenType type, std::string value, int lineNum) {
	token tokenStr;
	tokenStr.type = type;
	tokenStr.tokenString = value;
	tokenStr.lineNum = lineNum;

	return tokenStr;
}
