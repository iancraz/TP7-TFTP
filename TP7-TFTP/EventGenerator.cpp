#include "EventGenerator.h"
#include "Server.h"
#include "Client.h"
#define EV_BUFFERSIZE	(MAX_DATA_SIZE+2)
typedef unsigned int uint;

eventGenerator::eventGenerator(void * pointer, char type)
{
	this->type = type;
	this->pointer = pointer;
	this->eventTimer.start();
	this->pastTime = this->eventTimer.elapsed();
	return;
}

eventGenerator::eventGenerator()
{
	this->pointer = NULL;
	return;
}

void eventGenerator::setEventGenerator(void * pointer, char type)
{
	this->type = type;
	this->pointer = pointer;
	this->eventTimer.start();
	this->pastTime = this->eventTimer.elapsed();
	return;
}

int eventGenerator::getNextEvent()
{
	switch (this->type) {
	case CLIENT:
		Client * tempClient;
		tempClient = (Client *)pointer;
		this->newEvent.amountReceived = tempClient->NBReceiveDataFromServer(newEvent.received, EV_BUFFERSIZE);
		break;
	default:
		Server * tempServer;
		tempServer = (Server *)pointer;
		this->newEvent.amountReceived = tempServer->NBReceiveDataFromClient(newEvent.received, EV_BUFFERSIZE);
		break;
	}
	if (this->newEvent.amountReceived)
	{
		switch (newEvent.received[1]) {
		case RRQ:
			newEvent.eventCode = RRQ;
			break;
		case WRQ:
			newEvent.eventCode = WRQ;
			break;
		case DATA:
			newEvent.eventCode = DATA;
			break;
		case ACK:
			newEvent.eventCode = ACK;
			break;
		case EV_ERROR:
			newEvent.eventCode = EV_ERROR;
			break;
		}
	}
	else
		newEvent.eventCode = NONE;
	/*else
	{
		boost::timer::cpu_times elapsedSeconds = this->eventTimer.elapsed();
		if ((elapsedSeconds.wall - this->pastTime.wall) > 1e9)
		{
			newEvent.eventCode = TIMEOUT;
			this->pastTime = this->eventTimer.elapsed();
		}
	}*/
	return newEvent.eventCode;
}
