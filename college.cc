/*****************************************************************
	Liam Hendrickson
	Project 3
	CS 2401 - John Dolan
	Ohio University
	Implementation for college class
******************************************************************/

#include <string>
#include <iostream>
#include <fstream>
#include "college.h"
#include "node.h"
#include "course.h"

using namespace std;

college::college()
{
	set_name("");
	head=NULL;

}

college::college(string username)
{
	head =new node;
	name = username;

}

college::~college()
{
	node* tmpptr;

	while(head->link()!=NULL)
	{
		tmpptr=head;
		head=head->link();
		delete tmpptr;
	}
	delete head;
}

college::college(const college& other)
{
	node* cursor2;//cursor for list being copied

	head= new node(other.head->data());
	set_name(other.name);

	cursor2 = other.head;

	while(cursor2->link() != NULL)
	{
	add(cursor2->link()->data());
	cursor2= cursor2->link();
	}
}

void college:: operator=(const college& other)
{
	node* tmpptr;
	node* cursor1;
	node* cursor2;

	if(this==&other)
		return;

	while(head->link()!=NULL)
        {
                tmpptr=head;
                head=head->link();
                delete tmpptr;
        }
	delete head;
	head = new node;
	name = other.name;

        head->data() = other.head->data();
        cursor1 = head;
        cursor2 = other.head;

        while(cursor2->link() != NULL)
        {
                cursor1->set_link(new node);
                cursor2=cursor2->link();
                cursor1=cursor1->link();
                cursor1->data() = cursor2->data();
        }
        cursor1->set_link(new node);
        cursor1 = cursor1->link();
        cursor1->data() = cursor2->data();



}

void college:: add(const course& added)
{
	node* cursor;
	node* tmpptr;

	cursor=head;

	if(head == NULL)
	{
		head=new node(added);
		return;
	}

	if(head->data()>added)
	{
		tmpptr=head;
		head = new node(added, tmpptr);
		return;
	}
	cursor =head;
	while(cursor->link() != NULL)
	{
		if(cursor->link()->data()>added)
		{
			tmpptr=cursor->link();
			cursor->set_link(new node(added, tmpptr));
			return;
		}
		cursor = cursor->link();
	}

	cursor->set_link(new node(added));



}

void college:: display(ostream& cout)const
{
	node* cursor=head;

	cout<< head->data();

	while(cursor->link()!=NULL)
	{
		cout<< '\n'<< cursor->link()->data()<<endl;
		cursor =cursor->link();
	}

}

void college:: remove(const string& removed)
{
	node* cursor = head;
	node* tmpptr;

	if(head->data().get_course_number() == removed)
	{
		tmpptr = head;
		head=head->link();
		delete tmpptr;
		return;
	}


	while(cursor->link() != NULL)
	{
		if(cursor->link()->data().get_course_number() == removed)
		{
			tmpptr = cursor->link();
			cursor->set_link(cursor->link()->link());
			delete tmpptr;
			return;
		}
		cursor=cursor->link();
	}

	cout<<"\nCourse not found, please make sure course is entered correctly\n"<<endl;

}

double college:: hours()const
{
	node* cursor=head;
	double hours = 0;

	hours+= head->data().get_hours();

	while(cursor->link() != NULL)
	{
		hours+= cursor->link()->data().get_hours();
		cursor=cursor->link();
	}
	return hours;
}

double college:: gpa()const
{
	node* cursor=head;
	double calculated;
	double total_hours = 0;
	double credits=0;

	total_hours+=head->data().get_hours();
	credits+=(head->data().get_hours() * head->data().get_number_grade());

	while(cursor->link() != NULL)
	{
		total_hours += cursor->link()->data().get_hours();
        	credits += (cursor->link()->data().get_hours() * cursor->link()->data().get_number_grade());
		cursor = cursor ->link();
	}

	return calculated = credits/total_hours;
}

void college::load(istream& ins)
{
	course tmp;
	string username;
	getline(ins, username);
	set_name(username);

	ins>>tmp;

	while(!ins.eof())
	{
		add(tmp);
		ins>>tmp;
	}
}

void college::save(ostream& outs)
{
	node* cursor=head;

	outs<<name<<endl;

	outs<< head->data();

	while(cursor->link() != NULL)
	{
		outs<< cursor->link()->data();
		cursor = cursor->link();
	}
}
