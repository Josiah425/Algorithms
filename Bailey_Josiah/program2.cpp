#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <ctime>
#include <algorithm>

//Recursively calculates the length of the LCS
int findLCSLength(std::string xSeq, int xIn, std::string ySeq, int yIn){
	//String ended we've done all we can
	if(xSeq[xIn] == '\0' || ySeq[yIn] == '\0') return 0;
	//Check if the characters are equal to each other if so add 1 to Length and pass in next characters
	else if(xSeq[xIn] == ySeq[yIn]) return 1 + findLCSLength(xSeq, xIn+1, ySeq, yIn+1);
	//If the characters are not equal check whether the next char of x string will produce a larger LCS or the next char of y string will produce a larger LCS
	else return std::max(findLCSLength(xSeq, xIn+1, ySeq, yIn), findLCSLength(xSeq, xIn, ySeq, yIn+1));
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
	//x string
	std::string xSeq;
	//y string
	std::string ySeq;
	getline(xFile, xSeq);
	getline(yFile, ySeq);
	//length of LCS
	int length;
	//Start time
	int start_s = clock();	
	length = findLCSLength(xSeq, 0, ySeq, 0);
	//End time
	int stop_s = clock();

	oFile << length << std::endl;
	oFile << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << std::endl;

	xFile.close();
	yFile.close();
	oFile.close();

	return 0;
}
