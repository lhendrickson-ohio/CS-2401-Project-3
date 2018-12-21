/***************************************************************
	Liam Hendrickson
	Project 3
	CS 2401 - John Dolan
	Ohio University
	header file for the college class
****************************************************************/
#ifndef	COLLEGE_H
#define COLLEGE_H



#include <iostream>
#include <string>
#include <fstream>
#include "course.h"
#include "node.h"

using namespace std;

class college{
	public:
		college();//default constructor
		college(string username); //default constructor
		~college(); //destructor
		void operator= (const college& other); //assignment operator
		college(const college& other); //copy constuctor

		void add(const course& added);//adds a new course
		void display(ostream& outs)const;//displays all courses
		void remove(const string& removed);//removs a course by name
		double hours()const; //returns the number of hours taken
		double gpa()const; //returns the students gpa
		void set_name(const string& entered){name=entered;} //sets the students name

		void load(istream& ins); //loads list from a file
		void save(ostream& outs); //saves list to a file


	private:
		string name;
		node* head;
};

#endif
