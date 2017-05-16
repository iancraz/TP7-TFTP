#include <iostream>
#include <ctime>
#include "Server.h"
#include "Client.h"
#include "EventGenerator.h"
#include "ServerDispatcher.h"
#include "ClientDispatcher.h"
#include "GenericEvent.h"
#include "GenericState.h"
bool initProgram(void);
using namespace std;

int main(void)
{
	bool isServer = initProgram();
	bool exit = false;
	int mainEvent;
	eventGenerator eventQueue;
	if (isServer == true)
	{
		Server server(69);
		server.waitForClient();
		eventQueue.setEventGenerator(&server, SERVER);
	}
	else
	{
		Client client;
		client.ConnectToServer("localhost","69");
		eventQueue.setEventGenerator(&client, CLIENT);
	}
	mainEvent = eventQueue.getNextEvent();

	while ((isServer == true)&&(exit==false))
	{
		
	}

	return EXIT_SUCCESS;
}

bool initProgram(void)
{
	char temp;
	cout << "Type C if you want to act as a Client or S if you want to act as a Server." << endl;
	cin >> temp;
	switch (temp) {
	case 'C':
		return false;
	case 'S':
		return true;
	default:
		return true;
	}
}
