#include <iostream>
#include <cstdlib>
#include "RPtst.h"
#include "library2.h"

using namespace std;

bool arraysEqual(int* a, int* b, int n) {
	for (int i = 0; i < n; i++) {
		if (a[i] != b[i]) {
			return false;
		}
	}
	return true;
}

bool testInit() {
	void* dst = Init(5);
	ASSERT_NOT_EQUALS(dst, NULL);
	Quit(&dst);
	return true;
}

bool testAddStudent() {
	void* dst = Init(5);
	ASSERT_NOT_EQUALS(dst, NULL);
	ASSERT_EQUALS(INVALID_INPUT, AddStudent(NULL, 1,1,1)); //null dst
	ASSERT_EQUALS(INVALID_INPUT, AddStudent(dst, 0, 1, 1)); //<=0 other input
	ASSERT_EQUALS(INVALID_INPUT, AddStudent(dst, -1, 1, 1));
	ASSERT_EQUALS(INVALID_INPUT, AddStudent(dst, 1, 0, 1));
	ASSERT_EQUALS(INVALID_INPUT, AddStudent(dst, 1, -1, 1));
	ASSERT_EQUALS(INVALID_INPUT, AddStudent(dst, 1, 1, 0));
	ASSERT_EQUALS(INVALID_INPUT, AddStudent(dst, 1, 1, -1));
	ASSERT_EQUALS(INVALID_INPUT, AddStudent(dst, 1, 6, 1)); //team>n
	ASSERT_EQUALS(SUCCESS, AddStudent(dst, 1, 1, 1));
	ASSERT_EQUALS(FAILURE, AddStudent(dst, 1, 1, 1)); //student_id = 1 exists
	Quit(&dst);
	return true;
}

bool testRemoveStudent() {
	void* dst = Init(5);
	ASSERT_NOT_EQUALS(dst, NULL);
	ASSERT_EQUALS(INVALID_INPUT, RemoveStudent(NULL, 1)); //null dst
	ASSERT_EQUALS(INVALID_INPUT, RemoveStudent(dst, 0)); //student_id<=0
	ASSERT_EQUALS(INVALID_INPUT, RemoveStudent(dst, -1));
	ASSERT_EQUALS(FAILURE, RemoveStudent(dst, 1)); //no such student
	ASSERT_EQUALS(SUCCESS, AddStudent(dst, 1, 1, 1)); //add him
	ASSERT_EQUALS(SUCCESS, RemoveStudent(dst, 1)); //remove him
	ASSERT_EQUALS(FAILURE, RemoveStudent(dst, 1)); //no such student
	Quit(&dst);
	return true;
}

bool testJoinTeams() {
	void* dst = Init(7);
	ASSERT_NOT_EQUALS(dst, NULL);
	ASSERT_EQUALS(INVALID_INPUT, JoinTeams(NULL,1,1)); //null dst
	ASSERT_EQUALS(INVALID_INPUT, JoinTeams(dst, 0, 1)); //<=0 or >n
	ASSERT_EQUALS(INVALID_INPUT, JoinTeams(dst, -1, 1));
	ASSERT_EQUALS(INVALID_INPUT, JoinTeams(dst, 1, 0));
	ASSERT_EQUALS(INVALID_INPUT, JoinTeams(dst, 1, -1));
	ASSERT_EQUALS(INVALID_INPUT, JoinTeams(dst, 8, 1));
	ASSERT_EQUALS(INVALID_INPUT, JoinTeams(dst, 1, 8));
	//testing empty with empty, and empty with non empty(2), so total 3 cases
	// team 1 - empty, team 2 - empty, team 3 - not empty, team 4 - not empty
	// team 5 - empty , team 6 not empty, team 7 - empty
	ASSERT_EQUALS(SUCCESS, AddStudent(dst, 1, 3, 10));
	ASSERT_EQUALS(SUCCESS, AddStudent(dst, 2, 4, 16));
	ASSERT_EQUALS(SUCCESS, AddStudent(dst, 3, 6, 11));
	ASSERT_EQUALS(SUCCESS, AddStudent(dst, 4, 3, 15));
	ASSERT_EQUALS(SUCCESS, AddStudent(dst, 5, 4, 12));
	ASSERT_EQUALS(SUCCESS, AddStudent(dst, 6, 6, 19));
	ASSERT_EQUALS(SUCCESS, AddStudent(dst, 7, 3, 181));
	ASSERT_EQUALS(SUCCESS, AddStudent(dst, 8, 4, 12));
	ASSERT_EQUALS(SUCCESS, AddStudent(dst, 9, 6, 196));
	ASSERT_EQUALS(SUCCESS, JoinTeams(dst, 1, 2)); //1,2 still empty
	ASSERT_EQUALS(SUCCESS, JoinTeams(dst, 3, 4)); //3,4 not empty
	ASSERT_EQUALS(SUCCESS, JoinTeams(dst, 5, 6)); //5,6 not empty
	ASSERT_EQUALS(SUCCESS, JoinTeams(dst, 5, 1)); //5,6,1,2 not empty
	ASSERT_EQUALS(SUCCESS, JoinTeams(dst, 7, 3)); //3,4,7 not empty
	Quit(&dst);
	return true;
}

bool testTeamFight() {
	void* dst = Init(7);
	ASSERT_NOT_EQUALS(dst, NULL);
	ASSERT_EQUALS(INVALID_INPUT, TeamFight(NULL,1,1,1)); //null dst
	ASSERT_EQUALS(INVALID_INPUT, TeamFight(dst, 0, 1, 1));
	ASSERT_EQUALS(INVALID_INPUT, TeamFight(dst, -1, 1, 1));
	ASSERT_EQUALS(INVALID_INPUT, TeamFight(dst, 1, 0, 1));
	ASSERT_EQUALS(INVALID_INPUT, TeamFight(dst, 0, -1, 1));
	ASSERT_EQUALS(INVALID_INPUT, TeamFight(dst, 8, 1, 1));
	ASSERT_EQUALS(INVALID_INPUT, TeamFight(dst, 1, 8, 1));
	ASSERT_EQUALS(INVALID_INPUT, TeamFight(dst, 1, 1, 0));
	ASSERT_EQUALS(INVALID_INPUT, TeamFight(dst, 1, 1, -1));
	// team 1 - empty, team 2 - empty, team 3 - not empty, team 4 - not empty
	// team 5 - empty , team 6 not empty, team 7 - empty
	ASSERT_EQUALS(SUCCESS, AddStudent(dst, 1, 3, 10));
	ASSERT_EQUALS(SUCCESS, AddStudent(dst, 2, 4, 16));
	ASSERT_EQUALS(SUCCESS, AddStudent(dst, 3, 6, 11));
	ASSERT_EQUALS(SUCCESS, AddStudent(dst, 4, 3, 15));
	ASSERT_EQUALS(SUCCESS, AddStudent(dst, 5, 4, 12));
	ASSERT_EQUALS(SUCCESS, AddStudent(dst, 6, 6, 19));
	ASSERT_EQUALS(SUCCESS, AddStudent(dst, 7, 3, 181));
	ASSERT_EQUALS(SUCCESS, AddStudent(dst, 8, 4, 12));
	ASSERT_EQUALS(SUCCESS, AddStudent(dst, 9, 6, 196));
	//ASSERT_EQUALS(SUCCESS, TeamFight(dst, 1, 2, 1));
	ASSERT_EQUALS(SUCCESS, TeamFight(dst, 3, 4, 1));
	ASSERT_EQUALS(SUCCESS, TeamFight(dst, 5, 6, 1));
	ASSERT_EQUALS(SUCCESS, TeamFight(dst, 5, 1, 1));
	ASSERT_EQUALS(SUCCESS, TeamFight(dst, 7, 3, 1));
	ASSERT_EQUALS(SUCCESS, TeamFight(dst, 1, 2, 5));
	ASSERT_EQUALS(SUCCESS, TeamFight(dst, 3, 4, 5));
	ASSERT_EQUALS(SUCCESS, TeamFight(dst, 5, 6, 5));
	ASSERT_EQUALS(SUCCESS, TeamFight(dst, 5, 1, 5));
	ASSERT_EQUALS(SUCCESS, TeamFight(dst, 7, 3, 5));
	ASSERT_EQUALS(SUCCESS, JoinTeams(dst, 1, 2)); //1,2 still empty
	ASSERT_EQUALS(SUCCESS, JoinTeams(dst, 3, 4)); //3,4 not empty
	ASSERT_EQUALS(SUCCESS, JoinTeams(dst, 5, 6)); //5,6 not empty
	ASSERT_EQUALS(SUCCESS, JoinTeams(dst, 5, 1)); //5,6,1,2 not empty
	ASSERT_EQUALS(SUCCESS, JoinTeams(dst, 7, 3)); //3,4,7 not empty
	ASSERT_EQUALS(SUCCESS, TeamFight(dst, 1, 2, 1));
	ASSERT_EQUALS(SUCCESS, TeamFight(dst, 3, 4, 1));
	ASSERT_EQUALS(SUCCESS, TeamFight(dst, 5, 6, 1));
	ASSERT_EQUALS(SUCCESS, TeamFight(dst, 5, 1, 1));
	ASSERT_EQUALS(SUCCESS, TeamFight(dst, 7, 3, 1));
	ASSERT_EQUALS(SUCCESS, TeamFight(dst, 1, 2, 5));
	ASSERT_EQUALS(SUCCESS, TeamFight(dst, 3, 4, 5));
	ASSERT_EQUALS(SUCCESS, TeamFight(dst, 5, 6, 5));
	ASSERT_EQUALS(SUCCESS, TeamFight(dst, 5, 1, 5));
	ASSERT_EQUALS(SUCCESS, TeamFight(dst, 7, 3, 5));
	Quit(&dst);
	return true;
}

bool testGetNumOfWins() {
	void* dst = Init(8);
	ASSERT_NOT_EQUALS(dst, NULL);
	int* wins = (int*) malloc(sizeof(int));
	ASSERT_EQUALS(INVALID_INPUT, GetNumOfWins(NULL, 1, wins)); //null dst
	ASSERT_EQUALS(INVALID_INPUT, GetNumOfWins(dst, 0, wins));
	ASSERT_EQUALS(INVALID_INPUT, GetNumOfWins(dst, -1, wins));
	ASSERT_EQUALS(INVALID_INPUT, GetNumOfWins(dst, 9, wins));
	ASSERT_EQUALS(INVALID_INPUT, GetNumOfWins(dst, 1, NULL)); //null ptr
	// team 1 - empty, team 2 - empty, team 3 - not empty and strongest
	//team 4 - not empty and 2nd strongest
	//team 5 - empty , team 6 not empty and third storngest, team 7 - empty
	// team 8 - not empty, 1 strong x men
	// team 3 - 5 x mens
	// team 4 - 4 x mens
	// team 6 - 3 x mens
	for (int i = 1; i <= 5; i++) {
		ASSERT_EQUALS(SUCCESS, AddStudent(dst, i, 3, 300));
	}
	for (int i = 1; i <= 4; i++) {
		ASSERT_EQUALS(SUCCESS, AddStudent(dst, i + 5, 4, 100));
	}
	for (int i = 1; i <= 3; i++) {
		ASSERT_EQUALS(SUCCESS, AddStudent(dst, i + 9, 6, 100));
	}
	ASSERT_EQUALS(SUCCESS, AddStudent(dst, 13, 8, 3000));
	//wins = 0 at the start
	for (int i = 1; i <= 0; i++) {
		ASSERT_EQUALS(SUCCESS, GetNumOfWins(dst, i, wins));
		ASSERT_EQUALS(0, *wins);
	}
	//fight between two empty teams, so it's a tie
	ASSERT_EQUALS(SUCCESS, TeamFight(dst, 1, 2, 1));
	ASSERT_EQUALS(SUCCESS, GetNumOfWins(dst, 1, wins));
	ASSERT_EQUALS(0, *wins);
	ASSERT_EQUALS(SUCCESS, GetNumOfWins(dst, 2, wins));
	ASSERT_EQUALS(0, *wins);
	//team 8 should win: 3000>5*200
	ASSERT_EQUALS(SUCCESS, TeamFight(dst, 3, 8, 5));
	ASSERT_EQUALS(SUCCESS, GetNumOfWins(dst, 3, wins));
	ASSERT_EQUALS(0, *wins);
	ASSERT_EQUALS(SUCCESS, GetNumOfWins(dst, 8, wins));
	ASSERT_EQUALS(1, *wins);
	//now we'll join 3 and 8
	ASSERT_EQUALS(SUCCESS, JoinTeams(dst, 3, 8));
	ASSERT_EQUALS(SUCCESS, GetNumOfWins(dst, 3, wins));
	ASSERT_EQUALS(1, *wins);
	//10 fights with 100 wins
	for (int i = 1; i <= 10; i++) {
		ASSERT_EQUALS(SUCCESS, TeamFight(dst, 4, 6, 4));
	}
	ASSERT_EQUALS(SUCCESS, GetNumOfWins(dst, 4, wins));
	ASSERT_EQUALS(10, *wins);
	ASSERT_EQUALS(SUCCESS, GetNumOfWins(dst, 6, wins));
	ASSERT_EQUALS(0, *wins);
	//team 4 - 10 wins, team 3/8 - 1 win
	ASSERT_EQUALS(SUCCESS, JoinTeams(dst, 4, 3));
	//let's see if join also works correctly
	ASSERT_EQUALS(SUCCESS, GetNumOfWins(dst, 4, wins));
	ASSERT_EQUALS(11, *wins);
	ASSERT_EQUALS(SUCCESS, GetNumOfWins(dst, 3, wins));
	ASSERT_EQUALS(11, *wins);
	ASSERT_EQUALS(SUCCESS, GetNumOfWins(dst, 8, wins));
	ASSERT_EQUALS(11, *wins);
	free(wins);
	Quit(&dst);
	return true;
}

bool testGetStudentTeamLeader() {
	void* dst = Init(8);
	ASSERT_NOT_EQUALS(dst, NULL);
	int* leader = (int*) malloc(sizeof(int));
	ASSERT_EQUALS(INVALID_INPUT, GetStudentTeamLeader(NULL,1,leader)); //null dst
	ASSERT_EQUALS(INVALID_INPUT, GetStudentTeamLeader(dst, 0, leader));
	ASSERT_EQUALS(INVALID_INPUT, GetStudentTeamLeader(dst, -1, leader));
	ASSERT_EQUALS(INVALID_INPUT, GetStudentTeamLeader(dst,1,NULL)); // null ptr
	ASSERT_EQUALS(FAILURE, GetStudentTeamLeader(dst, 1, leader));
	//8 students in 8 teams, growing power
	for (int i = 1; i <= 8; i++) {
		ASSERT_EQUALS(SUCCESS, AddStudent(dst, i, i, i * 100));
	}
	//now every student should be leader of his team
	for (int i = 1; i <= 8; i++) {
		ASSERT_EQUALS(SUCCESS, GetStudentTeamLeader(dst, i, leader));
		ASSERT_EQUALS(i, *leader);
	}
	//now we'll join teams by pairs
	for (int i = 1; i <= 4; i++) {
		ASSERT_EQUALS(SUCCESS, JoinTeams(dst, i, i + 1));
		ASSERT_EQUALS(SUCCESS, GetStudentTeamLeader(dst, i, leader));
		ASSERT_EQUALS(i + 1, *leader);
		ASSERT_EQUALS(SUCCESS, GetStudentTeamLeader(dst, i + 1, leader));
		ASSERT_EQUALS(i + 1, *leader);
	}
	ASSERT_EQUALS(SUCCESS, JoinTeams(dst, 1, 3));
	ASSERT_EQUALS(SUCCESS, GetStudentTeamLeader(dst, 1, leader));
	ASSERT_EQUALS(4, *leader);
	ASSERT_EQUALS(SUCCESS, GetStudentTeamLeader(dst, 2, leader));
	ASSERT_EQUALS(4, *leader);
	ASSERT_EQUALS(SUCCESS, GetStudentTeamLeader(dst, 3, leader));
	ASSERT_EQUALS(4, *leader);
	ASSERT_EQUALS(SUCCESS, GetStudentTeamLeader(dst, 4, leader));
	ASSERT_EQUALS(4, *leader);
	ASSERT_EQUALS(SUCCESS, JoinTeams(dst, 5, 7));
	ASSERT_EQUALS(SUCCESS, GetStudentTeamLeader(dst, 5, leader));
	ASSERT_EQUALS(8, *leader);
	ASSERT_EQUALS(SUCCESS, GetStudentTeamLeader(dst, 6, leader));
	ASSERT_EQUALS(8, *leader);
	ASSERT_EQUALS(SUCCESS, GetStudentTeamLeader(dst, 7, leader));
	ASSERT_EQUALS(8, *leader);
	ASSERT_EQUALS(SUCCESS, GetStudentTeamLeader(dst, 8, leader));
	ASSERT_EQUALS(8, *leader);
	ASSERT_EQUALS(SUCCESS, JoinTeams(dst, 1, 6));
	for (int i = 1; i <= 8; i++) {
		ASSERT_EQUALS(SUCCESS, GetStudentTeamLeader(dst, i, leader));
		ASSERT_EQUALS(8, *leader);
	}
	free(leader);
	Quit(&dst);
	return true;
}

int main() {
	RUN_TEST(testInit);
	RUN_TEST(testAddStudent);
	RUN_TEST(testRemoveStudent);
	RUN_TEST(testJoinTeams);
	RUN_TEST(testTeamFight);
	RUN_TEST(testGetNumOfWins);
	RUN_TEST(testGetStudentTeamLeader);
	return 0;
}
