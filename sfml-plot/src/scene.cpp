#include "scene.h"

namespace sf
{
namespace plot
{

Scene::Scene(int width, int height)
{
    size_.x = width;
    size_.y = height;

    graphSize_.x = width-width*(kLegendSize/100.0);
    graphSize_.y = height-height*(kLegendSize/100.0);

    grid_.CreateGrid(graphSize_.x, graphSize_.y);
    xaxis_.SetSize(graphSize_);
    yaxis_.SetSize(graphSize_);

    render_.create(width, height);

    backgroundColor_ = sf::Color(220, 220, 220);
    Render();
}

void Scene::Render()
{
    render_.clear(backgroundColor_);
    render_.display();
}

Curve &Scene::CreateCurve(const std::string &name)
{
    curves_[name] = Curve(graphSize_);
    curves_[name].Label(name);
    return curves_[name];
}

void Scene::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    states.texture = NULL;

    sf::RectangleShape rectangle(sf::Vector2f(size_.x-kBorderSize*2, size_.y-kBorderSize*2));
    rectangle.setFillColor(backgroundColor_);
    rectangle.setOutlineColor(sf::Color(200, 0, 0));
    rectangle.setOutlineThickness(kBorderSize);
    target.draw(rectangle, states.transform.translate(2, 2));


    target.draw(xaxis_, states.transform.translate(10, 0));
    //target.draw(yaxis_, states);

    states.transform.translate(size_.x*(kLegendSize/100.0)/2, size_.y*(kLegendSize/100.0)/2);
    target.draw(grid_, states);

    for(std::map<std::string, Curve>::const_iterator it=curves_.begin();it!=curves_.end();++it)
        target.draw(it->second, states);
}

void Scene::Build()
{
    float minx = 0;
    float maxx =  0;
    for(std::map<std::string, Curve>::iterator it=curves_.begin();it!=curves_.end();++it)
    {
        Curve &curve = it->second;
        curve.Compute(minx, maxx);
    }
    xaxis_.Compute(minx, maxx);
    yaxis_.Compute();
}

}
}
