#include "ServerDispatcher.h"
#include <boost/asio.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <cstdint>

serverDispatcher::serverDispatcher(genericEvent * receivedEvent, Server * p2Server)
{
	this->myEvent = receivedEvent;
	this->p2Server = p2Server;
	currentState.setStateCode(WAITING);
	return;
}

void serverDispatcher::nextStep()
{
	if (currentState.getStateCode() == WAITING)
	{
		switch (myEvent->eventCode) {
		case WRQ:
			currentState.setStateCode(SENDING);
			
		}
	}
}