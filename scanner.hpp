//Student: Sean Dela Pena
//File: scanner.hpp
//
//
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


void testScanner(std::string filename);
void printTokenVector(std::vector<token> &tks);
void printTest(std::string file);
void filterComments(std::string line);
LinesContainer filter(std::string filename,int lineNumber);
std::vector<token> fsaDriver(std::string filename);
int getIntFsa(char ch);
void printError();
bool checkKeyword(std::string str);
token getToken(tokenType type, std::string value, int lineNum);
#endif
