#include "Server.h"
#include "Client.h"

int main(int argc, char *argv[])
{
	if((argc > 1 && *argv[1] == 'c')) {
		Client * client = new Client();
		client->Run();
	} else {
		Server * server = new Server();
	}
}