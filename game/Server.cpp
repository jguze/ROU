#include "Server.h"

Server::Server() {
	if(!listener.Listen(PORT)){}

	selector.Add(listener);
	RunServer();
}

void Server::RunServer() {
	unsigned int numSockets = selector.Wait();

	for(unsigned int i = 0; i < numSockets; ++i) {
		sf::SocketTCP socket = selector.GetSocketReady(i);

		if(socket == listener) {

			// We are accepting a connection from a new client
			sf::IPAddress address;
			sf::SocketTCP client;
			listener.Accept(client, &address);

			selector.Add(client); // Add new client to selector
		} else {

			// This is a client socket, so let's get the data from it
			sf::Packet packet;
			if(socket.Receive(packet) == sf::Socket::Done) {
				// TODO: Process client data here
			} else {
				// Error: remove the socket from the selector
				selector.Remove(socket);
			}
		}
	}
}