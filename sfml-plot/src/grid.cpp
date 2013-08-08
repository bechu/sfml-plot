#include "grid.h"

namespace sf
{
namespace plot
{

Grid::Grid()
{
  color_ = sf::Color(150, 150, 150);
}

void Grid::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  states.transform *= getTransform();
  target.draw(&vertices_[0], vertices_.size(), sf::Lines, states);

  sf::RectangleShape rectangle(sf::Vector2f(size_.x, size_.y));
  rectangle.setFillColor(sf::Color(0, 0, 0, 0));
  rectangle.setOutlineColor(sf::Color(0, 0, 0));
  rectangle.setOutlineThickness(1);
  target.draw(rectangle, states);
}

void Grid::CreateGrid(const sf::Vector2f &size)
{
  size_ = size;
  vertices_.clear();

  float offset = size_.y / kPart;
  for(int i=1;i<kPart;i++)
  {
    vertices_.push_back(sf::Vertex(sf::Vector2f(0, i*offset), color_));
    vertices_.push_back(sf::Vertex(sf::Vector2f(size_.x, i*offset), color_));
  }

  offset = size_.x / kPart;
  for(int i=1;i<kPart;i++)
  {
    vertices_.push_back(sf::Vertex(sf::Vector2f(i*offset, 0), color_));
    vertices_.push_back(sf::Vertex(sf::Vector2f(i*offset, size_.y), color_));
  }
}

}
}
