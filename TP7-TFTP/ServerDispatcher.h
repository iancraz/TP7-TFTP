#pragma once
#include "Server.h"
#include "GenericEvent.h"
#include "GenericState.h"
#include <fstream>

class serverDispatcher
{
public:
	serverDispatcher(genericEvent * receivedEvent, Server * p2Server);
	~serverDispatcher();
	void newEvent(genericEvent * receivedEvent);
	void nextStep();
protected:
	char * fileName;
	std::fstream myFile;
	std::streamsize fileSize;
	genericEvent * myEvent;
	genericState currentState;
	Server * p2Server;
	char package2Send[MAX_DATA_SIZE+2];
	char lastPackageSent[MAX_DATA_SIZE + 2];
};