#include <limits>
#include "plot.h"

namespace sf
{
namespace plot
{

Plot::Plot(const Vector2f &size, const std::string &title) : title_(title)
{
  size_ = size;

  graphPos_.x = size_.x * (kLeftSize/100.0);
  graphPos_.y = size_.y * (kTopSize/100.0);

  graphSize_.x = size_.x - kBorderSize * 2
      - size_.x * (kLeftSize/100.0)
      - size_.x * (kRightSize/100.0);
  graphSize_.y = size_.y - kBorderSize * 2
      - size_.y * (kTopSize/100.0)
      - size_.y * (kBottomSize/100.0);

  grid_.CreateGrid(graphSize_);
  grid_.setPosition(graphPos_);

  xaxis_.setSize(graphSize_.x);
  yaxis_.setSize(graphSize_.y);

  xaxis_.setPosition(graphPos_.x, graphPos_.y+graphSize_.y+5);
  yaxis_.setPosition(graphPos_.x-20, graphPos_.y+graphSize_.y);
  yaxis_.setRotation(-90);

  render_.create(size_.x, size_.y);

  backgroundColor_ = sf::Color(220, 220, 220);
  render_.clear(backgroundColor_);
  render_.display();
}

bool Plot::hasCurve(const std::string &name)
{
  return curves_.find(name) != curves_.end();
}

Curve &Plot::getCurve(const std::string &name)
{
  if(hasCurve(name) == false)
    return createCurve(name);
  return curves_[name];
}

Curve &Plot::createCurve(const std::string &name)
{
  curves_[name] = Curve(graphSize_);
  curves_[name].setLabel(name);
  curves_[name].setPosition(graphPos_);
  return curves_[name];
}

void Plot::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  states.transform *= getTransform();

  states.texture = NULL;

  sf::RectangleShape rectangle(sf::Vector2f(size_.x-kBorderSize*2, size_.y-kBorderSize*2));
  rectangle.setFillColor(backgroundColor_);
  rectangle.setOutlineColor(sf::Color(200, 0, 0));
  rectangle.setOutlineThickness(kBorderSize);
  target.draw(rectangle, states.transform.translate(2, 2));

  sf::Text title;
  title.setFont(font_);
  title.setCharacterSize(22);
  title.setColor(sf::Color(200, 0 ,0));
  title.setString(title_);

  sf::RenderStates statesForTitle = states;
  target.draw(title, statesForTitle.transform.translate(size_.x/2-title_.size()*4, 5));

  target.draw(xaxis_, states);
  target.draw(yaxis_, states);

  target.draw(grid_, states);

  for(std::map<std::string, Curve>::const_iterator it=curves_.begin();it!=curves_.end();++it)
    target.draw(it->second, states);
}

void Plot::build()
{
  sf::Vector2f rangex;
  sf::Vector2f rangey;

  rangex.x = std::numeric_limits<float>::max();
  rangey.x = std::numeric_limits<float>::min();

  rangey.x = std::numeric_limits<float>::max();
  rangey.y = std::numeric_limits<float>::min();

  for(std::map<std::string, Curve>::iterator it=curves_.begin();it!=curves_.end();++it)
  {
    Curve &curve = it->second;
    curve.build(rangex, rangey);
  }

  xaxis_.build(rangex);
  yaxis_.build(rangey);
}

void Plot::setFont(const std::string &filename)
{
  if (!font_.loadFromFile(filename))
  {
    throw ;
  }
  xaxis_.setFont(&font_);
  yaxis_.setFont(&font_);
}

}
}
