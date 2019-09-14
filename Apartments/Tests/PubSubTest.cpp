/*
  PubSubTest.cpp
  Matam 4
  Created by Ilya Kotlov on 6/24/16.
  Copyright © 2016 Ilya Kotlov. All rights reserved.
*/

#include <cstdlib>
#include "MtmTst.h"
#include "Broker.h"
#include "Client.h"
#include "Publisher.h"
#include "Subscriber.h"
#include "EncryptionSubscriber.h"
#include "EncryptionPublisher.h"

#include <list>
#include <assert.h>

using std::endl;
using std::stringstream;


/*

 We are going to implement a mini-YouTube.
 All the participants (broker, and all clients) are global variables.
 
 The first function test will connect all clients to relevant topics.
 
 The second function test will send maintance messages.
 
 The third function test will send messages between publishers and subscribers.
 
 The fourth function will disconnect the graph, replace the clients with their
 encrypted version and then reconnect the graph by calling the first function.
 
 The second function will be called again to show that the encryption doesn't 
 effect the maintainence messages.
 
 The fifth function will send encrypted messages between pubs and subs.
 
 Other functions:
 constructorDestructorTest - makes many Clients and Brokers. Check valgrind.

 
 
 ALL TOPICS:
 Funny
 TV & Movies
 Gaming
 Music
 Education
*/


//Globals:
Broker youtube;
std::stringstream youtubeServer;
std::stringstream expectedServer;
#define funny "funny"
#define tv "TV & Movies"
#define gaming "gaming"
#define music "Music"
#define education "education"
std::list<Topic> all_topics = {funny, tv, gaming, music, education};
std::string message = "";

#define checkEqual ASSERT_EQUALS(expectedServer.str(), youtubeServer.str())

#define maintanance(c) expectedServer<< "Client #" << c->getId() << \
" received maintenance message: " << message << std::endl;

#define sendMail(to, from, topic) expectedServer << "Topic: " \
<< topic <<". Sender: #" << from->getId() << \
". Receiver: #" << to->getId() << ". Message: " << message << std::endl;


Subscriber client0(2, youtube, youtubeServer);
Subscriber client1(2, youtube, youtubeServer);
Subscriber client2(0, youtube, youtubeServer);
Publisher client3(2, youtube, youtubeServer);
Publisher client4(0, youtube, youtubeServer);
Subscriber client5(1, youtube, youtubeServer);
Subscriber client6(3, youtube, youtubeServer);
Publisher client7(5, youtube, youtubeServer);
Publisher client8(0, youtube, youtubeServer);
Publisher client9(6, youtube, youtubeServer);
Publisher client10(6, youtube, youtubeServer);
Publisher client11(1, youtube, youtubeServer);
Publisher client12(3, youtube, youtubeServer);
Publisher client13(1, youtube, youtubeServer);
Subscriber client14(2, youtube, youtubeServer);
Subscriber client15(3, youtube, youtubeServer);
Subscriber client16(8, youtube, youtubeServer);
Publisher client17(6, youtube, youtubeServer);


Subscriber *outlaw37 = &client0;
Subscriber *G1 = &client1;
Subscriber *FuSioNuReX = &client2;
Publisher *VEVO = &client3;
Publisher *gameRanks = &client4;
Subscriber *naed90 = &client5;
Subscriber *Elmo582 = &client6;
Publisher *UNITY = &client7;
Publisher *pewdiepie = &client8;
Publisher *technion = &client9;
Publisher *TED = &client10;
Publisher *theSmithPlays = &client11;
Publisher *Dreamworks = &client12;
Publisher *failArmy = &client13;
Subscriber *holyShit33 = &client14;
Subscriber *EZIO = &client15;
Subscriber *zombii = &client16;
Publisher *DNews = &client17;

EncryptionSubscriber client0B(2, youtube, 'c' ,youtubeServer);
Subscriber client1B(2, youtube, youtubeServer);//not encrypted
EncryptionSubscriber client2B(0, youtube, 'a', youtubeServer);
EncryptionPublisher client3B(2, youtube, 'b', youtubeServer);
EncryptionPublisher client4B(0, youtube, 'b', youtubeServer);
Subscriber client5B(1, youtube, youtubeServer);//not encrypted
EncryptionSubscriber client6B(3, youtube, 'a', youtubeServer);
EncryptionPublisher client7B(5, youtube, 'b', youtubeServer);
EncryptionPublisher client8B(0, youtube, 'a', youtubeServer);
Publisher client9B(6, youtube, youtubeServer);//not encrypted
EncryptionPublisher client10B(6, youtube, 'a', youtubeServer);
Publisher client11B(1, youtube, youtubeServer);//not encrypted
Publisher client12B(3, youtube, youtubeServer);//not encrypted
EncryptionPublisher client13B(1, youtube, 'c', youtubeServer);
EncryptionSubscriber client14B(2, youtube, 'b', youtubeServer);
EncryptionSubscriber client15B(3, youtube, 'b', youtubeServer);
EncryptionSubscriber client16B(8, youtube, 'a', youtubeServer);
EncryptionPublisher client17B(6, youtube, 'a', youtubeServer);

bool testMaintenanceSingular();//implemented below
bool testLinkAll()
{
    ASSERT_THROW(Client::NonSubscribedTopic, outlaw37->unsubscribeToTopic(funny));
    ASSERT_NO_THROW(outlaw37->subscribeToTopic(funny));
    ASSERT_NO_THROW(outlaw37->subscribeToTopic(funny));
    ASSERT_NO_THROW(outlaw37->subscribeToTopic(funny));
    ASSERT_NO_THROW(outlaw37->subscribeToTopic(funny));
    ASSERT_NO_THROW(outlaw37->subscribeToTopic(funny));
    ASSERT_NO_THROW(outlaw37->unsubscribeToTopic(funny));
    ASSERT_THROW(Client::NonSubscribedTopic, outlaw37->unsubscribeToTopic(funny));
    ASSERT_NO_THROW(outlaw37->subscribeToTopic(funny));
    ASSERT_NO_THROW(outlaw37->subscribeToTopic(funny));
    ASSERT_NO_THROW(outlaw37->subscribeToTopic(funny));
    
    ASSERT_NO_THROW(outlaw37->subscribeToTopic(funny));
    ASSERT_NO_THROW(outlaw37->subscribeToTopic(music));
    ASSERT_NO_THROW(outlaw37->subscribeToTopic(tv));
    ASSERT_NO_THROW(outlaw37->subscribeToTopic(education));
    ASSERT_NO_THROW(outlaw37->subscribeToTopic(gaming));
    ASSERT_NO_THROW(outlaw37->subscribeToTopic(funny));
    ASSERT_NO_THROW(outlaw37->subscribeToTopic(music));
    ASSERT_NO_THROW(outlaw37->subscribeToTopic(tv));
    ASSERT_NO_THROW(outlaw37->subscribeToTopic(education));
    ASSERT_NO_THROW(outlaw37->subscribeToTopic(gaming));
    ASSERT_NO_THROW(outlaw37->subscribeToTopic(funny));
    ASSERT_NO_THROW(outlaw37->subscribeToTopic(music));
    ASSERT_NO_THROW(outlaw37->subscribeToTopic(tv));
    ASSERT_NO_THROW(outlaw37->subscribeToTopic(education));
    ASSERT_NO_THROW(outlaw37->subscribeToTopic(gaming));
    
    ASSERT_NO_THROW(outlaw37->unsubscribeToTopic(funny));
    ASSERT_NO_THROW(outlaw37->unsubscribeToTopic(gaming));
    ASSERT_NO_THROW(outlaw37->unsubscribeToTopic(education));
    
    ASSERT_NO_THROW(holyShit33->subscribeToTopic(funny));
    ASSERT_THROW(Client::NonSubscribedTopic, outlaw37->unsubscribeToTopic(funny));
    ASSERT_NO_THROW(holyShit33->unsubscribeToTopic(funny));
    
    ASSERT_NO_THROW(outlaw37->subscribeToTopic(music));
    ASSERT_NO_THROW(outlaw37->subscribeToTopic(tv));
    ASSERT_NO_THROW(outlaw37->subscribeToTopic(education));
    ASSERT_NO_THROW(outlaw37->subscribeToTopic(gaming));
    
    ASSERT_NO_THROW(holyShit33->subscribeToTopic(music));
    ASSERT_NO_THROW(EZIO->subscribeToTopic(tv));
    ASSERT_NO_THROW(holyShit33->subscribeToTopic(education));
    ASSERT_NO_THROW(FuSioNuReX->subscribeToTopic(gaming));
    
    ASSERT_NO_THROW(naed90->subscribeToTopic(music));
    ASSERT_NO_THROW(naed90->subscribeToTopic(tv));
    ASSERT_NO_THROW(naed90->subscribeToTopic(education));
    ASSERT_NO_THROW(naed90->subscribeToTopic(gaming));
    
    ASSERT_NO_THROW(outlaw37->unsubscribeAll());
    
    ASSERT_NO_THROW(Dreamworks->publishTopic(music));
    ASSERT_NO_THROW(Dreamworks->publishTopic(music));
    ASSERT_NO_THROW(Dreamworks->publishTopic(music));
    ASSERT_NO_THROW(Dreamworks->publishTopic(music));
    ASSERT_NO_THROW(Dreamworks->publishTopic(music));
    ASSERT_NO_THROW(Dreamworks->publishTopic(music));
    ASSERT_NO_THROW(Dreamworks->publishTopic(music));
    ASSERT_NO_THROW(Dreamworks->unpublishTopic(music));
    ASSERT_NO_THROW(Dreamworks->unpublishAll());
    ASSERT_NO_THROW(Dreamworks->publishTopic(music));
    ASSERT_NO_THROW(Dreamworks->unpublishAll());
    ASSERT_THROW(Client::NonPublishedTopic, Dreamworks->unpublishTopic(music));
    
    ASSERT_NO_THROW(naed90->unsubscribeAll());
    ASSERT_THROW(Client::NonSubscribedTopic, naed90->unsubscribeToTopic(tv));
    
    ASSERT_NO_THROW(holyShit33->unsubscribeAll());
    ASSERT_NO_THROW(holyShit33->unsubscribeAll());
    ASSERT_NO_THROW(holyShit33->unsubscribeAll());
    
    ASSERT_NO_THROW(FuSioNuReX->unsubscribeAll());
    ASSERT_NO_THROW(EZIO->unsubscribeAll());
    
    //Now, create actual graph
    //Add subscribers first (testing the FAQ) to show that they get messages
    //even though these topics aren't yet published (they'll get messages
    //when publishers are added and send stuff)
    ASSERT_NO_THROW(outlaw37->subscribeToTopic(funny));
    ASSERT_NO_THROW(outlaw37->subscribeToTopic(tv));
    
    ASSERT_NO_THROW(G1->subscribeToTopic(music));
    ASSERT_NO_THROW(G1->subscribeToTopic(gaming));
    
    ASSERT_NO_THROW(holyShit33->subscribeToTopic(funny));
    ASSERT_NO_THROW(holyShit33->subscribeToTopic(tv));
    
    ASSERT_NO_THROW(EZIO->subscribeToTopic(gaming));
    
    ASSERT_NO_THROW(zombii->subscribeToTopic(gaming));
    
    ASSERT_NO_THROW(FuSioNuReX->subscribeToTopic(gaming));
    ASSERT_NO_THROW(FuSioNuReX->subscribeToTopic(tv));
    ASSERT_NO_THROW(FuSioNuReX->subscribeToTopic(music));
    ASSERT_NO_THROW(FuSioNuReX->subscribeToTopic(funny));
    ASSERT_NO_THROW(FuSioNuReX->subscribeToTopic(education));
    
    ASSERT_NO_THROW(naed90->subscribeToTopic(music));
    ASSERT_NO_THROW(naed90->subscribeToTopic(education));
    ASSERT_NO_THROW(naed90->subscribeToTopic(gaming));
    
    ASSERT_NO_THROW(Elmo582->subscribeToTopic(education));
    
    
    
    ASSERT_NO_THROW(failArmy->publishTopic(funny));
    ASSERT_NO_THROW(failArmy->publishTopic(gaming));
    //should be removed down the road:
    ASSERT_NO_THROW(failArmy->publishTopic(tv));
    ASSERT_NO_THROW(failArmy->unpublishTopic(tv));
    ASSERT_NO_THROW(failArmy->publishTopic(funny));
    ASSERT_NO_THROW(failArmy->unpublishTopic(funny));
    ASSERT_NO_THROW(failArmy->publishTopic(funny));
    
    ASSERT_NO_THROW(Dreamworks->publishTopic(funny));
    ASSERT_NO_THROW(Dreamworks->publishTopic(gaming));
    ASSERT_NO_THROW(Dreamworks->publishTopic(tv));
    ASSERT_NO_THROW(Dreamworks->unpublishTopic(tv));
    ASSERT_NO_THROW(Dreamworks->publishTopic(funny));
    ASSERT_NO_THROW(Dreamworks->unpublishTopic(funny));
    ASSERT_NO_THROW(Dreamworks->publishTopic(funny));
    ASSERT_NO_THROW(Dreamworks->unpublishTopic(funny));
    ASSERT_THROW(Client::NonPublishedTopic, Dreamworks->unpublishTopic(funny));
    ASSERT_NO_THROW(Dreamworks->unpublishTopic(gaming));
    ASSERT_NO_THROW(Dreamworks->publishTopic(tv));
    
    ASSERT_NO_THROW(pewdiepie->publishTopic(tv));
    ASSERT_NO_THROW(pewdiepie->publishTopic(gaming));
    ASSERT_NO_THROW(pewdiepie->publishTopic(funny));
    ASSERT_NO_THROW(pewdiepie->unpublishAll());
    ASSERT_NO_THROW(pewdiepie->publishTopic(tv));
    ASSERT_NO_THROW(pewdiepie->publishTopic(gaming));
    ASSERT_NO_THROW(pewdiepie->publishTopic(funny));
    
    ASSERT_NO_THROW(theSmithPlays->publishTopic(gaming));
    ASSERT_NO_THROW(theSmithPlays->publishTopic(funny));
    
    ASSERT_NO_THROW(gameRanks->publishTopic(gaming));
    ASSERT_NO_THROW(gameRanks->publishTopic(tv));
    
    ASSERT_NO_THROW(VEVO->publishTopic(music));
    
    ASSERT_NO_THROW(UNITY->publishTopic(gaming));
    ASSERT_NO_THROW(UNITY->publishTopic(music));
    ASSERT_NO_THROW(UNITY->publishTopic(education));
    
    ASSERT_NO_THROW(technion->publishTopic(education));
    
    ASSERT_NO_THROW(TED->publishTopic(education));
    
    ASSERT_NO_THROW(DNews->publishTopic(education));
    
    //check that everyone is connected
    if(!testMaintenanceSingular())
    {
        assert(false);
        return false;
    }
    
    return true;
}

//checks topic by topic
bool testMaintenanceSingular()
{
    checkEqual;//nothing yet
    
    message = "ALL FUNNY RAISE YOUR HANDS!";
    list<string> l;
    l.push_back(funny);
    youtube.sendMaintenanceMessageAny(l, message);
    
    maintanance(FuSioNuReX);
    maintanance(pewdiepie);
    maintanance(theSmithPlays);
    maintanance(failArmy);
    maintanance(outlaw37);
    maintanance(holyShit33);
    checkEqual;
    
    message = "NEW! Trailer for star wars this week!";
    l.clear();
    l.push_back(tv);
    youtube.sendMaintenanceMessageAny(l, message);
    
    maintanance(FuSioNuReX);
    maintanance(gameRanks);
    maintanance(pewdiepie);
    maintanance(outlaw37);
    maintanance(holyShit33);
    maintanance(Dreamworks);
    checkEqual;
    
    message = "Ra Ra Oo La La Roma Roma Ma Ga Ga";
    l.clear();
       l.push_back(music);
       youtube.sendMaintenanceMessageAny(l, message);
    
    maintanance(FuSioNuReX);
    maintanance(naed90);
    maintanance(G1);
    maintanance(VEVO);
    maintanance(UNITY);
    checkEqual;
    
    message = "Last night on Runescape, a lvl 37...";
    l.clear();
       l.push_back(gaming);
       youtube.sendMaintenanceMessageAny(l, message);
    
    maintanance(FuSioNuReX);
    maintanance(gameRanks);
    maintanance(pewdiepie);
    maintanance(naed90);
    maintanance(theSmithPlays);
    maintanance(failArmy);
    maintanance(G1);
    maintanance(EZIO);
    maintanance(UNITY);
    maintanance(zombii);
    checkEqual;
    
    message = "David Zileg: The determinant... zzZZ";
    l.clear();
       l.push_back(education);
       youtube.sendMaintenanceMessageAny(l, message);
    
    maintanance(FuSioNuReX);
    maintanance(naed90);
    maintanance(Elmo582);
    maintanance(UNITY);
    maintanance(technion);
    maintanance(TED);
    maintanance(DNews);
    checkEqual;
    
    return true;
}

bool testMaintenance()
{
    if(!testMaintenanceSingular())
    {
        assert(false);
        return false;
    }
    
    message = "EVERYONE! WAKE UP!";
    youtube.sendMaintenanceMessageAny(all_topics, message);
    maintanance(FuSioNuReX);
    maintanance(gameRanks);
    maintanance(pewdiepie);
    maintanance(naed90);
    maintanance(theSmithPlays);
    maintanance(failArmy);
    maintanance(outlaw37);
    maintanance(G1);
    maintanance(VEVO);
    maintanance(holyShit33);
    maintanance(Elmo582);
    maintanance(Dreamworks);
    maintanance(EZIO);
    maintanance(UNITY);
    maintanance(technion);
    maintanance(TED);
    maintanance(DNews);
    maintanance(zombii);
    checkEqual;
    
    message = "Fuze - Only you my man";
    youtube.sendMaintenanceMessageAll(all_topics, message);
    maintanance(FuSioNuReX);
    checkEqual;
    
    youtube.sendMaintenanceMessageAny({}, "Sleep everyone, sleep...");
    checkEqual;
    
    //according to izik, the following should send to no one
    youtube.sendMaintenanceMessageAll({}, "Sleep everyone, sleep...");
    checkEqual;
    
    list<string> l;
    l.push_back("shiiiiit");
    youtube.sendMaintenanceMessageAny(l, message);
    checkEqual;
    
    youtube.sendMaintenanceMessageAll({"shiiiiit", funny}, message);
    checkEqual;
    
    message = "HAHAHAHAHAHA HAHAHA";
    youtube.sendMaintenanceMessageAll({funny, tv}, message);
    maintanance(FuSioNuReX);
    maintanance(pewdiepie);
    maintanance(outlaw37);
    maintanance(holyShit33);
    checkEqual;
    
    youtube.sendMaintenanceMessageAll({tv, funny}, message);
    maintanance(FuSioNuReX);
    maintanance(pewdiepie);
    maintanance(outlaw37);
    maintanance(holyShit33);
    checkEqual;
    
    message = "OPERA OPERA!!!";
    l.clear();
          l.push_back(funny);
          l.push_back(music);
          l.push_back(tv);
          youtube.sendMaintenanceMessageAll(l, message);
    maintanance(FuSioNuReX);
    checkEqual;
    
    youtube.sendMaintenanceMessageAll(l, message);;
    maintanance(FuSioNuReX);
    checkEqual;
    
    message = "this exists?";
    youtube.sendMaintenanceMessageAll({gaming, funny}, message);
    maintanance(FuSioNuReX);
    maintanance(pewdiepie);
    maintanance(theSmithPlays);
    maintanance(failArmy);
    checkEqual;
    
    
    message = "fdsanfsdfinewuobfdsn";
    youtube.sendMaintenanceMessageAny({gaming, funny}, message);
    maintanance(FuSioNuReX);
    maintanance(gameRanks);
    maintanance(pewdiepie);
    maintanance(naed90);
    maintanance(theSmithPlays);
    maintanance(failArmy);
    maintanance(outlaw37);
    maintanance(G1);
    maintanance(holyShit33);
    maintanance(EZIO);
    maintanance(UNITY);
    maintanance(zombii);
    checkEqual;
    
    message = "smart and exotic";
    youtube.sendMaintenanceMessageAny({gaming, education}, message);
    maintanance(FuSioNuReX);
    maintanance(gameRanks);
    maintanance(pewdiepie);
    maintanance(naed90);
    maintanance(theSmithPlays);
    maintanance(failArmy);
    maintanance(G1);
    maintanance(Elmo582);
    maintanance(EZIO);
    maintanance(UNITY);
    maintanance(technion);
    maintanance(TED);
    maintanance(DNews);
    maintanance(zombii);
    checkEqual;
    
    return true;
}

bool sendMessages()
{
    message = "m";
    ASSERT_NO_THROW(failArmy->sendMessage(message, funny));
    sendMail(FuSioNuReX, failArmy, funny);
    sendMail(outlaw37, failArmy, funny);
    sendMail(holyShit33, failArmy, funny);
    checkEqual;
    
    message = "fdason";
    ASSERT_NO_THROW(failArmy->sendMessage(message, gaming));
    sendMail(FuSioNuReX, failArmy, gaming);
    sendMail(naed90, failArmy, gaming);
    sendMail(G1, failArmy, gaming);
    sendMail(EZIO, failArmy, gaming);
    sendMail(zombii, failArmy, gaming);
    checkEqual;
    
    failArmy->unpublishTopic(gaming);
    ASSERT_THROW(Client::NonPublishedTopic, failArmy->sendMessage(message, gaming));
    checkEqual;
    
    failArmy->publishTopic(gaming);
    failArmy->publishTopic(gaming);
    failArmy->publishTopic(gaming);
    ASSERT_NO_THROW(failArmy->sendMessage(message, gaming));
    sendMail(FuSioNuReX, failArmy, gaming);
    sendMail(naed90, failArmy, gaming);
    sendMail(G1, failArmy, gaming);
    sendMail(EZIO, failArmy, gaming);
    sendMail(zombii, failArmy, gaming);
    checkEqual;
    
    ASSERT_NO_THROW(FuSioNuReX->unsubscribeToTopic(gaming));
    ASSERT_NO_THROW(failArmy->sendMessage(message, gaming));
    sendMail(naed90, failArmy, gaming);
    sendMail(G1, failArmy, gaming);
    sendMail(EZIO, failArmy, gaming);
    sendMail(zombii, failArmy, gaming);
    checkEqual;
    
    ASSERT_NO_THROW(FuSioNuReX->subscribeToTopic(gaming));
    
    ASSERT_NO_THROW(failArmy->sendMessage(message, gaming));
    sendMail(FuSioNuReX, failArmy, gaming);
    sendMail(naed90, failArmy, gaming);
    sendMail(G1, failArmy, gaming);
    sendMail(EZIO, failArmy, gaming);
    sendMail(zombii, failArmy, gaming);
    checkEqual;
    
    return true;
}

bool unlinkAll()
{
    
    ASSERT_NO_THROW(outlaw37->unsubscribeAll());
    ASSERT_NO_THROW(G1->unsubscribeAll());
    ASSERT_NO_THROW(FuSioNuReX->unsubscribeAll());
    ASSERT_NO_THROW(VEVO->unpublishAll());
    ASSERT_NO_THROW(gameRanks->unpublishAll());
    ASSERT_NO_THROW(naed90->unsubscribeAll());
    ASSERT_NO_THROW(Elmo582->unsubscribeAll());
    ASSERT_NO_THROW(UNITY->unpublishAll());
    ASSERT_NO_THROW(pewdiepie->unpublishAll());
    ASSERT_NO_THROW(technion->unpublishAll());
    ASSERT_NO_THROW(TED->unpublishAll());
    ASSERT_NO_THROW(theSmithPlays->unpublishAll());
    ASSERT_NO_THROW(Dreamworks->unpublishAll());
    ASSERT_NO_THROW(failArmy->unpublishAll());
    ASSERT_NO_THROW(holyShit33->unsubscribeAll());
    ASSERT_NO_THROW(EZIO->unsubscribeAll());
    ASSERT_NO_THROW(zombii->unsubscribeAll());
    ASSERT_NO_THROW(DNews->unpublishAll());
    
    return true;
}

bool turnOnEncryption()
{
    
    if(!unlinkAll())
    {
        assert(false); //instead of doing RUN_TEST(unlinkAll), because we
        //want to return a value from this function.
        return false;
    }
    
    checkEqual;
    
    //Test that no topic holds any person anymore:
    youtube.sendMaintenanceMessageAny(all_topics,
                                      "You should be disconnected!");
    checkEqual;
    //above equals makes sure that server did not change, which means
    //nobody got the message, meaning everyone is disconnected.
    
    
    //Replace pointers with encrypted versions of clients
    outlaw37 = &client0B;
    G1 = &client1B;
    FuSioNuReX = &client2B;
    VEVO = &client3B;
    gameRanks = &client4B;
    naed90 = &client5B;
    Elmo582 = &client6B;
    UNITY = &client7B;
    pewdiepie = &client8B;
    technion = &client9B;
    TED = &client10B;
    theSmithPlays = &client11B;
    Dreamworks = &client12B;
    failArmy = &client13B;
    holyShit33 = &client14B;
    EZIO = &client15B;
    zombii = &client16B;
    DNews = &client17B;
    
    //attempt to reconnect the graph - this shouldn't fail
    if(!testLinkAll())
    {
        assert(false);
        return false;
    }
    
    
    //All passed well:
    return true;
}

bool sendEncryptedMessages()
{
    
    message = "ccccc";
    ASSERT_NO_THROW(failArmy->sendMessage(message, funny));
    message = "aaaaa";
    sendMail(FuSioNuReX, failArmy, funny);
    message = "ccccc";
    sendMail(outlaw37, failArmy, funny);
    message = "bbbbb";
    sendMail(holyShit33, failArmy, funny);
    checkEqual;
    /*
    message = "ccccc";
    ASSERT_NO_THROW(failArmy->sendMessage(message, gaming));
    message = "aaaaa";
    sendMail(FuSioNuReX, failArmy, gaming);
    message = "\0\0\0\0\0";
    sendMail(naed90, failArmy, gaming);
    message = "\0\0\0\0\0";
    sendMail(G1, failArmy, gaming);
    message = "bbbbb";
    sendMail(EZIO, failArmy, gaming);
    message = "aaaaa";
    sendMail(zombii, failArmy, gaming);
    
    
    std::cout << expectedServer.str() << std::endl;
    std::cout << youtubeServer.str() << std::endl;
    checkEqual;*/
    
    /*
    //message = "\0\0\0\0\0";
    naed90->unsubscribeToTopic(gaming);
    G1->unsubscribeToTopic(gaming);
    std::string specialMessage("\0\0\0\0\0",5);
    ASSERT_NO_THROW(theSmithPlays->sendMessage(specialMessage, gaming));
    message = "aaaaa";
    sendMail(FuSioNuReX, failArmy, gaming);
    //message = "";
    //sendMail(naed90, failArmy, gaming);
    //message = "";
    //sendMail(G1, failArmy, gaming);
    message = "bbbbb";
    sendMail(EZIO, failArmy, gaming);
    message = "aaaaa";
    sendMail(zombii, failArmy, gaming);
    std::cout << expectedServer.str() << std::endl;
    std::cout << youtubeServer.str() << std::endl;
    checkEqual;*/
    
    return true;
}

bool constructorDestructorTest()
{
    
    std::stringstream blah;
    Broker *b4 = new Broker();
    
    try {
        Subscriber cNeg (-1, *b4, blah);
        assert(false);
    } catch (Client::IllegalPriority&) {
        //ok
    } catch (...)
    {
        assert(false);
    }
    
    try {
        Publisher cNeg (-1, *b4, blah);
        assert(false);
    } catch (Client::IllegalPriority&) {
        //ok
    } catch (...)
    {
        assert(false);
    }
    
    Subscriber client0(2, *b4, blah);
    EncryptionSubscriber client1(2, *b4, 'a', blah);
    Publisher client2(2, *b4, blah);
    Subscriber client3(2, *b4, blah);
    EncryptionPublisher client4(2, *b4, 'b', blah);
    Subscriber client5(2, *b4, blah);
    Publisher client6(2, *b4, blah);
    
    client0.subscribeToTopic("f");
    client0.subscribeToTopic("f");
    client0.subscribeToTopic("f");
    client0.subscribeToTopic("f");
    client0.subscribeToTopic("e");
    client0.subscribeToTopic("t");
    client0.subscribeToTopic("g");
    client0.subscribeToTopic("n");
    client0.subscribeToTopic("d");
    client0.subscribeToTopic("s");
    client0.subscribeToTopic("e");
    
    client1.subscribeToTopic("f");
    client1.subscribeToTopic("f");
    client1.subscribeToTopic("f");
    client1.subscribeToTopic("f");
    client1.subscribeToTopic("e");
    client1.subscribeToTopic("t");
    client1.subscribeToTopic("g");
    client1.subscribeToTopic("n");
    client1.subscribeToTopic("d");
    client1.subscribeToTopic("s");
    client1.subscribeToTopic("e");
    
    
    client2.publishTopic("f");
    client2.publishTopic("f");
    client2.publishTopic("f");
    client2.publishTopic("f");
    client2.publishTopic("e");
    client2.publishTopic("t");
    client2.publishTopic("g");
    client2.publishTopic("n");
    client2.publishTopic("d");
    client2.publishTopic("s");
    client2.publishTopic("e");
    
    
    
    client3.subscribeToTopic("f");
    client3.subscribeToTopic("f");
    client3.subscribeToTopic("f");
    client3.subscribeToTopic("f");
    client3.subscribeToTopic("e");
    client3.subscribeToTopic("t");
    client3.subscribeToTopic("g");
    client3.subscribeToTopic("n");
    client3.subscribeToTopic("d");
    client3.subscribeToTopic("s");
    client3.subscribeToTopic("e");
    
    
    client4.publishTopic("f");
    client4.publishTopic("f");
    client4.publishTopic("f");
    client4.publishTopic("f");
    client4.publishTopic("e");
    client4.publishTopic("t");
    client4.publishTopic("g");
    client4.publishTopic("n");
    client4.publishTopic("d");
    client4.publishTopic("s");
    client4.publishTopic("e");
    
    client2.sendMessage("blah1", "f");
    client2.sendMessage("blah1", "e");
    client2.sendMessage("blah1", "t");
    client2.sendMessage("blah1", "d");
    client2.sendMessage("blah1", "n");
    
    
    client3.unsubscribeAll();
    
    client2.unpublishAll();
    
    delete b4;
    
    return true;
}

//*********************************************************//
bool subscribeToTopicTest() {
	Broker broker;
	stringstream ss;
	Subscriber hungry(1, broker, ss);
	hungry.subscribeToTopic("Desserts");
	hungry.subscribeToTopic("Main courses");
	hungry.subscribeToTopic("Appetizers");
	hungry.subscribeToTopic("Brunches");
	hungry.subscribeToTopic("Midnight snacks");
	hungry.subscribeToTopic("Salads");
	hungry.subscribeToTopic("Appetizers");
	/*illegal priority exception*/
	ASSERT_THROW(Client::IllegalPriority, (Subscriber(-100, broker, ss)));

	ASSERT_NO_THROW(Subscriber(0, broker, ss));
	return true;
}

//*********************************************************//
bool unsubscribeToTopicTest() {
	Broker broker;
	stringstream ss;
	Subscriber hungry(1, broker, ss);
	hungry.subscribeToTopic("Desserts");
	hungry.subscribeToTopic("Main courses");
	hungry.subscribeToTopic("Appetizers");
	hungry.subscribeToTopic("Brunches");
	hungry.subscribeToTopic("Midnight snacks");
	hungry.subscribeToTopic("Salads");
	hungry.subscribeToTopic("Appetizers");

	hungry.unsubscribeToTopic("Desserts");
	hungry.unsubscribeToTopic("Main courses");
	hungry.unsubscribeToTopic("Brunches");
	hungry.unsubscribeToTopic("Midnight snacks");
	hungry.unsubscribeToTopic("Salads");
/*unsubscribing same topic*/
	hungry.unsubscribeToTopic("Appetizers");
	ASSERT_THROW(Subscriber::NonSubscribedTopic,hungry.unsubscribeToTopic("Appetizers"));
	ASSERT_THROW(Subscriber::NonSubscribedTopic,hungry.unsubscribeToTopic("None existing topic"));
	ASSERT_THROW(Subscriber::NonSubscribedTopic,hungry.unsubscribeToTopic("Appetizers"));

	return true;
}
//*********************************************************//
bool unsubscribeAllTest() {
	Broker broker;
	stringstream ss;
	Subscriber hungry(1, broker, ss);
	hungry.subscribeToTopic("Desserts");
	hungry.subscribeToTopic("Main courses");
	hungry.subscribeToTopic("Appetizers");
	hungry.subscribeToTopic("Brunches");
	hungry.subscribeToTopic("Midnight snacks");
	hungry.subscribeToTopic("Salads");
	hungry.unsubscribeAll();
	hungry.unsubscribeAll();

	Subscriber thirsty(1, broker, ss);
	thirsty.unsubscribeAll();
	return true;
}
//*********************************************************//
bool receiveMessageTest() {
	Broker broker;
	stringstream ss;
	Publisher bakery_house(5, broker, ss);

	Subscriber hungry(1, broker, ss);
	hungry.subscribeToTopic("Desserts");
	hungry.subscribeToTopic("Main courses");
	hungry.subscribeToTopic("Appetizers");
	hungry.subscribeToTopic("Brunches");
	hungry.subscribeToTopic("Midnight snacks");
	hungry.subscribeToTopic("Salads");

	hungry.receiveMessage("chocolate croissant", "Desserts", bakery_house);
	hungry.receiveMessage("mini pizza", "Appetizers", bakery_house);
	hungry.receiveMessage("fruit salad", "Salads", bakery_house);
	hungry.receiveMessage("egg muffin", "Main courses", bakery_house);
	hungry.receiveMessage("chocolate chip cookies and milk", "Midnight snacks",
			bakery_house);
	hungry.receiveMessage("waffles with icecream", "Brunches", bakery_house);
	hungry.receiveMessage("eggs and bacon muffins", "Brunches", bakery_house);

	stringstream expected;
	expected << "Topic: " << "Desserts" << ". Sender: #" << bakery_house.getId()
			<< ". Receiver: #" << hungry.getId() << ". Message: "
			<< "chocolate croissant" << endl;
	expected << "Topic: " << "Appetizers" << ". Sender: #"
			<< bakery_house.getId() << ". Receiver: #" << hungry.getId()
			<< ". Message: " << "mini pizza" << endl;
	expected << "Topic: " << "Salads" << ". Sender: #" << bakery_house.getId()
			<< ". Receiver: #" << hungry.getId() << ". Message: "
			<< "fruit salad" << endl;
	expected << "Topic: " << "Main courses" << ". Sender: #"
			<< bakery_house.getId() << ". Receiver: #" << hungry.getId()
			<< ". Message: " << "egg muffin" << endl;

	expected << "Topic: " << "Midnight snacks" << ". Sender: #"
			<< bakery_house.getId() << ". Receiver: #" << hungry.getId()
			<< ". Message: " << "chocolate chip cookies and milk" << endl;

	expected << "Topic: " << "Brunches" << ". Sender: #" << bakery_house.getId()
			<< ". Receiver: #" << hungry.getId() << ". Message: "
			<< "waffles with icecream" << endl;
	expected << "Topic: " << "Brunches" << ". Sender: #" << bakery_house.getId()
			<< ". Receiver: #" << hungry.getId() << ". Message: "
			<< "eggs and bacon muffins" << endl;

	ASSERT_EQUALS(expected.str(), ss.str());

	ASSERT_THROW(Client::NonSubscribedTopic,
			hungry.receiveMessage("hamburger and chips", "junk food",
					bakery_house));

	hungry.unsubscribeToTopic("Desserts");
	ASSERT_THROW(Client::NonSubscribedTopic,
			hungry.receiveMessage("french toast", "Desserts", bakery_house));
	hungry.subscribeToTopic("Desserts");
	ASSERT_NO_THROW(
			hungry.receiveMessage("french toast", "Desserts", bakery_house));

	hungry.unsubscribeAll();

	ASSERT_THROW(Client::NonSubscribedTopic,
			hungry.receiveMessage("bagel", "Brunches", bakery_house));
	ASSERT_THROW(Client::NonSubscribedTopic,
			hungry.receiveMessage("banana split", "Desserts", bakery_house));
	ASSERT_THROW(Client::NonSubscribedTopic,
			hungry.receiveMessage("pancakes with freshly cut fruit and nutella",
					"Appetizers", bakery_house));
	ASSERT_THROW(Client::NonSubscribedTopic,
			hungry.receiveMessage("mjaddara", "Main courses", bakery_house));
	ASSERT_THROW(Client::NonSubscribedTopic,
			hungry.receiveMessage("take abreak..have some snickers",
					"Midnight snacks", bakery_house));
	ASSERT_THROW(Client::NonSubscribedTopic,
			hungry.receiveMessage("Tabboli", "Salads", bakery_house));
	ASSERT_THROW(Client::NonSubscribedTopic,
			hungry.receiveMessage("junk food is healthy.", "junk food",
					bakery_house));

	return true;
}
//*********************************************************//
bool PublishTopicTest() {
	Broker broker;
	stringstream ss;
	Publisher Pizza_Hut(2, broker, ss);
	Pizza_Hut.publishTopic("Cheesy Bites");
	Pizza_Hut.publishTopic("Pizza Dip");
	Pizza_Hut.publishTopic("Family Sized Pizza");
	Pizza_Hut.publishTopic("Cheese Stuffed Crust");
	Pizza_Hut.publishTopic("Magaritta");
	Pizza_Hut.publishTopic("Cheesy Bites");

	return true;
}
//*********************************************************//
bool unPublishTopicTest() {
	Broker broker;
	stringstream ss;
	Publisher Pizza_Hut(2, broker, ss);
	Pizza_Hut.publishTopic("Cheesy Bites");
	Pizza_Hut.publishTopic("Pizza Dip");
	Pizza_Hut.publishTopic("Family Sized Pizza");
	Pizza_Hut.publishTopic("Cheese Stuffed Crust");
	Pizza_Hut.publishTopic("Magaritta");
	Pizza_Hut.publishTopic("Cheesy Bites");

	ASSERT_THROW(Subscriber::NonPublishedTopic,Pizza_Hut.unpublishTopic("Dominos crappy pizza"));
	ASSERT_THROW(Subscriber::NonPublishedTopic,Pizza_Hut.unpublishTopic("Munch yum yum"));
	ASSERT_THROW(Subscriber::NonPublishedTopic,Pizza_Hut.unpublishTopic("pizza is love.. pizza is life!"));

	Pizza_Hut.unpublishTopic("Cheesy Bites");
	Pizza_Hut.unpublishTopic("Pizza Dip");
	Pizza_Hut.unpublishTopic("Family Sized Pizza");
	Pizza_Hut.unpublishTopic("Cheese Stuffed Crust");
	Pizza_Hut.unpublishTopic("Magaritta");

	ASSERT_THROW(Publisher::NonPublishedTopic,Pizza_Hut.unpublishTopic("Cheesy Bites"));

	Pizza_Hut.publishTopic("Cheesy Bites");
	ASSERT_NO_THROW(Pizza_Hut.unpublishTopic("Cheesy Bites"));

	return true;
}
//*********************************************************//
bool unPublishAllTest() {
	Broker broker;
	stringstream ss;
	Publisher Pizza_Hut(2, broker, ss);
	Pizza_Hut.publishTopic("Cheesy Bites");
	Pizza_Hut.publishTopic("Pizza Dip");
	Pizza_Hut.publishTopic("Family Sized Pizza");
	Pizza_Hut.publishTopic("Cheese Stuffed Crust");
	Pizza_Hut.publishTopic("Magaritta");
	Pizza_Hut.publishTopic("Cheesy Bites");

	Pizza_Hut.unpublishAll();
	return true;
}
//*********************************************************//
bool sendMessageTest() {
	Broker broker;
	stringstream ss;
	stringstream expected;
	Publisher Resturant(10, broker, ss);
	Resturant.publishTopic("Lunch Deals");
	Resturant.sendMessage("Nobody should get this message", "Lunch Deals");
	ASSERT_EQUALS(expected.str(), ss.str());
	Subscriber customer1(5, broker, ss);
	Subscriber customer2(2, broker, ss);
	Subscriber customer3(4, broker, ss);
	Subscriber customer4(3, broker, ss);
	Subscriber customer5(5, broker, ss);
	Subscriber customer6(5, broker, ss);

	customer1.subscribeToTopic("Lunch Deals");
	customer3.subscribeToTopic("Lunch Deals");
	customer2.subscribeToTopic("Lunch Deals");
	customer4.subscribeToTopic("Lunch Deals");
	customer5.subscribeToTopic("Lunch Deals");

	Resturant.sendMessage("Great Lunch deal! fish and chips for 50%",
			"Lunch Deals");

	expected << "Topic: " << "Lunch Deals" << ". Sender: #" << Resturant.getId()
			<< ". Receiver: #" << customer2.getId() << ". Message: "
			<< "Great Lunch deal! fish and chips for 50%" << endl;

	expected << "Topic: " << "Lunch Deals" << ". Sender: #" << Resturant.getId()
			<< ". Receiver: #" << customer4.getId() << ". Message: "
			<< "Great Lunch deal! fish and chips for 50%" << endl;

	expected << "Topic: " << "Lunch Deals" << ". Sender: #" << Resturant.getId()
			<< ". Receiver: #" << customer3.getId() << ". Message: "
			<< "Great Lunch deal! fish and chips for 50%" << endl;
	expected << "Topic: " << "Lunch Deals" << ". Sender: #" << Resturant.getId()
			<< ". Receiver: #" << customer1.getId() << ". Message: "
			<< "Great Lunch deal! fish and chips for 50%" << endl;
	expected << "Topic: " << "Lunch Deals" << ". Sender: #" << Resturant.getId()
			<< ". Receiver: #" << customer5.getId() << ". Message: "
			<< "Great Lunch deal! fish and chips for 50%" << endl;

	ASSERT_EQUALS(expected.str(), ss.str());

	ASSERT_THROW(Client::NonPublishedTopic,
			Resturant.sendMessage("this is spam!", "Dinner Deals"));

	Resturant.unpublishTopic("Lunch Deals");
	ASSERT_THROW(Client::NonPublishedTopic,
			Resturant.sendMessage("this is spam!", "Lunch Deals"));

	Resturant.publishTopic("Sunday Brunch");
	Resturant.sendMessage("Free cocktail!", "Sunday Brunch");

	ASSERT_EQUALS(expected.str(), ss.str());

	return true;
}
//*********************************************************//
bool sendMaintenanceMessageAnyTest() {
	Broker broker;
	stringstream ss;
	stringstream expected;
	//publishers
	Publisher Mccdonalds(7, broker, ss);
	Publisher Burger_king(9, broker, ss);
	Publisher Zesty(1, broker, ss);
	Publisher Japanika(8, broker, ss);
	Publisher Max_Brenner(2, broker, ss);
	//subscribers
	Subscriber customer1(5, broker, ss);
	Subscriber customer2(9, broker, ss);
	Subscriber customer3(3, broker, ss);
	Subscriber customer4(7, broker, ss);
	Subscriber customer5(4, broker, ss);

	//creating topics list
	std::list<Topic> topics;
	topics.insert(topics.begin(), "Desserts");
	topics.insert(topics.begin(), "Main courses");
	topics.insert(topics.begin(), "Appetizers");
	topics.insert(topics.begin(), "Brunches");
	topics.insert(topics.begin(), "Salads");
	topics.insert(topics.begin(), "Midnight snacks");

	broker.sendMaintenanceMessageAny(topics, "Everybody is HUNGRY!");
	ASSERT_EQUALS(expected.str(), ss.str());

	customer5.subscribeToTopic("Junk Food");

	customer1.subscribeToTopic("Appetizers");
	customer2.subscribeToTopic("Salads");
	customer3.subscribeToTopic("Salads");
	customer4.subscribeToTopic("Salads");
	Mccdonalds.publishTopic("Midnight snacks");
	Burger_king.publishTopic("Brunches");
	Zesty.publishTopic("Appetizers");
	Japanika.publishTopic("Main courses");
	Max_Brenner.publishTopic("Desserts");


	broker.sendMaintenanceMessageAny(topics, "Sushi Rolls on the house!");

	expected << "Client #" << Zesty.getId() << " received maintenance message: "
			<< "Sushi Rolls on the house!" << endl;
	expected << "Client #" << Max_Brenner.getId()
			<< " received maintenance message: " << "Sushi Rolls on the house!"
			<< endl;
	expected << "Client #" << customer3.getId()
			<< " received maintenance message: " << "Sushi Rolls on the house!"
			<< endl;
	expected << "Client #" << customer1.getId()
			<< " received maintenance message: " << "Sushi Rolls on the house!"
			<< endl;
	expected << "Client #" << Mccdonalds.getId()
			<< " received maintenance message: " << "Sushi Rolls on the house!"
			<< endl;
	expected << "Client #" << customer4.getId()
			<< " received maintenance message: " << "Sushi Rolls on the house!"
			<< endl;
	expected << "Client #" << Japanika.getId()
			<< " received maintenance message: " << "Sushi Rolls on the house!"
			<< endl;
	expected << "Client #" << Burger_king.getId()
			<< " received maintenance message: " << "Sushi Rolls on the house!"
			<< endl;
	expected << "Client #" << customer2.getId()
			<< " received maintenance message: " << "Sushi Rolls on the house!"
			<< endl;

ASSERT_EQUALS(expected.str(),ss.str());
	return true;
}
//*********************************************************//
bool sendMaintenanceMessageAllTest() {
	Broker broker;
	stringstream ss;
	stringstream expected;
	//publishers
	Publisher Mccdonalds(7, broker, ss);
	Publisher Burger_king(9, broker, ss);
	Publisher Zesty(1, broker, ss);
	Publisher Japanika(8, broker, ss);
	Publisher Max_Brenner(2, broker, ss);
	//subscribers
	Subscriber customer1(5, broker, ss);
	Subscriber customer2(9, broker, ss);
	Subscriber customer3(3, broker, ss);
	Subscriber customer4(7, broker, ss);
	Subscriber customer5(4, broker, ss);

	//creating topics list
	std::list<Topic> topics;
	topics.insert(topics.begin(), "Desserts");
	topics.insert(topics.begin(), "Main courses");
	topics.insert(topics.begin(), "Salads");

	customer5.subscribeToTopic("Salads");
	customer5.subscribeToTopic("Desserts");

	customer1.subscribeToTopic("Salads");
	customer2.subscribeToTopic("Salads");
	customer3.subscribeToTopic("Salads");
	customer4.subscribeToTopic("Salads");
	Mccdonalds.publishTopic("Salads");
	Burger_king.publishTopic("Salads");
	Zesty.publishTopic("Salads");
	Japanika.publishTopic("Salads");
	Max_Brenner.publishTopic("Salads");

	customer1.subscribeToTopic("Main courses");
	customer2.subscribeToTopic("Main courses");
	customer3.subscribeToTopic("Main courses");
	customer4.subscribeToTopic("Main courses");
	Mccdonalds.publishTopic("Main courses");
	Burger_king.publishTopic("Main courses");
	Zesty.publishTopic("Main courses");
	Japanika.publishTopic("Main courses");
	Max_Brenner.publishTopic("Main courses");

	customer1.subscribeToTopic("Desserts");
	customer2.subscribeToTopic("Desserts");
	customer3.subscribeToTopic("Desserts");
	customer4.subscribeToTopic("Desserts");
	Mccdonalds.publishTopic("Desserts");
	Burger_king.publishTopic("Desserts");
	Zesty.publishTopic("Desserts");
	Japanika.publishTopic("Desserts");
	Max_Brenner.publishTopic("Desserts");

	broker.sendMaintenanceMessageAll(topics, "Sushi Rolls on the house!");

	expected << "Client #" << Zesty.getId() << " received maintenance message: "
			<< "Sushi Rolls on the house!" << endl;
	expected << "Client #" << Max_Brenner.getId()
			<< " received maintenance message: " << "Sushi Rolls on the house!"
			<< endl;
	expected << "Client #" << customer3.getId()
			<< " received maintenance message: " << "Sushi Rolls on the house!"
			<< endl;
	expected << "Client #" << customer1.getId()
			<< " received maintenance message: " << "Sushi Rolls on the house!"
			<< endl;
	expected << "Client #" << Mccdonalds.getId()
			<< " received maintenance message: " << "Sushi Rolls on the house!"
			<< endl;
	expected << "Client #" << customer4.getId()
			<< " received maintenance message: " << "Sushi Rolls on the house!"
			<< endl;
	expected << "Client #" << Japanika.getId()
			<< " received maintenance message: " << "Sushi Rolls on the house!"
			<< endl;
	expected << "Client #" << Burger_king.getId()
			<< " received maintenance message: " << "Sushi Rolls on the house!"
			<< endl;
	expected << "Client #" << customer2.getId()
			<< " received maintenance message: " << "Sushi Rolls on the house!"
			<< endl;

	ASSERT_EQUALS(expected.str(), ss.str());

	topics.insert(topics.begin(), "Sushi");
	broker.sendMaintenanceMessageAll(topics, "Sushi Rolls on the house!");
	ASSERT_EQUALS(expected.str(), ss.str());



	return true;
}
//*********************************************************//
bool EncryptionTest() {
	Broker broker;
	stringstream ss;
	stringstream expected;

	EncryptionPublisher Cafe_cafe(1, broker, static_cast<char>(0xFF), ss);
	EncryptionPublisher Mandarin(2, broker, static_cast<char>(0xFF), ss);
	EncryptionSubscriber customer1(3, broker, static_cast<char>(0xFF), ss);
	EncryptionSubscriber customer2(2, broker, static_cast<char>(0xFF), ss);
	EncryptionSubscriber customer3(4, broker, static_cast<char>(0xFF), ss);
	EncryptionSubscriber customer4(2, broker, static_cast<char>(0xFF), ss);
	EncryptionSubscriber customer5(2, broker, static_cast<char>(0xFF), ss);

	Cafe_cafe.publishTopic("Afternoon Sale");
	Mandarin.publishTopic("Free Ice-coffee");

	customer1.subscribeToTopic("Afternoon Sale");
	customer2.subscribeToTopic("Afternoon Sale");
	customer3.subscribeToTopic("Afternoon Sale");
	customer4.subscribeToTopic("Afternoon Sale");
	customer5.subscribeToTopic("Afternoon Sale");

	Cafe_cafe.sendMessage("All pasta meals for 20% off!", "Afternoon Sale");

	expected << "Topic: " << "Afternoon Sale" << ". Sender: #"
			<< Cafe_cafe.getId() << ". Receiver: #" << customer2.getId()
			<< ". Message: " << "All pasta meals for 20% off!" << endl;

	expected << "Topic: " << "Afternoon Sale" << ". Sender: #"
			<< Cafe_cafe.getId() << ". Receiver: #" << customer4.getId()
			<< ". Message: " << "All pasta meals for 20% off!" << endl;

	expected << "Topic: " << "Afternoon Sale" << ". Sender: #"
			<< Cafe_cafe.getId() << ". Receiver: #" << customer5.getId()
			<< ". Message: " << "All pasta meals for 20% off!" << endl;
	expected << "Topic: " << "Afternoon Sale" << ". Sender: #"
			<< Cafe_cafe.getId() << ". Receiver: #" << customer1.getId()
			<< ". Message: " << "All pasta meals for 20% off!" << endl;
	expected << "Topic: " << "Afternoon Sale" << ". Sender: #"
			<< Cafe_cafe.getId() << ". Receiver: #" << customer3.getId()
			<< ". Message: " << "All pasta meals for 20% off!" << endl;

	ASSERT_EQUALS(expected.str(), ss.str());
	return true;
}
//*********************************************************//

void PubSubTest()
{
    RUN_TEST(constructorDestructorTest);
    RUN_TEST(testLinkAll);
    RUN_TEST(testMaintenance);
    RUN_TEST(sendMessages);
    RUN_TEST(turnOnEncryption);
    RUN_TEST(testMaintenance);
    RUN_TEST(sendEncryptedMessages);
    //Subscriber
    RUN_TEST(subscribeToTopicTest);
    RUN_TEST(unsubscribeToTopicTest);
    RUN_TEST(unsubscribeAllTest);
    RUN_TEST(receiveMessageTest);
    //Publisher
    RUN_TEST(PublishTopicTest);
    RUN_TEST(unPublishTopicTest);
    RUN_TEST(unPublishAllTest);
    RUN_TEST(sendMessageTest);
    //Broker
    RUN_TEST(sendMaintenanceMessageAnyTest);
    RUN_TEST(sendMaintenanceMessageAllTest);
	RUN_TEST(EncryptionTest);
}
