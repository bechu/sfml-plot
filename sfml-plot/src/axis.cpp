#include "axis.h"

namespace sf
{
namespace plot
{

Axis::Axis()
{

}

void Axis::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
//    target.draw(&vertices_[0], vertices_.size(), sf::Lines, states);
}

}
}
