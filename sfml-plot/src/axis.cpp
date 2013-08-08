#include <sstream>
#include <cmath>

#include "axis.h"

namespace sf
{
namespace plot
{

Axis::Axis() : font_(0)
{
}

void Axis::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  if(!font_) return ;
  states.transform *= getTransform();
  for(std::vector<sf::Text>::const_iterator it=numbers_.begin();it!=numbers_.end();++it)
    target.draw(*it, states);
  target.draw(label_, states);
}

void Axis::build(const Vector2f &range)
{
  if(!font_) return ;
  numbers_.clear();

  double distance = fabs(range.y-range.x);
  if(distance == 0) distance = 1;

  float decx = size_ / kPart;

  double offset = distance / kPart;
  for(int i=0;i<=kPart;i++)
  {
    sf::Text text;
    text.setFont(*font_);
    text.setCharacterSize(16);
    text.setColor(sf::Color::Black);
    text.setPosition(i*decx, 0);
    std::stringstream ss;
    ss << range.x + offset * i;
    text.setString(ss.str());
    numbers_.push_back(text);
  }
}

void Axis::defineLabel()
{
  if(!font_) return ;
  label_.setFont(*font_);
  label_.setCharacterSize(16);
  label_.setColor(sf::Color::Black);
  label_.setString(name_);

  if(getRotation() != 0)
    label_.setPosition(size_/2-name_.size()*5, -20);
  else
    label_.setPosition(size_/2-name_.size()*5, 20);
}

}
}
