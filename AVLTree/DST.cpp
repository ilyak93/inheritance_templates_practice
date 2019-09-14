/*
 * DS.cpp


 *
 *  Created on: 28 באפר׳ 2016
 *      Author: lior
 */
#include "DST.h"
#include <iostream>
using std::cout;
Post* DST::GetAllPostOrderedByLikes() {
	return this->postsByLikes.returnSortedTreeElementsInOrder();
}
Post* DST::GetTrollPostsOrderedbyLikes(int ID) {
	if (ID <= 0) {
		throw DSTInvailedInput();
	}
	if (this->TrollsWithPosts.containsKey(ID) == false) {
		throw DSTTrollDoesNotExist();
	}
	return (*this->TrollsWithPosts[ID]).getPostSortedByLikes();
}
void DST::DeletePost(int ID) {
	Post temp(ID, 1, 1);
	if (ID <= 0)
		throw DSTInvailedInput();
	if (this->postsByPostID.AVLTreeContain(temp) == false)
		throw DSTPostDoesNotExist();
	Post post = this->postsByPostID.findElement(temp);
	AVLTreeNode<Post, postByLikesFunc, fillInEmptyLikesTree>* found =
			this->postsByLikes.find(post);
	Post p = found->getInfo();
	this->postsByPostID.deleteByInfo(post);
	this->postsByLikes.deleteByInfo(post);
	(*(this->TrollsWithPosts[post.GetOwnerID()])).deletePost(post.GetPostID());
	AVLTreeNode<Post, postByLikesFunc, fillInEmptyLikesTree>* max =
			this->postsByLikes.minPointerInAVLTree(
					this->postsByLikes.getRoot());
	if (max) {
		this->maxPostByLikes = max->getInfo();
	}

	this->numberOfPosts--;
}
int DST::getNumOfPosts() {
	return this->numberOfPosts;
}
void DST::AddPostLikes(int ID, int likes) {
	Post temp(ID, 1, 1);
	if (this->postsByPostID.AVLTreeContain(temp) == false) {
		throw DSTPostDoesNotExist();
	}
	Post post = this->postsByPostID.findElement(temp);

	(*this->TrollsWithPosts[post.GetOwnerID()]).addLikes(post.GetPostID(),
			likes);
	this->postsByPostID.deleteByInfo(post);
	this->postsByLikes.deleteByInfo(post);
	post.setLikes(post.GetLikes() + likes);
	this->postsByPostID.insert(post);
	this->postsByLikes.insert(post);
	if (post.GetLikes() > this->maxPostByLikes.GetLikes()
			|| (post.GetLikes() == this->maxPostByLikes.GetLikes()
					&& post.GetPostID() < this->maxPostByLikes.GetPostID())) {
		this->maxPostByLikes = post;
	}
}

void DST::addPost(int postID, int trollID, int LikesCount) {
	if (postID <= 0 || trollID <= 0 || LikesCount < 0) {
		throw DSTInvailedInput();
	}
	if (this->TrollsWithPosts.containsKey(trollID) == false) {
		throw DSTTrollDoesNotExist();
	}
	if (this->postsByPostID.AVLTreeContain(Post(postID, trollID, LikesCount))
			== true) {
		throw DSTPostAllreadyExist();
	}

	Post post(postID, trollID, LikesCount);
	this->postsByLikes.insert(post);
	this->postsByPostID.insert(post);
	(*this->TrollsWithPosts[trollID]).AddPost(post);
	if (this->maxPostByLikes.GetLikes() < post.GetLikes()) {
		this->maxPostByLikes = post;
	} else if (this->maxPostByLikes.GetLikes() == post.GetLikes()
			&& this->maxPostByLikes.GetPostID() > post.GetPostID()) {
		this->maxPostByLikes = post;
	}
	this->numberOfPosts++;
}
void DST::addTroll(int TrollID) {
	if (this->TrollsWithPosts.containsKey(TrollID) == true) {
		throw DSTTrollAlreadyExist();
	}
	Troll* troll = new Troll(TrollID);
	this->TrollsWithPosts.insert(TrollID, troll);
}
Post DST::GetTopPost() {
	return this->maxPostByLikes;
}

Post DST::GetTopPostOfTroll(int ID) {
	return (*this->TrollsWithPosts[ID]).getMaxPost();
}

int DST::getNumOfPostsOfTroll(int trollID) {
	return (*this->TrollsWithPosts[trollID]).getNumOfPosts();
}

MtmMap<int, Troll*> DST::getTrollMap() {
	return this->TrollsWithPosts;
}
bool DST::containPost(int postID) {
	if (postID <= 0) {
		return false;
	}
	if (this->postsByPostID.AVLTreeContain(Post(postID, 1, 1)) == true) {
		return true;
	}
	return false;
}
bool DST::containTroll(int trollID) {
	if (trollID <= 0) {
		return false;
	}
	if (this->TrollsWithPosts.containsKey(trollID) == true)
		return true;
	return false;
}

Post* DST::GetAllPostOrderedByID() {
	return this->postsByPostID.returnSortedTreeElementsInOrder();
}

static Post* merge(Post* p1, Post* p2, int size1, int size2) {
	int itr = 0, itr1 = 0, itr2 = 0;
	postByLikesFunc cmp;
	Post* merged = new Post[size1 + size2];
	while (itr1 < size1 && itr2 < size2) {
		if (cmp(p1[itr1], p2[itr2]) > 0) {
			merged[itr++] = p1[itr1++];
		} else {
			merged[itr++] = p2[itr2++];
		}
	}
	while (itr1 < size1) {
		merged[itr++] = p1[itr1++];
	}
	while (itr2 < size2) {
		merged[itr++] = p2[itr2++];
	}
	return merged;
}

static int getAmountOfPostsToFactor(Post* posts, int S, int size) {
	int count = 0;
	for (int i = 0; i < size; i++) {
		count += !(posts[i].GetPostID() % S);
	}
	return count;
}

static void devideByFactor(Post* src, Post** to_factor, Post** not_to_factor,
		int to_factor_size, int not_to_factor_size, int S, int factor) {
	int itr1 = 0, itr2 = 0;
	int size = to_factor_size + not_to_factor_size;
	for (int i = 0; i < size; i++) {
		if (src[i].GetPostID() % S == 0) {
			src[i].setLikes(src[i].GetLikes() * factor);
			(*to_factor)[itr1++] = src[i];
		} else {
			(*not_to_factor)[itr2++] = src[i];
		}
	}
}

static void updateLikesTree(Post* posts, int size, int S, int factor,
		AVLTree<Post, postByLikesFunc, fillInEmptyLikesTree>* empty) {
	int tmp = pow(2, ceil(log(size) / log(2)));
	int nearest_pow_of_two = tmp % 2 == 0 ? tmp * 2 : tmp;
	(*empty).createEmptyWholeAVLTree(nearest_pow_of_two);
	(*empty).removeInorderRightLeft((nearest_pow_of_two - 1) - size);
	int to_factor_size = getAmountOfPostsToFactor(posts, S, size);
	int not_to_factor_size = size - to_factor_size;
	Post* to_factor = new Post[to_factor_size];
	Post* not_to_factor = new Post[not_to_factor_size];

	devideByFactor(posts, &to_factor, &not_to_factor, to_factor_size,
			not_to_factor_size, S, factor);

	Post* new_posts = merge(to_factor, not_to_factor, to_factor_size,
			not_to_factor_size);
	if (new_posts == NULL)
		throw std::bad_alloc();
	fillInEmptyLikesTree fill(*empty, new_posts, S, factor);
	(*empty).operateInOrder(fill);
	free(posts);
	delete[] new_posts;
	delete[] to_factor;
	delete[] not_to_factor;
}

void DST::updateLikes(int S, int factor) {
	Post* posts_by_likes = this->GetAllPostOrderedByLikes();
	if (posts_by_likes == NULL)
		throw std::bad_alloc();
	int size_posts_by_likes = this->postsByLikes.getSize();
	if (!size_posts_by_likes)
		return;
	updateLikesTree(posts_by_likes, size_posts_by_likes, S, factor,
			&postsByLikes);
	this->updateTreeById(S, factor);
	AVLTreeNode<Post, postByLikesFunc, fillInEmptyLikesTree>* max =
			postsByLikes.minPointerInAVLTree(postsByLikes.getRoot());
	this->maxPostByLikes = max ? max->getInfo() : Post();
	for (MtmMap<int, Troll*>::iterator it = TrollsWithPosts.begin();
			it != TrollsWithPosts.end(); ++it) {
		(*it).second->updateLikes(S, factor);
	}
	free(posts_by_likes);
}

void DST::updateTreeById(int S, int factor) {
	Post* posts = this->postsByPostID.returnSortedTreeElementsInOrder();
	if (posts == NULL)
		throw std::bad_alloc();
	for (int i = 0; i < this->numberOfPosts; i++) {
		if (posts[i].GetPostID() % S == 0) {
			posts[i].setLikes(posts[i].GetLikes() * factor);
		}
	}
	fillInEmptyIDTree fill(this->postsByPostID, posts, S, factor);
	postsByPostID.operateInOrder(fill);
	free(posts);
}

