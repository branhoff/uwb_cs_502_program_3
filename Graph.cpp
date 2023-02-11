#include <fstream>
#include <iostream>
#include <queue>

#include "Graph.h"

using namespace std;

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

void Graph::printVertices() {
   for (int i = 1; i <= size; i++) {
      cout << "Vertex " << i << ": " << vertices[i].data->getDescription() << endl;
   }
}

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
   for (int source = 1; source <= size; source++)
   {
      T[source][source].dist = 0;
      T[source][source].visited = true;

      for (int n = 1; n <= size; n++) // find neighbor nodes
      {
         if (C[source][n] != INT_MAX)
         {
            T[source][n].dist = C[source][n];
            T[source][n].path = source;
         }
      }

      int v = 0;  // smallest vertex

      do  // find smallest weight
      {
         int min = INT_MAX;
         v = 0;

         for (int n = 1; n <= size; n++) // find closest child and continue search
         {
            if (!T[source][n].visited && (C[source][n] < min))
            {
               min = C[source][n];
               v = n;
            }
         }

         if (v == 0)
         {
            break;  // end loop
         }

         T[source][v].visited = true;  // node visited

         for (int w = 1; w <= size; ++w)
         {
            if (T[source][w].visited)
            {
               continue;
            }

            if (C[v][w] == INT_MAX)
            {
               continue;
            }

            if (v == w)
            {
               continue;
            }

            if (T[source][w].dist > T[source][v].dist + C[v][w])
            {
               T[source][w].dist = T[source][v].dist + C[v][w];
               T[source][w].path = v;
            }
         }
      }

      while (v != 0); // end loop
   }
}

void Graph::displayAll() {
   cout << "Shortest paths between all vertices:" << endl;
   for (int i = 1; i <= size; i++) {
      for (int j = 1; j <= size; j++) {
         cout << T[i][j].dist << "\t";
         cout << T[i][j].path << "\t";
         cout << T[i][j].visited << "\t";
      }
      cout << endl;
   }
}

