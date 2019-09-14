/*
 * Broker.cpp
 *
 *  Created on: Jun 16, 2016
 *      Author: Ilya
 */

#include "Broker.h"

using std::map;
using std::list;
using std::string;
using std::endl;

bool Broker::CompareClients::operator()(const Client* c1,
		const Client* c2) const {
	return c1->getPriority() == c2->getPriority() ?
			c1->getId() < c2->getId() : c1->getPriority() < c2->getPriority();
}

bool Broker::Broker::CompareTopics::operator()(const Topic& t1, const Topic& t2) const {
	return t1.compare(t2) < 0 ? true : false;
}

void Broker::subscribeToTopic(const Subscriber& sub, const Topic& t) {
	if (t.empty()) return;
	this->clients_topics_map[&sub].insert(t);
	this->topic_subscribers_map[t].insert(&sub);
}

void Broker::unsubscribeToTopic(const Subscriber& sub, const Topic& t) {
	if (t.empty()) return;
	if(this->clients_topics_map[&sub].remove(t) == false) throw Client::NonSubscribedTopic();
	this->topic_subscribers_map[t].remove(&sub);

}

void Broker::publishTopic(const Publisher& pub, const Topic& t) {
	if (t.empty()) return;
	this->clients_topics_map[&pub].insert(t);
}

void Broker::unpublishTopic(const Publisher& pub, const Topic& t) {
	if (t.empty()) return;
	if(this->clients_topics_map[&pub].remove(t) == false) throw Client::NonPublishedTopic();
}

void Broker::sendMaintenanceMessageAny(list<Topic> topics, string message) {
	list<Topic>::iterator t_itr = topics.begin();
	for (map<const Client*, SortedSet<Topic, CompareTopics>, CompareClients>::iterator itr =
			clients_topics_map.begin(); itr != clients_topics_map.end();
			++itr) {
		for (list<Topic>::iterator t_itr = topics.begin();
						t_itr != topics.end(); ++t_itr) {
			if(itr->second.find(*t_itr) != itr->second.end()){
				(*itr).first->receiveMaintenanceMessage(message);
				break;
			}
		}
	}
}
void Broker::sendMaintenanceMessageAll(list<Topic> topics, string message) {
	if (topics.size() != 0) {
		for (map<const Client*, SortedSet<Topic, CompareTopics>, CompareClients>::iterator itr =
			clients_topics_map.begin(); itr != clients_topics_map.end(); ++itr) {
			unsigned int count_all = 0;
			for (list<Topic>::iterator t_itr = topics.begin();
			t_itr != topics.end(); ++t_itr) {
				if (itr->second.find(*t_itr) == itr->second.end()) {
					break;
				}
				count_all++;
			}
			if (count_all == topics.size()) {
				(*itr).first->receiveMaintenanceMessage(message);
			}
		}
	}
}

void Broker::publishMessage(const Topic& t, const string& message,
		const Client& sender) const {
	for(map<Topic, SortedSet<const Client*, CompareClients>, CompareTopics>::const_iterator itr = this->topic_subscribers_map.begin();
			itr != this->topic_subscribers_map.end(); ++itr){
		if(itr->first == t){
			for(SortedSet<const Client*, CompareClients>::iterator subscribers_itr = itr->second.begin();
					subscribers_itr != itr->second.end(); ++subscribers_itr){
				(static_cast<const Subscriber*>(*subscribers_itr))->receiveMessage(message, t, sender);
			}
		}
	}
}




