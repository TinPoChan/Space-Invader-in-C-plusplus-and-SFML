#ifndef INTERSECT_H
#define INTERSECT_H

#include <SFML/Graphics.hpp>   
#include <Ship.h>
#include <Bullet.h>
#include <Aliens.h>
#include <AliensBullet.h>

class Intersect {
public:
    static bool isTouch(Ship &, Aliens &);                  //check is the ship touch the aliens
    static bool isTouch(Bullet &, Aliens &);                //check is the bullet touch the aliens
    static bool isTouch(AliensBullet &, Ship &);            //check is the aliens bullet touch the ship
};

bool Intersect::isTouch(Bullet &b_obj, Aliens &a_obj) {                             //Ref: https://www.sfml-dev.org/tutorials/2.4/graphics-transform.php
    sf::FloatRect Bullet_BoundingBox;                                               //FloatRect is a SFML function, which is let you define the bounding box. 
    Bullet_BoundingBox.left = b_obj.getSprite().getPosition().x;                    //bullet top left
    Bullet_BoundingBox.top = b_obj.getSprite().getPosition().y;                     //bullet top right
    Bullet_BoundingBox.width = b_obj.getSprite().getGlobalBounds().width;           //bullet width
    Bullet_BoundingBox.height = b_obj.getSprite().getGlobalBounds().height;         //bullet height


    sf::FloatRect Alien_BoundingBox;                                                //Bounding box for aliens
    Alien_BoundingBox.left = a_obj.getSprite().getPosition().x;                     //Alien top left
    Alien_BoundingBox.top = a_obj.getSprite().getPosition().y;                      //Alien top right
    Alien_BoundingBox.width = a_obj.getSprite().getGlobalBounds().width;            //Alien width
    Alien_BoundingBox.height = a_obj.getSprite().getGlobalBounds().height;          //Alien height

                                                                                    //ref for intersects: https://www.sfml-dev.org/documentation/2.4.2/classsf_1_1Rect.php
    return Bullet_BoundingBox.intersects(Alien_BoundingBox);                        //intersects is a SFML function(again), which check is a touching b ( eg. a.intersects(b); )
}

bool Intersect::isTouch(Ship &s_obj, Aliens &a_obj) {
    sf::FloatRect Ship_BoundingBox;
    Ship_BoundingBox.left = s_obj.getSprite().getPosition().x;					  //Ship top left
    Ship_BoundingBox.top = s_obj.getSprite().getPosition().y;                     //Ship top right
    Ship_BoundingBox.width = s_obj.getSprite().getGlobalBounds().width;           //Ship width
    Ship_BoundingBox.height = s_obj.getSprite().getGlobalBounds().height;         //Ship height

    sf::FloatRect Alien_BoundingBox;                                              //Bounding box for aliens
    Alien_BoundingBox.left = a_obj.getSprite().getPosition().x;                   //Alien top left
    Alien_BoundingBox.top = a_obj.getSprite().getPosition().y;                    //Alien top right
    Alien_BoundingBox.width = a_obj.getSprite().getGlobalBounds().width;          //Alien width
    Alien_BoundingBox.height = a_obj.getSprite().getGlobalBounds().height;        //Alien height

    return Ship_BoundingBox.intersects(Alien_BoundingBox);                        //intersects is a SFML function(again), which check is a touching b ( eg. a.intersects(b); )

}

bool Intersect::isTouch(AliensBullet &ab_obj, Ship &s_obj) {
    sf::FloatRect Ship_BoundingBox;
    Ship_BoundingBox.left = s_obj.getSprite().getPosition().x;					  //Ship top left
    Ship_BoundingBox.top = s_obj.getSprite().getPosition().y;                     //Ship top right
    Ship_BoundingBox.width = s_obj.getSprite().getGlobalBounds().width;           //Ship width
    Ship_BoundingBox.height = s_obj.getSprite().getGlobalBounds().height;         //Ship height

    sf::FloatRect AlienBullet_BoundingBox;
    AlienBullet_BoundingBox.left = ab_obj.getSprite().getPosition().x;                   //Alien top left
    AlienBullet_BoundingBox.top = ab_obj.getSprite().getPosition().y;                    //Alien top right
    AlienBullet_BoundingBox.width = ab_obj.getSprite().getGlobalBounds().width;          //Alien width
    AlienBullet_BoundingBox.height = ab_obj.getSprite().getGlobalBounds().height;        //Alien height

    return Ship_BoundingBox.intersects(AlienBullet_BoundingBox);                //intersects is a SFML function(again), which check is a touching b ( eg. a.intersects(b); )
}


#endif // !INTERSECT_H
