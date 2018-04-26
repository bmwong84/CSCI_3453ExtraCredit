*******************************************************
*  Name      :      Bryant Wong    
*  Student ID:      107571009           
*  Class     :  CSC 3453         
*  HW#       :  ExtraLab              
*  Due Date  :  Dec 1, 2017
*******************************************************


                 Read Me


*******************************************************
*  Description of the program
*******************************************************

This program simulates old HDD disk scheduling algorithms: First Come First Serve(FCFS),
Shortest Seek Time First (SSTF), SCAN, and C-LOOK.  The output gives the track of the head
movement from cylinder to cylinder throughout the program as well as a total number of cylinders
traveled.
The input file should be named input.txt (or whatever file you have)

*******************************************************
*  Source files
*******************************************************

Name:  main.cpp
   Main program.  This has member function calls that contains all of the actual code.

Name:  DiskReplacement.cpp
   Holds all of the code for the algorithms as well as menu functions and associated search
algorithms as well as read data function.

Name:  DiskReplacement.h
   Holds the class for DiskReplacement and any associated function prototypes used in the cpp. 

   
   
*******************************************************
*  Circumstances of programs
*******************************************************

Compiles and runs on csegrid.  

Developed on Visual Studio Community 2017 version 15.3.2.  


*******************************************************
*  How to build and run the program
*******************************************************


    You should see a directory named won1009 with the files:
        main.cpp
	DiskReplacement.cpp
	DiskReplacement.h
        makefile
	input.txt
        Readme.txt


    Compile the program by:
    % make

Run the program by:
   % ./extraLab

Delete the obj files, executables, and core dump by
   %./make clean
