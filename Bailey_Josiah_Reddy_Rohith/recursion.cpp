#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <ctime>
#include <algorithm>
#include <sys/time.h>

struct activity{
	int start;
	int finish;
	int profit;
} activity;

struct include{
	int * includeArray;
	int price;
	bool contributed;
} include;

struct activity * sortedActivity;
struct include * optimal;
int totalSlots;

int Search(int j){
	for(int i = j-1; i >= 0; i--){
		if(sortedActivity[j-1].start >= sortedActivity[i].finish){
			return i;
		}
	}
	return -1;
}

int timeval_subtract(struct timeval *result, struct timeval *t2, struct timeval *t1)
{
    long int diff = (t2->tv_usec + 1000000 * t2->tv_sec) - (t1->tv_usec + 1000000 * t1->tv_sec);
    result->tv_sec = diff / 1000000;
    result->tv_usec = diff % 1000000;

    return (diff<0);
}

void timeval_print(char *str, struct timeval *tv)
{
    printf("%s %ld sec, %06ld micro sec\n", str, tv->tv_sec, tv->tv_usec);
}

int Weighted_Activity_Selection(int n){
	if(n == 1) return sortedActivity[n-1].profit;
	int taken = sortedActivity[n-1].profit;
	int candidate = Search(n);
	//std::cout << "Candidate: " << candidate << std::endl;
	if(candidate != -1) taken += Weighted_Activity_Selection(candidate+1);
	int notTaken = Weighted_Activity_Selection(n-1);
	
	//std::cout << taken << ' ' << notTaken << std::endl;	

	return std::max(taken, notTaken);
}

int main(int argc, char * argv[]){
	std::ifstream input;
	input.open(argv[1]);
	std::ofstream output;
	output.open(argv[2]);
	
	std::string s;
	int i = 0;
	getline(input, s);
	totalSlots = atoi(s.c_str());
	std::vector<struct activity> activityVector;
	sortedActivity = new struct activity[totalSlots];
	optimal = new struct include[totalSlots];

	for(int j = 0; j < totalSlots; j++){
		optimal[j].includeArray = new int[totalSlots];
		for(int k = 0; k < totalSlots; k++){
			optimal[j].includeArray[k] = 0;
		}
		optimal[j].price = 0;
		optimal[j].contributed = 0;
	}

	while(!input.eof()){
		struct activity temp;
		getline(input, s);
		std::istringstream ss(s);
		getline(ss, s, ',');
		temp.start = atoi(s.c_str());
		getline(ss, s, ',');
		temp.finish = atoi(s.c_str());
		getline(ss, s, ',');
		temp.profit = atoi(s.c_str());
		activityVector.push_back(temp);
		i++;
	}
	i = 0;
	
	//Sort by finish time
	while(i < totalSlots){
		int min = 100000000;
		int minIndex = 0;
		for(int j = 0; j < totalSlots; j++){
			if(activityVector[j].finish < min){
				min = activityVector[j].finish;
				minIndex = j;
			}
		}
		sortedActivity[i] = activityVector[minIndex];
		//std::cout << sortedActivity[i].start << ' ' << sortedActivity[i].finish << ' ' << sortedActivity[i].profit << std::endl;
		activityVector[minIndex].finish = 100000000;
		i++;
	}

	//std::cout << std::endl;
	struct timeval tvDiff, tvStart, tvEnd;
	gettimeofday(&tvStart, NULL);
	int answer = Weighted_Activity_Selection(totalSlots);
	gettimeofday(&tvEnd, NULL);
	output << answer << std::endl;
	timeval_subtract(&tvDiff, &tvEnd, &tvStart);
	output << "Time: " << tvDiff.tv_sec << " sec, " << tvDiff.tv_usec << " micro sec" << std::endl;

	return 0;
}
