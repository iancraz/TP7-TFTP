#pragma once
#include <boost/chrono.hpp>
#include <boost/timer/timer.hpp>
#include <cstdint>
#include "GenericEvent.h"
#define NO_EVENT -1
#define SERVER 0
#define CLIENT 1
class eventGenerator
{
public:
	eventGenerator(void * _pointer,char type);
	eventGenerator();
	void setEventGenerator(void * _pointer, char type);
	int getNextEvent();
	genericEvent newEvent;
protected:
	boost::timer::cpu_timer eventTimer;
	boost::timer::cpu_times pastTime;
	void * pointer;
	char type;
};
