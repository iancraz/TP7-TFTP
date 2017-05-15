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

}