#ifndef MTM4_PUBLISHER_H
#define MTM4_PUBLISHER_H


#include "Client.h"

using std::string;
using std::cout;

class Publisher : public Client {

public:
	Publisher(int priority, BrokerIfc& broker, ostream& messagesSink = cout);
	Publisher(const Publisher& sub) = delete;
	virtual ~Publisher(){}

	void publishTopic(const Topic& t);
	void unpublishTopic(const Topic& t);
	void unpublishAll();
	virtual void sendMessage(const string& s, const Topic& t);
};


#endif //MTM4_PUBLISHER_H
