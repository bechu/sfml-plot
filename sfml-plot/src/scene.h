#ifndef SFML_PLOT_SCENE_H
#define SFML_PLOT_SCENE_H

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

class Scene : public sf::Drawable, public sf::Transformable
{
public:
    Scene(int width, int height);
    void Grid(bool enable);
    void Plot();
    void Draw();
    void XLabel(const std::string &name);
    void YLabel(const std::string &name);
    void BackgroundColor(const sf::Color &color);
    Curve &CreateCurve(const std::string &name);
    void Build();
private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void Render();
    sf::Color backgroundColor_;
    Axis xaxis_;
    Axis yaxis_;
    plot::Grid grid_;
    sf::Vector2i size_;
    sf::RenderTexture render_;
    std::map<std::string, Curve> curves_;
    sf::Vector2i graphSize_;

    static const float kLegendSize = 0.1;
    static const int kBorderSize = 2;

};

inline void Scene::BackgroundColor(const sf::Color &color)
{
    backgroundColor_ = color;
}

}
}

#endif // SFML_PLOT_SCENE_H

