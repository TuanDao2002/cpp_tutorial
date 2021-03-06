// bookclub.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "Book.h"
#include "RegularMember.h"
#include "ModeratorMember.h"

using namespace std;

int main()
{
	// 4 book items with 1 rare book item
	Book *b1 = new Book("B001", "Designing Interfaces");
	Book *b2 = new Book("B003", "To Kill a Mockingbird", true);
	Book *b3 = new Book("B002", "Educated");
	Book *b4 = new Book("B004", "A guide to Game Theory");

	// 3 members with 1 moderator member
	RegularMember *m1 = new RegularMember("M001", "Minh Dinh");
	RegularMember *m2 = new RegularMember("M002", "Janet Yong");
	ModeratorMember *m3 = new ModeratorMember("M003", "Anthony Bull");

	// regular member M001 try to borrow 3 normal book items
	m1->borrowing(b1);
	m1->borrowing(b3);
	m1->borrowing(b4);	// this one should fail
	// regular member M001 try to return 2 normal book items
	m1->returning(b1);
	m1->returning(b3);
	// moderator member M003 try to borrow 1 normal book item
	m3->borrowing(b1);
	// moderator member M003 try to borrow 1 rare book item
	m3->borrowing(b2);

    cout << "Program finished\n"; 
}
