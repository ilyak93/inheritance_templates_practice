#ifndef MTM4_CLIENT_H
#define MTM4_CLIENT_H

#include <exception>
#include <string>
#include "BrokerIfc.h"
#include <iostream>
#include "SortedSet.h"
#include <list>

using std::ostream;
using std::list;

class Client {

public:

	class ClientException: public std::exception {
	};
	class IllegalPriority: public ClientException {
	};
	class NonSubscribedTopic: public ClientException {
	};
	class NonPublishedTopic: public ClientException {
	};

	Client(int priority, BrokerIfc& broker, std::ostream& messagesSink =
			std::cout);

	Client(const Client& c) = delete;

	Client& operator=(const Client&) = delete;

	virtual ~Client(){}

	int getPriority() const;

	int getId() const;

	void receiveMaintenanceMessage(const std::string& s) const;

protected:
	int priority;
	BrokerIfc *broker;
	ostream& messagesSink;
	int id;
	list<Topic> topics;
	static int id_generator;
};

#endif //MTM4_CLIENT_H
