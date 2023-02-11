// -------------------------------------------------------------------------- -
// HW3.CPP
// Driver code for testing the Graph class.
// Authors:  Clark Olson and Carol Zander
//---------------------------------------------------------------------------
// This code tests the basic functionality of the class to
// perform Dijkstra's algorithm for CSS 502 Program 3.
// It is not meant to exhaustively test the class.
//
// Assumptions:
//   -- a text file named "HW3.txt" exists in the same directory
//      as the code and is formatted as described in the specifications
//---------------------------------------------------------------------------
#include <iostream>
#include <fstream>
#include "Graph.h"
using namespace std;
//-------------------------- main -------------------------------------------
// Tests the Graph class by reading data from "HW3.txt" 
// Preconditions:   If lab3.txt file exists, it must be formatted
//                  as described in the lab specifications.
// Postconditions:  The basic functionalities of the Graph class 
//                  are used.  Should compile, run to completion, and output  
//                  correct answers if the classes are implemented correctly.
int main() {
   ifstream infile1("HW3.txt");
   if (!infile1) {
      cerr << "File could not be opened." << endl;
      return 1;
   }

   cout << "-----Testing Build Graph From File----" << endl;
   Graph G;
   G.buildGraph(infile1);
   G.printVertices();
   G.printEdges();
   G.findShortestPath();
   G.displayAll();
   G.display(2, 3);


   cout << endl << "-----Testing Copy Constructor----" << endl;
   Graph G1(G);
   G1.printVertices();
   G1.printEdges();
   G1.findShortestPath();
   G1.displayAll();
   G1.display(2, 3);

   cout << endl << "-----Testing Assign Operator----" << endl;
   Graph G2;
   G2 = G;
   G2.printVertices();
   G2.printEdges();
   G2.findShortestPath();
   G2.displayAll();
   G2.display(2, 3);

   cout << endl << "-----Testing Assign Operator with Self Assignment----" << endl;   
   G2 = G2;
   G2.printVertices();
   G2.printEdges();
   G2.findShortestPath();
   G2.displayAll();
   G2.display(2, 3);



   //for each graph, find the shortest path from every node to all other nodes
   //for (;;) {
   //   Graph G;
   //   G.buildGraph(infile1);       // see supplied code
   //   if (infile1.eof())
   //      break;
   //   G.findShortestPath();
   //   G.displayAll();              // display shortest distances, path to cout
   //   cout << endl << "The path from vertex 2 to vertex 3 is:" << endl;
   //   G.display(2, 3);             // display path from node 2 to node 3 to cout
   //   cout << endl;
   // }
   return 0;
}
