#pragma once
#include "Client.h"
#include "GenericEvent.h"
#include "GenericState.h"
#include <fstream>

class clientDispatcher
{
public:
	clientDispatcher(genericEvent * receivedEvent, Client * p2Client);
	~clientDispatcher();
	void newEvent(genericEvent * receivedEvent);
	void nextStep();
protected:
	char * fileName;
	std::fstream myFile;
	int fileSize;
	genericEvent * myEvent;
	genericState currentState;
	Client * p2Client;
	char package2Send[MAX_DATA_SIZE + 2];
	char lastPackageSent[MAX_DATA_SIZE + 2];
	void whatDoYouWannaDo();
private:
	int whatDidHeTypedIn();
};