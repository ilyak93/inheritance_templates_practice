#ifndef MTM4_BROKER_H
#define MTM4_BROKER_H

#include <map>
#include <list>
#include "SortedSet.h"
#include "Publisher.h"
#include "Subscriber.h"
#include "Client.h"
#include "BrokerIfc.h"

using std::list;
using std::map;
using std::string;

class Broker: public BrokerIfc {

	class CompareClients {
	public:
		bool operator()(const Client* c1, const Client* c2) const;
	};

	/*class CompareClientsById {
	public:
		bool operator()(const Client* c1, const Client* c2) const;
	};*/

	class CompareTopics {
	public:
		bool operator()(const Topic& t1, const Topic& t2) const;
	};

	virtual void subscribeToTopic(const Subscriber& sub, const Topic& t)
			override;

	virtual void unsubscribeToTopic(const Subscriber& sub, const Topic& t)
			override;

	virtual void publishTopic(const Publisher& pub, const Topic& t) override;

	virtual void unpublishTopic(const Publisher& pub, const Topic& t) override;

	virtual void publishMessage(const Topic& t, const std::string& message,
			const Client& sender) const override;

public:
	Broker() = default;
	Broker(const Broker& broker) = default;
	Broker& operator=(const Broker& broker) = default;
	~Broker(){};
	void sendMaintenanceMessageAny(list<Topic> topics, string message);
	void sendMaintenanceMessageAll(list<Topic> topics, string message);

private:
	map<const Client*, SortedSet<Topic, CompareTopics>, CompareClients>
														clients_topics_map;
	map<Topic, SortedSet<const Client*, CompareClients>, CompareTopics>
													 topic_subscribers_map;
};

#endif //MTM4_BROKER_H

