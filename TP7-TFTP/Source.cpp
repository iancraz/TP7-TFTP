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
	while (!exit)
	{
		
	}
	return EXIT_SUCCESS;
}

bool initProgram(void)
{
	char temp;
	cout << "Type C if you want to act as a Client or S if you want to act as a Server." << endl;
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
