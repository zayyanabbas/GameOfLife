#include <SFML/Graphics.hpp>

class GridUI : public sf::Drawable, public sf::Transformable {
    uint gr_width;
    uint gr_height;
    uint cl_length = 10;

    sf::VertexArray vertices;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        states.transform *= getTransform();
        target.draw(vertices, states);
    }
public:
    GridUI(uint width, uint height) {
        gr_width = width;
        gr_height = height;

        vertices.setPrimitiveType(sf::Quads);
        vertices.resize(gr_width*gr_height*4);
    }
    void update_vertices(bool* map) {
        for (uint x = 0; x < gr_width; ++x) {
            for (uint y = 0; y < gr_height; ++y) {
                bool state = map[x * gr_height + y];
                sf::Vertex* quad = &vertices[(x * gr_height + y)*4];

                quad[0].position = sf::Vector2f(x * cl_length, (y+1) * cl_length);
                quad[1].position = sf::Vector2f(x * cl_length, y * cl_length);
                quad[2].position = sf::Vector2f((x+1) * cl_length, y * cl_length);
                quad[3].position = sf::Vector2f((x+1) * cl_length, (y+1) * cl_length);

                quad[0].color = state ? sf::Color::Black : sf::Color::White;
                quad[1].color = state ? sf::Color::Black : sf::Color::White;;
                quad[2].color = state ? sf::Color::Black : sf::Color::White;;
                quad[3].color = state ? sf::Color::Black : sf::Color::White;;
            }
        }
    }
};