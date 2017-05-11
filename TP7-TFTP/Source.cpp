#include <iostream>
#include <ctime>
#include "GenericEvent.h"
#include "GenericState.h"
bool initProgram(void);

using namespace std;

int main(void)
{
	bool isServer = initProgram();
	bool exit = false;
	genericEvent myEvent;
	while (!exit)
	{
		
	}
	return EXIT_SUCCESS;
}

bool initProgram(void)
{
	char temp;
	cout << "Ingrese C si desea actuar como CLIENTE, o S si desea actuar como Servidor" << endl;
	cin >> temp;
	switch (temp) {
	case 'C':
		return false;
	case 'S':
		return true;
	default:
		return true;
	}
}
