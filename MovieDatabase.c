
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_STR_LEN 1024

typedef struct MovieReview_struct
{
	char movie_title[MAX_STR_LEN];
	char movie_studio[MAX_STR_LEN];
	int year;
	float BO_total;
	int score;
} MovieReview;

typedef struct ReviewNode_struct
{
	MovieReview review;
	struct ReviewNode_struct *next;
} ReviewNode;

ReviewNode *newMovieReviewNode()
{
    /*
     * This function allocates a new, empty ReviewNode, and initializes the
     * contents of the MovieReview for this node to empty values.
     * The function must return a pointer to the newly allocated and initialized
     * node. If something goes wrong, the function returns NULL
     */
 
	ReviewNode *new_review=NULL;
	new_review=(ReviewNode *)calloc(1,sizeof(ReviewNode));
	
	strcpy(new_review -> review.movie_title,"");
	strcpy(new_review -> review.movie_studio,"");
	new_review -> review.year = -1;
	new_review -> review.BO_total = -1;
	new_review -> review.score = -1;
	new_review ->next = NULL;
	
    return new_review;	
}



ReviewNode *search_for_review( ReviewNode *head, const char title[], const char studio[],  int year) 
{
	/*
     * This function looks through the linked list to find a node that 
     * contains a review for a restaurant whose name matches the 'name_key'
     * If found, return a pointer to the node with the review. Else
     * return NULL.
     */

	ReviewNode *p=NULL;
	p=head;
	while (p!=NULL){
		if (strcmp(p->review.movie_title,title)==0 && strcmp(p->review.movie_studio,studio)==0){
			if (p->review.year==year) {
				return p;
			}
		}
		p=p->next;
	}
	return NULL; // The search key was not found!
}


ReviewNode *findMovieReview(char title[MAX_STR_LEN], char studio[MAX_STR_LEN], int year, ReviewNode *head)
{
    /*
     * This function searches through the linked list for a review that matches the input query. 
     * In this case, the movie review must match the title, studio, and year provided in the 
     * parameters for this function.
     * 
     * If a review matching the query is found, this function returns a pointer to the node that
     * contains that review. 
     * 
     * If no such review is found, this function returns NULL
     */
    
	search_for_review(head, title, studio, year);
	
	ReviewNode *test=NULL;
	test = search_for_review(head, title, studio, year);
    
    return test;	
}


ReviewNode *search( ReviewNode *head, const char title[], const char studio[],  int year,  float BO_total,  int score) 
{
	ReviewNode   *p=NULL; // Traversal pointer
	p=head;
	while (p!=NULL){
		if (strcmp(p->review.movie_title,title)==0 && strcmp(p->review.movie_studio,studio)==0){
			if ((p->review.year==year)  && (p->review.BO_total==BO_total)){
				if (p->review.score==score){
					return p;
				}
			}
		}
		p=p->next;
	}
	return NULL; // The search key was not found!
}


ReviewNode *insert_at_head(ReviewNode *head, ReviewNode *new_node)
{
     /* This function adds a new node at the head of the list.
        Input parameters:
               head : The pointer to the current head of the list
               new_node:  The pointer to the new node
        Returns:
           The new head pointer
	 */

     new_node->next=head;
	 return new_node;
}

ReviewNode *insertMovieReview(char title[MAX_STR_LEN], char studio[MAX_STR_LEN], int year, float BO_total, int score, ReviewNode *head)
{
    /*
     * This function inserts a new movie review into the linked list.
     * 
     * The function takes as input parameters the data neede to fill-in the review,
     * as well as apointer to the current head of the linked list.
     * 
     * If head==NULL, then the list is still empty.
     * 
     * The function inserts the new movie review *at the head* of the linked list,
     * and returns the pointer to the new head node.
     * 
     * The function MUST check that the movie is not already in the list before
     * inserting (there should be no duplicate entries). If a movie with matching
     * title, studio, and year is already in the list, nothing is inserted and the
     * function returns the current list head.
     */

	ReviewNode *one_review=NULL;
	ReviewNode *test=NULL;
	one_review = newMovieReviewNode();

	test = search(head, title, studio, year, BO_total, score);

	if (test==NULL){
		strcpy(one_review->review.movie_title,title);
		
		strcpy(one_review->review.movie_studio,studio);
		
		one_review->review.year = year;
		one_review->review.BO_total = BO_total;
		one_review->review.score = score;
		
		head=insert_at_head(head,one_review);
	}
	else{
		printf("Sorry, that movie already exists\n");	 
	}
	
			
    return head;	// <--- This should change when after you implement your solution
}


int countReviews(ReviewNode *head)
{
  /*
   * This function returns the length of the current linked list. This requires
   * list traversal.
   */

	int count=0;
	
	ReviewNode *p=NULL;
	ReviewNode *q=NULL;
	p=head;

	while (p!=NULL){
		 q=p->next;
		 count++;
		 p=q;
	}
	return count;
}




void updateMovieReview(char title[MAX_STR_LEN], char studio[MAX_STR_LEN], int year, float BO_total, int score, ReviewNode *head)
{
    /*
     * This function looks for a review matching the input query [title, studio, year].
     * If such a review is found, then the function updates the Box-office total, and the score.
     * If no such review is found, the function prints out 
     * "Sorry, no such movie exists at this point"
     */

	ReviewNode *test;
	test = search_for_review(head, title, studio, year);
	
	if (test == NULL){
		printf("Sorry, no such movie exists at this point");
	}
	else{
		test->review.BO_total= BO_total;
		test->review.score= score;
		
	}
}

ReviewNode *deleteMovieReview(char title[MAX_STR_LEN], char studio[MAX_STR_LEN],int year, ReviewNode *head)
{
    /*
     * This function removes a review matching the input query from the linked list. If no such review can
     * be found, it does nothing.
     * 
     * The function returns a pointer to the head of the linked list (which may have changed as a result
     * of the deletion process)
     */

	ReviewNode *test;
	test = search_for_review(head, title, studio, year);
	
	if (test != NULL){
		ReviewNode *p=NULL;
		ReviewNode *q=NULL;
		p=head;

		while (p!=NULL){ 

		 	q=p->next;

			if (p==test){
				p = head->next;
				free(p);
				head = p;
				return (head);
			}

			else if (p->next==test){
				p->next = test->next;
				free(test);
					  return(head);
			}	
			p=q;
		}
	}
    return NULL;	
}

void printMovieReviews(ReviewNode *head)
{
    /*
     * This function prints out all the reviews in the linked list, one after another.
     * Each field in the review is printed in a separate line, with *no additional text*
     * (that means, the only thing printed is the value of the corresponding field).
     * 
     * Reviews are separated from each other by a line of
     * "*******************"
     * 
     * See the Assignment handout for a sample of the output that should be produced
     * by this function
     */
    
	ReviewNode *p=NULL;
	p = head;
	while (p!=NULL){
		printf("%s\n",p->review.movie_title);
		printf("%s\n",p->review.movie_studio);
		printf("%d\n",p->review.year);
		printf("%f\n",p->review.BO_total);
		printf("%d\n",p->review.score);
		printf("*******************\n");
		
		p=p->next;
	}
}

void queryReviewsByStudio(char studio[MAX_STR_LEN], ReviewNode *head)
{
    /*
     * This function looks for reviews whose studio matches the input query.
     * It prints out the contents of all reviews matching the query in exactly
     * the same format used by the printMovieReviews() function above.
     */
    
	ReviewNode *p;
	p = head;
	
	while (p!=NULL){
		if (strcmp(p->review.movie_studio,studio)==0){
			printf("%s\n",p->review.movie_title);
			printf("%s\n",p->review.movie_studio);
			printf("%d\n",p->review.year);
			printf("%f\n",p->review.BO_total);
			printf("%d\n",p->review.score);
			printf("*******************\n");
		}
		p = p->next;
	}
}

void queryReviewsByScore(int min_score, ReviewNode *head)
{
    /*
     * This function looks for reviews whose score is greater than, or equal to
     * the input 'min_score'.
     * It prints out the contents of all reviews matching the query in exactly
     * the same format used by the printMovieReviews() function above.
     */
    
	ReviewNode *p;
	p = head;
	
	while (p!=NULL){
		if (p->review.score >= min_score){
			printf("%s\n",p->review.movie_title);
			printf("%s\n",p->review.movie_studio);
			printf("%d\n",p->review.year);
			printf("%f\n",p->review.BO_total);
			printf("%d\n",p->review.score);
			printf("*******************\n");
		}
		p = p->next;
	}
}

ReviewNode *deleteReviewList(ReviewNode *head)
{
  /*
   * This function deletes the linked list of movie reviews, releasing all the
   * memory allocated to the nodes in the linked list.
   * 
   * Returns a NULL pointer so that the head of the list can be set to NULL
   * after deletion.
   */
      
	ReviewNode *p=NULL;
	ReviewNode *q=NULL;
	
	p=head;
	while (p!=NULL){
		q=p->next;
		free(p);
		p=q;
	}
	
    return p;	
}

ReviewNode *sortReviewsByTitle(ReviewNode *head)
{
  /*
   * This function sorts the list of movie reviews in ascending order of movie
   * title. If duplicate movie titles exist, the order is arbitrary (i.e. you
   * can choose which one goes first).
   * 
   * However you implement this function, it must return a pointer to the head
   * node of the sorted list.
   */

	ReviewNode *p=NULL;
	MovieReview q;
	ReviewNode *start = NULL;
	ReviewNode *r=NULL;
	ReviewNode *smallest=NULL;
	p = head;
	smallest = p;
		int changed = 0;
		while (p!=NULL){
			smallest = p;
			start = p->next;
			while (start!=NULL){
				if ((int)(start->review.movie_title[0]) < (int)(smallest->review.movie_title[0])){
					smallest = start;
				}
				start = start->next;
			}
			
			printf("%c\n", smallest->review.movie_title[0]);
		
			q = p->review;
			r = p->next;
			p->review = smallest->review;
			smallest->review = q;
			p = r;	
		}  

    return head;	// <--- This should change when after you implement your solution
}

