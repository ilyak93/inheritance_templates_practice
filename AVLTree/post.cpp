/*
 * post.cpp
 *
 *  Created on: 26 באפר׳ 2016
 *      Author: lior
 */

#include <iostream>
#include <string>
#include "post.h"
void Post::setLikes(int likes){
	this->likes=likes;
}
int Post::GetLikes(){
	return this->likes;
}
int Post::GetOwnerID(){
	return this->ownerID;
}
int Post::GetPostID(){
	return this->postID;
}



