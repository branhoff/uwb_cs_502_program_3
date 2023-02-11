#pragma once

#include <string>
class Vertex
{

private:
   std::string m_description;
   int m_cost;

public:
   Vertex();
   Vertex(std::string desc);

   std::string getDescription() const;

   int getCost() const;

   void setCost(int value);

};

