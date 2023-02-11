#pragma once

#include <string>
class Vertex
{

private:
   std::string m_description;
   int m_cost;

public:
   Vertex(std::string desc) : m_description(desc) {}

   std::string getDescription() const { return m_description; };

   int getCost() const { return m_cost; }

   void setCost(int value) { m_cost = value; }

   bool operator<(const Vertex& other) const {
      return m_cost < other.m_cost;
   }

};

