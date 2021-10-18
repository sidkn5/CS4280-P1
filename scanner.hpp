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


//character filter();
void printTest(std::string file);
void filterComments(std::string line);
LinesContainer filter(std::string filename,int lineNumber);
void fsaDriver(std::string filename);
int getIntFsa(char ch);
void printError();
#endif
