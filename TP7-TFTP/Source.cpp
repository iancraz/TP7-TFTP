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
	eventGenerator eventQueue;
	Server server(69);
	Client client;
	if (isServer == true)
	{
		server.waitForClient();
		eventQueue.setEventGenerator(&server, SERVER);
	}
	else
	{
		client.ConnectToServer("localhost","69");
		eventQueue.setEventGenerator(&client, CLIENT);
	}
	serverDispatcher svDisp(&eventQueue.newEvent, &server);
	clientDispatcher clDisp(&eventQueue.newEvent, &client);
	while ((isServer == true)&&(exit==false))
	{
		svDisp.nextStep();
		eventQueue.getNextEvent();
		svDisp.newEvent(&eventQueue.newEvent);
	}
	while ((isServer == false) && (exit == false))
	{
		clDisp.nextStep();
		eventQueue.getNextEvent();
		clDisp.newEvent(&eventQueue.newEvent);
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
