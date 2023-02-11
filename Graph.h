#pragma once
#include <fstream>
#include "Vertex.h"

using namespace std;

class Graph {
public:
   //-------------------------------- buildGraph ---------------------------------
   // Builds a graph by reading data from an ifstream
   // Preconditions:  infile has been successfully opened and the file contains
   //                 properly formated data (according to the program specs)
   // Postconditions: One graph is read from infile and stored in the object
   void buildGraph(ifstream& infile);

   void printVertices();

   void printEdges();

   //-------------------------------- findShortestPath ----------------------------
   // Calculates and stores the shortest path from the starting vertex to all other 
   // vertices in the graph, using the Dijkstra's algorithm. 
   // Precondition: The graph must be initialized with vertices and edges.
   // Postcondition: The shortest path is stored in a 2D table T[MAX_VERTICES][MAX_VERTICES], 
   //                where T[i][j] represents the cost of the shortest path from vertex i to vertex j.
   void findShortestPath();

private:
   static const int MAX_VERTICES = 101;

   struct EdgeNode { // can change to a class, if desired
      int adjVertex; // subscript of the adjacent vertex 
      int weight; // weight of edge
      EdgeNode* nextEdge;
   };

   struct VertexNode {
      EdgeNode* edgeHead; // head of the list of edges
      Vertex* data; // store vertex data here
   };

   void insertEdge(int src, int dest, int weight);

   // array of VertexNodes
   VertexNode vertices[MAX_VERTICES];
   // table of information for Dijkstra's algorithm
   struct Table {
      bool visited; // whether vertex has been visited
      int dist; // shortest known distance from source
      int path; // previous vertex in path of min dist
   };

   int size; // number of vertices in the graph
   Table T[MAX_VERTICES][MAX_VERTICES];
   // stores visited, distance, path -
   // two dimensional in order to solve
   // for all sources
};

