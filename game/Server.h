#pragma once
#include "Common.h"

class Server {

public:
	Server();
	void RunServer();

private:
	sf::SelectorTCP selector;
	sf::SocketTCP listener;
};