#ifndef SFML_PLOT_PLOT_H
#define SFML_PLOT_PLOT_H

#include <map>
#include <string>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "axis.h"
#include "grid.h"
#include "curve.h"

namespace sf
{
namespace plot
{

class Plot : public sf::Drawable, public sf::Transformable
{
public:
  Plot(const sf::Vector2f &size, const std::string &title="");
  void grid(bool enable);
  void draw();
  Curve &createCurve(const std::string &name);

  void build();

  void setXLabel(const std::string &name);
  void setYLabel(const std::string &name);
  void setBackgroundColor(const sf::Color &color);
  void setTitle(const std::string &title);
  void setFont(const std::string &filename);
private:
  void draw(sf::RenderTarget& target, sf::RenderStates states) const;
  sf::Color backgroundColor_;
  Axis xaxis_;
  Axis yaxis_;
  plot::Grid grid_;
  sf::Vector2f size_;
  sf::RenderTexture render_;
  std::map<std::string, Curve> curves_;
  sf::Vector2f graphSize_;
  sf::Vector2f graphPos_;

  static const int kTopSize = 10;
  static const int kLeftSize = 12;
  static const int kRightSize = 5;
  static const int kBottomSize = 12;

  static const int kBorderSize = 2;

  std::string title_;
  sf::Font font_;
};

inline void Plot::setXLabel(const std::string &name)
{
  xaxis_.name(name);
}

inline void Plot::setYLabel(const std::string &name)
{
  yaxis_.name(name);
}

inline void Plot::setTitle(const std::string &title)
{
  title_ = title;
}

inline void Plot::setBackgroundColor(const sf::Color &color)
{
  backgroundColor_ = color;
}

}
}

#endif // SFML_PLOT_PLOT_H

