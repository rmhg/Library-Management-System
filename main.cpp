/*
* Created By Rahul Mishra
* Library Management System
* Still Have A lot of Bug And Performance Issues
*/
#include <SFML/Graphics.hpp>            //for Renders
#include <SFML/Audio.hpp>              //for Sound click
#include <SFML/System.hpp>         //for sf::Sleep
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <mutex>
#include "SQL\SQL.h"
#define FONT "data/sans.ttf"
#include "LocalHeader\Clickable.h"
#include "LocalHeader\Form.h"
#include "LocalHeader\Login.h"
#include "LocalHeader\Menu.h"
#include "LocalHeader\About.h"
#include "LocalHeader\Table.h"
#include "LocalHeader\Function.h"
#include "LocalHeader\User.h"
#include "LocalHeader\Window.h"
#include "LocalHeader\Load.h"
int main()
{

 sf::RenderWindow window;
 load w(&window);
 w.Play();
 w.~load();
 Window(&window).Play();
 return 0;
}
