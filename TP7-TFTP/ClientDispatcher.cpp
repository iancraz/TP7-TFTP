#include "ClientDispatcher.h"
#include <boost/asio.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include <cstdint>
#include <cstdio>
typedef unsigned int uint;
using namespace std;
typedef enum {PUT,GET,HELP,QUIT,TYPE_ERROR}typed_t;

clientDispatcher::clientDispatcher(genericEvent * receivedEvent, Client * p2Client)
{
	this->myEvent = receivedEvent;
	this->p2Client = p2Client;
	this->fileName = new char[MAX_DATA_SIZE];
	for (uint i = 0; i <= MAX_DATA_SIZE; i++)
		fileName[i] = 0;
	currentState.setStateCode(WAITING);
	this->fileSize = 0;
	return;
}

clientDispatcher::~clientDispatcher()
{
	delete fileName;
	return;
}

void clientDispatcher::nextStep(void)
{
	if (this->currentState.getStateCode() == WAITING)
	{
		whatDoYouWannaDo();
	}
	//else if ((this->myEvent->eventCode != TIMEOUT))
	//{
	else if (this->currentState.getStateCode() == SENDING)
		{
			package2Send[0] = 0;
			switch (myEvent->eventCode) {
			case ACK:
				package2Send[1] = DATA;
				char c;
				for (int i = 0; i <= MAX_DATA_SIZE; i++)
				{
					myFile.get(c);
					package2Send[i + 2] = c;
				}
				if ((myFile.gcount() - fileSize) >= MAX_DATA_SIZE)
					fileSize -= MAX_DATA_SIZE;
				else
				{
					fileSize = 0;
					currentState.setStateCode(WAITING);
				}
				this->p2Client->sendData(package2Send, MAX_DATA_SIZE + 2);
				break;
			case NONE:
				break;
			default:
				package2Send[1] = EV_ERROR;
				this->p2Client->sendData(package2Send, 2);
				break;
			}
		}
		else if (this->currentState.getStateCode() == RECEIVING)
		{
			switch (myEvent->eventCode) {
			case DATA:
				if (myEvent->amountReceived >= (MAX_DATA_SIZE + 2))
				{
					char c = 0;
					for (int i = 0; (i <= MAX_DATA_SIZE) && (c = myEvent->received[i + 2]); i++)
						myFile.put(c);
				}
				else
				{
					char c = 0;
					for (int i = 0; (i <= myEvent->amountReceived) && (c = myEvent->received[i + 2]); i++)
						myFile.put(c);
				}
				package2Send[1] = ACK;
				break;
			case NONE:
				break;
			default:
				package2Send[1] = EV_ERROR;
				this->p2Client->sendData(package2Send, 2);
				break;
			}
		}
	//}
	/*else
		this->p2Client->sendData(lastPackageSent, MAX_DATA_SIZE + 2);*/
	for (int i = 0; i <= (MAX_DATA_SIZE + 2); i++)
		lastPackageSent[i] = package2Send[i];
	return;
}

void clientDispatcher::newEvent(genericEvent * receivedEvent)
{
	this->myEvent = receivedEvent;
	return;
}


void clientDispatcher::whatDoYouWannaDo()
{
	package2Send[0] = 0;
	int typedIn;
	cout << "Please type the action you want to do. Type HELP for the instructions." << endl;
	typedIn = whatDidHeTypedIn();
	switch (typedIn) {
	case PUT:
		package2Send[1] = WRQ;
		currentState.setStateCode(SENDING);
		for (int i = 0; i <= MAX_DATA_SIZE; i++)
			package2Send[i + 2] = fileName[i];
		this->p2Client->sendData(package2Send, MAX_DATA_SIZE + 2);
		break;
	case GET:
		currentState.setStateCode(RECEIVING);
		package2Send[1] = RRQ;
		for (int i = 0; i <= MAX_DATA_SIZE; i++)
			package2Send[i + 2] = fileName[i];
		this->p2Client->sendData(package2Send, MAX_DATA_SIZE + 2);
		break;
	case QUIT:
		package2Send[1] = EV_ERROR;
		this->p2Client->sendData(package2Send,2);
		break;
	case HELP:
		cout << "Type PUT <File Name>      For Writing a file on the Server." << endl;
		cout << "Type GET <File Name>      For reading a file from the Server." << endl;
		cout << "Type QUIT                 For stopping the communication." << endl;
		break;
	default:
		break;
	}
	return;
}


int clientDispatcher::whatDidHeTypedIn()
{
	int answer=TYPE_ERROR;
	char commandPrompt[MAX_DATA_SIZE+4];
	for (int i = 0; i < MAX_DATA_SIZE+4; i++)
		commandPrompt[i] = 0;
	char c = 0;
	getchar();
	for (int i = 0; (i <= (MAX_DATA_SIZE+4))&&(c!='\n'); i++)
	{
		c = getchar();
		commandPrompt[i] = c;
	}
	if (commandPrompt[0] == 'P')
	{
		if (commandPrompt[1] == 'U')
		{
			if (commandPrompt[2] == 'T')
			{
				for (int i = 0; i <= MAX_DATA_SIZE; i++)
					fileName[i] = commandPrompt[i + 4];
				answer = PUT;
			}
		}
	}
	else if (commandPrompt[0] == 'G')
	{
		if (commandPrompt[1] == 'E')
		{
			if (commandPrompt[2] == 'T')
			{
				for (int i = 0; i <= MAX_DATA_SIZE; i++)
					fileName[i] = commandPrompt[i + 4];
				answer = GET;
			}
		}
	}
	else if (commandPrompt[0] == 'H')
	{
		if (commandPrompt[1] == 'E')
		{
			if (commandPrompt[2] == 'L')
			{
				if (commandPrompt[3] == 'P')
				{
					answer = HELP;
				}
			}
		}
	}
	else if (commandPrompt[0] == 'Q')
	{
		if (commandPrompt[1] == 'U')
		{
			if (commandPrompt[2] == 'I')
			{
				if (commandPrompt[3] == 'T')
				{
					answer = QUIT;
				}
			}
		}
	}
	for (int i = 0; (i <= MAX_DATA_SIZE); i++)
		fileName[i] == '\n' ? fileName[i] = 0 : fileName[i];
	switch (answer) {
	case PUT:
		myFile.open(this->fileName, fstream::in);
		break;
	case GET:
		myFile.open(this->fileName, fstream::app);
		break;
	default:
		break;
	}
	return answer;
}