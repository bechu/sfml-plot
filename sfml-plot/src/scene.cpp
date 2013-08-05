#include <iostream>

#include "scene.h"

namespace sf
{
namespace plot
{

Scene::Scene(int width, int height)
{
    size_.x = width;
    size_.y = height;

    grid_.CreateGrid(400, 400);

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
    curves_[name] = Curve(sf::Vector2i(400, 400));
    curves_[name].Label(name);
    return curves_[name];
}

void Scene::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    states.texture = NULL;

    target.draw(sf::Sprite(render_.getTexture()));

    states.transform.translate(size_.x*kLegendSize/2, size_.y*kLegendSize/2);
    target.draw(grid_, states);
    //target.draw(xaxis_, states);
    //target.draw(yaxis_, states);

    for(std::map<std::string, Curve>::const_iterator it=curves_.begin();it!=curves_.end();++it)
        target.draw(it->second, states);
}

void Scene::Build()
{

}

}
}
