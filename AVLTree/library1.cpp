/*
 * library1.cpp
 *
 *  Created on: 7 במאי 2016
 *      Author: lior
 */
#include "library1.h";

#include "DST.h"
using std::bad_alloc;
void* Init() {
	try {
		DST* ds = new DST();
		return ds;
	} catch (const bad_alloc& bad_alloc) {
		return NULL;
	}
}

StatusType AddTroll(void* ds, int trollID) {
	try {
		if (ds == NULL || trollID <= 0) {
			return INVALID_INPUT;
		}
		DST* ds1 = static_cast<DST*>(ds);
		if ((*ds1).containTroll(trollID) == true) {
			return FAILURE;
		}
		(*ds1).addTroll(trollID);
		return SUCCESS;
	} catch (std::bad_alloc&) {
		return ALLOCATION_ERROR;
	}
}
StatusType PublishPost(void *DS, int postID, int trollID, int LikesCount) {
	try {
		if (DS == NULL || postID <= 0 || trollID <= 0 || LikesCount < 0) {
			return INVALID_INPUT;
		}
		DST* ds1 = static_cast<DST*>(DS);
		if ((*ds1).containTroll(trollID) == false
				|| (*ds1).containPost(postID) == true) {
			return FAILURE;
		}
		(*ds1).addPost(postID, trollID, LikesCount);
		return SUCCESS;
	} catch (const bad_alloc& bad_alloc) {
		return ALLOCATION_ERROR;
	}

}
StatusType DeletePost(void *DS, int postID) {
	try {
		if (DS == NULL || postID <= 0) {
			return INVALID_INPUT;
		}
		DST* ds1 = static_cast<DST*>(DS);
		if ((*ds1).containPost(postID) == false) {
			return FAILURE;
		}
		(*ds1).DeletePost(postID);
		//TODO: what happens if there is no post with postI

		return SUCCESS;
	} catch (const bad_alloc& bad_alloc) {
		return ALLOCATION_ERROR;
	}
}

StatusType FeedTroll(void *DS, int postID, int LikesIncrease) {
	try {
		if (DS == NULL || postID <= 0 || LikesIncrease <= 0) {
			return INVALID_INPUT;
		}
		DST* ds1 = static_cast<DST*>(DS);
		if ((*ds1).containPost(postID) == false) {
			return FAILURE;
		}
		(*ds1).AddPostLikes(postID, LikesIncrease);

		return SUCCESS;
	} catch (const bad_alloc& bad_alloc) {
		return ALLOCATION_ERROR;
	}
}
StatusType GetTopPost(void *DS, int trollID, int *postID) {
	if (DS == NULL || trollID == 0 || postID == NULL) {
		return INVALID_INPUT;
	}
	DST* ds1 = static_cast<DST*>(DS);
	if (trollID < 0) {
		*postID = ((*ds1).GetTopPost().GetPostID());
		return SUCCESS;
	}
	if ((*ds1).containTroll(trollID) == false) {
		return FAILURE;
	}
	*postID = ((*ds1).GetTopPostOfTroll(trollID).GetPostID());
	return SUCCESS;
}

StatusType GetAllPostsByLikes(void *DS, int trollID, int **posts,
		int *numOfPost) {
	try {
		if (DS == NULL || trollID == 0 || posts == NULL || numOfPost == NULL) {
			return INVALID_INPUT;
		}
		Post* postArr;
		int numberOfPost;
		DST* ds1 = static_cast<DST*>(DS);
		if (trollID < 0) {
			//TODO catch if Post array is faild in alloc
			postArr = (*ds1).GetAllPostOrderedByLikes();
			numberOfPost = (*ds1).getNumOfPosts();
		} else if (trollID > 0 && (*ds1).containTroll(trollID) == false) {
			*numOfPost = 0;
			posts = NULL;
			return FAILURE;
		} else {
			postArr = (*ds1).GetTrollPostsOrderedbyLikes(trollID);
			if (postArr == NULL) {
				return ALLOCATION_ERROR;
			}
			numberOfPost = (*ds1).getNumOfPostsOfTroll(trollID);
		}
		void* postIDArr1 = malloc(numberOfPost * (sizeof(int)));
		if (postIDArr1 == NULL) {
			free(postArr);

			return ALLOCATION_ERROR;
		}
		int* postIDArr = (int*) postIDArr1;
		for (int i = 0; i < numberOfPost; i++) {
			postIDArr[i] = postArr[i].GetPostID();
		}
		*posts = postIDArr;
		*numOfPost = numberOfPost;
		free(postArr);
		return SUCCESS;
	} catch (const bad_alloc& bad_alloc) {
		return ALLOCATION_ERROR;
	}
}
void Quit(void** DS) {
	if (DS != NULL || *DS != NULL) {
		void* ds = *DS;
		DST* ds1 = static_cast<DST*>(ds);
		delete (ds1);
		*DS = NULL;
	}
}
StatusType UpdateLikes(void *DS, int postsCode, int postsFactor) {
	try {
		if (DS == NULL || postsCode < 1 || postsFactor < 1) {
			return INVALID_INPUT;
		}
		DST* ds1 = static_cast<DST*>(DS);
		(*ds1).updateLikes(postsCode, postsFactor);
		return SUCCESS;
	} catch (const bad_alloc& bad_alloc) {
		return ALLOCATION_ERROR;
	}
}
