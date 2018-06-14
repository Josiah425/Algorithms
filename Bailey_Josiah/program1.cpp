#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <ctime>

#define DIAGONAL 1
#define UP 2
#define LEFT 3

//Backtrace goes through the char table to get the exact LCS string
std::string backtrace(int ** charTable, std::string xSeq, std::string ySeq){
	std::string returnVal = "";
	int i = xSeq.length();
	int j = ySeq.length();
	//Move through table
	while(charTable[i][j] != 0){
		if(charTable[i][j] == DIAGONAL){
			returnVal += xSeq[i-1];
			i = i-1;
			j = j-1;
		}
		else if(charTable[i][j] == UP){
			i = i-1;
		}
		else if(charTable[i][j] == LEFT){
			j = j-1;
		}
		else{
			std::cout << "SOMETHING WENT WRONG" << std::endl;
		}
	}
	//Reverse string
	for(int i = 0; i < returnVal.length()/2; i++){
		std::swap(returnVal[i], returnVal[returnVal.length()-i-1]);
	}
	return returnVal;
}

int main(int argc, char * argv[]){
	//input x file
	std::ifstream xFile;
	xFile.open(argv[1]);
	//input y file
	std::ifstream yFile;
	yFile.open(argv[2]);
	//output file
	std::ofstream oFile;
	oFile.open(argv[3]);
	//x string from x file
	std::string xSeq;
	//y string from y file
	std::string ySeq;
	getline(xFile, xSeq);
	getline(yFile, ySeq);
	//iterate through one char in x string
	char xChar;
	//iterate through one char in y string
	char yChar;
	//2-D array table of length calculations
	int** intTable = new int*[xSeq.length()+1];
	//2-D array table of path for LCS
	int** charTable = new int*[xSeq.length()+1];
	for(int i = 0; i <= xSeq.length(); i++){
		intTable[i] = new int[ySeq.length()+1];
		charTable[i] = new int[ySeq.length()+1];
	}
	//Start time
	int start_s = clock();
	//Iterate through each character in each subarray and populate table
	for(int i = 1; i <= xSeq.length(); i++){
		xChar = xSeq[i-1];
		for(int j = 1; j <= ySeq.length(); j++){
			yChar = ySeq[j-1];
			//If the characters are equal, then update value from up left position
			if(xChar == yChar){
				intTable[i][j] = intTable[i-1][j-1] + 1;
				charTable[i][j] = DIAGONAL;
			}
			//If the value above is the max of left or equal to left then take it 
			else if(intTable[i-1][j] >= intTable[i][j-1]){
				intTable[i][j] = intTable[i-1][j];
				charTable[i][j] = UP;
			}
			//If the value to the left is the max of up and left then take it
			else{
				intTable[i][j] = intTable[i][j-1];
				charTable[i][j] = LEFT;
			}
		}
	}
	//End time
	int stop_s = clock();
	
	//If string size is leq to 10, then we output the table
	if(xSeq.length() <= 10 && ySeq.length() <= 10){
		for(int i = 0; i <= xSeq.length(); i++){
			for(int j = 0; j <= ySeq.length(); j++){
				oFile << intTable[i][j] << ' ';
			}
			oFile << std::endl;
		}
		std::string LCS = backtrace(charTable, xSeq, ySeq);
		oFile << LCS << std::endl;
		oFile << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << std::endl;
	}
	else{
		oFile << intTable[xSeq.length()][ySeq.length()] << std::endl;
		oFile << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << std::endl;
	}
	//Deal with memory leaks
	for(int i = 0; i < xSeq.length(); i++){
		delete intTable[i];
		delete charTable[i];
	}
	//Deal with memory leaks
	delete intTable;
	delete charTable;

	xFile.close();
	yFile.close();
	oFile.close();

	return 0;
}
