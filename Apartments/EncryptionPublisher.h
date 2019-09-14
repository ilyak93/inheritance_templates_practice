//
// Created by izikgo on 5/23/2016.
//

#ifndef MTM4_ENCRYPTIONPUBLISHER_H
#define MTM4_ENCRYPTIONPUBLISHER_H


#include "Publisher.h"

class EncryptionPublisher : public Publisher {
private:
	char key;

public:
	EncryptionPublisher(int priority, BrokerIfc& broker, char key, ostream& messagesSink = cout);
	EncryptionPublisher(const Publisher& pub) = delete;
	virtual ~EncryptionPublisher(){}

	void sendMessage(const string& s, const Topic& t) override;

};


#endif //MTM4_ENCRYPTIONPUBLISHER_H
