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
	int getNextEvent();
protected:
	boost::timer::cpu_timer eventTimer;
	boost::timer::cpu_times pastTime;
	genericEvent newEvent;
	void * pointer;
	char type;
};
