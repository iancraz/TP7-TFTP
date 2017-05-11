#include "EventGenerator.h"

eventGenerator::eventGenerator(void * pointer, int type)
{
	if (type == SERVER)
	{
		this->p2Client = NULL;
		this->p2Server = (Server*)pointer;
	}
	else
	{
		this->p2Server = NULL;
		this->p2Client = (Client *)pointer;
	}
	this->eventCode = NO_EVENT;
	this->received = NULL;
	this->sent = NULL;
	this->eventTimer.start();
	this->currentTime = this->eventTimer.elapsed();
	return;
}

int eventGenerator::getNextEvent()
{

}