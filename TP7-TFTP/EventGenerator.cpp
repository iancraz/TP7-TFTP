#include "EventGenerator.h"
#include "Server.h"
#include "Client.h"
//typedef enum { TIMER, WRQ, RRQ, DATA, ACK, EV_ERROR }event_t;
typedef unsigned int uint;

eventGenerator::eventGenerator(void * pointer, char type)
{
	this->type = type;
	this->pointer = pointer;
	this->eventCode = NO_EVENT;
	this->received = new char[EV_BUFFERSIZE];
	for (uint i = 0; i <= EV_BUFFERSIZE; i++)
		received[i] = 0;
	this->amountReceived = 0;
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
		this->amountReceived = tempClient->NBReceiveDataFromServer(this->received, EV_BUFFERSIZE);
		break;
	default:
		Server * tempServer;
		tempServer = (Server *)pointer;
		this->amountReceived = tempServer->NBReceiveDataFromClient(this->received, EV_BUFFERSIZE);
		break;
	}
	if (this->amountReceived)
	{
		switch (received[1]) {
		case 1:
			this->eventCode = RRQ;
			break;
		case 2:
			this->eventCode = WRQ;
			break;
		case 3:
			this->eventCode = DATA;
			break;
		case 4:
			this->eventCode = ACK;
			break;
		case 5:
			this->eventCode = EV_ERROR;
			break;
		}
	}
	else
	{
		boost::timer::cpu_times elapsedSeconds = this->eventTimer.elapsed();
		if ((elapsedSeconds.wall - this->pastTime.wall) > 1e9)
		{
			this->eventCode = TIMEOUT;
			this->pastTime = this->eventTimer.elapsed();
		}
	}
	return this->eventCode;
}
