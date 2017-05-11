#pragma once
#include "Server.h"
#include "GenericEvent.h"
#include "GenericState.h"

class serverDispatcher
{
public:
	serverDispatcher();
	~serverDispatcher();
	void nextStep();
protected:
	genericEvent * myEvent;
	genericState currentState;
	Server * p2Server;
};