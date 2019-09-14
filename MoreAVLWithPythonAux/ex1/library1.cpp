/*
 * library1.cpp
 *
 *  Created on: Dec 6, 2016
 *      Author: Ilya Kotlov
 */

#include "library1.h"
#include "DST.h"

using std::bad_alloc;

void* Init(){
	DST* ds = new DST();
	return (void*)ds;
}

StatusType AddTeam(void *DS, int teamID){
	if(!DS || teamID <= 0){
		return INVALID_INPUT;
	}
	try{
		((DST*)DS)->addTeam(teamID);
	} catch(bad_alloc& e){
		return ALLOCATION_ERROR;
	} catch(DSTTeamAlreadyExist& e){
		return FAILURE;
	}
	return SUCCESS;
}

StatusType AddStudent(void *DS, int studentID, int grade, int power){
	if(!DS || studentID <= 0 || grade < 0 || power <= 0){
		return INVALID_INPUT;
	}
	try{
		((DST*)DS)->addStudent(studentID, grade, power);
	} catch(bad_alloc& e){
		return ALLOCATION_ERROR;
	} catch(DSTStudentAllreadyExist& e){
		return FAILURE;
	}
	return SUCCESS;
}

StatusType MoveStudentToTeam(void *DS, int studentID, int teamID){
	if(!DS || studentID <= 0 || teamID <= 0){
		return INVALID_INPUT;
	}
	try{
		((DST*)DS)->addStudentToTeam(studentID, teamID);
	} catch(bad_alloc& e){
		return ALLOCATION_ERROR;
	} catch(DSTTeamDoesNotExist& e){
		return FAILURE;
	}
	return SUCCESS;
}

StatusType RemoveStudent(void *DS, int studentID){
	if(!DS || studentID <= 0){
		return INVALID_INPUT;
	}
	try{
		((DST*)DS)->removeStudent(studentID);
	} catch(bad_alloc& e){
		return ALLOCATION_ERROR;
	} catch(DSTStudentDoesNotExist& e){
		return FAILURE;
	}
	return SUCCESS;
}

StatusType IncreaseLevel(void *DS, int grade, int powerIncrease){
	if(!DS || grade < 0 || powerIncrease<=0){
		return INVALID_INPUT;
	}
	try{
		((DST*)DS)->increaseLevel(grade, powerIncrease);
	} catch(bad_alloc& e){
		return ALLOCATION_ERROR;
	} catch(DSTInvailedInput& e){
		return INVALID_INPUT;
	}
	return SUCCESS;
}

StatusType GetMostPowerful(void *DS, int teamID, int *studentID){
	if(!DS || !studentID || teamID==0){
		return INVALID_INPUT;
	}
	int ID;
	try{
		ID = ((DST*)DS)->getMostPowerful(teamID).getStudentID();
	} catch(bad_alloc& e){
		return ALLOCATION_ERROR;
	} catch(DSTTeamDoesNotExist& e){
		return FAILURE;
	}
	assert(ID>0 || ID==-1);
	*studentID =ID;
	return SUCCESS;
}

StatusType GetAllStudentsByPower(void *DS, int teamID, int **students,
								 int *numOfStudents){
	if(!DS || teamID==0 || !students || !numOfStudents){
		return INVALID_INPUT;
	}
	Student** studentsArray = NULL;
	try{
		studentsArray = ((DST*)DS)->getAllStudentsByPower(teamID, numOfStudents);
	} catch(bad_alloc& e){
		return ALLOCATION_ERROR;
	} catch(DSTTeamDoesNotExist& e){
		free(studentsArray);
		return FAILURE;
	}
	assert((studentsArray==NULL&&*numOfStudents==0)
			|| (studentsArray&&*numOfStudents>0));
	if (*numOfStudents > 0) {
		*students = (int*)malloc((sizeof(int))*(*numOfStudents));
		if (!(*students)) {
			free(studentsArray); //TODO: check correct release;
			return ALLOCATION_ERROR;
		}
		for (int i = 0; i < *numOfStudents; i++) {
			//assert(students[i]);
			assert(studentsArray);
			(*students)[i] = studentsArray[i]->getStudentID();
		}

	} else {
		*students = NULL;
	}
	free(studentsArray);
	return SUCCESS;
}

void Quit(void** DS){
	delete((DST*)(*DS));
	*DS = NULL;
}
