#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <cmath>

using namespace sf;

float magnitude(Vector2f);
Vector2f normalize(Vector2f);
void limit(Vector2f &, float);
float heading(Vector2f vector);
