#include <cmath>
#include <limits>

#include "curve.h"

namespace sf
{
namespace plot
{

Curve::Curve(const Vector2f &size) : size_(size)
{
  setColor(sf::Color(19, 13, 200));
}

void Curve::addValue(float value)
{
  data_.push_back(value);
  if(data_.size() > 100)
  {
    data_.pop_front();
  }
}

void Curve::build(sf::Vector2f &rangex, sf::Vector2f &rangey)
{
  rangex.x = 0;
  rangex.y = data_.size();

  if(data_.size() > 1)
  {
    if(rangey.x == std::numeric_limits<float>::max())
    {
      rangey.x = data_.front();
    }
    if(rangey.y == std::numeric_limits<float>::min())
    {
      rangey.y = data_.front();
    }
    // calculate the min and max for the inputs value
    for(std::list<float>::iterator it=data_.begin();it!=data_.end();++it)
    {
      // min
      if(*it < rangey.x)
      {
        rangey.x = *it;
      }
      // max
      if(float(*it) > float(rangey.y))
      {
        rangey.y = *it;
      }
    }

    line_.clear();
    float distance = fabs(rangey.y-rangey.x);
    if(distance == 0) distance = 1;

    int xoffset = size_.x / (data_.size());

    while(xoffset * data_.size() < (size_.x+xoffset))
      xoffset++;

    int i = 0;
    float x = 0;
    for(std::list<float>::reverse_iterator it=data_.rbegin();it!=data_.rend();++it)
    {
      x = size_.x - (i++ * xoffset);
      float realy = (*it - rangey.x) / distance;
      float y = size_.y - size_.y * realy;
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
