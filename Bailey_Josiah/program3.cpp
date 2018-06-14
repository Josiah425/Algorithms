#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <string>
#include <ctime>
#include <algorithm>

//Table to store lengths of subsequences
int ** intTable;
//x string
std::string xSeq;
//y string
std::string ySeq;

//Using memoization recursively calculate the LCS
int recursiveSolve(int i, int j){
	if(i == xSeq.length() || j == ySeq.length()) return 0;
	if(intTable[i][j] < 0){
		if(xSeq[i] == '\0' || ySeq[j] == '\0') intTable[i][j] = 0;
		else if(xSeq[i] == ySeq[j]) intTable[i][j] = 1 + recursiveSolve(i+1, j+1);
		else intTable[i][j] = std::max(recursiveSolve(i+1, j), recursiveSolve(i, j+1));
	}
	return intTable[i][j];
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
	getline(xFile, xSeq);
	getline(yFile, ySeq);

	intTable = new int *[xSeq.length()];
	//Create the 2-D array dynamically
	for(int i = 0; i < xSeq.length(); i++){
		intTable[i] = new int[ySeq.length()];
	}	

	//Set defaut value to -1
	for(int i = 0; i < xSeq.size(); i++){
		for(int j = 0; j < ySeq.size(); j++){
			intTable[i][j] = -1;
		}
	}

	//Start time
	int start_s = clock();
	int length = recursiveSolve(0, 0);
	//End time
	int stop_s = clock();

	oFile << length << std::endl;
	oFile << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << std::endl;

	return 0;
}
