#ifndef MTM_EXCEPTIONS_H
#define MTM_EXCEPTIONS_H

class MtmException {};
class TreeException {};
class TrollException {};
class DSTException {};

class MapException: public MtmException {};
class MapElementNotFoundException : public MapException {};
class MapElementAlreadyExistException : public MapException {};

class TreeElementNotFoundException : public TreeException {};
class TreeEmpty : public TreeException {};

class TrollInvailedInput : public TrollException{};
class TrollPostDoesntExist : public TrollException{};
class TrollPostExist : public TrollException{};
class TrollBadID : public TrollException{};
class TrollNoPosts : public TrollException{};

class DSTTrollAlreadyExist : public DSTException{};
class DSTTrollDoesNotExist : public DSTException{};
class DSTPostAllreadyExist : public DSTException{};
class DSTPostDoesNotExist : public DSTException{};
class DSTInvailedInput : public DSTException{};
#endif
