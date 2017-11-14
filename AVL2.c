#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
void insertInList(const struct student *node, FILE *list);
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
        printf("new student greater than node");
        //if the values is greater than the node and right of node is free set the right of the node as newstudent if not run in recursive the function with node equal node right 
        if (node->right == NULL ) {
            printf("free right node");
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
        printf("new student smaller than node");
        //if the values is glower than the node and right of node is free set the right of the node as newstudent if not run in recursive the function with node equal node right 
        if (node->left == NULL ) {
            printf("free left node");
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
    printf("\n enterd in Height\n");
    //Case 1: node has a parent
    if(node->parent){
        printf("\n has a parent \n");
        //Case 1.1: change the height of the node parent if the node has the same or bigger height
        //Check if there are the condition for reshaping
        if(node->parent->height <= node->height){ 
            if(node->left){
                if(node->left->height == node->height-3){
                    node=turnLeft(node);
                    return node;
                }
            }
            if(node->left == NULL && node->height == 3){
                node=turnLeft(node);
                return node;
            }
            if(node->right){
                if(node->right->height == node->height-3){
                    node=turnRight(node);
                    return node;
                }
            }
            if(node->right==NULL && node->height==3){
                node=turnRight(node);
                return node;
            }
            node->parent->height=node->height+1;
            return Height(node->parent);
        }
        else{
            return node;
        }
    }
    //Case 2: node is beginning
    else{
    	//Case 2.1: check the condition for reshaping
        printf("\n node is beginning \n");
        if(node->left){
            if(node->left->height == node->height-3){
            node=turnLeft(node);
            return node;
            }
        }
        if(node->left == NULL && node->height == 3){
            node=turnLeft(node);
            return node;
        }
        if(node->right){
            if(node->right->height == node->height-3){
            node=turnRight(node);
            return node;
            }
        }
        if(node->right==NULL && node->height==3){
            node=turnRight(node);
            return node;
        }
        return node;
    }
}

//Choose what type of reshape on the left the tree has to do
struct student * turnLeft(struct student *node){
    printf("enterd in turnLeft\n");
    printf("%s\n",node->name );
    if(node->right->right==NULL){
        printf("debug4\n");
        node=doubleTurnLeft(node);
        return node;
    }
    if(node->right->left){
        printf("exist node->right->left\n");
        if(node->right->left->height > node->right->right->height){
            printf("debug1\n");
            node=doubleTurnLeft(node);
            return node;
        }
        if(node->right->right==NULL){
            printf("debug2\n");
            node=doubleTurnLeft(node);
            return node;
        }
        else{
            printf("debug3\n");
            node=singleTurnLeft(node);
            return node;
        }
    }

    else{
        node=singleTurnLeft(node);
        return node;
    }
}

//New subRoot is node->right->right
struct student * singleTurnLeft(struct student *node){
    printf("enterd in singleTurnLeft\n");
    node->height=node->height-2;
    if(node->parent){
    	printf("node->parent\n");
        struct student *Parent= node->parent;
        if(Parent->right==node){
        	printf("node is right child\n");
        	Parent->right=NULL;
	        struct student *new=linearReshapeLeft(node);
	        new->parent=Parent;
	        Parent->right=new;
	        return new;
	    }
	    else{
	    	printf("node is left child\n");
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
    printf("enterd in linearReshapeLeft\n");
    node->parent=NULL;
    struct student *subRoot =node->right;
    if(subRoot->left){
    	printf("subRoot->left\n");
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
    printf("enterd in doubleTurnLeft\n");
    node->right->left->height=node->right->height;
    node->right->height=node->right->height-1;
    if(node->left){
    	printf("node->left\n");
    	node->height=node->left->height+1;
    }
    else{
    	printf("not node->left\n");
    	node->height=node->height-2;
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
    	printf("subRoot->left\n");
        tmp1=subRoot->left;
        tmp1->parent=node;
        node->right=tmp1;
    }
    if(subRoot->right){
    	printf("subRoot->right\n");
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
    printf("enterd in turnright\n");
    printf("%s\n",node->name );
    if(node->left->left==NULL){
        printf("debug4\n");
        node=doubleTurnRight(node);
        return node;
    }
    if(node->left->right){
        printf("exist node->left->right\n");
        if(node->left->right->height > node->left->left->height){
            printf("debug1\n");
            node=doubleTurnRight(node);
            return node;
        }
        if(node->left->left==NULL){
            printf("debug2\n");
            node=doubleTurnRight(node);
            return node;
        }
        else{
            printf("debug3\n");
            node=singleTurnRight(node);
            return node;
        }
    }

    else{
    	printf("debug5\n");
        node=singleTurnRight(node);
        return node;
    }
}

//node->left->left->height is bigger than node->left->right->height so node left is the new subRoot
struct student *singleTurnRight(struct student *node){
    printf("enterd in singleTurnright\n");
    node->height=node->height-2;
    if(node->parent){
        struct student *Parent= node->parent;
        if(Parent->right==node){
        	printf("node is right child\n");
        	Parent->right=NULL;
	        struct student *new=linearReshapeRight(node);
	        new->parent=Parent;
	        Parent->right=new;
	        return new;
	    }
	    else{
	    	printf("node is left child\n");
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
    printf("enterd in linearReshaperight\n");
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
    printf("enterd in doubleTurnright\n");
    node->left->right->height=node->left->height;
    node->left->height=node->left->height-1;
    if(node->right){
        node->height=node->right->height+1;
        printf("case1\n");
    }
    else{
        node->height=node->height-2;
        printf("case2\n");
    }
    if(node->parent){
    	printf("has a parent\n");
        struct student *Parent= node->parent;
        if(Parent->right==node){
        	printf("node is right child\n");
        	Parent->right=NULL;
	        struct student *new=notLinearReshapeRight(node);
	        new->parent=Parent;
	        Parent->right=new;
	        return new;
	    }
	    else{
	    	printf("node is left child\n");
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
    	printf("subRoot->right\n");
        tmp1=subRoot->right;
        tmp1->parent=node;
        node->left=tmp1;
    }
    if(subRoot->left){
    	printf("subRoot->left\n");
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
	printf("searching \n");
	//if smaller rerun the function for node->left
	if (node == NULL) {
        printf("Not found.\n");
        return NULL;
    }
    if (strcmp(name, node->name) < 0) {
      printf("name smaller than node name - ");
      return search(node->left, name);
  }
	//if bigger rerun the function for node->right
  if (strcmp(name, node->name) > 0) {
      printf("name bigger than node name - ");
      return search(node->right, name);
  }
	//if equal return node
  if (strcmp(name, node->name) == 0) {
	//else{
      printf("name equal node name");
      return node;
  }
}

//add mark to a student
void add_mark(struct student *node, char *name, int p, float mark) {
	name=name;
	//search for the student you have to change the vote 
	struct student *toAddMark = search(beginning, name);
	//change the vote
	toAddMark->marks[p-1] = mark;
	return;
}

//prepare and finish the process for deleting a student
void delete(struct student *toDelete, char *name){
	printf("enterd in delete\n");
    toDelete=search(beginning,name);
    struct student *tmp;
    struct student *tmpl=NULL;
    struct student *tmpr=NULL;
    if(toDelete->parent){
    	printf("has a parent\n");
        struct student *Parent= toDelete->parent;
        printf("Parent is %s\n",Parent->name );
        if(Parent->parent){
        	tmp=Parent->parent;
        	printf("tmp is %s\n",tmp->name );
        	if(tmp->left==Parent){
        		tmpl=tmp->left;
        	}
        	else{
        		tmpr=tmp->right;
        	}
        }
        if(Parent->left==toDelete){
        	Parent->left=NULL;
        	toDelete->parent=NULL;
        	struct student *new= Deleting(toDelete);
        	new->parent=Parent;
        	Parent->left=new;
        	printf("\n\n\n");
        	stabilizeHeight(new);
        	Height(new);
            if(tmpl != NULL){
            	tmp->left=Parent;
            	printf("tmp is %s and is left son is Parent %s\n", tmp->name, Parent->name );
            }
            if(tmpr != NULL){
            	tmp->right=Parent;
            	printf("tmp is %s and is left son is Parent %s\n", tmp->name, tmp->right->name );
            }
            return;
        }
        else{
        	printf("toDelete is right child\n");
            Parent->right=NULL;
            toDelete->parent=NULL;
            struct student *new = Deleting(toDelete);
            printf("%s\n",Parent->name );
            if(new!=NULL){
            	new->parent=Parent;
            }
            Parent->right=new;
            if(new!=NULL){
            	stabilizeHeight(new);
            	Height(new);
            }
            return;
        }
    }
    else{
    	printf("toDelete is root\n");
        struct student *new = Deleting(toDelete);
        beginning=new;
        return;
    }
}

//delete a student a stabilize its subtree
struct student *Deleting(struct student *toDelete){
	count--;
	printf("enterd in Deleting\n");
    if(toDelete->left){
        struct student *new=maxLeft(toDelete->left);
        printf("new is %s\n", new->name );
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
        		printf("new has left child\n");
	            struct student *tmp= new->left;
	            printf("new parent is %s\n",new->parent );
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
        		printf("new right is %s\n",new->right );
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
        		Height(new);
        		return new;
        	}
        }
    }
    if(toDelete->right){
    	printf("toDelete has no left child\n");
        struct student *new=toDelete->right;
        toDelete->right=NULL;
        new->parent=NULL;
        free(toDelete);
        return new; 
    }
    if(toDelete->left==NULL && toDelete->right==NULL){
    	printf("toDelete has no right or left sons\n");
        free(toDelete);
        printf("deleted\n");
        return NULL;
    }
}

//set the new value of height of the tree after deleting
void stabilizeHeight(struct student *node){
	printf("enterd in stabilizeHeight\n");
	printf("%s\n",node->name );
    if(node->parent){
    	printf("has a parent\n");
        if(node->parent->left){
        	printf("the parent has a left child\n");
            if(node->parent->left==node){
            	printf("node is left child\n");
                if(node->parent->right){
                	printf("parent has a right child\n");
                    if(node->parent->right->height < node->height){
                    	printf("node is bigger than parent right\n");
                        node->parent->height=node->height+1;
                        return stabilizeHeight(node->parent);
                    }
                    else{
                    	printf("node is smaller than parent right \n");
                        return;
                    }
                }
                else{
                	printf("node->parent has no right child\n");
                    node->parent->height=node->height+1;
                    return stabilizeHeight(node->parent);
                }
            }
            else{
            	printf("node is right child\n");
                if(node->parent->left->height < node->height){
                	printf("node is bigger than parent left\n");
                    node->parent->height=node->height+1;
                    return stabilizeHeight(node->parent);
                }
                else{
                	printf("node is smaller than parent left\n");
                    return;
                }
            }
        }
        else{
        	printf("node parent left = NULL\n");
            node->parent->height=node->height+1;
            return stabilizeHeight(node->parent);
        }
    }
    else{
    	printf("has no parent\n");
        return;
    }
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


//main function
int main(void) {
	int a, i, p;
	char name[20], sNumber[100];
	float marks[10];
	float mark;
	while (a != 7) {
		printf(
            "\n 1 for add a new student \n 2 for add a mark \n 3 to delete a student \n 4 to print the report of all the students \n 5 to save file \n 6 to open the file \n 7 exit the program \n 8 show the root\n 9 show root height \n 10 numberof nodes\n");
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

        case 8: printf("root is %s", beginning->name);
        break;

        case 9: 
        printf("root height is %d", beginning->height);
        break;

        case 10:
        printf("number of nodes %d\n", count);
    	}
	}
}

