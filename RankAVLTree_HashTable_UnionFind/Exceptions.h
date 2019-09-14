#ifndef MTM_EXCEPTIONS_H
#define MTM_EXCEPTIONS_H

class MtmException {};
class TreeException {};
class TrollException {};
class TeamException {};
class DSTException {};

class MapException: public MtmException {};
class MapElementNotFoundException : public MapException {};
class MapElementAlreadyExistException : public MapException {};

class TreeElementNotFoundException : public TreeException {};
class TreeEmpty : public TreeException {};

class TrollInvailedInput : public TrollException{};
class TrollBadID : public TrollException{};

class TeamInvailedInput : public TeamException{};

class DSTTrollAlreadyExist : public DSTException{};
class DSTTrollDoesNotExist : public DSTException{};
class DSTInvailedInput : public DSTException{};
class DSTFAILURE : public DSTException{};
#endif
