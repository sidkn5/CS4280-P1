//Student: Sean Dela Pena
//File: scanner.hpp
//
//Source: https://www.geeksforgeeks.org/remove-comments-given-cc-program/
//	modified for our project needs
//


#ifndef SCANNER_H
#define SCANNER_H
#include "character.hpp"
#include "token.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>

void testScanner(std::string filename);
void printTokenVector(std::vector<token> &tks);
LinesContainer filter(std::string filename,int lineNumber);
std::vector<token> fsaDriver(std::string filename);
int getIntFsa(char ch, int l, int n);
void printError(std::string str, int line, int charNumber);
bool checkKeyword(std::string str);
token getToken(tokenType type, std::string value, int lineNum, int charNum);
#endif
