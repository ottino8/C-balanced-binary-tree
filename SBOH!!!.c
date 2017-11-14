#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//////////////////////////////////////BINARY TREE//////////////////////////////////////////////////////////////////////////////////////////

struct student {
	char name[20];
	float marks[10];
	char sNumber[100];
	struct student *left;
	struct student *right;
	struct student *parent;
	int height;
};

struct student *beginning = NULL;
struct student *minRight(struct student *node);
void addStudent(char *name, char *sNumber, float marks[]);
struct student *maxLeft(struct student *node);
void add_mark(struct student *beginning, char *name, int p, float mark);
void inOrder(struct student *node);
void studentInsertion(struct student *node, struct student *newStudent );
void writeList(const struct student *node);
void openList();
void insertInList(const struct student *node, FILE *list);
void writeList2(const struct student *node);
void insertInList2(const struct student *node, FILE *list);
void openList2();
struct student *doubleTurnRight(struct student *node);
struct student * turnLeft(struct student *node);
struct student *singleTurnLeft(struct student *node);
struct student *doubleTurnLeft(struct student *node);
struct student *turnRight(struct student *node);
struct student *singleTurnRight(struct student *node);
struct student *linearReshapeLeft(struct student *node);
struct student *notLinearReshapeLeft(struct student *node);
struct student *linearReshapeRight(struct student *node);
struct student *notLinearReshapeRight(struct student *node);
struct student *Height(struct student *node);
void delete(struct student *toDelete, char *name);
struct student *Deleting(struct student *toDelete);
void stabilizeHeight(struct student *node);
void adjusting(struct student *node);
int count=0;

//create and choose the condition to insert the node
void addStudent(char *name, char *sNumber, float marks[]) {
	// Create the new student:
	count++;
	struct student *newStudent = (struct student *) malloc(sizeof(struct student));
	strcpy(newStudent->name, name);
	strcpy(newStudent->sNumber, sNumber);
	int i;
	for (i = 0; i < 10; i++) {
		newStudent->marks[i] = marks[i];
	}
	newStudent->left = NULL;
	newStudent->right = NULL;
	newStudent->parent = NULL;
	newStudent->height= 1;
	
	// Case 1: List is empty
	if (beginning == NULL ) {
		beginning = newStudent;
		beginning->left = NULL;
		beginning->right = NULL;
		beginning->parent = NULL;
		beginning->height = 1;
		return;
	}
	// Case 2: New student added somewhere else
	else{
		studentInsertion(beginning, newStudent);
		return;
	}
}
//find the minimum node on the right side of the tree
struct student *minRight(struct student *node) {
	if (node->left != NULL ) {
		return minRight(node->left);
	} else {
		return node;
	}
}
//find the maximum node on the right side of the tree
struct student *maxLeft(struct student *node) {
	if (node->right != NULL ) {
		return maxLeft(node->right);
	} else {
		return node;
	}
}

//insert student in the AVL binary tree
void studentInsertion(struct student *node, struct student *newStudent){
    //if the value of name is greater than the one of the current node
    if (strcmp(newStudent->name, node->name) > 0) {
        //printf("new student greater than node");
        //if the values is greater than the node and right of node is free set the right of the node as newstudent if not run in recursive the function with node equal node right 
        if (node->right == NULL ) {
            //printf("free right node");
            node->right = newStudent;
            newStudent->parent = node;
            Height(newStudent);
            return;
        } 
        else {
            studentInsertion(node->right,newStudent);
        }
    }
    //if the value of name is lower than the one of the current node
    if  (strcmp(newStudent->name, node->name) < 0) {
    //else{
        //printf("new student smaller than node");
        //if the values is glower than the node and right of node is free set the right of the node as newstudent if not run in recursive the function with node equal node right 
        if (node->left == NULL ) {
            //printf("free left node");
            node->left = newStudent;
            newStudent->parent = node;
            Height(newStudent);
            return;
        } 
        else {
            studentInsertion(node->left,newStudent);
        }
    }   
}

//measure and set the height of each node and see if the tree has to reshape itself
struct student *Height(struct student *node){
    //printf("\n enterd in Height\n");
    //printf("node name is %s\n and height is %d \n", node->name, node->height );
    //Case 1: node has a parent
    if(node->parent){
        //printf("\n has a parent \n");
        //Case 1.1: change the height of the node parent if the node has the same or bigger height
        //Check if there are the condition for reshaping
        //printf("parent name is %s\n and height is %d \n", node->parent->name, node->parent->height );
        if(node->parent->height <= node->height){ 
            if(node->left){
                if(node->left->height == node->height-3){
                	//printf("node->left name is %s\n and height is %d \n", node->left->name, node->left->height );
                    node=turnLeft(node);
                    return node;
                }
            }
            if(node->left == NULL && node->height == 3){
            	//printf("node->left name is NULL\n and height is 0 \n");
                node=turnLeft(node);
                return node;
            }
            if(node->right){
                if(node->right->height == node->height-3){
                	//printf("node->right name is %s\n and height is %d \n", node->right->name, node->right->height );
                    node=turnRight(node);
                    return node;
                }
            }
            if(node->right==NULL && node->height==3){
            	//printf("node->right name is NULL\n and height is 0 \n");
                node=turnRight(node);
                return node;
            }
            node->parent->height=node->height+1;
            return Height(node->parent);
        }
        else{
        	//printf("parent name is %s\n and height is %d \n", node->parent->name, node->parent->height );
        	if(node->left){
                if(node->left->height == node->height-3){
                	//printf("node->left name is %s\n and height is %d \n", node->left->name, node->left->height );
                    node=turnLeft(node);
                    return node;
                }
            }
            if(node->left == NULL && node->height == 3){
            	//printf("node->left name is NULL\n and height is 0 \n");
                node=turnLeft(node);
                return node;
            }
            if(node->right){
                if(node->right->height == node->height-3){
                	//printf("node->right name is %s\n and height is %d \n", node->right->name, node->right->height );
                    node=turnRight(node);
                    return node;
                }
            }
            if(node->right==NULL && node->height==3){
            	//printf("node->right name is NULL\n and height is 0 \n");
                node=turnRight(node);
                return node;
            }
            if(node->parent->height == node->height+3){
            	return Height(node->parent);
            }
            return node;
        }
    }
    //Case 2: node is beginning
    else{
    	//Case 2.1: check the condition for reshaping
        //printf("\n node is beginning \n");
        if(node->left){
            if(node->left->height == node->height-3){
            //printf("node->left name is %s\n and height is %d \n", node->left->name, node->left->height );
            node=turnLeft(node);
            return node;
            }
        }
        if(node->left == NULL && node->height == 3){
        	//printf("node->left name is NULL\n and height is 0 \n");
            node=turnLeft(node);
            return node;
        }
        if(node->right){
            if(node->right->height == node->height-3){
            	//printf("node->right name is %s\n and height is %d \n", node->right->name, node->right->height );
	            node=turnRight(node);
	            return node;
            }
        }
        if(node->right==NULL && node->height==3){
        	//printf("node->right name is NULL\n and height is 0 \n");
            node=turnRight(node);
            return node;
        }
        return node;
    }
}

//measure and set the height of each node and see if the tree has to reshape itself
struct student *HeightDelete(struct student *node){
    //printf("\n enterd in Height\n");
    //printf("node name is %s\n and height is %d \n", node->name, node->height );
    //Case 1: node has a parent
    if(node->parent){
        //printf("\n has a parent \n");
        //Case 1.1: change the height of the node parent if the node has the same or bigger height
        //Check if there are the condition for reshaping
        //printf("parent name is %s\n and height is %d \n", node->parent->name, node->parent->height );
        if(node->parent->height <= node->height){ 
            if(node->left){
                if(node->left->height == node->height-3){
                	//printf("node->left name is %s\n and height is %d \n", node->left->name, node->left->height );
                    node=turnLeft(node);
                    return node;
                }
            }
            if(node->left == NULL && node->height == 3){
            	//printf("node->left name is NULL\n and height is 0 \n");
                node=turnLeft(node);
                return node;
            }
            if(node->right){
                if(node->right->height == node->height-3){
                	//printf("node->right name is %s\n and height is %d \n", node->right->name, node->right->height );
                    node=turnRight(node);
                    return node;
                }
            }
            if(node->right==NULL && node->height==3){
            	//printf("node->right name is NULL\n and height is 0 \n");
                node=turnRight(node);
                return node;
            }
            node->parent->height=node->height+1;
            return Height(node->parent);
        }
        else{
        	//printf("parent name is %s\n and height is %d \n", node->parent->name, node->parent->height );
        	if(node->left){
                if(node->left->height == node->height-3){
                	//printf("node->left name is %s\n and height is %d \n", node->left->name, node->left->height );
                    node=turnLeft(node);
                    return node;
                }
            }
            if(node->left == NULL && node->height == 3){
            	//printf("node->left name is NULL\n and height is 0 \n");
                node=turnLeft(node);
                return node;
            }
            if(node->right){
                if(node->right->height == node->height-3){
                	//printf("node->right name is %s\n and height is %d \n", node->right->name, node->right->height );
                    node=turnRight(node);
                    return node;
                }
            }
            if(node->right==NULL && node->height==3){
            	//printf("node->right name is NULL\n and height is 0 \n");
                node=turnRight(node);
                return node;
            }
            if(node->parent->height == node->height+3){
            	return Height(node->parent);
            }
            return Height(node->parent);;
        }
    }
    //Case 2: node is beginning
    else{
    	//Case 2.1: check the condition for reshaping
        //printf("\n node is beginning \n");
        if(node->left){
            if(node->left->height == node->height-3){
            //printf("node->left name is %s\n and height is %d \n", node->left->name, node->left->height );
            node=turnLeft(node);
            return node;
            }
        }
        if(node->left == NULL && node->height == 3){
        	//printf("node->left name is NULL\n and height is 0 \n");
            node=turnLeft(node);
            return node;
        }
        if(node->right){
            if(node->right->height == node->height-3){
            	//printf("node->right name is %s\n and height is %d \n", node->right->name, node->right->height );
	            node=turnRight(node);
	            return node;
            }
        }
        if(node->right==NULL && node->height==3){
        	//printf("node->right name is NULL\n and height is 0 \n");
            node=turnRight(node);
            return node;
        }
        //printf("return node\n");
        return node;
    }
}
//Choose what type of reshape on the left the tree has to do
struct student * turnLeft(struct student *node){
    //printf("enterd in turnLeft\n");
    //printf("%s\n",node->name );
    if(node->right->right==NULL && node->right->left){
        //printf("debug4\n");
        node=doubleTurnLeft(node);
        return node;
    }
    if(node->right->left){
        //printf("exist node->right->left\n");
        if(node->right->left->height > node->right->right->height){
            //printf("debug1\n");
            node=doubleTurnLeft(node);
            return node;
        }
        if(node->right->right==NULL){
            //printf("debug2\n");
            node=doubleTurnLeft(node);
            return node;
        }
        else{
            //printf("debug3\n");
            node=singleTurnLeft(node);
            return node;
        }
    }

    else{
        node=singleTurnLeft(node);
        return node;
    }
}

//New subRoot is node->right
struct student * singleTurnLeft(struct student *node){
    //printf("enterd in singleTurnLeft\n");
    if(node->left){
    	//printf("node left height is %d\n", node->left->height);
    	if(node->right->left){
    		node->height=node->left->height+1;
	    	//printf("node height %d\n", node->height);
	    	if(node->right->left->height==node->right->right->height){
	    		//printf("node->right->left==node->righ->right\n");
	    		node->right->height=node->height;
	    		if(node->right->left->height > node->left->height){
	    			node->height=node->right->left->height+1;
	    		}
	    	}
	    }
	    else{
	    	node->height=node->left->height+1;
	    	//printf("node height %d\n", node->height);
	    }
    }
    else{
    	if(node->right->left){
	    	if(node->right->left->height==node->right->right->height){
	    		node->right->height=node->height;
	    		node->height=node->right->left->height+1;
	    	}
	    }
	    else{
	    	node->height=node->height-2;
	    }
    }
	    
    if(node->parent){
    	//printf("node->parent\n");
        struct student *Parent= node->parent;
        if(Parent->right==node){
        	//printf("node is right child\n");
        	Parent->right=NULL;
	        struct student *new=linearReshapeLeft(node);
	        new->parent=Parent;
	        Parent->right=new;
	        return new;
	    }
	    else{
	    	//printf("node is left child\n");
	    	Parent->left=NULL;
	        struct student *new=linearReshapeLeft(node);
	        new->parent=Parent;
	        Parent->left=new;
	        return new;
	    }
        
    }
    else{
    	if(beginning==node){
    		beginning=linearReshapeLeft(node);
	        beginning->parent=NULL;
	        return beginning;
    	}
	    else{
	    	struct student *new=linearReshapeLeft(node);
	        new->parent=NULL;
	        return new;
	    }
    }
}

 
/*							O 				  O*
							 \				 /  \
moving from this situation	   O*    to 	O    O
								\
								 O  
								 */
struct student *linearReshapeLeft(struct student *node){
    //printf("enterd in linearReshapeLeft\n");
    node->parent=NULL;
    struct student *subRoot =node->right;
    if(subRoot->left){
    	//printf("subRoot->left\n");
        struct student *tmp=subRoot->left;
        tmp->parent=node;
        node->right=tmp;
    }
    else{
        node->right=NULL;
    }
    node->parent=subRoot;
    subRoot->left=node;
    subRoot->parent=NULL;
    return subRoot;
}


//make node->right->left the new subRoot 
struct student *doubleTurnLeft(struct student *node){
    //printf("enterd in doubleTurnLeft\n");
    node->right->left->height=node->right->left->height+1;
    node->right->height=node->right->height-1;
    if(node->left){
    	printf("node->left\n");
    	node->height=node->left->height+1;
    	if(node->right->left->left){
    		if(node->right->left->left->height > node->left->height){
    			node->height=node->right->left->left->height+1;
    		}
    	}
    }
    else{
    	printf("not node->left\n");
    	node->height=node->height-2;
    	if(node->right->left->left){
    		if(node->right->left->left->height > node->left->height){
    			node->height=node->right->left->left->height+1;
    		}
    	}
    }
    if(node->parent){
        struct student *Parent= node->parent;
        if(Parent->right==node){
        	printf("node is right child\n");
        	Parent->right=NULL;
	        struct student *new=notLinearReshapeLeft(node);
	        new->parent=Parent;
	        Parent->right=new;
	        return new;
	    }
	    else{
	    	printf("node is left child\n");
	    	Parent->left=NULL;
	        struct student *new=notLinearReshapeLeft(node);
	        new->parent=Parent;
	        Parent->left=new;
	        return new;
	    }
        
    }
    else{
        
        if(beginning==node){
    		beginning=notLinearReshapeLeft(node);
	        beginning->parent=NULL;
	        return beginning;
    	}
	    else{
	    	struct student *new=notLinearReshapeLeft(node);
	        new->parent=NULL;
	        return new;
	    }
    }
}

/*							 O 				  O*
							  \				 /  \
moving from this situation	   O    to 		O    O
							  /
							 O*  
								 */
struct student *notLinearReshapeLeft(struct student *node){
    node->parent=NULL;
    struct student *subRoot= node->right->left;
    struct student *tmp1;
    struct student *tmp2;
    node->right->left=NULL;
    node->right=NULL;
    subRoot->parent->parent=subRoot;
    if(subRoot->left){
    	//printf("subRoot->left\n");
        tmp1=subRoot->left;
        tmp1->parent=node;
        node->right=tmp1;
    }
    if(subRoot->right){
    	//printf("subRoot->right\n");
        tmp2=subRoot->right;
        tmp2->parent=subRoot->parent;
        subRoot->parent->left=tmp2;
    }
    subRoot->right=subRoot->parent;
    node->parent=subRoot;
    subRoot->left=node;
    subRoot->parent=NULL;
    return subRoot;
}

//choose what kind of reshape on the right the tree has to do
struct student *turnRight(struct student *node){
    //printf("enterd in turnright\n");
    //printf("%s\n",node->name );
    if(node->left->left==NULL){
        //printf("debug4\n");
        node=doubleTurnRight(node);
        return node;
    }
    if(node->left->right){
        //printf("exist node->left->right\n");
        if(node->left->right->height > node->left->left->height){
            //printf("debug1\n");
            node=doubleTurnRight(node);
            return node;
        }
        if(node->left->left==NULL){
            //printf("debug2\n");
            node=doubleTurnRight(node);
            return node;
        }
        else{
            //printf("debug3\n");
            node=singleTurnRight(node);
            return node;
        }
    }

    else{
    	//printf("debug5\n");
        node=singleTurnRight(node);
        return node;
    }
}

//node->left->left->height is bigger than node->left->right->height so node left is the new subRoot
struct student *singleTurnRight(struct student *node){
    //printf("enterd in singleTurnright\n");
    if(node->right){
    	//printf("node right height is %d\n", node->right->height);
    	if(node->left->right){
    		node->height=node->right->height+1;
	    	//printf("node height %d\n", node->height);
	    	if(node->left->right->height==node->left->left->height){
	    		//printf("node->left->right==node->righ->left\n");
	    		node->left->height=node->height;
	    		if(node->left->right->height > node->right->height){
	    			node->height=node->left->right->height+1;
	    		}
	    	}
	    }
	    else{
	    	node->height=node->right->height+1;
	    	//printf("node height %d\n", node->height);
	    }
    }
    else{
    	if(node->left->right){
	    	if(node->left->right->height==node->left->left->height){
	    		node->left->height=node->height;
	    		node->height=node->left->right->height+1;
	    	}
	    }
	    else{
	    	node->height=node->height-2;
	    }
    }
    if(node->parent){
        struct student *Parent= node->parent;
        if(Parent->right==node){
        	//printf("node is right child\n");
        	Parent->right=NULL;
	        struct student *new=linearReshapeRight(node);
	        new->parent=Parent;
	        Parent->right=new;
	        return new;
	    }
	    else{
	    	//printf("node is left child\n");
	    	Parent->left=NULL;
	        struct student *new=linearReshapeRight(node);
	        new->parent=Parent;
	        Parent->left=new;
	        return new;
	    }
        
    }
    else{
    	if(beginning==node){
    		beginning=linearReshapeRight(node);
	        beginning->parent=NULL;
	        return beginning;
    	}
	    else{
	    	struct student *new=linearReshapeRight(node);
	        new->parent=NULL;
	        return new;
	    }
    }
}

/*							     O 			  O*
							   	/			 / \
moving from this situation	   O*    to 	O   O
							  /
							 O  
								 */
struct student *linearReshapeRight(struct student *node){
    //printf("enterd in linearReshaperight\n");
    node->parent=NULL;
    struct student *subRoot =node->left;
    if(subRoot->right){
        struct student *tmp=subRoot->right;
        tmp->parent=node;
        node->left=tmp;
    }
    else{
        node->left=NULL;
    }
    node->parent=subRoot;
    subRoot->right=node;
    subRoot->parent=NULL;
    return subRoot;
}

//node->left->right height is bigger than the one of node->left->left
struct student * doubleTurnRight(struct student *node){
    //printf("enterd in doubleTurnright\n");
    node->left->right->height=node->left->height;
    node->left->height=node->left->height-1;
    if(node->right){
    	//printf("node->right\n");
    	node->height=node->right->height+1;
    	if(node->left->right->right){
    		if(node->left->right->right->height > node->right->height){
    			node->height=node->left->right->right->height+1;
    		}
    	}
    }
    else{
    	//printf("not node->right\n");
    	node->height=node->height-2;
    	if(node->left->right->right){
    		if(node->left->right->right->height > node->right->height){
    			node->height=node->left->right->right->height+1;
    		}
    	}
    }
    if(node->parent){
    	//printf("has a parent\n");
        struct student *Parent= node->parent;
        if(Parent->right==node){
        	//printf("node is right child\n");
        	Parent->right=NULL;
	        struct student *new=notLinearReshapeRight(node);
	        new->parent=Parent;
	        Parent->right=new;
	        return new;
	    }
	    else{
	    	//printf("node is left child\n");
	    	Parent->left=NULL;
	        struct student *new=notLinearReshapeRight(node);
	        new->parent=Parent;
	        Parent->left=new;
	        return new;
	    }
    }
    else{
        if(beginning==node){
    		beginning=notLinearReshapeRight(node);
	        beginning->parent=NULL;
	        return beginning;
    	}
	    else{
	    	struct student *new=notLinearReshapeRight(node);
	        new->parent=NULL;
	        return new;
	    }
    }
}

/*							  O 			  O*
							 /				 / \
moving from this situation	O    to 		O   O
							 \
							  O*  
								 */
struct student *notLinearReshapeRight(struct student *node){
    node->parent=NULL;
    struct student *subRoot= node->left->right;
    struct student *tmp1;
    struct student *tmp2;
    node->left->right=NULL;
    node->left=NULL;
    subRoot->parent->parent=subRoot;
    if(subRoot->right){
    	//printf("subRoot->right\n");
        tmp1=subRoot->right;
        tmp1->parent=node;
        node->left=tmp1;
    }
    if(subRoot->left){
    	//printf("subRoot->left\n");
        tmp2=subRoot->left;
        tmp2->parent=subRoot->parent;
        subRoot->parent->right=tmp2;
    }
    subRoot->left=subRoot->parent;
    node->parent=subRoot;
    subRoot->right=node;
    subRoot->parent=NULL;
    return subRoot;
}


//search for the right node in recursive
struct student *search(struct student *node, char *name) {
	//printf("searching \n");
	//if smaller rerun the function for node->left
	if (node == NULL) {
        //printf("Not found.\n");
        return NULL;
    }
    if (strcmp(name, node->name) < 0) {
      //printf("name smaller than node name - ");
      if(node->left){
      	return search(node->left, name);
      }
      else{
      	return NULL;
      }
  	}
	//if bigger rerun the function for node->right
  if (strcmp(name, node->name) > 0) {
      //printf("name bigger than node name - ");
      if(node->right){
      	return search(node->right, name);
      }
      else{
      	return NULL;
      }
  	}
	//if equal return node
  if (strcmp(name, node->name) == 0) {
	//else{
      //printf("name equal node name");
      return node;
  	}
}

//add mark to a student
void add_mark(struct student *node, char *name, int p, float mark) {
	name=name;
	//search for the student you have to change the vote 
	struct student *toAddMark = search(beginning, name);
	if(toAddMark==NULL){
		//printf("student to add mark to not found\n");
		return;
	}
	//change the vote
	toAddMark->marks[p-1] = mark;
	return;
}

//prepare and finish the process for deleting a student
void delete(struct student *toDelete, char *name){
	printf("enterd in delete\n");
    toDelete=search(beginning,name);
    if(toDelete==NULL){
    	//printf("student to delete not found\n");
    	return;
    }
    struct student *toAdjust;
    struct student *tmp;
    struct student *tmpl=NULL;
    struct student *tmpr=NULL;
    if(toDelete->parent){
    	//printf("has a parent\n");
        struct student *Parent= toDelete->parent;
        //printf("Parent is %s\n",Parent->name );
        if(Parent->parent){
        	tmp=Parent->parent;
        	//printf("tmp is %s\n",tmp->name );
        	if(tmp->left==Parent){
        		tmpl=tmp->left;
        	}
        	else{
        		tmpr=tmp->right;
        	}
        }
        if(Parent->left==toDelete){
        	//printf("toDelete is left child\n");
        	Parent->left=NULL;
        	toDelete->parent=NULL;
        	struct student *new= Deleting(toDelete);
        	if(new==NULL){
        		Parent->left=NULL;
        		if(Parent->right==NULL){
        			//printf("no parent right\n");
        			Parent->height=1;
        			stabilizeHeight(Parent);
	        		toAdjust=Height(Parent);
	        		adjusting(toAdjust);
        		}
	        	else{
	        		//printf("parent right is %s and height is %d\n", Parent->right->name, Parent->right->height);
	        		stabilizeHeight(Parent);
	        		toAdjust=Height(Parent->right);
	        		adjusting(toAdjust);
	        	}	
        		return;
        	}
        	new->parent=Parent;
        	Parent->left=new;
        	//printf("\n\n\n");
        	stabilizeHeight(new);
        	//printf("new height is %d\n Parent->height is %d\n", new->height, Parent->height);
        	toAdjust=Height(new);
            if(tmpl != NULL){
            	tmp->left=Parent;
            	//printf("tmp is %s and is left son is Parent %s\n", tmp->name, Parent->name );
            }
            if(tmpr != NULL){
            	tmp->right=Parent;
            	//printf("tmp is %s and is left son is Parent %s\n", tmp->name, tmp->right->name );
            }
            adjusting(toAdjust);
            return;
        }
        else{
        	//printf("toDelete is right child\n");
            Parent->right=NULL;
            toDelete->parent=NULL;
            struct student *new = Deleting(toDelete);
            if(new==NULL){
            	if(Parent->left==NULL){
        			Parent->height=1;
        			stabilizeHeight(Parent);
	        		toAdjust=Height(Parent);
	        		adjusting(toAdjust);
        		}
        		else{
        			stabilizeHeight(Parent->left);
	        		//printf("stabilized\n");
	        		toAdjust=Height(Parent->left);
	        		adjusting(toAdjust);
        		}	
        		return;
        	}
            //printf("Parent is %s\n",Parent->name );
            new->parent=Parent;
            Parent->right=new;
        	stabilizeHeight(new);
        	//printf("exit from stabilizeHeight\n");
        	//printf("new height is %d\n Parent->height is %d\n", new->height, Parent->height);
        	toAdjust=Height(new);
        	adjusting(toAdjust);
            return;
        }
    }
    else{
    	//printf("toDelete is root\n");
        struct student *new = Deleting(toDelete);
        beginning=new;
        return;
    }
}

//delete a student a stabilize its subtree
struct student *Deleting(struct student *toDelete){
	count--;
	//printf("enterd in Deleting\n");
    if(toDelete->left){
        struct student *new=maxLeft(toDelete->left);
        //printf("new is %s\n", new->name );
        if(new->left){
        	if(new->parent==toDelete){
        		if (toDelete->right){
        			toDelete->right->parent=new;
        		}
        		toDelete->left=NULL;
        		new->right=toDelete->right;
        		toDelete->right=NULL;
        		new->parent=NULL;
        		if(new->right){
        			if(new->right->height >= new->height){
        				new->height=new->right->height+1;
        			}
        		}
        		free(toDelete);
        		new=Height(new);
        		return new;
        	}
        	else{
        		new->height=toDelete->height;
        		//printf("new has left child\n");
	            struct student *tmp= new->left;
	            //printf("new parent is %s\n",new->parent );
	            tmp->parent= new->parent;
	            new->parent->right=tmp;
	            new->height=toDelete->height;
	            new->right=toDelete->right;
	            new->left=toDelete->left;
	            toDelete->right=NULL;
	            toDelete->left=NULL;
	            if (new->right) new->right->parent=new;
	            if (new->left) new->left->parent=new;
	            new->parent=NULL;
	            free(toDelete);
	            stabilizeHeight(tmp);
	            Height(tmp);
	            return new;
        	}
        }
        else{
        	if(new->parent->left == NULL){
        		new->parent->height=1;
        	}
        	struct student *tmp = new->parent;
        	if(tmp==toDelete){
        		toDelete->left=NULL;
        		new->right=toDelete->right;
        		//printf("new right is %s\n",new->right );
        		toDelete->right=NULL;
        		new->parent=NULL;
        		if(new->right){
        			new->right->parent=new;
        			new->height=new->right->height+1;
        		}
        		free(toDelete);
        		new=Height(new);
        		return new;
        	}
        	else{
        		new->height=toDelete->height;
        		tmp->right=NULL;
        		new->parent=NULL;
        		if(toDelete->right){
        			toDelete->right->parent=new;
        		}
        		toDelete->left->parent=new;
        		new->left=toDelete->left;
        		new->right=toDelete->right;
        		free(toDelete);
        		stabilizeHeight(new);
        		new=Height(new);
        		return new;
        	}
        }
    }
    if(toDelete->right){
    	//printf("toDelete has no left child\n");
        struct student *new=toDelete->right;
        toDelete->right=NULL;
        new->parent=NULL;
        free(toDelete);
        return new; 
    }
    if(toDelete->left==NULL && toDelete->right==NULL){
    	//printf("toDelete has no right or left sons\n");
        free(toDelete);
        //printf("deleted\n");
        return NULL;
    }
}

//set the new value of height of the tree after deleting
void stabilizeHeight(struct student *node){
	//printf("\n\nenterd in stabilizeHeight\n\n");
	//printf("node is %s\n and height %d \n",node->name, node->height );
    if(node->parent){
    	//printf("has a parent\n");
    	//printf("parent is %s\n and height %d \n",node->parent->name, node->parent->height );
        if(node->parent->left){
        	//printf("the parent has a left child\n");
            if(node->parent->left==node){
            	//printf("node is left child\n");
                if(node->parent->right){
                	//printf("parent has a right child\n");
                    if(node->parent->right->height <= node->height){
                    	//printf("node is bigger than parent right\n");
                        node->parent->height=node->height+1;
                        //printf("parent is %s\n and height %d \n",node->parent->name, node->parent->height );
                        return stabilizeHeight(node->parent);
                    }
                    else{
                    	//printf("node is smaller than parent right \n");
                    	//printf("parent right is %s\n and height %d \n",node->parent->right->name, node->parent->right->height );
                    	node->parent->height=node->parent->right->height+1;
                    	//printf("parent is %s\n and height %d \n",node->parent->name, node->parent->height );
                        return stabilizeHeight(node->parent);
                    }
                }
                else{
                	//printf("node->parent has no right child\n");
                    node->parent->height=node->height+1;
                    //printf("parent is %s\n and height %d \n",node->parent->name, node->parent->height );
                    return stabilizeHeight(node->parent);
                }
            }
            else{
            	//printf("node is right child\n");
                if(node->parent->left->height <= node->height){
                	//printf("node is bigger than parent left\n");
                    node->parent->height=node->height+1;
                    //printf("parent is %s\n and height %d \n",node->parent->name, node->parent->height );
                    return stabilizeHeight(node->parent);
                }
                else{
                	//printf("node is smaller than parent left\n");
                	//printf("parent left is %s\n and height %d \n",node->parent->left->name, node->parent->left->height );
                	node->parent->height=node->parent->left->height+1;
                	//printf("parent is %s\n and height %d \n",node->parent->name, node->parent->height );
                	//printf("debug\n");
                    return stabilizeHeight(node->parent);
                }
            }
        }
        else{
        	//printf("node parent left = NULL\n");
            node->parent->height=node->height+1;
            //printf("parent is %s\n and height %d \n",node->parent->name, node->parent->height );
            return stabilizeHeight(node->parent);
        }
    }
    else{
    	//printf("has no parent\n");
        return;
    }
}

void adjusting(struct student *node){
	//printf("\n enterd in adjusting\n");
	int b,c;
	b=beginning->height;
	HeightDelete(node);
	stabilizeHeight(node);
	c=beginning->height;
	if(c!=b){
		adjusting(node);
	}
	else{
		return;
	}
	/*if(node->parent){
		printf("\nenterd in adjusting\n");
		stabilizeHeight(node);
		if(node!=HeightDelete(node)){
			node=HeightDelete(node);
			return adjusting(node->parent);
		}
		else{
			return;
		}
	}
	else{
		return;
	}
	*/	
}

//print in alphabetical orde from left to right
void inOrder(struct student *node) {
	if(beginning == NULL){
		return;
	}
	//print from left to right
	if (node->left) {
		inOrder(node->left);
	}
	printf("\n Student Name: %s \n Student Number: %s \n Height: %d \n The marks are: \n ", node->name, node->sNumber, node->height);
	int k;
	for (k = 0; k < 10; k++) {
		printf("%f ", node->marks[k]);
	}
	printf("\n");
	if (node->right) {
		inOrder(node->right);
	}
}

//save the list in a file
void writeList(const struct student *node){
	FILE *list;
	list = fopen("list.bin","wb");
	insertInList(node, list);
	fclose(list);
	return;
}

//insert each struct in the list in alphabetical order
void insertInList(const struct student *node, FILE *list){
	 int res;
	if (node->left) {
	  insertInList(node->left,list);
	}
	res=fwrite(node, sizeof(struct student),1,list);
	printf("Write Student %s %d\n",node->name,res);
	if (node->right) {
	  insertInList(node->right,list);	
	}	
}

//open a file with the struct and recreate the binarytree
void openList(){
	struct student *newStudent = (struct student *)malloc(sizeof(struct student)); 
	FILE *list = fopen("list.bin", "rb");
	
	printf("READ function, struct size %d... \n", sizeof(struct student));
	size_t debug = fread(newStudent, sizeof(struct student), 1, list);
	
	while(debug == 1){
		printf("READ Student %s\n",newStudent->name);
		if (beginning == NULL){
			printf("%s is root \n" , newStudent->name); 
			beginning = newStudent;
			beginning->left=NULL;
			beginning->right=NULL;
			beginning->parent=NULL;
			beginning->height=1;
		}
		else{
			newStudent->left=NULL;
			newStudent->right=NULL;
			newStudent->parent = NULL;
            newStudent->height = 1;
			studentInsertion(beginning, newStudent);
			printf("\n \n STUDENT INSERTED \n \n");
			printf("%s is root\n\n",beginning->name);
		}
		count++;
		newStudent = (struct student *)malloc(sizeof(struct student));
		debug = fread(newStudent, sizeof(struct student), 1, list);
	}
	fclose(list);
	return;	
}


void writeList2(const struct student *node){
	FILE *list;
	list = fopen("list2.bin","wb");
	insertInList(node, list);
	fclose(list);
	return;
}

//insert each struct in the list in alphabetical order
void insertInList2(const struct student *node, FILE *list){
	 int res;
	if (node->left) {
	  insertInList(node->left,list);
	}
	res=fwrite(node, sizeof(struct student),1,list);
	printf("Write Student %s %d\n",node->name,res);
	if (node->right) {
	  insertInList(node->right,list);	
	}	
}

//open a file with the struct and recreate the binarytree
void openList2(){
	struct student *newStudent = (struct student *)malloc(sizeof(struct student)); 
	FILE *list = fopen("list2.bin", "rb");
	
	printf("READ function, struct size %d... \n", sizeof(struct student));
	size_t debug = fread(newStudent, sizeof(struct student), 1, list);
	
	while(debug == 1){
		printf("READ Student %s\n",newStudent->name);
		if (beginning == NULL){
			printf("%s is root \n" , newStudent->name); 
			beginning = newStudent;
			beginning->left=NULL;
			beginning->right=NULL;
			beginning->parent=NULL;
			beginning->height=1;
		}
		else{
			newStudent->left=NULL;
			newStudent->right=NULL;
			newStudent->parent = NULL;
            newStudent->height = 1;
			studentInsertion(beginning, newStudent);
			printf("\n \n STUDENT INSERTED \n \n");
			printf("%s is root\n\n",beginning->name);
		}
		count++;
		newStudent = (struct student *)malloc(sizeof(struct student));
		debug = fread(newStudent, sizeof(struct student), 1, list);
	}
	fclose(list);
	return;	
}
//////////////////////////////////////////////////////////////////////LINKED LIST///////////////////////////////////////////////////////////
//crete the struct
struct Students{
	char Name[20];
	float  Marks[10];
	char numberOfTheStudent[100];
	struct Students *next;
};

struct Students *root = NULL;
void insertStudent(struct Students *block);
void addMark( char *Name, int n, float Mark);
void deleteStudent(char *Name);
void printStudent();
void writeIntoFILE(struct Students *block);
void readFromFILE();

//create a student
void createStudent(char *Name, char *numberOfTheStudent, float Marks[]) {
// Create the new Students:
	struct Students *studentNew = (struct Students *) malloc(sizeof(struct Students));
	strcpy(studentNew->Name, Name);
	strcpy(studentNew->numberOfTheStudent, numberOfTheStudent);
	int i;
	for (i = 0; i < 10; i++) {
		studentNew->Marks[i] = Marks[i];
	}
	studentNew->next = NULL;
	insertStudent(studentNew);
}

//insert the student in the linked list
void insertStudent(struct Students *block){
 // Case 1: List is empty
	if (root == NULL) {
		root = block;
		root->next = NULL;
		return ;
	}

// Case 2: New Students has to be added at the root of the list
	if (strcmp(block->Name, root->Name) < 0) {
		struct Students *current = root;
		root = block;
		root->next = current;
		return ;
	}
// Case 3: Students is to be added somewhere after the first element
	struct Students *variable = root;
	while (variable->next!=NULL) {
		if (strcmp(block->Name, variable->next->Name) < 0) {
			struct Students *current = variable->next;
			variable->next = block;
			block->next = current;
			return ;
		}
		printf("Iteration\n%s", variable->Name);
		variable = variable->next;
	}
	block->next = NULL;
	variable->next = block;
	return ;
}

//add mark to a student
void addMark( char *Name, int n, float Mark){
	struct Students *current = root;
	while (current != NULL){
//printf("Debug2.2");
		if(strcmp(current->Name,Name)==0){
			current->Marks[n-1]=Mark;
//printf("adding Mark");
			return;
		}
		else{
			current= current->next;
		}
	}
}

//delete a student
void deleteStudent(char *Name){
	struct Students *current = root;
	if(strcmp(root->Name,Name)==0){
		current=root;
		root=root->next;
		free(current);
		return;
	}
	else{
		while (current->next != NULL){
			if(strcmp(current->next->Name,Name)==0){
				struct Students *newContinue=current->next->next;
				free(current->next);
				current->next=newContinue;
				return;
			}
			else{
				current= current->next;
			}
		}
	}
		
}

void singleStudentReport(char *Name, struct Students *current){
	int k;
	if(strcmp(Name,current->Name)==0){
		printf("\n Students Name: %s \n Students Number: %s \n The Marks are: \n", current->Name, current->numberOfTheStudent);
		for(k=0; k<10; k++){
			printf("%f ", current->Marks[k]);
		}
		printf("\n");
		return;
	}
	else{
		singleStudentReport(Name,current->next);
	}
}

//print student report
void printStudent(){
	int k;
	struct Students *current = root;
	while (current != NULL){
		printf("\n Students Name: %s \n Students Number: %s \n The Marks are: \n", current->Name, current->numberOfTheStudent);
		for(k=0; k<10; k++){
			printf("%f ", current->Marks[k]);
		}
		current = current->next;
	}
	return;
}

//save list into a file
void writeIntoFILE(struct Students *block){
	FILE *FILE;
	int j;
	FILE = fopen("FILE.bin","wb");
	struct Students *variable=root;
	while(variable!=NULL){
		fwrite(variable, sizeof(struct Students),1,FILE);
		printf("Write Students %s \n",variable->Name);
		variable=variable->next;
	}
	fclose(FILE);
	return;
} 

//read structures from file
void readFromFILE(){
	struct Students *studentNew = (struct Students *)malloc(sizeof(struct Students)); 
	FILE *FILE = fopen("FILE.bin", "rb");
	printf("READ function, struct size %d... \n", sizeof(struct Students));
	size_t t = fread(studentNew, sizeof(struct Students), 1, FILE);
	while(t == 1){
		printf("READ Students %s\n",studentNew->Name);
		insertStudent(studentNew);
		studentNew = (struct Students *)malloc(sizeof(struct Students));
		t = fread(studentNew, sizeof(struct Students), 1, FILE);
	}   
	fclose(FILE);
	return;
}


///////////////////////////////////////////////////////////////////////////////////MAIN///////////////////////////////////////////////////////////////////////////////////////////


int main(int argc, char const *argv[])
{
	if(argc < 2){
		return 0;
	}
	if(!strcmp(argv[1], "linkedlist")){
		int a, i, n;
		char Name[20], numberOfTheStudent[100];
		float Marks[10];
		float Mark;
		while (a !=8){ 
			printf("\n 1 Add a Students \n 2 Add a Mark to Students \n 3 delete a Students \n 4 Print the report of all the Studentss \n 5 save to FILE \n 6 open from flie \n 7 single student report\n 8 exit the program \n");
			scanf("%d", &a);
			switch(a){

				case 1:
					printf("\n insert Students informations \n Name: ");
					scanf("%s", Name);
					printf("\n Students number: ");
					scanf("%s",numberOfTheStudent);
					for (i=0; i<10; i++){
						Marks[i]=0;
					}
					createStudent(Name, numberOfTheStudent, Marks);               
					break;

				case 2: 
					printf("\n Insert the Name of the Students you want to add the Mark to: ");
					scanf("%s", Name);
					printf("\n Insert the number of the subject: ");
					scanf("%d", &n);
					printf("\n Insert the Mark: ");
					scanf("%f", &Mark);
					addMark(Name,n,Mark);
					break;

				case 3:
					printf("\n Insert the Name of the Students you want to see report: ");
					scanf("%s", Name);
					deleteStudent(Name);
					break;

				case 4:
					printStudent();
					break;

				case 5:
					writeIntoFILE(root);
					break;

				case 6:
					readFromFILE();
					break;

				case 7:
					printf("\n Insert the Name of the Students you want to delete: ");
					scanf("%s", Name);
					singleStudentReport(Name,root);
					break;	
			}
		}        
	}
	else if (!strcmp(argv[1], "binarytree")){
		int a, i, p;
		char name[20], sNumber[100];
		float marks[10];
		float mark;
		struct student *try;
		while (a != 8) {
			printf(
	            "\n 1 for add a new student \n 2 for add a mark \n 3 to delete a student \n 4 to print the report of all the students \n 5 to save file \n 6 to open the file \n 7 print report of a single student \n 8 exit the program \n");
			scanf("%d", &a);
			switch (a) {
	          case 1:
	          printf("\nStudent Name: ");
	          scanf("%s", name);
	          printf("\n student number: ");
	          scanf("%s", sNumber);
	          for (i = 0; i < 10; i++) {
	            marks[i] = 0;
	        }
	        addStudent(name, sNumber, marks);
	        //Reshape();

	        break;

	        case 2:
	        printf("\n insert the name of the student you want to add the mark to: ");
	        scanf("%s", name);
	        printf("\n insert the number of the subject: ");
	        scanf("%d", &p);
	        printf("\n insert the mark: ");
	        scanf("%f", &mark);
	        add_mark(beginning, name, p, mark);
	        break;

	        case 3:
	        printf("\n insert the name of the student you want to delete: ");
	        scanf("%s", name);
	        delete(beginning, name);
	        break;

	        case 4:
	        inOrder(beginning);
	        break;

	        case 5:
	        writeList(beginning);
	        break;

	        case 6:
	        openList();
	        break;

	        case 7:
	        printf("name of the student you want to see the report:\n");
	        scanf("%s", name);
	        try=search(beginning, name);
	        if(try!=NULL){
	        	printf("student name is %s\n student number is %s\n student marks are:\n", try->name, try->sNumber);
		        for(i=0; i<10; i++){
		        	printf("%f  ", try->marks[i] );
		        }
	        }
		    else{
		    	printf("student not found\n");
		    }    
	        break;

	        case 12: 
	        printf("%s", beginning->name);
	        break;

	        case 9: 
	        printf("%d", beginning->height);
	        break;

	        case 10:
	        writeList2(beginning);
	        break;

	        case 11:
	        openList2();
	        break;
	    	}
		}
	}
}