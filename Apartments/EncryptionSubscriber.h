//
// Created by izikgo on 5/23/2016.
//

#ifndef MTM4_ENCRYPTIONSUBSCRIBER_H
#define MTM4_ENCRYPTIONSUBSCRIBER_H

#include "Subscriber.h"

class EncryptionSubscriber : public Subscriber {
private:
	char key;

public:
	EncryptionSubscriber(int priority, BrokerIfc& broker, char key,
			ostream& messagesSink = cout);
	EncryptionSubscriber(const EncryptionSubscriber& sub) = delete;
	virtual ~EncryptionSubscriber(){}

	void receiveMessage(const string& message, const Topic& t, const Client& c) const override;

};


#endif //MTM4_ENCRYPTIONSUBSCRIBER_H
