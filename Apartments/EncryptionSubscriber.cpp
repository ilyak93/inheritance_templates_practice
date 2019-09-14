/*
 * EncryptionSubscriber.cpp
 *
 *  Created on: Jun 20, 2016
 *      Author: Ilya
 */

#include "EncryptionSubscriber.h"

using std::string;

EncryptionSubscriber::EncryptionSubscriber(int priority, BrokerIfc& broker, char key, ostream& messagesSink) : Subscriber(priority, broker, messagesSink){
	this->key = key;
}

void EncryptionSubscriber::receiveMessage(const string& message, const Topic& t, const Client& c) const{
	string decrypted = message;
	for(string::iterator char_itr = decrypted.begin(); char_itr != decrypted.end(); ++char_itr){
		*char_itr = (*char_itr)^key;
	}
	Subscriber::receiveMessage(decrypted, t, c);
}
