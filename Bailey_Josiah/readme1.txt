Program 1
Bottom-Up
Compiled using the makefile provided
Command line arguments: xFile, yFile, outputFile (in this order)
Data Structures: 2-Dimensional array used to store the direction of the LCS and a 2-Dimensional array used to store the total length of the LCS
The direction 2-D array is used to follow the path and output the LCS.
The length 2-D array is used to output the actual length of the LCS.
Computation Time: The time is O(n*m) where n = length(xString) and m = length(yString) because the algorithm only has to iterate through each character in both strings.
