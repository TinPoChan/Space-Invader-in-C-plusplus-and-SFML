#ifndef Bullet_H
#define Bullet_H

#include <SFML/Graphics.hpp>   
#include <SFML/Audio.hpp>

#include <Ship.h>

class Bullet{
public:
    Bullet();                                           //constructor
    void print(sf::RenderWindow &window);               //print function
    void shoot(Ship &myship);                           //shoot function
    bool isFire = false;                                //check is fired
    void Kill();                                        //kill function
    bool isAlive = false;                               //check is alive
    sf::Sprite & getSprite();                           //getter for the sprite

private:
    sf::Music music;                                    //Music for sound effect
    sf::Vector2f position;                              //this is recording the object position (x,y) cord
    sf::Texture photo;                                  //Texture
    sf::Sprite bullet;                                  //sprite

};

Bullet::Bullet() {                                      //constructor
    photo.loadFromFile("bullet.png");                   //load the texture
    bullet.setTexture(photo);                           //set the sprite to "bullet.png" (in the other words: set bullet = bullet.png"
    music.openFromFile("shoot.wav");                    //load the sound effect
}

sf::Sprite & Bullet::getSprite(){                       //getter for the sprite
    return bullet;
}

void Bullet::shoot(Ship &myship) {                      //shoot function
    music.play();                                       //play the gun shoot sound effect
    position.x = myship.position.x + 10.0f;             //when shoot, get the spaceship current x position, +10.0f is because i want to shoot it from middle instead of from the left side
    position.y = myship.position.y - 0.5f;              //same as the upper line, this one get the y position
    isFire = true;                                      //fired is ture
    isAlive = true;                                     //the bullet is alive 
}

void Bullet::print(sf::RenderWindow &window) {          //print function, argument is the window
    if (!isAlive) {                                     //if the bullet is hit an alien, the bullet will GG
        isFire = false;                                 //is fired is false when the bullet is not alive
        bullet.setPosition(900, 900);                   //one of the issue i will improve afterward, what i want to do here is when the bullet hit the aliens, the bullet will gone
    }
    if (isFire && position.y > -20 && isAlive) {        //if shot, and the bullet inside in window (y > -20 is just checking bounding), and is alive
        position.y -= 7.0f;                             //y -=0.1f (which means keep going up)
        bullet.setPosition(position.x, position.y);     //set the new position to the bullet
        window.draw(bullet);                            //print it
    }
    else isFire = false;                                //else is false 
}

void Bullet::Kill() {                                   //if bullet gg
    isAlive = false;                                    //rip bullet
}

#endif // !Bullet_H
