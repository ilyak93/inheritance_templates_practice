/*
 * EncryptionPublisher.cpp
 *
 *  Created on: Jun 20, 2016
 *      Author: Ilya
 */


#include "EncryptionPublisher.h"

EncryptionPublisher::EncryptionPublisher(int priority, BrokerIfc& broker, char key, ostream& messagesSink) : Publisher(priority, broker, messagesSink){
	this->key = key;
}

void EncryptionPublisher::sendMessage(const string& s, const Topic& t) {
	string encrypted = s;
	for(string::iterator char_itr = encrypted.begin(); char_itr != encrypted.end(); ++char_itr){
		*char_itr = (*char_itr)^key;
	}
	Publisher::sendMessage(encrypted, t);
}


