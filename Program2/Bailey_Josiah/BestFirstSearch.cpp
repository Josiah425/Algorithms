#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>

int maxprofit = 0;
int * bestset;
int * sorted_profit;
int * sorted_weight;
int capacity = 0;
int n = 0;
int nodesVisited = 1; //always starts at 1 since root counts as first
int leafNodes = 0;

struct node{
	std::vector<int> include;
	int level;
	int profit;
	int weight;
	double bound;
	//This isn't needed but it's an alternative to the auto node_cmp I used below, looks much simpler but decided to just keep both
	bool operator<(const struct node& y) const{
		return bound < y.bound;
	}
};

/* UpperBound takes a node and a bool to see if it's root node
   I keep track of the total weight and once the total weight plus the next item is over capacity
   I add a fraction of the next item into the knapsack, and since the items are in profit/weight order
   This ensures I get the largest bound possible
   returns the upper bound
*/
int UpperBound(node u, bool first){
	int bound = 0;
	int i = 0;
	int totalWeight = 0;
	if(u.weight > capacity) return 0;
	else{
		bound = u.profit;
		//Simply to get the correct bound for subsequent node at first level
		if(!first) i = u.level+1;
		totalWeight = u.weight;
		while((i < n) && (totalWeight + sorted_weight[i] <= capacity)){
			totalWeight = totalWeight + sorted_weight[i];
			bound = bound + sorted_profit[i];
			i++;
		}
		if(i < n) bound = bound + (capacity - totalWeight) * sorted_profit[i]/(double)sorted_weight[i];
	}
	return bound;

}

/* BFS_Branch_And_Bound takes nothing because it manipulates global variables
   Initializes priority queue that prioritizes items by largest bound
   Checks if the current bound is greater than or equal to the max profit
   the u node is updated to keep track of nodes combined together and if its promising
   Add it's two children (include element v not include element)
   Updates maxprofit along the way and keeps track of which items are in the knapsack
   returns nothing since everything global is updated as it goes
*/
void BFS_Branch_And_Bound(){
	/*First time I've used a priority queue in code, had to look up how to create them and implement them
	  This is me setting up what the priority queue looks for when restructuring itself, I want it to prioritize
	  The bound as the most important feature, obviously for best first search
	*/
	auto node_cmp = [](const struct node& l, const struct node& r) {return l.bound < r.bound;};
	std::priority_queue<struct node,std::vector<struct node>,decltype(node_cmp)> Queue{node_cmp};

	struct node u, v;
	Queue.empty();
	//Need this bool to set the u.level to correct value on the first time through
	bool first = true;
	v.level = 0;
	v.profit = 0;
	v.weight = 0;
	v.bound = 0;
	int maxNodeIndex = 0;
	maxprofit = -1;
	Queue.push(v);
	for(int i = 0; i < n; i++) {
		u.include.push_back(0);
		v.include.push_back(0);
	}
	while(!Queue.empty()){
		v = Queue.top();
		Queue.pop();
		//No need to do useless checks on nodes that won't yield anything after they were added into queue
		//std::cout << maxprofit << std::endl;
		if(v.bound > maxprofit){
			for(int i = 0; i < n; i++) u.include[i] = v.include[i];
			if(first) {
				first = false;
				u.level = 0;
			}
			else u.level = v.level + 1;
			u.weight = v.weight + sorted_weight[u.level];
			u.profit = v.profit + sorted_profit[u.level];
			u.bound = UpperBound(u, first);
			u.include[u.level] = 1;
			//for(int i = 0; i < n; i++) std::cout << u.include[i];
			//std::cout << std::endl;
			nodesVisited++;
			if(u.weight <= capacity && u.profit > maxprofit) {
				maxNodeIndex = u.level;
				maxprofit = u.profit;
			}
			if(u.bound >= maxprofit && u.level != n-1) Queue.push(u);//include the yes child in queue
			else{
				leafNodes++;
			}
			u.weight = v.weight;
			u.profit = v.profit;
			u.bound = UpperBound(u, first);
			u.include[u.level] = 0;
			//for(int i = 0; i < n; i++) std::cout << u.include[i];
			//std::cout << std::endl;
			nodesVisited++;
			if(u.bound >= maxprofit && u.level != n-1) Queue.push(u);//include the no child in queue
			else{
				leafNodes++;
			}
		}
		else{
			//The excess nodes left in queue are leaf nodes
			leafNodes++;
		}
	}
	int total = 0;
	for(int i = 0; i < n; i++) bestset[i] = u.include[i];
	bestset[maxNodeIndex] = 1;
	return;
}

int main(int argc, char * argv[]){
	std::ifstream fin(argv[1]);
	std::ofstream fout(argv[2]);
	int j = 0;
	std::string s;
	getline(fin, s);
	std::istringstream ss(s);
	getline(ss, s, ',');
	n = atoi(s.c_str());
	getline(ss, s, ',');
	capacity = atoi(s.c_str());
	int weight[n];
	int profit[n];
	sorted_weight = new int[n];
	sorted_profit = new int[n];
	bestset = new int[n];

	for(int i = 0; i < n; i++){
		sorted_weight[i] = 0;
		sorted_profit[i] = 0;
		bestset[i] = 0;
	}

	while(!fin.eof()){
		getline(fin, s);
		std::istringstream ss(s);
		getline(ss, s, ',');
		weight[j] = atoi(s.c_str());
		getline(ss, s, ',');
		profit[j] = atoi(s.c_str());
		j++;
	}

	j = 0;
	while(j < n){
		double max_ratio = 0;
		int max_index = 0;
		for(int i = 0; i < n; i++){
			if(profit[i]/(double)weight[i] > max_ratio){
				max_ratio = profit[i]/(double)weight[i];
				max_index = i;
			}
		}
		sorted_weight[j] = weight[max_index];
		sorted_profit[j] = profit[max_index];
		weight[max_index] = 0;
		profit[max_index] = 0;
		j++;
	}
	BFS_Branch_And_Bound();
	int items = 0;
	for(int i = 0; i < n; i++){
		if(bestset[i] == 1) items++;
	}
	fout << n << ',' << maxprofit << ',' << items << std::endl;
	fout << nodesVisited << ',' << leafNodes << std::endl;
	for(int i = 0; i < n; i++){
		if(bestset[i] == 1) fout << sorted_weight[i] << ',' << sorted_profit[i] << std::endl;
	}

	return 0;
}
