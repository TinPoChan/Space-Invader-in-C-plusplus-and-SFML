#ifndef Ship_H
#define Ship_H

#include <SFML/Graphics.hpp>   

class Ship {
    friend class Bullet;                                //friend class
    friend class Intersect;                             //friend class
public:
    Ship();                                             //constructor
    void print(sf::RenderWindow &window);               //print function
    void Kill();                                        //kill function
    void moveLeft();                                    //move left function
    void moveRight();                                   //move right function
    bool isAlive = true;                                //check is alive

protected:
    sf::Sprite & getSprite();                           //getter for the sprite
    sf::Vector2f position;                              //the object postion

private:
    sf::Music music;                                    //SFML sound effect
    sf::Texture photo;                                  //Texture
    sf::Sprite spaceShip;                               //Sprite
};

Ship::Ship() : position(300, 700) {                     //default position
    photo.loadFromFile("ship.png");                     //load the texture
    spaceShip.setTexture(photo);                        //set the sprite to "ship.png" (in the other words: set ship = ship.png"
    music.openFromFile("die.wav");                      //load the sound effect
}

void Ship::print(sf::RenderWindow &window) {            //print function
    if (isAlive) {                                      //check is alive
        spaceShip.setPosition(position.x, position.y);  //set the ship position
        window.draw(spaceShip);                         //print
    }
}

void Ship::moveLeft() {                                 //moveLeft function (press left button)
    if (position.x >= 0) position.x -= 5.0f;            //bounding check and //set x -= 5.0f
}

void Ship::moveRight() {                                //moveRight function (press Right button)
    if (position.x <= 565) position.x += 5.0f;          //bounding check //set x += 5.0f
}

sf::Sprite & Ship::getSprite() {                        //getter for the sprite
    return spaceShip;                                   //return the aliens sprite
}

void Ship::Kill() {                                     //kill function
    music.play();                                       //play the sound effect
    isAlive = false;                                    //set isalive = false
}

#endif // !Ship_H
