#ifndef MTM4_SUBSCRIBER_H
#define MTM4_SUBSCRIBER_H


#include "Client.h"

using std::ostream;
using std::string;
using std::cout;

class Subscriber : public Client {

public:
	Subscriber(int priority, BrokerIfc& broker, ostream& messagesSink = cout);
	Subscriber(const Subscriber& sub) = delete;
	virtual ~Subscriber(){}

	void subscribeToTopic(const Topic& t);
	void unsubscribeToTopic(const Topic& t);
	void unsubscribeAll();
	virtual void receiveMessage(const string& message, const Topic& t, const Client& c) const;

};


#endif //MTM4_SUBSCRIBER_H
