#include "lib/Queue.h"

void Queue::enqueue (Chain* item)
{
    
    out.println("enqueue in Queue wird aufgerufen");
    
	item->next = 0; 
	*tail = item;    
	tail = &(item->next);
    
    if (tail == 0) {
        out.println("tail ist Null");   
    }
    
    if (head == 0) {
        out.println("head ist Null");   
    }
    
    for (int i = 0; i < 30000000; i++) {}
}


Chain* Queue::dequeue ()
{
	Chain* item;

	item = head;   
	if (item) {
		head = item->next; 
		if (!head)           
			tail = &head;      
		else              
			item->next = 0;  
	}
	
	out.println("dequeue in Queue wird aufgerufen");
    
    if (item == 0) {
        out.println("Rueckgabewert ist Null");
    }
    
    for (int i = 0; i < 30000000; i++) {}
    
	return item;
    
}


void Queue::remove (Chain* item)
{
	Chain* curr;

	if (head) {
		curr = head; 
		if (item == curr)
			dequeue ();    
		else {
			while (curr->next && item != curr->next) 
				curr = curr->next;  

			if (curr->next) {
				curr->next = item->next; 
				item->next = 0;      

				if (!curr->next)     
					tail = &(curr->next); 
			}
		}
	}
}

