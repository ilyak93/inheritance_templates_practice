/*
 * Troll.cpp
 *
 *  Created on: 26 באפר׳ 2016
 *      Author: lior
 */
#include "Troll.h"
#include "Exceptions.h"
/*
 * The function receive two ordered arrays of posts and merged to 1 sorted
 * array
 * Note: the order is determined by the sorted function of the posts tree
 */


/*
 *The function receive an array, its size and the a factor,
 *and return the amount of posts in the array with postID % S == 0
 *
 */

/*
 * The function get a src array of posts which is not ordered, yet it can be
 * divided to 2 sorted "mini" arrays which are does which can be determined by
 * the postCode (S) of "update likes". Also we have  the size those 2 mini
 * array (to_factor_size and not_to_factor_size).
 * the Function divides this post array to the 2 arrays and also flip the
 *  order.
 *
 */


static Post* merge(Post* p1, Post* p2, int size1, int size2) {
	int itr = 0, itr1 = 0, itr2 = 0;
	postByLikesFunc cmp;
	Post* merged = new Post[size1 + size2];
	while (itr1 < size1 && itr2 < size2) {
		if(cmp(p1[itr1], p2[itr2]) > 0){
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
		count+=!(posts[i].GetPostID() % S);
	}
	return count;
}

static void devideByFactor(Post* src, Post** to_factor, Post** not_to_factor,
						  int to_factor_size, int not_to_factor_size,
						  int S, int factor) {
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



int Troll::GetTrollID(){
	return this->TrollID;
}
Post Troll::getMaxPost(){
	return this->maxPostByLikes;
}
void Troll::AddPost(Post post){
	if(this->postsByPostID.AVLTreeContain(post)==true){
		throw TrollPostExist();
	}else if(post.GetOwnerID()!=this->TrollID){
		throw TrollBadID();
	}
	this->postsByPostID.insert(post);
	this->postsByLikes.insert(post);
	if(this->maxPostByLikes.GetLikes()<post.GetLikes()){
		this->maxPostByLikes=post;
	}else if(this->maxPostByLikes.GetLikes()==post.GetLikes()&&
			this->maxPostByLikes.GetPostID()>post.GetPostID()){
		this->maxPostByLikes=post;
	}
	this->numberOfPosts++;
}
int Troll::getNumOfPosts(){
	return this->numberOfPosts;
}
void Troll::deletePost(int ID){ // update max Post
	if(this->numberOfPosts==0){
		throw TrollNoPosts();
	}
	Post tmp(ID,0, 0);
	AVLTreeNode<Post, postByPostIdFunc, fillInEmptyIDTree >* found
								= this->postsByPostID.find(tmp);
	Post p = found->getInfo();
	Post post=this->postsByPostID.findElement(tmp);
	this->postsByPostID.deleteByInfo(post);
	this->postsByLikes.deleteByInfo(post);
	AVLTreeNode<Post, postByLikesFunc, fillInEmptyLikesTree >* max =
		this->postsByLikes.minPointerInAVLTree(this->postsByLikes.getRoot());
	this->maxPostByLikes = max ? max->getInfo() : Post();
	this->numberOfPosts--;
}
Post* Troll::getPostSortedByLikes(){
		return this->postsByLikes.returnSortedTreeElementsInOrder();
}

void Troll::addLikes(int ID, int likesNum){
	if(likesNum <= 0 || ID <= 0){
		throw TrollInvailedInput::TrollException();
	}if(this->postsByPostID.AVLTreeContain(Post(ID,1,1))==false){
		throw TrollPostDoesntExist();
	}
	Post tmp(ID,this->GetTrollID(),1);
 	Post post= this->postsByPostID.findElement(tmp);
	this->postsByPostID.deleteByInfo(post);
	this->postsByLikes.deleteByInfo(post);
	post.setLikes(post.GetLikes()+likesNum);
	this->postsByLikes.insert(post);
	this->postsByPostID.insert(post);
	if(this->maxPostByLikes.GetLikes()<post.GetLikes()||
		(this->maxPostByLikes.GetLikes()==post.GetLikes() &&
				this->maxPostByLikes.GetPostID() > post.GetPostID())){
		this->maxPostByLikes=post;
	}
}

Post* Troll::getPostSortedByID(){
		return this->postsByPostID.returnSortedTreeElementsInOrder();
}

static void updateLikesTree(Post* posts, int size, int S, int factor,
							AVLTree<Post, postByLikesFunc,
	   	   	   	   	   	   	   	   	  fillInEmptyLikesTree>* empty){
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
		if(new_posts == NULL) throw std::bad_alloc();
		fillInEmptyLikesTree fill(*empty, new_posts, S, factor);
		(*empty).operateInOrder(fill);
		free(posts);
		delete[] new_posts;
		delete[] to_factor;
		delete[] not_to_factor;
}


void Troll::updateTreeById(int S, int factor){
	Post* posts=this->postsByPostID.returnSortedTreeElementsInOrder();
	if(posts == NULL) throw std::bad_alloc();
	for(int i=0; i<this->numberOfPosts;i++){
		if(posts[i].GetPostID() % S==0){
			posts[i].setLikes(posts[i].GetLikes()*factor);
		}
	}
	fillInEmptyIDTree fill(this->postsByPostID, posts, S, factor);
	postsByPostID.operateInOrder(fill);
	//free(posts);
}

void Troll::updateLikes(int S,int factor){
	int size_posts_by_likes = this->postsByLikes.getSize();
	if(!size_posts_by_likes) return;
	Post* posts_by_likes =  this->getPostSortedByLikes();
	updateLikesTree(posts_by_likes, size_posts_by_likes, S, factor,
													&postsByLikes);
	this->updateTreeById(S, factor);
	AVLTreeNode<Post, postByLikesFunc, fillInEmptyLikesTree>* max =
			postsByLikes.minPointerInAVLTree(postsByLikes.getRoot());
	this->maxPostByLikes = max ? max->getInfo() : Post();
	//free(posts_by_likes);
}


