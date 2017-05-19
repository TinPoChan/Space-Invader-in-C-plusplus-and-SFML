//Source.cpp
//Assignment: COMSC200 - Group Project
//Title: SPACE INVADER
//Member: Tin Po Chan, Dang Le, Jordan Rasmussen
//Description: using SFML (simple and fast mutimedia library) to implment the classic space invader game in c++
//------------------------------------------------------------------------------------------------------

#include <SFML/Graphics.hpp>        //SFML library for graphics use
#include <SFML/Audio.hpp>           //SFML library for audio use
#include <Aliens.h>                 //Aliens Class
#include <AliensBullet.h>           //Aliens Bullet Class
#include <Boss.h>                   //Boss Class
#include <Ship.h>                   //Ship Class
#include <Bullet.h>                 //Ship Bullet Class
#include <Intersect.h>              //Intersect Class (check is a touching b)
#include <windows.h>                //windows key event use

#include <iostream>                 //Stand IOS use
#include <array>                    //c++ 11 array
#include <vector>                   //vector
#include <fstream>                  //file access use
#include <conio.h>                  //_getch(), for continue after pressing a key
#include <string>                   //string 
#include <sstream>                  //string stream
#include <iterator>                 //iterator for STL container
#include <iomanip>                  //output formatting 
#include <filesystem>               //get the current path

//Global variables
const int MAX_WIDTH = 600;          //define the windows width
const int MAX_HEIGHT = 800;         //define the windows height
const int MAX_ALIENS = 18;          //define the max aliens number

//function prototype
void score(std::string name, int second);
void menu();
void win(int second);
void lose();

//define a namespace for using the path feature
namespace fs = std::experimental::filesystem;

int main()
{
    //gameover check
    bool gameover = false;
    int record = 0;

    //start a do-while loop
    do {
        menu();     //run the menu

        //using SFML library to create a windows, ref: https://www.sfml-dev.org/documentation/2.4.2/classsf_1_1RenderWindow.php#aebef983e01f677bf5a66cefc4d547647
        sf::RenderWindow window(sf::VideoMode(MAX_WIDTH, MAX_HEIGHT), "Space Invader (Comsc 200 Group Project) ");

        window.setFramerateLimit(500);          //set fps = 500
        window.setVerticalSyncEnabled(true);    //set the vertical sync is true

        //create objects
        Ship myship;
        Bullet myBullet;
        AliensBullet aliensbullet;
        Boss boss;

        //array of aliens objects(x,y)
        std::array<Aliens, MAX_ALIENS> alienArray = {
            Aliens(100.0,60.0),
            Aliens(200.0,60.0),
            Aliens(300.0,60.0),
            Aliens(400.0,60.0),
            Aliens(150.0,110.0),
            Aliens(250.0,110.0),
            Aliens(350.0,110.0),
            Aliens(100.0,160.0),
            Aliens(200.0,160.0),
            Aliens(300.0,160.0),
            Aliens(400.0,160.0),
            Aliens(150.0,210.0),
            Aliens(250.0,210.0),
            Aliens(350.0,210.0),
            Aliens(100.0,260.0),
            Aliens(200.0,260.0),
            Aliens(300.0,260.0),
            Aliens(400.0,260.0),
        };

        //implementing polymorphism
        Aliens *a_boss;
        a_boss = &boss;

        //clock for aliens moving, ref: https://www.sfml-dev.org/documentation/2.4.2/classsf_1_1Clock.php
        sf::Clock alienClock;
        sf::Clock moveDownClock;
        //clock for game timer
        sf::Clock gameClock;


        //for aliens movement
        bool moveRight = false;
        int aliensLeft = MAX_ALIENS;

        //for boss aliens movement
        bool boss_moveRight = false;

        //aliens die music loaded, ref: https://www.sfml-dev.org/documentation/2.4.2/classsf_1_1Music.php
        sf::Music music;
        music.openFromFile("explosion.wav");

        //when the windows open
        while (window.isOpen()) {

            //set the window focus
            window.requestFocus();

            //check all the windows event, like close, resize....
            sf::Event evet;
            while (window.pollEvent(evet)) {

                //if user press X (top right) or press ESC, then window close and gameover
                if (evet.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
                    gameover = true;
                    window.close();
                }
            }

            //-----------------------------------------SHIP-------------------------------------------------

            //print the spaceship and bullet
            myship.print(window);
            myBullet.print(window);

            //spaceship movement
            //SFML keyboard ref: https://www.sfml-dev.org/documentation/2.4.2/classsf_1_1Keyboard.php
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {              //if Left Key pressed
                myship.moveLeft();                                                  //ship move left
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {             //if Right Key pressed
                myship.moveRight();                                                 //ship move right
            }

            //spaceship shooting
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {                     //if Space Key pressed
                //if a bullet is still alive, you cannot shot again (shoot once a time)
                if (myBullet.isFire == false && myship.isAlive) myBullet.shoot(myship);
            }

            //----------------------------------------END_SHIP----------------------------------------------

            //------------------------------------------Aliens----------------------------------------------

            //checking aliens bounding
            if (alienArray[0].getSprite().getPosition().x <= 30) moveRight = true;
            if (alienArray[3].getSprite().getPosition().x >= 530) moveRight = false;
            if (a_boss->getSprite().getPosition().x <= 30) boss_moveRight = true;
            if (a_boss->getSprite().getPosition().x >= 530) boss_moveRight = false;


            //time for aliens movement speed
            sf::Time time = alienClock.getElapsedTime();
            sf::Time down_time = moveDownClock.getElapsedTime();
            //keep moving left or right (depends on the bounding check)
            if (time.asSeconds() > 0.1) {                                       //each 0.1 second the aliens will move
                if (moveRight)                                                  //if moveRight is true, then all aliens move right { move.(10.0f, 0.0f) }
                    for (int i = 0; i < MAX_ALIENS; ++i) {
                        alienArray[i].getSprite().move(10.0f, 0.0f);
                    }

                if (!moveRight)                                                 //if moveRight is false, then all aliens move left { move.(-10.0f, 0.0f) }
                    for (int i = 0; i < MAX_ALIENS; ++i) {
                        alienArray[i].getSprite().move(-10.0f, 0.0f);
                    }

                if (down_time.asSeconds() > 3) {                                //each 3 second the aliens will move downward { move.(0.0f, 10.0f) }
                    for (int i = 0; i < MAX_ALIENS; ++i) {
                        alienArray[i].getSprite().move(0.0f, 10.0f);
                    }
                    moveDownClock.restart();                                    //reset the 3 second clock
                }

                if (boss_moveRight) a_boss->getSprite().move(20.0f, 0.0f);      //if boss_moveRight is true, boss will move right { move(20.0f, 0.0f) }
                if (!boss_moveRight) a_boss->getSprite().move(-20.0f, 0.0f);    //if boss_moveRight is false, boss will move left { move(-20.0f, 0.0f) }
                                                                                //notice that, boss would not move down since boss is moving faster

                alienClock.restart();                                           //reset the 0.1 second clock
            }

            //This loop will do the following:
            //1. check is the bullet hit the aliens and is the alien alive 
            //1.1 kill the alien;  1.2 play the explosion sound effect
            //1.2 kill the bullet(since it hitted the alien)
            //1.3 sub the aliensLeft
            //2. check is the ship hit the aliens and is the alien alive and is the ship alive
            //2.1 kill the ship
            //3 print the aliens
            for (int i = 0; i < MAX_ALIENS; ++i) {
                if (Intersect::isTouch(myBullet, alienArray[i]) && alienArray[i].isAlive) {                                 //1
                    alienArray[i].Kill();
                    record += 500; //500 points per alien
                    music.play();
                    myBullet.Kill();
                    aliensLeft--;

                }
                if (Intersect::isTouch(myship, alienArray[i]) && alienArray[i].isAlive && myship.isAlive) myship.Kill();    //2
                alienArray[i].print(window);                                                                                //3
            }
            //--------------------------------------END_Aliens--------------------------------------------

            //-----------------------------------------Boss-----------------------------------------------

            if (Intersect::isTouch(myBullet, boss) && a_boss->isAlive) {          //check is the bullet hit the boss and is the boss alive (a_boss is a point to boss)
                a_boss->Kill();                                                   //if yes then kill the boss
                record += 10000;                                                  //10000 points for the boss
                music.play();                                                     //play the explosion music
                myBullet.Kill();                                                  //kill the bullet
                aliensLeft--;                                                     //aliensLeft sub 1
            }

            //if the boss alive then print the boss
            if (a_boss->isAlive) boss.print_boss(window);

            //--------------------------------------END_Boss----------------------------------------------


            //-------------------------------------AliensBullet-------------------------------------------

            if (aliensbullet.isAlive == false) {                                  //aliens can only shoot once a time
                aliensbullet.alien_shoot(alienArray[rand()&MAX_ALIENS - 1]);      //choose a alien randomly to shoot
            }

            if (Intersect::isTouch(aliensbullet, myship) && myship.isAlive) {     //check is the aliens bullet hit the ship and is the ship alive
                myship.Kill();                                                    //if yes then kill the ship
            }

            //print the aliens bullet
            aliensbullet.print(window);

            //----------------------------------END_AliensBullet------------------------------------------



            sf::Time gameTime = gameClock.getElapsedTime();
            if (gameTime.asSeconds() > 1) {
                record += 100;
                gameClock.restart();
            }

            //-------------------------------------GameOver-----------------------------------------------

            //------------------------------------DISPLAY GAME STATS----------------------------------------
            //https://www.sfml-dev.org/tutorials/2.0/graphics-text.php
            sf::Font font;
            font.loadFromFile("VT323-Regular.ttf");
            sf::Text scoreText;
            // select the font
            scoreText.setFont(font); // font is a sf::Font
            scoreText.setString("Score: " + std::to_string(record)); // set the string to display
            scoreText.setCharacterSize(30);  // set the character size
            scoreText.setPosition(50, 750);

            window.draw(scoreText); // draw score
            //-----------------------------------END DISPLAY GAME STATS-------------------------------------


            //if the ship is not alive, then gameover
            if (myship.isAlive == false) gameover = true;
            //boss is not include in the MAX_ALIENS, so set the condition == -1
            if (aliensLeft == -1) gameover = true;

            //check the gameover condition (win or lose)
            if (gameover) {
                if (aliensLeft == -1) {
                    window.close();
                    win(record);
                }
                else {
                    window.close();
                    lose();
                }
                record = 0;
                gameover = false;

            }

            //-----------------------------------END_GameOver---------------------------------------------


            //SFML standard use
            window.display();   //print the window (like cout but this for graphic use specifically)
            window.clear();     //clear the window (like system"cls" but this one is much faster since it is using a buffer)
        }
    } while (gameover == false);     //gameover = true then stop the loop

    return 0;
}

//menu function
void menu() {
    using namespace std;                    //using std library 
    string input;
    ifstream myfile;
    myfile.exceptions(ifstream::badbit);    //reference: http://www.cplusplus.com/reference/ios/ios/exceptions/

    try {                                   //using exception
        myfile.open("menu.txt");            //file open
        while (getline(myfile, input)) {    //print all the lines to the console
            cout << input << endl;
        }

        _getch();                           //press any key to continue
        system("cls");                      //clear the screen (not efficiency, but here is ok)
        myfile.close();                     //file close
    }
    catch (ifstream::failure e) {           //if failure catched
        cerr << "Cannot open the file";     //cerr = output for error (can use cout if you wish)
    }

    if (GetAsyncKeyState(VK_ESCAPE))        //windows key event (when esc pressed)
        exit(EXIT_SUCCESS);                 //exit


}

void win(int point) {
    using namespace std;                    //using std library 
    string input;
    ifstream myfile;
    myfile.exceptions(ifstream::badbit);    //reference: http://www.cplusplus.com/reference/ios/ios/exceptions/

    try {                                   //using exception
        myfile.open("win.txt");             //file open
        while (getline(myfile, input)) {    //print all the lines to the console
            cout << input << endl;
        }
        _getch();                           //press any key to continue
        system("cls");                      //clear the screen (not efficiency, but here is ok)
        myfile.close();                     //file close

        cout << "Please Enter Your Name: "; //get the user name
        getline(cin, input);
        score(input, point);               //pass the name and the score to the scoreboard
    }
    catch (ifstream::failure e) {           //if failure catched
        cerr << "Cannot open the file";     //cerr = output for error (can use cout if you wish)
    }

    if (GetAsyncKeyState(VK_ESCAPE))        //windows key event (when esc pressed)
        exit(EXIT_SUCCESS);                 //exit
}

void score(std::string name, int point) {
    using namespace std;
    string input;
    fstream myfile;
    ofstream outputfile;
    myfile.exceptions(ifstream::badbit);    //reference: http://www.cplusplus.com/reference/ios/ios/exceptions/


    vector<pair<string, int>> user;         //STL container using pair (pair is a struct template) ref:http://en.cppreference.com/w/cpp/utility/pair

    try {                                               //using exception
        myfile.open("score.txt");                       //file open
        user.push_back(make_pair(name, point));         //push back the name and record to the vector
        while (getline(myfile, input)) {                //get all the record fomr the file
            stringstream ss(input);                     //use stream
            ss >> name >> point;                        //convert string to string and int
            user.push_back(make_pair(name, point));     //push it to the vector
        }

        //lambda expression for soring
        sort(user.begin(), user.end(), [](const pair<string, int> &first, const pair<string, int> &second) { return first.second < second.second; });

        myfile.close();                                 //file close

        outputfile.open("score.txt");                   //output file open
        if (outputfile.is_open()) {

            vector<pair<string, int>>::iterator iter;                           //iterator for the pair vector
            vector<pair<string, int>>::iterator end_iter = user.end();          //iterator for the pair vector (the end point)

            cout << "Here is the Score Board!!!" << endl << endl;
            cout << "Name" << "     Score" << endl;
            for (iter = user.begin(); iter != end_iter; ++iter) {               //This loop: print and store the data to console and output file
                cout << iter->first << setw(10) << iter->second << endl;
                outputfile << iter->first << " " << iter->second << endl;
            }

            // C++17 path feature ref: http://en.cppreference.com/w/cpp/experimental/fs/path
            cout << endl << "The score file store at: " << fs::current_path();
            outputfile.close();
        }

        _getch();                           //press any key to continue
        system("cls");                      //clear the screen (not efficiency, but here is ok)
    }
    catch (ifstream::failure e) {           //if failure catched
        cerr << "Cannot open the file";     //cerr = output for error (can use cout if you wish)
    }

    if (GetAsyncKeyState(VK_ESCAPE))        //windows key event (when esc pressed)
        exit(EXIT_SUCCESS);                 //exit
}

void lose() {
    using namespace std;                    //using std library 
    string input;
    ifstream myfile;
    myfile.exceptions(ifstream::badbit);    //reference: http://www.cplusplus.com/reference/ios/ios/exceptions/

    try {                                   //using exception
        myfile.open("lose.txt");            //file open
        while (getline(myfile, input)) {
            cout << input << endl;
        }

        _getch();                           //press any key to continue
        system("cls");                      //clear the screen (not efficiency, but here is ok)
        myfile.close();                     //file close
    }
    catch (ifstream::failure e) {           //if failure catched
        cerr << "Cannot open the file";     //cerr = output for error (can use cout if you wish)
    }

    if (GetAsyncKeyState(VK_ESCAPE))        //windows key event (when esc pressed)
        exit(EXIT_SUCCESS);                 //exit
}



