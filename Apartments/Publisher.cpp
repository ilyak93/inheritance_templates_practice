/*
 * Publisher.cpp
 *
 *  Created on: Jun 19, 2016
 *      Author: Ilya
 */

/*
 * Subscriber.cpp
 *
 *  Created on: Jun 19, 2016
 *      Author: Ilya
 */

#include "Publisher.h"

using std::endl;

Publisher::Publisher(int priority, BrokerIfc& broker,
		std::ostream& messagesSink) :
		Client::Client(priority, broker, messagesSink) {}

void Publisher::publishTopic(const Topic& t) {
	this->broker->publishTopic(*this, t);
	for (list<Topic>::iterator itr = this->topics.begin(); itr != topics.end();
			++itr) {
		if (*itr == t)
			return;
	}
	topics.push_back(t);
}

void Publisher::unpublishTopic(const Topic& t) {
	this->broker->unpublishTopic(*this, t);
	for (list<Topic>::iterator itr = this->topics.begin(); itr != topics.end();
			++itr) {
		if (*itr == t) {
			topics.remove(t);
			break;
		}
	}
}

void Publisher::unpublishAll() {
	for (list<Topic>::iterator itr = this->topics.begin(); itr != topics.end();
			++itr) {
		this->broker->unpublishTopic(*this, *itr);
	}
	topics.clear();
}

void Publisher::sendMessage(const string& message, const Topic& t) {
	if (this) {
		broker->unpublishTopic(static_cast<Publisher&>(*this), t);
		broker->publishTopic(*this, t);

		broker->publishMessage(t, message, *this);
	}
}

