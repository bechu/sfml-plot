#ifndef SFML_PLOT_CURVE_H
#define SFML_PLOT_CURVE_H

#include <vector>
#include <list>
#include <string>
#include <SFML/Graphics.hpp>

namespace sf
{
namespace plot
{

class Curve : public sf::Drawable, public sf::Transformable
{
public:
  Curve() {}
  Curve(const sf::Vector2f &size);
  void setLabel(const std::string &label);
  void setColor(const sf::Color &color);
  void addValue(float value);
  void build(sf::Vector2f &rangex, sf::Vector2f &rangey);
  void setFill(bool fill);
private:
  void draw(sf::RenderTarget& target, sf::RenderStates states) const;
  std::string label_;
  sf::Color color_;
  sf::Color fillColor_;
  std::list<float> data_;
  std::vector<sf::Vertex> line_;
  sf::Vector2f size_;
  bool fill_;
};

inline void Curve::setFill(bool fill)
{
  fill_ = fill;
}

inline void Curve::setLabel(const std::string &label)
{
  label_ = label;
}

inline void Curve::setColor(const sf::Color &color)
{
  color_ = color;
  fillColor_ = color;
  fillColor_.a = 100;
}

}
}

#endif // SFML_PLOT_CURVE_H
