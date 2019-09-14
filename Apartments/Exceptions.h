#ifndef MTM_EXCEPTIONS_H
#define MTM_EXCEPTIONS_H

class MtmException {};


class SortedSetException: public MtmException {};
class MapElementNotFoundException : public SortedSetException {};
class MapElementAlreadyExistException : public SortedSetException {};


#endif
