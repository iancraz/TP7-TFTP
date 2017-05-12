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

void serverDispatcher::setPackage2Send()
{
	package2Send[0] = 0;
	package2Send[1] = myEvent->eventCode;
	return;
}


void serverDispatcher::nextStep()
{
	if (currentState.getStateCode() == WAITING)
	{
		switch (myEvent->eventCode) {
		case WRQ:
			currentState.setStateCode(RECEIVING);
			for (uint i = 0; (i <= MAX_DATA_SIZE - 2) && (myEvent->received[i + 2] != 0); i++)
				this->fileName[i] = myEvent->received[i + 2];
			this->myFile.open(this->fileName, fstream::app);
			break;
		case RRQ:
			currentState.setStateCode(SENDING);
			for (uint i = 0; (i <= MAX_DATA_SIZE - 2) && (myEvent->received[i + 2] != 0); i++)
				this->fileName[i] = myEvent->received[i + 2];
			this->myFile.open(this->fileName, fstream::in);
			this->fileSize = myFile.gcount();
			setPackage2Send();
			if (fileSize >= MAX_DATA_SIZE)
			{
				for (int i = 0, char c; i <= MAX_DATA_SIZE; i++)
				{
					myFile.get(c);
					package2Send[i + 2] = c;
				}
				fileSize -= MAX_DATA_SIZE;
				this->p2Server->sendData(package2Send, MAX_DATA_SIZE + 2);
			}
			else if (fileSize < MAX_DATA_SIZE)
			{
				for (int i = 0, char c; i <= fileSize; i++)
				{
					myFile.get(c);
					package2Send[i + 2] = c;
				}
				this->p2Server->sendData(package2Send, fileSize + 2);
				fileSize = 0;
			}
			break;
		case ACK:

		}
	}
}