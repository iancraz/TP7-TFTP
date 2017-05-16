#include "GenericEvent.h"

genericEvent::genericEvent()
{
	this->received = new char[MAX_DATA_SIZE];
	for (int i = 0; i <= MAX_DATA_SIZE; i++)
		this->received[i] = 0;
	this->eventCode = NONE;
	this->blockNumber = NONE;
	this->amountReceived = 0;
	return;
}

genericEvent::~genericEvent()
{
	delete received;
	return;
}