#include "ServerDispatcher.h"
#include <boost/asio.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <cstdint>
using namespace std;
typedef unsigned int uint;

serverDispatcher::serverDispatcher(genericEvent * receivedEvent, Server * p2Server)
{
	this->myEvent = receivedEvent;
	this->p2Server = p2Server;
	this->fileName = new char[MAX_DATA_SIZE];
	for (uint i = 0; i <= MAX_DATA_SIZE; i++)
		fileName[i] = 0;
	currentState.setStateCode(WAITING);
	this->fileSize = 0;
	return;
}
serverDispatcher::~serverDispatcher()
{
	delete fileName;
	return;
}

void serverDispatcher::newEvent(genericEvent * receivedEvent)
{
	this->myEvent = receivedEvent;
	return;
}

void serverDispatcher::nextStep()
{
	if (myEvent->eventCode != TIMEOUT)
	{
		if (currentState.getStateCode() == WAITING)
		{
			package2Send[0] = 0;
			switch (myEvent->eventCode) {
			case WRQ:
				currentState.setStateCode(RECEIVING);
				for (uint i = 0; (i <= MAX_DATA_SIZE - 2) && (myEvent->received[i + 2] != 0); i++)
					this->fileName[i] = myEvent->received[i + 2];
				this->myFile.open(this->fileName, fstream::app);
				package2Send[1] = ACK;
				this->p2Server->sendData(package2Send,2);
				break;
			case RRQ:
				currentState.setStateCode(SENDING);
				for (uint i = 0; (i <= MAX_DATA_SIZE - 2) && (myEvent->received[i + 2] != 0); i++)
					this->fileName[i] = myEvent->received[i + 2];
				this->myFile.open(this->fileName, fstream::in);
				this->fileSize = myFile.gcount();
				package2Send[1] = DATA;
				if (fileSize >= MAX_DATA_SIZE)
				{
					for (int i = 0; i <= MAX_DATA_SIZE; i++)
					{
						char c;
						myFile.get(c);
						package2Send[i + 2] = c;
					}
					fileSize -= MAX_DATA_SIZE;
					this->p2Server->sendData(package2Send, MAX_DATA_SIZE + 2);
				}
				else if (fileSize < MAX_DATA_SIZE)
				{
					for (int i = 0; i <= fileSize; i++)
					{
						char c;
						myFile.get(c);
						package2Send[i + 2] = c;
					}
					this->p2Server->sendData(package2Send, (uint)fileSize + 2);
					fileSize = 0;
				}
				break;
			default:
				package2Send[1] = EV_ERROR;
				this->p2Server->sendData(package2Send, 2);
				break;
			}
		}
		else if (currentState.getStateCode() == RECEIVING)
		{
			package2Send[0] = 0;
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
			default:
				package2Send[1] = EV_ERROR;
				this->p2Server->sendData(package2Send, 2);
				break;
			}
		}
		else if (SENDING)
		{
			package2Send[0] = 0;
			switch (myEvent->eventCode) {
			case ACK:
				package2Send[1] = DATA;
				this->myFile.seekg(myFile.gcount() - fileSize);
				char c;
				for (int i = 0; i <= MAX_DATA_SIZE; i++)
				{
					myFile.get(c);
					package2Send[i + 2] = c;
				}
				if ((myFile.gcount() - fileSize) >= MAX_DATA_SIZE)
					fileSize -= MAX_DATA_SIZE;
				else
					fileSize = 0;
				this->p2Server->sendData(package2Send, MAX_DATA_SIZE + 2);
				break;
			default:
				package2Send[1] = EV_ERROR;
				this->p2Server->sendData(package2Send, 2);
				break;
			}
		}
	}
	else
		this->p2Server->sendData(lastPackageSent, MAX_DATA_SIZE + 2);
	for (int i = 0; i <= (MAX_DATA_SIZE+2); i++)
		lastPackageSent[i] = package2Send[i];
	return;
}	
