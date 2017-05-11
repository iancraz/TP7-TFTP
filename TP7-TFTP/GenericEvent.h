#pragma once
#define MAX_DATA_SIZE	512
typedef enum { TIMER,WRQ,WWQ,DATA,ACK,ERROR, NONE}eventCode_t;

class genericEvent
{
public:
	genericEvent();
	int getEventCode();
	void setEventCode(int _eventCode);
	char eventData[MAX_DATA_SIZE];
protected:
	int eventCode;
	int blockNumber;
};