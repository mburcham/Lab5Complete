#include "ListLinked.h"


template <typename DataType>
List<DataType>::List(int ignored)  {
    head = NULL;     
    cursor = NULL;                       
}


template <typename DataType>
List<DataType>::List(const List& other)  {
    ListNode* copy = other.head;
    
    while (copy != NULL)  {
       this->dataItem = copy->dataItem;
       this->next = copy->next;
       gotoNext();
       copy = copy->next;
    }
    *this = other;                        
}


template <typename DataType>
List<DataType>& List<DataType>::operator=(const List& other)  {
    ListNode* copy = other.head;
    while (copy != NULL)  {
          insert(copy->dataItem);
          gotoNext();
          copy = copy->next;
    }
    return *this;
}

template <typename DataType>
List<DataType>::~List()  {
    ListNode* trash;
    ListNode* step = head;
    while (step != NULL)  {
          trash = step;
          step = step->next;
          delete trash;
    }
    head = NULL;
}

template <typename DataType>			//fixed problem with adding between nodes
void List<DataType>::insert(const DataType& newDataItem) throw (logic_error)  {
     if (!isEmpty())  {
        ListNode* tempNode = cursor;
        cursor = new ListNode(newDataItem, tempNode->next);
        tempNode->next = cursor;
     }
     else if (isEmpty())  {
          head = new ListNode(newDataItem, 0);
          cursor = head;
          
     }
}

//Needs work.  Only works if attempting to remove from empty list or if removing head item.
//Problems if remove from list past head position.
template <typename DataType>
void List<DataType>::remove() throw (logic_error)  {
     ListNode* lostNode;
     if (isEmpty())  {
        cout << "Cannot remove from empty list." << endl;
     }
     else if (cursor == head)  {
        lostNode = head;
        head = head->next;
        gotoNext();
        delete lostNode;
     }
     else  {
           ListNode* previous;
           lostNode = cursor;
		   previous = head;
           while( previous->next != cursor )  {
               previous = previous->next;
           }
		   if(cursor->next != NULL)
				cursor = cursor->next;
		   else
				cursor = head;
		   previous->next = lostNode->next;
           delete lostNode;
           lostNode = NULL;
     }
}

template <typename DataType>
void List<DataType>::replace(const DataType& newDataItem) throw (logic_error)  {
     if(head != NULL)
		cursor->dataItem = newDataItem;
}

//Dangling memory?
template <typename DataType>
void List<DataType>::clear()  {
   if (isEmpty())  {
      cout << "List is already empty!" << endl;
   }
   else  {
	  cursor = head;
	  ListNode *lostNode;
	  while(cursor != NULL){
		lostNode = head;
        head = head->next;
        cursor = cursor->next;
        delete lostNode;
	  }
      head = NULL;
      cursor = NULL;
   }
}

template <typename DataType>
bool List<DataType>::isEmpty() const  {
    if (head == NULL && cursor == NULL)  {
       return true;
    }
    else  {
       return false;
    }
}

//Assume list will never be full.
template <typename DataType>
bool List<DataType>::isFull() const  {
     return false;
}


template <typename DataType>
void List<DataType>::gotoBeginning() throw (logic_error)  {
     cursor = head;
}


template <typename DataType>
void List<DataType>::gotoEnd() throw (logic_error)  {
	while(cursor->next != NULL){
		cursor = cursor->next;
	}
}

template <typename DataType>
bool List<DataType>::gotoNext() throw (logic_error)  {
     if (cursor->next != NULL) {
         cursor = cursor->next;
		 return true;
     }
     else  {
         return false;
     }
}

template <typename DataType>
bool List<DataType>::gotoPrior() throw (logic_error)  {
	if(cursor != head && head != NULL){
    	ListNode *findPrior = head;
		while(findPrior->next != cursor)
			findPrior = findPrior->next;
		cursor = findPrior;
		return true;
	}
	else
		return false;
}

template <typename DataType>
DataType List<DataType>::getCursor() const throw (logic_error)  {
   if (!isEmpty())  {
         return cursor->dataItem;
   }
   else{
		ListNode* logic_error;
		throw logic_error;
   }   
}

    // Programming exercise 2
template <typename DataType>
void List<DataType>::moveToBeginning () throw (logic_error)  {
	if (cursor != head && head != NULL)  {
		ListNode* findPrior = head;
		while(findPrior->next != cursor)  {
			findPrior = findPrior->next;
		}
		findPrior->next = cursor->next;
		cursor->next = head;
		head = cursor;
	}
}

    // Programming exercise 3
template <typename DataType>
void List<DataType>::insertBefore(const DataType& newDataItem) throw (logic_error)  {
    if (isEmpty())  {
		 head = new ListNode(newDataItem, 0);
         cursor = head; 
	}
	else  {
		 if (cursor == head)  {
			ListNode *node = new ListNode(newDataItem, head);
			head = node;
			cursor = node;	
		 }
		 else  {
		 	gotoPrior();
		 	insert(newDataItem);
		}
	} 
}
  
template <typename DataType>
void List<DataType>::showStructure() const  {
     // Outputs the items in a list. If the list is empty, outputs
// "Empty list". This operation is intended for testing and
// debugging purposes only.
    if ( isEmpty() )
    {
       cout << "Empty list" << endl;
    } 
    else
    {
	for (ListNode* temp = head; temp != 0; temp = temp->next) {
	    if (temp == cursor) {
		cout << "[";
	    }

	    // Assumes that dataItem can be printed via << because
	    // is is either primitive or operator<< is overloaded.
	    cout << temp->dataItem;	

	    if (temp == cursor) {
		cout << "]";
	    }
	    cout << " ";
	}
	cout << endl;
    }
}

template <typename DataType>
List<DataType>::ListNode::ListNode(const DataType& nodeData, ListNode* nextPtr)  {
    dataItem = nodeData;
    next = nextPtr;                                        
}
