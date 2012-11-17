// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include <stdio.h>

// TODO: reference additional headers your program requires here
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <map>
#include <iostream>
#include <cassert>
#include <cmath>

#define CLIENT_IP "198.84.206.189"
#define SERVER_IP "99.237.30.2"
#define PORT 49094

#define SERVER false
#define CLIENT true

#define SERVER_PLAYER 0
#define CLIENT_PLAYER 1