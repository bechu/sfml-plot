#ifndef SFML_PLOT_GRID_H
#define SFML_PLOT_GRID_H

#include <vector>
#include <SFML/Graphics.hpp>

namespace sf
{
namespace plot
{

class Grid : public sf::Drawable, public sf::Transformable
{
public:
    Grid();
    void CreateGrid(const Vector2f &size);
private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    std::vector<sf::Vertex> vertices_;
    sf::Color color_;
    // means that cut the grid in kPart
    static const int kPart = 4;
    sf::Vector2f size_;
};

}
}

#endif // SFML_PLOT_GRID_H
