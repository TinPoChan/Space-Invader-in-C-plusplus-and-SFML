#ifndef ALIENSBULLET_H
#define ALIENSBULLET_H

#include <SFML/Graphics.hpp>   
#include <SFML/Audio.hpp>

#include <Aliens.h>

class AliensBullet{
public:
    AliensBullet();                         //constructor
    void print(sf::RenderWindow &window);   //print function
    void alien_shoot(Aliens &myalien);      //alien shoot function
    bool isAlive = false;                   //check is alive
    void Kill();                            //kill function
    sf::Sprite & getSprite();               //getter for sprite
private:
    sf::Vector2f position;                  //this is recording the object position (x,y) cord
    sf::Texture photo;                      //Texture
    sf::Sprite aliens_bullet;               //Sprite
};

AliensBullet::AliensBullet() {              //constructor
    photo.loadFromFile("AliensBullet.png"); //loae the texture
    aliens_bullet.setTexture(photo);        //set the photo to the sprite
}

sf::Sprite & AliensBullet::getSprite() {    //getter for the sprite
    return aliens_bullet;
}

void AliensBullet::alien_shoot(Aliens &myalien) {               //alien shoot function
    position.x = myalien.getSprite().getPosition().x + 5.0f;    //get the current aliens position x
    position.y = myalien.getSprite().getPosition().y;           //get the current aliens position y
    if (myalien.isAlive == false) isAlive = false;              //check is the alive
    else isAlive = true;                                        
}

void AliensBullet::print(sf::RenderWindow &window) {            //print function
    if  (position.y < 800 && isAlive) {                         //check bounding and is alive
        position.y += 5.0f;                                     //moving downward
        aliens_bullet.setPosition(position.x, position.y);      //set the new postion
        window.draw(aliens_bullet);                             //draw the bullet to the buffer
    }
    if (position.y > 750) isAlive = false;                      //if the bullet get thru the bound, then the bullet should not alive
}

void AliensBullet::Kill() {                 //kill function
    isAlive = false;                        //killed
}

#endif // !ALIENSBULLET_H