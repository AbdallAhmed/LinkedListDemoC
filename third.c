#include <stdio.h>
#include <stdlib.h>
#include "third.h"

//prints out the linked list with tab separation
void print_list(node_t * head) {
    node_t * current = head;
    
    if(current == NULL)
    {
        printf("\n");
    }
    else 
    {
        while (current != NULL) {
        printf("%d\t", current->val);
        current = current->next;
        }
        printf("\n");
    }
}

//method to push a new value onto the linked list
void push(node_t ** head, int v)
{
    //if there is nothing at the head, create a head
    if( *head == NULL)
    {
        *head = (node_t*)malloc(sizeof(node_t));
        (*head)->val = v;
        (*head)->next = NULL;
        
    }

    else {
        
        node_t * check = *head;
        
        //insures that duplicates are not inserted
        while (check != NULL) {
            if(check->val == v)
                return;
            check = check->next;
        }

        //want to insert in increasing order so if the value is less than the value of the head
        //insert as the new head
        if(v < (*head)->val)
        {
            node_t* new_node;
            new_node = malloc(sizeof(node_t));
            new_node->val = v;
            new_node->next = *head;
            *head = new_node;
        }
        
        else {
            node_t* prev = NULL;
            node_t* curr = *head;
            
            //if there is only a head node and the new value is not less than that of the head
            //insert after the head node
            if(curr->next == NULL)
            {
                node_t* new_node;
                new_node = malloc(sizeof(node_t));
                new_node->val = v;
                new_node->next = NULL;
                (*head)->next = new_node;
            }
            
            else
            {
                while(curr->next != NULL)
                {
                    //walks through the list with two pointers and is able to relink the list
                    if(v < curr->val)
                    {
                        node_t* hold = curr;
                        node_t* ins;
                        ins = malloc(sizeof(node_t));
                        ins->val = v;
                        ins->next = hold;
                        prev->next = ins;
                        break;
                    }
                    prev = curr;
                    curr = curr->next;
                }
                
                //if we made it through the above loop we are now on the last node of our list
                //if the value of what we are inserting is less that of the last node then 
                //we must relink the list and keep the tail the same
                //if value is greater (aka greatest of our list) we have a new tail value
                if(curr->next == NULL)
                {
                    //case that it is smaller than our tail
                    if(v < curr->val)
                    {
                        node_t* new_node;
                        new_node = malloc(sizeof(node_t));
                        new_node->val = v;
                        new_node->next = curr;
                        prev->next = new_node;
                        curr->next = NULL;
                    }

                    //case that it is bigger than our tail 
                    else{
                        node_t* new_node;
                        new_node = malloc(sizeof(node_t));
                        new_node->val = v;
                        new_node->next = NULL;
                        curr->next = new_node;
                    }
                }
                
            }
        }
    }
    
}

//method to delete nodes from the list
void del(node_t ** head, int v)
{
    if( *head == NULL)
    {
        return; 
    }

    else {
        
        //check to see if the number you want to delete is in the list
        node_t * check = *head;
        int isThere = 0;
        while (check != NULL) {
            if(check->val == v)
                isThere = 1;
            check = check->next;
        }

        //if not in the list silently exit the deletion method
        if(isThere == 0)
            return;

        //case of deleting the head. if there is more than one node in the list then need to create
        //a new head node. Otherwise make a null list.
        if((*head)->val == v)
        {
            //case that it is only the head
            if((*head)->next == NULL)
            {
                (*head) = NULL;
            }

            //case that ther are other nodes
            else
            {
                *head = (*head)->next;
            }

            return;
        }

        node_t* prev = NULL;
        node_t* curr = *head;

        //deletes a node in the middle fo the list. relinks as needed
        //makes sure to free that data of the node we are unlinking
        while(curr->next != NULL)
        {
            if(v == curr->val)
            {
                prev->next = curr->next;
                free(curr);
                break;
             }
                prev = curr;
                curr = curr->next;
        }

        //deletes a node at the end of the list. 
        if(curr->next == NULL)
        {
            if(curr->val == v)
            {
                prev->next = NULL;
                free(curr);
            }
        }
                
    }
}

int main(int argc, char* argv[])
{
    FILE * fpointer;
    node_t * head = NULL;
    
    //program needs to take at least the file name as input
    if(argc == 1)
    {
     printf("error\n");
     exit(1);
     }
    
    //checks to see if the file that was requested exists
    if((fpointer = fopen(argv[argc-1],"r")) == NULL)
     {
     printf("error\n");
     exit(1);
     }
     
     char action;
     int check = 0;
     int num = 0;
     
     //goes through the file until it hits the end
     while(!feof(fpointer))
     {
     	fscanf(fpointer, "%c %d \n", &action, &num);
     	
        //insertion method
	    if(action == 'i')
	    {
	    	push(&head,num);
	    }

        //method for deletion
        else if(action == 'd')
        {
            del(&head, num);
        }

        //program guidelines were to break if an improper input was received
        else
        {
            printf("error\n");
            check = 1;
            break;
        }
     }

     //prints the list as long as there was no bad input
     if(check == 0)
        print_list(head);


     fclose(fpointer);

     //properly frees the linked list
     node_t * tmp = head->next;
     if((head)->next == NULL)
        free((head));
    else
    {
        while(tmp != NULL)
        {
            free(head);
            tmp = tmp->next;
            head = tmp;
        }
    }
     return 0;
}
