//--------------------------------------------------------------------
// GRAPH.H
// Declaration and definition of the Graph class
// Author: [Your Name]
//--------------------------------------------------------------------
// Graph class:
//   Implements a graph data structure and various graph algorithms
//   using the following methods:
//      Graph - constructor that initializes an empty graph
//      ~Graph - destructor that deallocates memory used by the graph
//      insertEdge - adds an edge to the graph
//      removeEdge - removes an edge from the graph
//      printEdges - displays all edges in the graph
//      printVertices - displays all vertices in the graph
//      displayAll - displays the shortest path between all vertices in the graph
//   Assumptions:
//      - The insertEdge method assumes that the src and dst vertex numbers are valid
//      - The removeEdge method assumes that the edge to be removed exists in the graph
//      - The input to the displayAll method should result in a connected graph
//--------------------------------------------------------------------

#pragma once
#include <fstream>
#include "Vertex.h"

using namespace std;

class Graph {
public:
   //--------------------------------- Graph -------------------------------------
   // Graph constructor
   // Preconditions: None
   // Postconditions: A graph object is created and initialized with the following:
   //    - All vertices set to nullptr
   //    - All edges set to nullptr
   //    - T[i][j].dist set to INT_MAX for all i and j
   //    - T[i][j].visited set to false for all i and j
   //    - T[i][j].path set to -1 for all i and j
   //    - C[i][j] set to 0 for all i and j
   //    - size set to 0
   Graph(); // constructor

   //------------------------------ Graph(const Graph& g) ------------------------------
   // Constructs a copy of a graph object
   // Preconditions: The graph object g is initialized
   // Postconditions: A new graph object is created with the same values as the original graph object g
   Graph(const Graph& g); // copy constructor

   //---------------------------------- ~Graph -----------------------------------
   // Destructor for the Graph class
   // Preconditions:  Graph object has been created
   // Postconditions: Graph object's memory is deallocated and its resources are freed
   ~Graph(); // destructor

   //------------------------------- operator= ----------------------------------
   // Overloads the assignment operator to copy one graph to another graph object
   // Preconditions:  The graph object must be properly initialized.
   // Postconditions: The graph object is copied from the input graph object, including
   //                 all vertices and edges. The previous data in the graph object is deleted.
   Graph& operator=(const Graph& g); // assign operator

   //-------------------------------- buildGraph ---------------------------------
   // Builds a graph by reading data from an ifstream
   // Preconditions:  infile has been successfully opened and the file contains
   //                 properly formated data (according to the program specs)
   // Postconditions: One graph is read from infile and stored in the object
   void buildGraph(ifstream& infile);

   //-------------------------------- printVertices ---------------------------------
   // Prints the vertices in the graph
   // Preconditions:  Graph object is initialized with vertices
   // Postconditions: The description of each vertex in the graph is printed to the console
   void printVertices();

   //------------------------------- printEdges -------------------------------
   // Prints all of the edges in the graph.
   // Preconditions: The graph must be initialized with vertices and edges.
   // Postconditions: All of the edges in the graph are printed to the console.
   void printEdges();

   //-------------------------------- findShortestPath ----------------------------
   // Calculates and stores the shortest path from the starting vertex to all other 
   // vertices in the graph, using the Dijkstra's algorithm. 
   // Precondition: The graph must be initialized with vertices and edges.
   // Postcondition: The shortest path is stored in a 2D table T[MAX_VERTICES][MAX_VERTICES], 
   //                where T[i][j] represents the cost of the shortest path from vertex i to vertex j.
   void findShortestPath();

   //------------------------------- displayAll -------------------------------
   // Displays the shortest paths between all vertices in the graph
   // Preconditions:  The graph is not empty and the T matrix has been populated
   //                 with the shortest path data
   // Postconditions: The shortest paths between all vertices in the graph have
   //                 been displayed on the console
   void displayAll();

   //------------------------------- display -----------------------------------
   // Displays the shortest path from the source vertex to the destination vertex
   // Preconditions: The `findShortestPath` method has been called and the shortest
   //                path from the source vertex to the destination vertex has been
   //                calculated and stored in the 2D table T[][].
   //                The `src` and `dst` parameters represent the source and
   //                destination vertices, respectively.
   // Postconditions: The shortest path from the source vertex to the destination
   //                 vertex, including the total cost and the list of vertices
   //                 visited along the way, is displayed on the console.
   void display(int src, int dst);

   //-------------------------------- insertEdge ---------------------------------
   // Inserts an edge between two vertices of the graph
   // Preconditions:  The graph has been initialized with vertices, and `src` and `dest` are valid vertices in the graph.
   // Postconditions: An edge is inserted between the vertices `src` and `dest` with a weight of `weight`.
   void insertEdge(int src, int dest, int weight);

   //-------------------------------- removeEdge ---------------------------------
   // Removes an edge from the graph
   // Preconditions:  src and dst vertices must exist in the graph
   //                 and have an edge between them
   // Postconditions: The edge between src and dst vertices is removed from the graph
   void removeEdge(int src, int dest);

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

   //-------------------------------- calcPath ---------------------------------
   // Helper method to get the path from the source vertex to the destination vertex
   // Preconditions: The graph must be initialized with vertices and edges, and the 
   //                `findShortestPath` method must have been executed.
   // Postconditions: Returns a string representation of the path from the source vertex 
   //                 to the destination vertex, represented as a sequence of vertex IDs separated by spaces.
   string calcPath(int src, int dst);

   //-------------------------------- getVerticesName ------------------------------
   // Returns the description of a path from a source vertex to a destination vertex
   // Preconditions: The `findShortestPath` method has been successfully executed, 
   //                and the shortest paths are stored in the table T[MAX_VERTICES][MAX_VERTICES].
   //                The vertices have descriptions.
   // Postconditions: The method returns the description of the shortest path from 
   //                 the source vertex to the destination vertex.
   string getVerticesName(int src, int dst);

   //-------------------------------- clear ---------------------------------
   // Clears the graph of all vertices and edges
   // Preconditions:  The graph object must be initialized
   // Postconditions: The graph object will be cleared of all vertices and edges, and its size will be reset to 0. All dynamically allocated memory will be freed.
   void clear();

   // --------------------------------copy-------------------------------- -
   // Copies the data from a given Graph object into the current Graph object.
   // Preconditions: The input Graph object must be properly initialized with vertices and edges.
   // Postconditions: The current Graph object is initialized with the same vertices and edges as the input Graph object.
   void copy(const Graph& g);
};

