#pragma once

#include <string>
class Vertex
{

private:
   std::string m_description;

public:
   Vertex(std::string desc) : m_description(desc) {}

   std::string getDescription() const { return m_description; };

};

