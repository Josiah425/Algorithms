BestFirstSearch
Compiled using the makefile provided
Command line arguments: inputFile, outputFile (in this order)
Data Structures: Priority Queue
The priority Queue is ordered based on bound
Computation Time: The worst case time complexity is O(2^n).  N is the size of the data.  The reason it's O(2^n) and not O(2^n+1) is because once the depth = n, there are no more nodes to check and the queue empties itself.
