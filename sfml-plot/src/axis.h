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
    void Name(const std::string &name);
private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    std::string name_;
};

inline void Axis::Name(const std::string &name)
{
    name_ = name;
}

}
}

#endif // SFML_PLOT_AXIS_H
