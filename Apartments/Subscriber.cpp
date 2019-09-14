/*
 * Subscriber.cpp
 *
 *  Created on: Jun 19, 2016
 *      Author: Ilya
 */

#include "Subscriber.h"
#include <sstream>
#include <algorithm>

using std::endl;
using std::stringstream;
using std::remove_if;

Subscriber::Subscriber(int priority, BrokerIfc& broker,
		std::ostream& messagesSink) :
		Client::Client(priority, broker, messagesSink) {
}

void Subscriber::subscribeToTopic(const Topic& t) {
	try {
		this->broker->subscribeToTopic(*this, t);
	} catch (NonPublishedTopic&) {
		return;
	}
	for (list<Topic>::iterator itr = this->topics.begin(); itr != topics.end();
			++itr) {
		if (*itr == t)
			return;
	}
	topics.push_back(t);
}

void Subscriber::unsubscribeToTopic(const Topic& t) {
	this->broker->unsubscribeToTopic(*this, t);
	for (list<Topic>::iterator itr = this->topics.begin(); itr != topics.end();
			++itr) {
		if (*itr == t) {
			topics.remove(t);
			break;
		}
	}
}

void Subscriber::unsubscribeAll() {
	for (list<Topic>::iterator itr = this->topics.begin(); itr != topics.end();
			++itr) {
		this->broker->unsubscribeToTopic(*this, *itr);
	}
	topics.clear();
}

void Subscriber::receiveMessage(const string& message, const Topic& t, const Client& c) const {
	if (this) {
		for (list<Topic>::const_iterator itr = topics.begin(); itr != topics.end(); ++itr) {
			if (*itr == t) {
				this->messagesSink << "Topic: " << t << ". Sender: #" << c.getId()
					<< ". Receiver: #" << this->getId() << ". Message: " << message << endl;
				return;
			}
		}
		throw Client::NonSubscribedTopic();
	}
}
