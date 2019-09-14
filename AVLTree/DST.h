/*
 * DS.h
 *
 *  Created on: 27 באפר׳ 2016
 *      Author: lior
 */

#ifndef DST_H_
#define DST_H_
#include "Troll.h"
#include "MtmMap.h"
using namespace mtm;

class DST {
private:
	Post maxPostByLikes;
	int numberOfPosts;
	AVLTree<Post, postByPostIdFunc, fillInEmptyIDTree> postsByPostID;
	AVLTree<Post, postByLikesFunc, fillInEmptyLikesTree> postsByLikes;
	MtmMap<int, Troll*> TrollsWithPosts;
public:
	DST() :
			numberOfPosts(0), TrollsWithPosts(NULL) {

	}
	;

	~DST() {
		for (MtmMap<int, Troll*>::iterator it = TrollsWithPosts.begin();
				it != TrollsWithPosts.end(); ++it) {
			delete (*it).second;
		}
	}
	/*
	 * return array posts ordered by likes
	 * throw exception in case of problem
	 */
	Post* GetAllPostOrderedByLikes();

	/*
		 * return array posts ordered by ids
		 * throw exception in case of problem
		 */
	Post* GetAllPostOrderedByID();

	/*
	 * Get ID of a troll and returns an array of Posts ordered by ID
	 */
	Post* GetTrollPostsOrderedbyLikes(int ID);

	/*
	 * Get post ID and and likes, it adds the post with post ID the
	 * number of likes
	 */
	void AddPostLikes(int ID, int likes);
	/*
	 * Get post ID and delete the post with the ID;
	 */
	void DeletePost(int ID);
	/*
	 * add a new post with the post ID, trollID and likesCount
	 * to the system. make sure there is no post like it and the troll exists
	 * and the like count is positive.
	 */
	void addPost(int postID, int trollID, int LikesCount);
	//The function add a new Troll to the DS, make sure the troll is not exist
	// and the TrollID is positive;
	void addTroll(int TrollID);
	//return the The post with maximum like in the DS
	Post GetTopPost();
	//return the the post of troll with troll ID with maximum likes;
	Post GetTopPostOfTroll(int ID);
	//return the number of posts of the DS;
	int getNumOfPosts();
	//return the number of posts of a troll;
	int getNumOfPostsOfTroll(int trollID);
	MtmMap<int, Troll*> getTrollMap();
	void updateLikes(int postCode, int postFactor);
	//checks if the troll is already exist
	bool containTroll(int trollID);
	//checks if the post is already exist;
	bool containPost(int postID);
	//updates all the posts of tree of posts by ids
	void updateTreeById(int S, int factor);

};

#endif /* DST_H_ */
