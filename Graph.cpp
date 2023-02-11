#include <fstream>
#include <iostream>

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
         vertices[v].data = new Vertex(description);
         //infile >> *vertices[v].data;
      }
   // fill cost edge array
   /*int src = 1, dest = 1, weight = 1;
   for (;;) {
      infile >> src >> dest >> weight;
      if (src == 0 || infile.eof())
         break;
      insertEdge(src, dest, weight);
   }*/
}

void Graph::printVertices() {
   for (int i = 1; i <= size; i++) {
      cout << "Vertex " << i << ": " << vertices[i].data->getDescription() << endl;
   }
}

void Graph::insertEdge(int src, int dest, int weight) {
   EdgeNode* currentEdge = vertices[src].edgeHead;
   EdgeNode* previousEdge = nullptr;

   while (currentEdge != nullptr && currentEdge->adjVertex != dest) {
      previousEdge = currentEdge;
      currentEdge = currentEdge->nextEdge;
   }

   if (currentEdge != nullptr) {
      currentEdge->weight = weight;
      return;
   }

   EdgeNode* newEdge = new EdgeNode;
   newEdge->adjVertex = dest;
   newEdge->weight = weight;
   newEdge->nextEdge = nullptr;
   if (previousEdge == nullptr) {
      vertices[src].edgeHead = newEdge;
      cout << "Created new edge from vertex " << src << " to vertex " << dest << endl;
   }
   else {
      previousEdge->nextEdge = newEdge;
      cout << "Inserted edge from vertex " << src << " to vertex " << dest << endl;
   }
   // Debug check
   if (vertices[src].edgeHead->nextEdge != vertices[src].edgeHead) {
      cout << "Error: nextEdge not set correctly." << endl;
   }

}