/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Logger.h"
#include <fstream>
#include <iostream>
#include <ctime>
using namespace std;

ofstream outFS;

Logger::Logger() {
	//automatically only goes to logFile right now, would change if new file should be created everytime
	outFS.open("logFile.txt");
}

void Logger::Periodic() {}

//doesn't need the fileName param at the moment but leaving it for now
void Logger::LoadDataToFile(string fileName, string varName, double varValue) {
	
	//checks to make sure the file was found and opened successfully
	if (!outFS.is_open()) {
		cout << "Could not open file logFile.txt." << endl;
	}

    time_t ttime = time(0);
    
    char* dt = ctime(&ttime);

	while (!outFS.eof()) {
        outFS << dt << endl;
		outFS << varName << ": " << varValue;
		outFS << endl;
	}
	cout << "Load complete" << endl;
 

}