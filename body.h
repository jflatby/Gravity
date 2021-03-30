#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/CircleShape.hpp>

class Body
{
private:
    float radius;
    float mass;
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::CircleShape shape;
    sf::Vector2f getGravityForce(std::vector<Body>& bodies);

public:
    Body(float r, float m, sf::Vector2f pos, sf::Vector2f vel = sf::Vector2f(0, 0));
    void update(std::vector<Body>& bodies);
    sf::CircleShape getShape();
    float getMass();
    sf::Vector2f getPosition();
};