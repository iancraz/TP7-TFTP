#include "EventGenerator.h"
#include "Server.h"
#include "Client.h"
typedef unsigned int uint;

eventGenerator::eventGenerator(void * pointer, char type)
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
		case 1:
			newEvent.eventCode = RRQ;
			break;
		case 2:
			newEvent.eventCode = WRQ;
			break;
		case 3:
			newEvent.eventCode = DATA;
			break;
		case 4:
			newEvent.eventCode = ACK;
			break;
		case 5:
			newEvent.eventCode = EV_ERROR;
			break;
		}
	}
	else
	{
		boost::timer::cpu_times elapsedSeconds = this->eventTimer.elapsed();
		if ((elapsedSeconds.wall - this->pastTime.wall) > 1e9)
		{
			newEvent.eventCode = TIMEOUT;
			this->pastTime = this->eventTimer.elapsed();
		}
	}
	return newEvent.eventCode;
}
