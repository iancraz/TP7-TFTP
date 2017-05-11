#pragma once
#define MAX_DATA_SIZE	512
typedef enum { TIMEOUT,WRQ,RRQ,DATA,ACK,EV_ERROR, NONE}eventCode_t;

class genericEvent
{
public:
	genericEvent();
	~genericEvent();
	char * received;
	size_t amountReceived;
	int eventCode;
	int blockNumber;
};
