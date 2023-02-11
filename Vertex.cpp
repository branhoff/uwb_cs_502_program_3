#include "Vertex.h"


Vertex::Vertex() {
   m_description = "";
   m_cost = 0;
}

Vertex::Vertex(std::string desc) : m_description(desc) {
   m_description = desc;
   m_cost = 0;
}

std::string Vertex::getDescription() const { return m_description; };

int Vertex::getCost() const { return m_cost; }

void Vertex::setCost(int value) { m_cost = value; }