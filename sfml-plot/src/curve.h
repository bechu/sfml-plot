#ifndef SFML_PLOT_CURVE_H
#define SFML_PLOT_CURVE_H

#include <vector>
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
    Curve(const sf::Vector2i &size);
    void Label(const std::string &label);
    void Color(const sf::Color &color);
    void Plot(float x, float y);
private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    std::string label_;
    sf::Color color_;
    //std::vector<float> data_;
    std::vector<sf::Vertex> line_;
    sf::Vector2i size_;
};

inline void Curve::Label(const std::string &label)
{
    label_ = label;
}

inline void Curve::Color(const sf::Color &color)
{
   color_ = color;
}

}
}

#endif // SFML_PLOT_CURVE_H
