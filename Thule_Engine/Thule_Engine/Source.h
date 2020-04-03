/*System specific includes*/
#include<iostream>
#include<ctime>
#include<cstdlib>
#include<vector>
#include<list>
#include<fstream>
#include<sstream>
#include<stack>
#include<map>
#include<cmath>

/*Library Includes*/

#include"SFML/Graphics.hpp"
#include"SFML/Window.hpp"
#include"SFML/System.hpp"
#include"SFML/Audio.hpp"
#include"SFML/Network.hpp"

#define PI 3.141592f

float constrainAngle(float rad_angle);

float lerp(float value, float start, float end);

bool isInRange(float x, float a, float b);