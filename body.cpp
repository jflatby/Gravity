#include "body.h"

Body::Body(float r, float m, sf::Vector2f pos, sf::Vector2f vel)
{
    radius = r;
    mass = m;
    velocity = vel;

    shape = sf::CircleShape(r);
    shape.setPosition(pos);
    shape.setOrigin(r, r);
    shape.setFillColor(sf::Color::Blue);
}

void Body::update(std::vector<Body>& bodies)
{
    //Calculate gravity from all other bodies
    sf::Vector2f force = getGravityForce(bodies);

    //Use to calculate new velocity and position
    velocity += force / mass;
    shape.setPosition(getPosition() + velocity);
}

sf::Vector2f Body::getGravityForce(std::vector<Body>& bodies){
    //TODO: make this a global constant
    const float gravitationalConstant = 1;

    sf::Vector2f totalGravForce = sf::Vector2f(0, 0);
    for (int i=0; i<bodies.size(); i++){
        //Calculate gravity force between this and all others
        if(&bodies[i] != this){
            //vector between bodies
            sf::Vector2f rvec = (bodies[i].getPosition() - getPosition());
            //length of that vector squared
            float r2 = pow(rvec.x, 2) + pow(rvec.y, 2);
            //unit vector in that direction
            sf::Vector2f unit_r = rvec / sqrt(r2);
            //magnitude of gravitational force
            float F = gravitationalConstant * mass * bodies[i].getMass() / r2;
            //add force vector to total force.
            totalGravForce += unit_r * F;
        }
    }
    return totalGravForce;
}

sf::CircleShape Body::getShape()
{
    return shape;
}

float Body::getMass(){
    return mass;
}

void Body::setPosition(sf::Vector2f newPos){
    shape.setPosition(newPos);
}
sf::Vector2f Body::getPosition(){
    return shape.getPosition();
}