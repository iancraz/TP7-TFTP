#pragma once
#include "Server.h"
#include "Client.h"
#include <boost/chrono.hpp>
#include <boost/timer/timer.hpp>

typedef enum {TIMER, WRQ,RRQ,DATA,ACK,EV_ERROR}event_t;
#define NO_EVENT -1
#define SERVER 0
#define CLIENT 1
class eventGenerator
{
public:
	eventGenerator(void * _pointer,int type);
	int getNextEvent();
protected:
	boost::timer::cpu_timer eventTimer;
	boost::timer::cpu_times currentTime;
	int eventCode;
	char * received;
	char * sent;
	Client * p2Client;
	Server * p2Server;
};

/*
	t.start();
	boost::timer::cpu_times pastTime = t.elapsed();
	double elapsedSeconds = 0.0;

	boost::timer::cpu_times currentTime = t.elapsed();

	if ((currentTime.wall - pastTime.wall) > 1e9)
	{
	elapsedSeconds += (currentTime.wall - pastTime.wall)/1e9;
	pastTime = currentTime;
	cout << "Pasaron " << elapsedSeconds <<" segundos." << endl;
	}
*/