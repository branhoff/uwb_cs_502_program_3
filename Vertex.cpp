//------------------------------------------------------------
// VERTEX.CPP
// Implementation of the Vertex class
// Author: [Your Name]
//------------------------------------------------------------
// Vertex class:
//   Implements the properties and methods of a Vertex in a graph.
//   Using the following methods:
//      Vertex - default constructor that initializes properties
//      Vertex - constructor that takes a description as an argument
//      ~Vertex - destructor
//      getDescription - returns the description of the Vertex
//      setDescription - sets the description of the Vertex
//      getCost - returns the cost of the Vertex
//      setCost - sets the cost of the Vertex
//   Assumptions:
//      - The input string for the Vertex constructor and setDescription method should not be empty
//      - The cost value should be a non-negative integer
//------------------------------------------------------------

#include "Vertex.h"
#include <iostream>

//-------------------------------- Vertex ---------------------------------
// Constructor for Vertex class
// Preconditions: None
// Postconditions: A new Vertex object is created with empty description and cost set to 0.
Vertex::Vertex() {
   m_description = "";
   m_cost = 0;
}

//-------------------------------- Vertex ---------------------------------
// Constructs a vertex with a description
// Preconditions: None
// Postconditions: A vertex is created with the given description and cost initialized to 0.
Vertex::Vertex(std::string desc) : m_description(desc) {
   m_description = desc;
   m_cost = 0;
}

//------------------------------ getDescription -------------------------------
// Returns the description of the Vertex object
// Preconditions:  None
// Postconditions: The description of the Vertex object is returned
std::string Vertex::getDescription() const { return m_description; };

//----------------------------- setDescription -------------------------------
// Sets the description of a Vertex object
// Preconditions:  desc is a valid string
// Postconditions: The description of the Vertex object has been set to desc
void Vertex::setDescription(std::string desc) {
   m_description = desc;
}

//-------------------------------- getCost ---------------------------------
// Returns the cost of a Vertex
// Preconditions:  None
// Postconditions: Returns the cost of the Vertex object
int Vertex::getCost() const { return m_cost; }

//-------------------------------- setCost ---------------------------------
// Sets the cost of a vertex
// Preconditions:  none
// Postconditions: The cost of the vertex is set to the value passed in.
void Vertex::setCost(int value) { m_cost = value; }

//-------------------------------- operator>> ---------------------------------
// Overloads the >> operator to extract data from an istream into a Vertex object
// Preconditions:  istream is in a valid state and contains properly formatted data
// Postconditions: Vertex object is populated with data extracted from the istream
std::ostream& operator<<(std::ostream& out, const Vertex& v) {
   out << v.getDescription() << " (cost: " << v.getCost() << ")";
   return out;
}

//------------------------------- operator>> ---------------------------------
// Reads data from an istream into a Vertex object
// Preconditions:  istream is successfully opened and contains properly formatted
//                 data (according to the program specs)
// Postconditions: Data is read from istream into the Vertex object and stored
std::istream& operator>> (std::istream& in, Vertex& v) {
   std::string desc;
   std::getline(in, desc);
   v.setDescription(desc);
   return in;
}