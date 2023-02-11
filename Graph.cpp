#include <fstream>
#include <iostream>
#include <queue>
#include <iomanip>

#include "Graph.h"

using namespace std;

Graph::Graph()
{
   for (int v = 1; v < MAX_VERTICES; v++)
   {
      vertices[v].data = nullptr;
      vertices[v].edgeHead = nullptr;
   }
}

Graph::~Graph()
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

string Graph::calcPath(int src, int dst)
{
   if (T[src][dst].path < 0)
      return to_string(dst);

   return calcPath(src, T[src][dst].path) + " " + to_string(dst);
}

string Graph::getVerticesName(int src, int dst)
{
   string desc = vertices[dst].data->getDescription();
   if (T[src][dst].path < 0)
      return desc;

   return getVerticesName(src, T[src][dst].path) + "\n" + desc;
}