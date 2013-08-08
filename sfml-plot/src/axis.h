#ifndef SFML_PLOT_AXIS_H
#define SFML_PLOT_AXIS_H

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

namespace sf
{
namespace plot
{

class Axis : public sf::Drawable, public sf::Transformable
{
private:
  static const int kPart = 4;
public:
  Axis();
  void setSize(float size);
  void name(const std::string &name);
  void build(const Vector2f &range);
  void setFont(sf::Font *font);
private:
  void defineLabel();
  void draw(sf::RenderTarget& target, sf::RenderStates states) const;
  std::string name_;
  sf::Font *font_;
  float size_;
  sf::Text label_;
  std::vector<sf::Text> numbers_;
};

inline void Axis::setFont(sf::Font *font)
{
  font_ = font;
  defineLabel();
}

inline void Axis::setSize(float size)
{
  size_ = size;
}

inline void Axis::name(const std::string &name)
{
  name_ = name;
  defineLabel();
}

}
}

#endif // SFML_PLOT_AXIS_H
