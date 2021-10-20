//Student: Sean Dela Pena

#include "scanner.hpp"
#include "token.hpp"
#include "character.hpp"


const int rowSize = 28;
const int colSize = 25;
int specificKeyword = 0;
int charNumber = 0;
bool startComment = false;
bool endComment = false;
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
	"EOFTk", "KEYWORDTk", "STARTTk", "STOPTk", "LOOPTk", "WHILETk", "FORTk", "LABELTk", "EXITTk", "LISTENTk",
	"TALKTk", "PROGRAMTk", "IFTk", "THENTk", "ASSIGNTk", "DECLARETk", "JUMPTk", "ELSETk"
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
	{FINAL, FINAL,FINAL,FINAL,FINAL,FINAL,FINAL,FINAL,FINAL,FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL},	//s25
	{FINAL, FINAL,FINAL,FINAL,FINAL,FINAL,FINAL,FINAL,FINAL,FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL, FINAL},	//s25
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
	{']', RIGHTBRACKET}, {EOF, 23},      //EOF
	{'\0',24}
};


void testScanner(std::string filename) {
	std::vector <token> tks = fsaDriver(filename);
	printTokenVector(tks);
}

void printTokenVector(std::vector<token> &tks) {

	for (int i = 0; i < tks.size(); i++) {
		if (tks[i].type == HOLDERTK || tks[i].type == WSTK || tks[i].tokenString == "") {
			//since we considered WS as a tk to help with the FSA TABLE our vector will
			//have WStks but we don't need it so delete them
			tks.erase(tks.begin() + i);
			i--;
		}
		else {
			std::cout << "[" << tokenNames[tks[i].type] << ", \"" << tks[i].tokenString
				<< "\", line " << tks[i].lineNum << ":" << tks[i].charNum << "]" << std::endl;
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

void printError(std::string str, int line, int charNumber) {
	std::cout << "This is an error state, terminating...\n";
	std::cout << "ERORR SCANNER: Error in word " << "\"" << str << "\"" << " line: " << line << ":" << charNumber << "\n";
}

/*
void filterComments(std::string filename) {
	std::ifstream file;
	LinesContainer buffer;

	file.open(filename);
	if (std::getline(file, buffer.value)) {
		buffer.value.insert(0, 1, ' ');

		for (int i = 0; i < buffer.value.size(); i++) {

			if (startComment == true && buffer.value[i] == '&' && buffer.value[i + 1] == '&') {
				buffer.value[i] == ' ';
				buffer.value[i + 1] == ' ';
				startComment = false;
				i++;

			}
			else if (startComment) {

				buffer.value[i] = ' ';
				//buffer.value[i+1] = ' ';

			}
			else if (buffer.value[i] == '&' && buffer.value[i + 1] == '&') {
				buffer.value[i] == ' ';
				buffer.value[i + 1] == ' ';

				startComment = true;
				i++;

			}
		}
	}

	std::cout << buffer.value << "\n";
}

void checkWhiteSpace(std::string &line) {
	for (int i = 0; i < line.size(); i++) {
		if (line[i] == ' ')
			line = "";
	}
}*/

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
			buffer.value.insert(0, 1, ' ');
			//std::cout << "line: " << lineNumber << " boolean: " << startComment << "\n";
			//std::cout << buffer.value <<  " boolean " << startComment << "\n";
			

			//remove the comments
			for (int i = 0; i < buffer.value.size(); i++) {
				
				if (startComment == true && buffer.value[i] == '&' && buffer.value[i + 1] == '&') {
					//buffer.value[i] == ' ';
					//buffer.value[i + 1] == ' ';
					startComment = false;

					i++;
					break;
				}
				else if (startComment) {
					buffer.value[i] = ' ';
					
				}

				else if (buffer.value[i] == '&' && buffer.value[i + 1] == '&') {
					//buffer.value[i] == ' ';
					//buffer.value[i + 1] == ' ';

					startComment = true;

					i++;

				}
				
		
			}
			
	
			if (lineNumber <= 0) break;
		}
		else {
			
			buffer.endOfFile = true;
			
			break;
		}

		
	}
	replace(buffer.value.begin(), buffer.value.end(), '&', ' ');
	startComment = false;		
	std::cout << buffer.value << std::endl;
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
	int lookahead = 0;		//not used
	std::string word = "";
	int charColumn;
	int tokenIntType;
	int previousState;		//might be helpful?
	

	//token test;
	
	while (!currentLine.endOfFile) {

		currentLine = filter(filename, currentLineNum);
		int length = currentLine.value.size();
		charNumber = 0;
		//std::cout << "size " << currentLine.value.size() << "\n";
		for (int i = 0; i < length; i++) {
			charColumn = getIntFsa(currentLine.value[i]);
			nextState = fsaTable[state][charColumn];
			charNumber = i-1;
			
			if (nextState <= ERROR || nextState > FINAL) {
				//std::cout << "ERROR: \n";
				printError(word, currentLineNum, charNumber);
				exit(1);
			}
			else if (nextState == FINAL) {
			
				specificKeyword = 0;
				if (checkKeyword(word)) {
					allTokens.push_back(getToken(tokenType(KEYWORDTK + specificKeyword), word, currentLineNum, (charNumber-word.size() + 1)));
					word = "";
					state = s1;
					nextState = fsaTable[state][charColumn];
					
					word.append(1, currentLine.value[i]);
					if (nextState != FINAL) {
						state = nextState;
					}
				}
				else {
					/*/reset the word
					if (charNumber < 0 && tokenType(previousState) == WSTK) {
						//tokenIntType = state;
						//spreviousState = getIntFsa(word[word.size() -1]);
						
						allTokens.push_back(getToken(tokenType(previousState), word, currentLineNum-1, (currentLine.value.size() - word.size())));
						//allTokens.push_back(getToken(tokenType(tokenIntType), "hello", currentLineNum - 1, (currentLine.value.size() - word.size())));
						//std::cout << "Token word: " << word << " char " << charNumber << " token type " << tokenType(tokenIntType-1)  << "\n";
						word = "";
						
					}*/
					//else {
						previousState = state;
						//previousState = getIntFsa(word[word.size() - 1]);
						tokenIntType = state;
						//std::cout << "value: " << word << " line Number: " << currentLineNum << " token: " << tokenNames[tokenIntType] << "\n";
						allTokens.push_back(getToken(tokenType(tokenIntType), word, currentLineNum, (charNumber - word.size() + 1)));
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
				previousState = state;
				state = nextState;
				word.append(1, nextChar);
				nextChar = currentLine.value[i + 1];
				charColumn = getIntFsa(nextChar);
			}

		}
		//after going through the line there will be one last string the is stored in word, tokenize it.
		//check if last is keyword
		specificKeyword = 0;
		if (checkKeyword(word)) {
			allTokens.push_back(getToken(tokenType(KEYWORDTK + specificKeyword), word, currentLineNum, (charNumber - word.size())));
			word = "";		//reset the word after tokenizing
		}
		else {
			allTokens.push_back(getToken(tokenType(state), word, currentLineNum, (charNumber - word.size())));
			word = "";		//reset the word after tokenizing
		}
		
		
		currentLineNum++;
	}

	//when endOfFile is true add an EOFTK at the end
	allTokens.push_back(getToken(EOFTK, "EOF", currentLineNum-1, 0));

	return allTokens;

}

int getIntFsa(char ch) {
	//the symbols are in a map
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
		specificKeyword++;
		if (str == keywordStrings[i]) {
			
			return true;
		}
	}
	return false;
}

token getToken(tokenType type, std::string value, int lineNum, int charNum) {
	token tokenStr;
	tokenStr.type = type;
	tokenStr.tokenString = value;
	tokenStr.lineNum = lineNum;
	tokenStr.charNum = charNum;

	return tokenStr;
}
