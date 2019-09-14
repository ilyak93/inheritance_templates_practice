/*
 * Client.cpp
 *
 *  Created on: Jun 17, 2016
 *      Author: Ilya
 */

#include "Client.h"

using std::ostream;
using std::endl;

int Client::id_generator = 0;

Client::Client(int priority, BrokerIfc& broker, ostream& messagesSink) :
		priority(priority), broker(&broker), messagesSink(messagesSink), id(
				id_generator++) {
	if (priority < 0) throw Client::IllegalPriority();
}

int Client::getPriority() const {
	if (this) {
		return this->priority;
	}
	return -1;
}

int Client::getId() const {
	if (this) {
		return this->id;;
	}
	return -1;
}

void Client::receiveMaintenanceMessage(const std::string& s) const{
	if (this) {
		this->messagesSink << "Client #" << this->id <<
		" received maintenance message: " << s << endl;
	}
}
