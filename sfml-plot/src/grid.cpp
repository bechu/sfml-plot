#include "grid.h"

namespace sf
{
namespace plot
{

Grid::Grid()
{
    color_ = sf::Color(100, 100, 100);
}

void Grid::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(&vertices_[0], vertices_.size(), sf::Lines, states);
}

void Grid::CreateGrid(int w, int h)
{
    vertices_.clear();

    double offset = w * (kGranularity_) / 100.0;
    for(int i=0;i<=kGranularity_;i++)
    {
        vertices_.push_back(sf::Vertex(sf::Vector2f(i*offset, 0), color_));
        vertices_.push_back(sf::Vertex(sf::Vector2f(i*offset, h), color_));
    }

    offset = h * (kGranularity_) / 100.0;
    for(int i=0;i<=kGranularity_;i++)
    {
        vertices_.push_back(sf::Vertex(sf::Vector2f(0, i*offset), color_));
        vertices_.push_back(sf::Vertex(sf::Vector2f(w, i*offset), color_));
    }
}

}
}
