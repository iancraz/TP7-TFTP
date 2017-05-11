#include "GenericEvent.h"

genericEvent::genericEvent()
{
	for (int i = 0; i <= MAX_DATA_SIZE; i++)
		eventData[i] = 0;
	eventCode = NONE;
	blockNumber = NONE;
	return;
}

int genericEvent::getEventCode()
{
	return eventCode;
}

void genericEvent::setEventCode(int _eventCode)
{
	this->eventCode = _eventCode;
	return;
}