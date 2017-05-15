#include "ClientDispatcher.h"
#include <boost/asio.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <cstdint>
typedef unsigned int uint;

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

void clientDispatcher::nextStep(void)
{
	if (this->myEvent->eventCode != TIMEOUT)
	{
		if (this->currentState.getStateCode() == WAITING)
		{
			whatDoYouWannaDo();
		}
		else if (this->currentState.getStateCode() == SENDING)
		{
			package2Send[0] = 0;
			switch (myEvent->eventCode) {
			case ACK:
				package2Send[1] = DATA;
				this->myFile.seekg(myFile.gcount() - fileSize);
				for (int i = 0, char c; i <= MAX_DATA_SIZE; i++)
				{
					myFile.get(c);
					package2Send[i + 2] = c;
				}
				if ((myFile.gcount() - fileSize) >= MAX_DATA_SIZE)
					fileSize -= MAX_DATA_SIZE;
				else
					fileSize = 0;
				this->p2Client->sendData(package2Send, MAX_DATA_SIZE + 2);
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
					for (int i = 0, char c = 0; (i <= MAX_DATA_SIZE) && (c = myEvent->received[i + 2]); i++)
						myFile.put(c);
				else
					for (int i = 0, char c = 0; (i <= myEvent->amountReceived) && (c = myEvent->received[i + 2]); i++)
						myFile.put(c);
				package2Send[1] = ACK;
				break;
			default:
				package2Send[1] = EV_ERROR;
				this->p2Client->sendData(package2Send, 2);
				break;
			}
		}
	}
	else
		this->p2Client->sendData(lastPackageSent, MAX_DATA_SIZE + 2);
	for (int i = 0; i <= (MAX_DATA_SIZE + 2); i++)
		lastPackageSent[i] = package2Send[i];
	return;
}

