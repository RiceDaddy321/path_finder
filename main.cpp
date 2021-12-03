#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "directedGraph.h"
using namespace std;

int main()
{
	//declare constants
	string inFile = "inputMaze.txt";
	string outFile = "outputMaze.txt";
	fstream readMaze, writeMaze;
	readMaze.open(inFile, fstream::in);
	writeMaze.open(outFile, fstream::out);

	//for the storage of the characters
	vector< vector<char*> > maze;
	int numberOfLines = 0;
	directedGraph mazeBoard;

	//for storing location of s and e
	char* start = nullptr;
	char* end = nullptr;

	//read-in maze (got this from stackoverflow, but this could've also been achieved with getline)
	std::stringstream buffer;
	buffer << readMaze.rdbuf();
	std::string in(buffer.str());

	vector<char*> rowMaze;

	//create a maze-like-structure using a vector of vectors, which store the address of each of the characters
	//in the og string, so we can modify them directly
	for (int i = 0; i < in.size(); i++)
	{
		//create a new row when we encounter a newline character
		if (in[i] == '\n')
		{
			maze.push_back(rowMaze);
			rowMaze.clear();
		}
		else // when not a newline character then just add it normally
		{
			//store the location of s and e while we're at it.
			if (in[i] == 's')
				start = &in[i];
			else if (in[i] == 'e')
				end = &in[i];
			rowMaze.push_back(&in[i]);
		}
	}
	if (!rowMaze.empty())
		maze.push_back(rowMaze);

	//put this maze in the graph
	for (int row = 0; row < maze.size(); row++)
	{
		for (int col = 0; col < maze[row].size(); col++)
		{
			mazeBoard.addVertex(maze[row][col]);

			//2 cases in each direction: out of bounds or in bounds check
			//check up
			if (row == 0) // out-of-bounds
			{
				//todo: something or nothing
			}
			else //we good
			{
				//just to ensure that the top row has the same number of cols as this row
				if (col < maze[row - 1].size() && *maze[row - 1][col] != '#')
					mazeBoard.addBasicEdge(maze[row - 1][col], maze[row][col]);
			}

			//check left
			if (col == 0) // out-of-bounds
			{
				//todo: something or nothing
			}
			else //we good
			{
				if (*maze[row][col - 1] != '#')
					mazeBoard.addBasicEdge(maze[row][col - 1], maze[row][col]);

			}
		}
	}
	//ensure that we don't read from nullptr
	if (start != nullptr && end != nullptr)
		mazeBoard.shortestPath(start, end);
	else
		cout << "something is nullptr" << endl;

	//since we passed the address of the characters in the sting
	//we can just write the original string to the file, because its contents
	//have been modified indirectly, producing the final maze
	writeMaze << in;

	//cleanup
	readMaze.close();
	writeMaze.close();
}