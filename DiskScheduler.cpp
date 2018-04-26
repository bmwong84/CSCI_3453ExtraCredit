//Bryant Wong
//CSCI 3453 Extra Lab
#include "DiskScheduler.h"
#include <cmath>
#include <algorithm>

DiskScheduler::DiskScheduler()
{}

void DiskScheduler::runMenu()
{
	char menuchoice = '0';
	while (menuchoice != '5')
	{
		initialPosition = 0;
		seekRequests.clear();
		totalDistanceTraveled = 0;
		std::cout << "Disk Scheduling Simulation" << std::endl;
		std::cout << "Enter the algorithm to simulate" << std::endl;
		std::cout << "1. First come first serve (FCFS)" << std::endl;
		std::cout << "2. Shortest Seek Time First (SSTF)" << std::endl;
		std::cout << "3. SCAN algorithm" << std::endl;
		std::cout << "4. C-LOOK algorithm" << std::endl;
		std::cout << "5. Exit" << std::endl;
		std::cin >> menuchoice;

		switch (menuchoice)
		{
		case'1':
		{
			readData();
			getStartPosition();
			runFCFS();
			break;
		}
		case'2':
		{
			readData();
			getStartPosition();
			runSSTF();
			break;
		}
		case'3':
		{
			readData();
			getStartPosition();
			runSCAN();
			break;
		}
		case'4':
		{
			readData();
			getStartPosition();
			runCLOOK();
			break;
		}
		case'5':
		{
			break;
		}
		default:
			std::cout << "Invalid choice, enter a valid choice" << std::endl;

		}
	}
}



void DiskScheduler::runFCFS()
{
	std::ofstream outfile;
	std::string filename;
	std::cin.ignore(1);
	std::cout << "Enter an output file name" << std::endl;
	std::getline(std::cin, filename);
	outfile.open(filename.c_str());
	int previousCylinder = initialPosition;
	std::cout << "First Come First Serve with initial cylinder = " << initialPosition << std::endl;
	outfile << "First Come First Serve with initial cylinder = " << initialPosition << std::endl;
	for (int count = 0; count < seekRequests.size(); count++)
	{
		int temp = abs(previousCylinder - seekRequests[count]);
		std::cout << "[" << previousCylinder << "->" << seekRequests[count] << "] ";
		outfile << "[" << previousCylinder << "->" << seekRequests[count] << "] ";
		previousCylinder = seekRequests[count];
		totalDistanceTraveled = totalDistanceTraveled + temp;
	}
	std::cout << std::endl;
	std::cout << "Total number of cylinder movements: " << totalDistanceTraveled << " cylinders" << std::endl;
	outfile << std::endl;
	outfile << "Total number of cylinder movements: " << totalDistanceTraveled << " cylinders" << std::endl;
	outfile.close();
}

void DiskScheduler::runSSTF()
{
	std::ofstream outfile;
	std::string filename;
	std::cin.ignore(1);
	std::cout << "Enter an output file name" << std::endl;
	std::getline(std::cin, filename);
	outfile.open(filename.c_str());
	int previousCylinder = initialPosition;
	int size = seekRequests.size();
	std::cout << "Shortest Seek Time First with initial cylinder = " << initialPosition << std::endl;
	outfile << "Shortest Seek Time First with initial cylinder = " << initialPosition << std::endl;
	for (int count = 0; count < size; count++)
	{
		int currentCylinder = findClosestCylinder(previousCylinder);
		int temp = abs(previousCylinder - currentCylinder);
		std::cout << "[" << previousCylinder << "->" << currentCylinder << "] ";
		outfile << "[" << previousCylinder << "->" << currentCylinder << "] ";
		previousCylinder = currentCylinder;
		totalDistanceTraveled = totalDistanceTraveled + temp;
	}

	std::cout << std::endl;
	std::cout << "Total number of cylinder movements: " << totalDistanceTraveled << " cylinders" << std::endl;
	outfile << std::endl;
	outfile << "Total number of cylinder movements: " << totalDistanceTraveled << " cylinders" << std::endl;
	outfile.close();
}


void DiskScheduler::printOutput()
{
}

void DiskScheduler::runSCAN()
{
	std::ofstream outfile;
	std::string filename;
	std::cin.ignore(1);
	std::cout << "Enter an output file name" << std::endl;
	std::getline(std::cin, filename);
	outfile.open(filename.c_str());
	int previousCylinder = initialPosition;
	seekRequests.push_back(initialPosition);
	std::sort(seekRequests.begin(), seekRequests.end());
	std::cout << "SCAN with initial cylinder = " << initialPosition << std::endl;
	outfile << "SCAN with initial cylinder = " << initialPosition << std::endl;

	int index = 0;
	for (int count = 0; count < seekRequests.size(); count++)			//get index of initial cylinder position
	{
		if (seekRequests[count] == initialPosition)
			index = count;
	}
	if (upDown == '1')    //up
	{
		std::cout << "Initial movement direction is UP" << std::endl;
		outfile << "Initial movement direction is UP" << std::endl;
		for (int count = index+1; count < seekRequests.size(); count++)   //going up
		{
			int temp = abs(previousCylinder - seekRequests[count]);
			std::cout << "[" << previousCylinder << "->" << seekRequests[count] << "] ";
			outfile << "[" << previousCylinder << "->" << seekRequests[count] << "] ";
			previousCylinder = seekRequests[count];
			totalDistanceTraveled = totalDistanceTraveled + temp;
		}
		totalDistanceTraveled = totalDistanceTraveled + (abs(199 - previousCylinder));		//hits the end, rebounds back, adding distance to the end and back to last cylinder processed
		std::cout << "[" << previousCylinder << "->" << "199] ";
		outfile << "[" << previousCylinder << "->" << "199] ";
		previousCylinder = 199;
		for (int count = index-1; count < seekRequests.size() - index; count--)	//going down
		{
			int temp = abs(previousCylinder - seekRequests[count]);
			std::cout << "[" << previousCylinder << "->" << seekRequests[count] << "] ";
			outfile<< "[" << previousCylinder << "->" << seekRequests[count] << "] ";
			previousCylinder = seekRequests[count];
			totalDistanceTraveled = totalDistanceTraveled + temp;
		}
	}
	else if (upDown == '0')//down
	{
		std::cout << "Initial movement direction is DOWN" << std::endl;
		outfile << "Initial movement direction is DOWN" << std::endl;
		for (int count = index-1; count < seekRequests.size() - index; count--)	//going down
		{
			int temp = abs(previousCylinder - seekRequests[count]);
			std::cout << "[" << previousCylinder << "->" << seekRequests[count] << "] ";
			outfile<< "[" << previousCylinder << "->" << seekRequests[count] << "] ";
			previousCylinder = seekRequests[count];
			totalDistanceTraveled = totalDistanceTraveled + temp;
		}
		totalDistanceTraveled = totalDistanceTraveled + previousCylinder;				//rebounds off 0, returns to previous cylinder location
		std::cout << "[" << previousCylinder << "->" << "0] ";
		outfile << "[" << previousCylinder << "->" << "0] ";
		previousCylinder = 0;
		for (int count = index+1; count < seekRequests.size(); count++)   //going up
		{
			int temp = abs(previousCylinder - seekRequests[count]);
			std::cout << "[" << previousCylinder << "->" << seekRequests[count] << "] ";
			outfile << "[" << previousCylinder << "->" << seekRequests[count] << "] ";
			previousCylinder = seekRequests[count];
			totalDistanceTraveled = totalDistanceTraveled + temp;
		}
	}
	std::cout << std::endl;
	std::cout << "Total number of cylinder movements: " << totalDistanceTraveled << " cylinders" << std::endl;
	outfile << std::endl;
	outfile << "Total number of cylinder movements: " << totalDistanceTraveled << " cylinders" << std::endl;
	outfile.close();
}


void DiskScheduler::runCLOOK()
{
	std::ofstream outfile;
	std::string filename;
	std::cin.ignore(1);
	std::cout << "Enter an output file name" << std::endl;
	std::getline(std::cin, filename);
	outfile.open(filename.c_str());
	int previousCylinder = initialPosition;
	seekRequests.push_back(initialPosition);
	std::sort(seekRequests.begin(), seekRequests.end());
	std::cout << "C-LOOK with initial cylinder = " << initialPosition << std::endl;
	outfile << "C-LOOK with initial cylinder = " << initialPosition << std::endl;
	int index = 0;
	for (int count = 0; count < seekRequests.size(); count++)			//get index of initial cylinder position
	{
		if (seekRequests[count] == initialPosition)
			index = count;
	}
	if (upDown == '1')    //up
	{
		std::cout << "Initial movement direction is UP" << std::endl;
		outfile << "Initial movement direction is UP" << std::endl;
		for (int count = index + 1; count < seekRequests.size(); count++)   //going up
		{
			int temp = abs(previousCylinder - seekRequests[count]);
			std::cout << "[" << previousCylinder << "->" << seekRequests[count] << "] ";
			outfile << "[" << previousCylinder << "->" << seekRequests[count] << "] ";
			previousCylinder = seekRequests[count];
			totalDistanceTraveled = totalDistanceTraveled + temp;
		}
		for (int count = 0; count < index; count++)   //going up
		{
			int temp = abs(previousCylinder - seekRequests[count]);
			std::cout << "[" << previousCylinder << "->" << seekRequests[count] << "] ";
			outfile << "[" << previousCylinder << "->" << seekRequests[count] << "] ";
			previousCylinder = seekRequests[count];
			totalDistanceTraveled = totalDistanceTraveled + temp;
		}
	}
	else if (upDown == '0')//down
	{
		std::cout << "Initial movement direction is DOWN" << std::endl;
		outfile << "Initial movement direction is DOWN" << std::endl;
		for (int count = index - 1; count < seekRequests.size() - index-1; count--)	//going down
		{
			int temp = abs(previousCylinder - seekRequests[count]);
			std::cout << "[" << previousCylinder << "->" << seekRequests[count] << "] ";
			outfile << "[" << previousCylinder << "->" << seekRequests[count] << "] ";
			previousCylinder = seekRequests[count];
			totalDistanceTraveled = totalDistanceTraveled + temp;
		}
		for (int count = seekRequests.size()-1; count > index; count--)	//going down
		{
			int temp = abs(previousCylinder - seekRequests[count]);
			std::cout << "[" << previousCylinder << "->" << seekRequests[count] << "] ";
			outfile<< "[" << previousCylinder << "->" << seekRequests[count] << "] ";
			previousCylinder = seekRequests[count];
			totalDistanceTraveled = totalDistanceTraveled + temp;
		}
	}
	std::cout << std::endl;
	std::cout << "Total number of cylinder movements: " << totalDistanceTraveled << " cylinders" << std::endl;
	outfile << std::endl;
	outfile << "Total number of cylinder movements: " << totalDistanceTraveled << " cylinders" << std::endl;
	outfile.close();
}

int DiskScheduler::findClosestCylinder(int currentCylinder)			//for shortest seek time first
{
	int distance = 200;
	int cylinder = 0;
	int index = 0;
	for (int count = 0; count < seekRequests.size(); count++)
	{
		if (abs(currentCylinder - seekRequests[count]) < distance)
		{
			distance = abs(currentCylinder - seekRequests[count]);
			cylinder = seekRequests[count];
			index = count;
		}
	}
	seekRequests[index] = 999999;		//set to very high number so it will never be the closest
	return cylinder;
}
void DiskScheduler::readData()
{
	std::cout << "Enter name of file to read" << std::endl;
	std::string filename;
	std::cin >> filename;
	std::ifstream infile;
	infile.open(filename.c_str());
	std::string temp;
	std::vector<std::string> split;
	while (std::getline(infile, temp))						
	{
		std::istringstream sStream(temp);
		std::string temp2;
		while (std::getline(sStream >> std::ws, temp2, ','))		//split data by commas, ignoring whitespaces
			split.push_back(temp2);
	}
	for (int count = 0; count < split.size(); count++)
	{
		int temp;
		temp = std::stoi(split[count]);			//change string to int
		seekRequests.push_back(temp);
	}
	infile.close();
}

void DiskScheduler::getStartPosition()		//self explanatory
{
	std::cout << "Please enter start position (0-199)" << std::endl;
	int temp;
	std::cin >> temp;
	while (std::cin.fail() || temp > 199 || temp < 0)
	{
		std::cout << "Invalid Entry, enter start position (0-199)" << std::endl;
		std::cin >> temp;
	}
	initialPosition = temp;

	std::cout << "Please enter if the cylinder will start moving up (1) or down (0)" << std::endl;
	char tempChar;
	std::cin >> tempChar;
	while (tempChar != '0' && tempChar != '1')
	{
		std::cout << "Invalid Entry, enter start position (0-199)" << std::endl;
		std::cin >> tempChar;
	}
	upDown = tempChar;
}