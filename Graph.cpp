#include <fstream>
#include <iostream>
#include <queue>
#include <iomanip>

#include "Graph.h"

using namespace std;

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
Graph::Graph()
{
   for (int v = 1; v < MAX_VERTICES; v++)
   {
      vertices[v].data = nullptr;
      vertices[v].edgeHead = nullptr;
   }

   for (int i = 0; i < MAX_VERTICES; i++)
   {
      for (int j = 0; j < MAX_VERTICES; j++)
      {
         T[i][j].dist = INT_MAX;
         T[i][j].visited = false;
         T[i][j].path = -1;
         C[i][j] = 0;
      }
   }
   size = 0;
}

//------------------------------ Graph(const Graph& g) ------------------------------
// Constructs a copy of a graph object
// Preconditions: The graph object g is initialized
// Postconditions: A new graph object is created with the same values as the original graph object g
Graph::Graph(const Graph& g) : Graph()
{
   copy(g);
}

//---------------------------------- ~Graph -----------------------------------
// Destructor for the Graph class
// Preconditions:  Graph object has been created
// Postconditions: Graph object's memory is deallocated and its resources are freed
Graph::~Graph()
{
   clear();
}

//------------------------------- operator= ----------------------------------
// Overloads the assignment operator to copy one graph to another graph object
// Preconditions:  The graph object must be properly initialized.
// Postconditions: The graph object is copied from the input graph object, including
//                 all vertices and edges. The previous data in the graph object is deleted.
Graph& Graph::operator=(const Graph& g)
{
   if (this == &g) // check self-assignment
      return *this;

   clear();
   copy(g);

   return *this;
}

//-------------------------------- buildGraph ---------------------------------
// Builds a graph by reading data from an ifstream
// Preconditions:  infile has been successfully opened and the file contains
//                 properly formated data (according to the program specs)
// Postconditions: One graph is read from infile and stored in the object
void Graph::buildGraph(ifstream& infile) {
   string description;

   infile >> size;                          // data member stores array size
   if (infile.eof())
      return;
   infile.ignore();                         // throw away '\n' to go to next line
      // get descriptions of vertices
      for (int v = 1; v <= size; v++) {
         getline(infile, description);
         vertices[v].edgeHead = nullptr;
         vertices[v].data = new Vertex(description);
         //infile >> *vertices[v].data;
      }
   // fill cost edge array
   int src = 1, dest = 1, weight = 1;
   for (;;) {
      infile >> src >> dest >> weight;
      if (src == 0 || infile.eof())
         break;
      insertEdge(src, dest, weight);
   }
}

//-------------------------------- printVertices ---------------------------------
// Prints the vertices in the graph
// Preconditions:  Graph object is initialized with vertices
// Postconditions: The description of each vertex in the graph is printed to the console

void Graph::printVertices() {
   for (int i = 1; i <= size; i++) {
      cout << "Vertex " << i << ": " << vertices[i].data->getDescription() << endl;
   }
}

//-------------------------------- insertEdge ---------------------------------
// Inserts an edge between two vertices of the graph
// Preconditions:  The graph has been initialized with vertices, and `src` and `dest` are valid vertices in the graph.
// Postconditions: An edge is inserted between the vertices `src` and `dest` with a weight of `weight`.
void Graph::insertEdge(int src, int dest, int weight) {
   EdgeNode* currentEdge = vertices[src].edgeHead;
   EdgeNode* previousEdge = nullptr;

   // check if dst exists

   while (currentEdge != nullptr ) {
      if (currentEdge->adjVertex == dest) {
         // replace weight
         currentEdge->weight = weight;
         return;
      }
      previousEdge = currentEdge;
      currentEdge = currentEdge->nextEdge;
   }

   EdgeNode* newEdge = new EdgeNode;
   newEdge->adjVertex = dest;
   newEdge->weight = weight;

   if (previousEdge == nullptr) { // update head
      newEdge->nextEdge = vertices[src].edgeHead;
      vertices[src].edgeHead = newEdge;
      return;
   }

   previousEdge->nextEdge = newEdge;
   newEdge->nextEdge = nullptr;   
}

//------------------------------- printEdges -------------------------------
// Prints all of the edges in the graph.
// Preconditions: The graph must be initialized with vertices and edges.
// Postconditions: All of the edges in the graph are printed to the console.
void Graph::printEdges() {
   for (int i = 1; i <= size; i++) {
      EdgeNode* currentEdge = vertices[i].edgeHead;
      while (currentEdge != nullptr) {
         cout << i << " -> " << currentEdge->adjVertex
            << " with weight " << currentEdge->weight << endl;
         currentEdge = currentEdge->nextEdge;
      }
   }
}

//-------------------------------- findShortestPath ----------------------------
// Calculates and stores the shortest path from the starting vertex to all other 
// vertices in the graph, using the Dijkstra's algorithm. 
// Precondition: The graph must be initialized with vertices and edges.
// Postcondition: The shortest path is stored in a 2D table T[MAX_VERTICES][MAX_VERTICES], 
//                where T[i][j] represents the cost of the shortest path from vertex i to vertex j.
void Graph::findShortestPath()
{
   for (int i = 1; i <= size; i++)
   {
      for (int j = 1; j <= size; j++)
      {
         T[i][j].dist = INT_MAX;
         T[i][j].visited = false;
         T[i][j].path = -1;        
      }

      T[i][i].dist = 0;
      

      int v = 0;  // smallest vertex

      while (true) 
      {
         v = -1;

         int min_dist = INT_MAX;
         
          // pick the vertex with the smallest distance in visited node
         for (int j = 1; j <= size; j++)
         {
            if (T[i][j].visited == false )
            {
               if (T[i][j].dist < min_dist)
               {
                  min_dist = T[i][j].dist;
                  v = j;
               }
            }
         }

         if (v < 0) {
            break;
         }

         
         T[i][v].visited = true;

         // iterate the adjus
         VertexNode node = vertices[v];
         EdgeNode* curr = node.edgeHead;

         while (curr != nullptr)
         {
            int u = curr->adjVertex;
            int weight = curr->weight;

            if (T[i][v].dist + weight < T[i][u].dist && !T[i][u].visited)
            {
               T[i][u].dist = T[i][v].dist + weight;
               T[i][u].path = v;               
            }            

            curr = curr->nextEdge;
         }

      }
     
   }
}

void Graph::displayAll() {
   cout << "Shortest paths between all vertices:" << endl;
   cout << setw(30) << left << "Description" << setw(6) << left << "From" << setw(6) << left << "To" << setw(6) << left << "Dist" << "Path" << endl;
   for (int i = 1; i <= size; i++) {
      cout << vertices[i].data->getDescription() << endl;
      for (int j = 1; j <= size; j++)
      {
         if (i == j)
            continue;

         cout << setw(30) << left << "" << setw(6) << left << i << setw(6) << left << j;
         if (T[i][j].visited)
         {
            cout << setw(6) << left << T[i][j].dist;
            // generate path
            string path = calcPath(i, j);
          
            cout << path;
         }
         else
         {
            cout << setw(6) << left << "--";
         }

         cout << endl;
      }    
   }
}

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
void Graph::display(int src, int dst)
{
   cout << setw(6) << left << src << setw(6) << left << dst;
   if (T[src][dst].visited)
   {
      cout << setw(6) << left << T[src][dst].dist;

      string path = calcPath(src, dst);
      string visited_vertices = getVerticesName(src, dst);

      cout << path;
      cout << endl;
      cout << visited_vertices;
      cout << endl;
   }
   else
   {
      cout << setw(6) << left << "--";
      cout << endl;
   }
}

//-------------------------------- calcPath ---------------------------------
// Helper method to get the path from the source vertex to the destination vertex
// Preconditions: The graph must be initialized with vertices and edges, and the 
//                `findShortestPath` method must have been executed.
// Postconditions: Returns a string representation of the path from the source vertex 
//                 to the destination vertex, represented as a sequence of vertex IDs separated by spaces.
string Graph::calcPath(int src, int dst)
{
   if (T[src][dst].path < 0)
      return to_string(dst);

   return calcPath(src, T[src][dst].path) + " " + to_string(dst);
}

//-------------------------------- getVerticesName ------------------------------
// Returns the description of a path from a source vertex to a destination vertex
// Preconditions: The `findShortestPath` method has been successfully executed, 
//                and the shortest paths are stored in the table T[MAX_VERTICES][MAX_VERTICES].
//                The vertices have descriptions.
// Postconditions: The method returns the description of the shortest path from 
//                 the source vertex to the destination vertex.

string Graph::getVerticesName(int src, int dst)
{
   string desc = vertices[dst].data->getDescription();
   if (T[src][dst].path < 0)
      return desc;

   return getVerticesName(src, T[src][dst].path) + "\n" + desc;
}

//-------------------------------- clear ---------------------------------
// Clears the graph of all vertices and edges
// Preconditions:  The graph object must be initialized
// Postconditions: The graph object will be cleared of all vertices and edges, and its size will be reset to 0. All dynamically allocated memory will be freed.
void Graph::clear()
{
   for (int v = 1; v <= size; v++)
   {
      if (vertices[v].data != nullptr)
      {
         delete vertices[v].data;
         vertices[v].data = nullptr;
      }

      if (vertices[v].edgeHead != nullptr)
      {
         EdgeNode* curr = vertices[v].edgeHead;

         while (curr != nullptr)
         {
            EdgeNode* next = curr->nextEdge;
            delete curr;
            curr = next;
         }

         vertices[v].edgeHead = nullptr;
      }
   }
   size = 0;
}

// --------------------------------copy-------------------------------- -
// Copies the data from a given Graph object into the current Graph object.
// Preconditions: The input Graph object must be properly initialized with vertices and edges.
// Postconditions: The current Graph object is initialized with the same vertices and edges as the input Graph object.
void Graph::copy(const Graph& g)
{
   // copy vertices data
   size = g.size;
   for (int v = 1; v <= g.size; v++)
   {
      if (g.vertices[v].data != nullptr)
      {
         vertices[v].data = new Vertex(g.vertices[v].data->getDescription());
         vertices[v].data->setCost(g.vertices[v].data->getCost());
      }
   }

   // copy edges data
   for (int v = 1; v < g.size; v++)
   {
      EdgeNode* currg = g.vertices[v].edgeHead;
      EdgeNode* curr = nullptr;

      while (currg != nullptr)
      {
         EdgeNode* newEdge = new EdgeNode;
         newEdge->adjVertex = currg->adjVertex;
         newEdge->weight = currg->weight;
         newEdge->nextEdge = nullptr;

         if (curr == nullptr)
         {
            // create head
            vertices[v].edgeHead = newEdge;
         }
         else
         {
            curr->nextEdge = newEdge;
         }
         curr = newEdge;

         currg = currg->nextEdge;
      }
   }
}