/*
 * post.h
 *
 *  Created on: 26 באפר׳ 2016
 *      Author: lior
 */

#ifndef POST_H_
#define POST_H_
#include <iostream>
#include <string>
using std::istream;
using std::ostream;

class Post {
private:
	int postID;
	int ownerID;
	int likes;
public:
	Post() :
			postID(-1), ownerID(-1), likes(-1) {
	}
	Post(int postId, int ownerId, int like) :
			postID(postId), ownerID(ownerId), likes(like) {
		if (like < 0 || ownerId < 0) {
			throw 1; // throw expention
		}
	}
	~Post() {
	}
	;
	Post(const Post& post) {
		this->postID = post.postID;
		this->likes = post.likes;
		this->ownerID = post.ownerID;
	}
	//edit the post number of likes to likes
	void setLikes(int likes);
	// return the number of likes
	int GetLikes();
	//return the post owner ID
	int GetOwnerID();
	//return the post postID
	int GetPostID();

};

#endif /* POST_H_ */

