#pragma once
#include "Server.h"
#include "Client.h"
#include <boost/chrono.hpp>
#include <boost/timer/timer.hpp>
typedef enum {TIMEOUT, WRQ,RRQ,DATA,ACK,EV_ERROR}event_t;
#define NO_EVENT -1
#define SERVER 0
#define CLIENT 1
#define EV_BUFFERSIZE	512
class eventGenerator
{
public:
	eventGenerator(void * _pointer,char type);
	int getNextEvent();
protected:
	boost::timer::cpu_timer eventTimer;
	boost::timer::cpu_times pastTime;
	int eventCode;
	char * received;
	int amountReceived;
	void * pointer;
	char type;
};
