//Student: Sean Dela Pena
//
//
//
//
//
//

#include "scanner.hpp"

using namespace std;


int main(int argc, char* argv[]){

	std::string filename = "";
	ifstream file;
	//std::cout << keywords[1] << endl;
	
	if (argc > 2) {
		printf("perror: Incorrect use of the program.\n");
		exit(0);
	}
	else if (argc == 2) {
		filename = argv[1];
		file.open(filename);
		if (file) {
			std::cout << "Opening and working with the file..." << endl;
			//printTest(filename);
			//filter(filename);
			//fsaDriver(filename);
			testScanner(filename);
		}
		else {
			std::cout << "The file does not exist! Terminating..." << endl;
			exit(0);
		}
	}
	//for now 
	else {
		std::cout << "Will read from stdin." << endl;
		printTest(filename);
	}

	file.close();

	return 0;
}
