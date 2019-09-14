#ifndef MTM_EXCEPTIONS_H
#define MTM_EXCEPTIONS_H

class MtmException {};
class TreeException {};
class StudentException {};
class TeamException {};
class DSTException {};

class MapException: public MtmException {};
class MapElementNotFoundException : public MapException {};
class MapElementAlreadyExistException : public MapException {};

class TreeElementNotFoundException : public TreeException {};
class TreeEmpty : public TreeException {};

class TeamInvailedInput : public TeamException{};
class TeamStudentDoesntExist : public TeamException{};
class TeamStudentExist : public TeamException{};
class TeamBadID : public TeamException{};
class TeamNoStudents : public TeamException{};

class StudentInvailedInput : public StudentException{};
class StudentBadID : public StudentException{};

class DSTTeamAlreadyExist : public DSTException{};
class DSTTeamDoesNotExist : public DSTException{};
class DSTStudentAllreadyExist : public DSTException{};
class DSTStudentDoesNotExist : public DSTException{};
class DSTInvailedInput : public DSTException{};
class DSTFAILURE : public DSTException{};
#endif
