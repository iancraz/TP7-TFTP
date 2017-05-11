#include "GenericState.h"

genericState::genericState()
{
	stateCode = WAITING;
	return;
}

int genericState::getStateCode()
{
	return stateCode;
}

void genericState::setStateCode(int _stateCode)
{
	this->stateCode = _stateCode;
	return;
}
