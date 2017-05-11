#pragma once
typedef enum{RECEIVING,SENDING,WAITING}stateCodes_t;
class genericState
{
public:
	genericState();
	int getStateCode();
	void setStateCode(int _stateCode);
protected:
	int stateCode;
};