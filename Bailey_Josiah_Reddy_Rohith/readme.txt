Josiah Bailey and Rohith Reddy

The best_case.txt and average_case.txt work for both
However, the worst_case is different for each of the programs
The reason for this is because the worst case for bottomup, requires the candidate search function
to go through every iteration, therefore the worst case would be to have no candidate solution for each activity
The worst case for the recursive approach is when we include everything and a candidate solution is found everytime
This causes the most recursive calls to be made

INTERESTING NOTE: The worst case for recursive call, is a best case for bottomup

Compiled using the makefile provided
Command line arguments: inputFile, outputFile (in this order)
Data Structures: Array, an activity struct that is 3 integer values, the bottomup has an include array which was for my own curiosity to see if everything worked
Functions: Search function goes through the list of activities from the current activity and before to find the first candidate activity
	   It does this by checking start time of current activity and the finish time of previous activities to find no conflicts
	   The weighted_activity functions both find the optimal value for a set of activities from the input
Computation Time: The worst case time complexity is O(2^n) for recursive solution.
		  Worst case is O(n^2) for bottomup.
