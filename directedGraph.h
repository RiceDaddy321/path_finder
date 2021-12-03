#pragma once
#include <string>
#include <vector>
#include <map> //binary search tree (balanced)
#include <queue>
using namespace std;

class directedGraph
{
	//protected is like private, but it allows inherited classes access
protected:
	class vertex
	{
	public:
		char* data;
		vector<vertex*> neighbors;

		//Variables for BFS
		bool marked;
		vertex* breadcrumb;

		vertex(char* x)
		{
			data = x;

			marked = false;
			breadcrumb = nullptr;
		}
	};

	//Now it's a balanced binary search tree
	map<char*, vertex*> vertexSet;

	//O(n) time.
	void clearData()
	{
		for (auto x : vertexSet)
		{
			x.second->marked = false;
			x.second->breadcrumb = nullptr;
		}
	}

	//Do a BFS from source vertex s
	void breadthFirstSearch(vertex* s)
	{
		//Step -1: setup
		queue<vertex*> Q;
		clearData(); //initialize marked and breadcrumbs

					 //Step 0: mark s, put s into a Q
		s->marked = true;
		Q.push(s);

		//Step 1: BFS loop
		while (!Q.empty())
		{
			//Step 1.1 get item from Q
			vertex* x = Q.front();
			Q.pop();

			//Step 1.2: visit all of x's
			//unmarked neighbors
			for (int i = 0; i<x->neighbors.size(); i++)
			{
				vertex* y = x->neighbors[i];
				if (!y->marked)
				{
					y->marked = true;
					Q.push(y);
					y->breadcrumb = x;
				}
			}
		}

	}

public:

	//Return shortest path from a to b
	void shortestPath(char* a, char* b)
	{
		//Get vertices of the given values
		vertex* aVert = vertexSet[a];
		vertex* bVert = vertexSet[b];

		//Call BFS to compute bread crumbs
		breadthFirstSearch(aVert);

		//check if the path exists
		if (bVert->breadcrumb == nullptr)
			return;//do nothing

		//Trace bread-crumb trail back from b to a
		//to get shortest path
		vertex* current = bVert->breadcrumb;
		while (current != aVert)
		{
			*(current->data) = '.';
			current = current->breadcrumb;
		}
	}

	//Add a new vertex x to the graph: O(log |V|)
	void addVertex(char* x)
	{
		//Create a new vertex
		vertex* babyVertex = new vertex(x);

		//Add the baby vertex to the vertex set
		//vertexSet.push_back(babyVertex);
		//Run time: O(log n)
		vertexSet[x] = babyVertex;
	}

	//Add edge going from a to b: O(log |V|)
	void addDirectedEdge(char* a, char* b)
	{
		//Find the vertices that hold a and b: O(log n)
		vertex* aVert = vertexSet[a];
		vertex* bVert = vertexSet[b];

		//Push b's vertex into a's neighbor list: O(1) time
		aVert->neighbors.push_back(bVert);
	}

	//Add a bidirectional edge connecting a and b.
	void addBasicEdge(char* a, char* b)
	{
		addDirectedEdge(a, b);
		addDirectedEdge(b, a);
	}


};