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

//void Graph::findShortestPath() {
//   for (int i = 1; i <= size; i++) {
//      vertices[i].data->setCost(INT_MAX);
//   }
//
//   vertices[1].data->setCost(0);
//
//   priority_queue<Vertex*, std::vector<Vertex*>, std::greater<Vertex*>> heap;
//   heap.push(vertices[1].data);
//
//   while (!heap.empty()) {
//      VertexNode* currentVertex = heap.top();
//      heap.pop();
//
//      int currentVertexIndex = currentVertex - vertices;
//      if (currentVertex->visited) continue;
//      currentVertex->visited = true;
//
//      for (EdgeNode* currentEdge = currentVertex->edgeHead; currentEdge != nullptr; currentEdge = currentEdge->nextEdge) {
//         int destIndex = currentEdge->adjVertex;
//         int newCost = currentVertex->cost + currentEdge->weight;
//         if (vertices[destIndex].cost > newCost) {
//            vertices[destIndex].cost = newCost;
//            heap.push(&vertices[destIndex]);
//         }
//      }
//   }
//}


