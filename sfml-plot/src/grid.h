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
    void CreateGrid(int x, int y);
private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    std::vector<sf::Vertex> vertices_;
    sf::Color color_;
    static const int kGranularity_ = 10;
};

}
}

#endif // SFML_PLOT_GRID_H
