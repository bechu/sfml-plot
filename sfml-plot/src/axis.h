#ifndef SFML_PLOT_AXIS_H
#define SFML_PLOT_AXIS_H

#include <string>
#include <SFML/Graphics.hpp>

namespace sf
{
namespace plot
{

class Axis : public sf::Drawable, public sf::Transformable
{
public:
    Axis();
    void SetSize(const Vector2i &size);
    void Name(const std::string &name);
    void Compute(float min=0, float max=0);
private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    std::string name_;
    sf::Font font_;
    sf::Text max_;
    sf::Text min_;
    sf::Vector2i size_;
};

inline void Axis::SetSize(const sf::Vector2i &size)
{
    size_ = size;
}

inline void Axis::Name(const std::string &name)
{
    name_ = name;
}

}
}

#endif // SFML_PLOT_AXIS_H
