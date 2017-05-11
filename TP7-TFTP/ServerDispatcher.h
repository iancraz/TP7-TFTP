#pragma once
#include "Server.h"
#include "GenericEvent.h"
#include "GenericState.h"
#include <fstream>

class serverDispatcher
{
public:
	serverDispatcher(genericEvent * receivedEvent, Server * p2Server);
	void nextStep();
protected:
	fstream myFile;
	genericEvent * myEvent;
	genericState currentState;
	Server * p2Server;
};