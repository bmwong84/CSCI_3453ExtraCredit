//Bryant Wong
//CSCI 3453 Extra Lab
#ifndef _DISKSCHEDULER
#define _DISKSCHEDULER
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>

class DiskScheduler
{
private:
	std::vector<int> seekRequests;
	char upDown;				//up = 1, down =0
	int initialPosition=0;		//between 0-199
	int totalDistanceTraveled=0;


public:
	DiskScheduler();
	void runMenu();
	void readData();
	void getStartPosition();
	void printOutput();
	void runFCFS();
	void runSSTF();	//shortest seek time first
	int findClosestCylinder(int currentCylinder);
	void runSCAN();
	void runCLOOK();

};

#endif // !1

