/*
 * Troll.h
 *
 *  Created on: 26 áàôø× 2016
 *      Author: lior
 */
#include "post.h"
#include "AVLTree.h"
#include "AVLTreeNode.h"
#include <math.h>

using std::endl;
using std::cout;


//Comparator for posts by likes and secondly by ids
class postByLikesFunc {
public:
	int operator()(Post a, Post b) {
		if (a.GetLikes() == b.GetLikes()) {
			return (b.GetPostID() - a.GetPostID());
		}
		return a.GetLikes() - b.GetLikes();
	}
};

//Comparator for posts by ids
class postByPostIdFunc {
public:

	int operator()(Post a, Post b) {
		return (a.GetPostID() - b.GetPostID());
	}
};

//fill functor to fill an empty tree by likes
class fillInEmptyLikesTree {
private:
	AVLTree<Post, postByLikesFunc, fillInEmptyLikesTree>& updated_posts;
	Post* posts;
	Post max_post;
	int itr;
	int S;
	int factor;
public:
	fillInEmptyLikesTree(
			AVLTree<Post, postByLikesFunc, fillInEmptyLikesTree>& empty,
			Post* posts, int S, int factor) :
			updated_posts(empty), posts(posts), itr(0), S(S), factor(factor){
	}
	void operator()(
			AVLTreeNode<Post, postByLikesFunc, fillInEmptyLikesTree>*cur_node){
		cur_node->setInfo(posts[itr]);
		itr++;
	}
	AVLTree<Post, postByLikesFunc, fillInEmptyLikesTree> getTree() {
		return updated_posts;
	}
};

//fill functor to fill an empty tree by likes
class fillInEmptyIDTree {
private:
	AVLTree<Post, postByPostIdFunc, fillInEmptyIDTree>& updated_posts;
	Post* posts;
	Post max_post;
	int itr;
	int S;
	int factor;
public:
	fillInEmptyIDTree(AVLTree<Post, postByPostIdFunc, fillInEmptyIDTree>&empty,
			Post* posts, int S, int factor) :
			updated_posts(empty), posts(posts), itr(0), S(S), factor(factor){
	}
	void operator()(
			AVLTreeNode<Post, postByPostIdFunc, fillInEmptyIDTree>* cur_node){
		cur_node->setInfo(posts[itr]);
		itr++;
	}
	AVLTree<Post, postByPostIdFunc, fillInEmptyIDTree> getTree() {
		return updated_posts;
	}
};

#ifndef TROLL_H_
#define TROLL_H_

#include "AVLTree.h"
class Troll {
private:
	int TrollID;
	int numberOfPosts;
	Post maxPostByLikes;
	AVLTree<Post, postByLikesFunc, fillInEmptyLikesTree> postsByLikes;
	AVLTree<Post, postByPostIdFunc, fillInEmptyIDTree> postsByPostID;
public:
	Troll(int ownerID) :
			TrollID(ownerID), numberOfPosts(0) {
		if (TrollID <= 0)
			throw TrollBadID();
	}
	~Troll() {
	}
	;
	//return the Troll ID;
	int GetTrollID();
	//add a post to the troll, make sure the post and troll has the same ID.
	void AddPost(Post post);
	// delete a post with the post id of the troll.
	void deletePost(int ID);
	//return the post with maximum number of likes;
	Post getMaxPost();
	//return an array of the troll post sorted by likes;
	Post* getPostSortedByLikes();
	//return an array of the troll post sorted by ID;
	Post* getPostSortedByID();
	//add likesNum to a post with postID equal to ID;
	void addLikes(int ID, int likesNum);
	//return the number of posts the troll holds
	int getNumOfPosts();
	//updates all posts of troll by PostCode and by Postfactor
	void updateLikes(int S, int factor);
	//updates likes of all posts of troll
	//by PostCode and by Postfactor
	void updateTreeById(int S, int factor);

};

#endif /* TROLL_H_ */
