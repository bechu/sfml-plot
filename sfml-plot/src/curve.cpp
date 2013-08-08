#include <limits>
#include <cmath>

#include "curve.h"

namespace sf
{
namespace plot
{

Curve::Curve(const sf::Vector2i &size) : size_(size)
{
    Color(sf::Color(19, 13, 200));
}

void Curve::Plot(float x, float y)
{
  line_.push_back(sf::Vertex(sf::Vector2f(x*size_.x, y*size_.y), sf::Color(200, 0, 0)));
}

void Curve::Plot(float value)
{
  data_.push_back(value);
  if(data_.size() > 100)
  {
    data_.pop_front();
  }
}

void Curve::Compute(float &min, float &max)
{
  if(data_.size() > 4)
  {
    // calculate the min and max for the inputs value
    max = std::numeric_limits<double>::min();
    min = std::numeric_limits<double>::max();
    for(std::list<float>::iterator it=data_.begin();it!=data_.end();++it)
    {
      if(*it > max)
        max = *it;
      if(*it < min)
        min = *it;
    }

    line_.clear();
    float distance = fabs(max-min);
    if(distance == 0) distance = 1;


    int xoffset = size_.x / (data_.size());

    while(xoffset * data_.size() < size_.x+xoffset)
      xoffset++;

    int i = 0;
    float x = 0;
    for(std::list<float>::reverse_iterator it=data_.rbegin();it!=data_.rend();++it)
    {
      x = size_.x - (i++ * xoffset);
      float y = size_.y - ((*it-min) / distance * size_.y);
      if(x < 0)
      {
        // normally with have to calcule the real value of y
        line_.push_back(sf::Vertex(sf::Vector2f(0, y), color_));
        break;
      }
      else
      {
        line_.push_back(sf::Vertex(sf::Vector2f(x, y), color_));
      }
    }
  }
}

void Curve::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  states.transform *= getTransform();
  std::vector<sf::Vertex> vertices;
  for(std::vector<sf::Vertex>::const_iterator it=line_.begin();it!=line_.end();++it)
  {
    vertices.push_back(sf::Vertex(it->position, fillColor_));
    vertices.push_back(sf::Vertex(sf::Vector2f(it->position.x, size_.y), fillColor_));
  }
  target.draw(&vertices[0], vertices.size(), sf::TrianglesStrip, states);
  target.draw(&line_[0], line_.size(), sf::LinesStrip, states);
}

}
}
