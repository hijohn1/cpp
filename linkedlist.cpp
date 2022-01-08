#include<iostream>
#include<string>
using namespace std;

template <class T>               //declare the data structure
struct li
{
	li<T> *preVious;        //previous pointer
	T v;                    //store the data
	li<T> *neXt;            //next pointer
};

//set up an iterator class
template<class T>
class iteratorlinkedlist
{
	private:		
		li<T> *cur;
	public:
		iteratorlinkedlist()
		{
			cur=nullptr;
		}
		iteratorlinkedlist(li<T> *temp)
		{
			cur=temp;
		}
		iteratorlinkedlist operator ++()
		{
			cur=cur->neXt;
			return *this;
		}
		iteratorlinkedlist operator --()
		{
			cur=cur->preVious;
			return *this;
		}		
		T operator *()
		{
			return cur->v;
		}
		bool operator !=(iteratorlinkedlist<T> temp)
		{
			return cur!=temp.cur;
		}
		bool operator ==(iteratorlinkedlist<T> temp)
		{
			return cur==temp.cur;
		}
};

//set up linked list
template <class T>
class linkedlist
{
	private:
		li<T> *fi;       // set up a pointer for pointing to data
		li<T> *la;
	public:
		//default constructor
		linkedlist()
		{
			fi=nullptr;    
			la=nullptr;
		}

		//destructor
		~linkedlist()
		{
			li<T> *t;

			while(fi)
			{
				t=fi->neXt;
				delete fi;
				fi=t;
			}
			delete fi;
		}

		//copy a pointer
		linkedlist(const linkedlist<T> &right)
		{
			li<T> *t;
			li<T> *tr;

			t=fi;
			tr=right.fi;
			while(tr)
			{
				t->preVious=tr->preVious;
				t->v=tr->v;
				t->neXt=tr->neXt;
				t=fi->neXt;
				tr=right.fi->neXt;
			}
			la=tr.la;
		}

		//operator= overloading
		linkedlist operator=(const linkedlist<T> &right)
		{
			if(fi!=right)
			{
				li<T> *t;
				li<T> *tr;

				t=fi;
				tr=right.fi;
				while(tr)
				{
					t->preVious=tr->preVious;
					t->v=tr->v;
					t->neXt=tr->neXt;
					t=fi->neXt;
					tr=right.fi->neXt;
				}
				la=tr.la;
			}
			return *this;
		}

		//insert a pointer
		void initem(T num)                
		{
			li<T> *traItem;         //set up a pointer to traverse the list
			li<T> *newItem;         //set up a pointer to hold new data

			newItem=new li<T>;      //allocate memory to the pointer
			newItem->v=num;        //set up the pointer to hold input number
			newItem->neXt=nullptr;  
			newItem->preVious=nullptr;  //set up the nodes in the new pointer as an empty

			if(!fi)                 //if the list is empty,let the new data be inserted into the first pointer
			{
				fi=newItem;
				la=newItem;
			}
			else  //if the list isn`t empty, the program will search the last node and then insert
			{
				traItem=fi;
				while(traItem->neXt)
				{
					traItem=traItem->neXt;
				}
				traItem->neXt=newItem;
				newItem->preVious=traItem;
				la=newItem;
			}
			cout<<endl<<"The number has been inserted!"<<endl<<endl;
		}

		//print the list from the front to end
		void pritem() 
		{
			li<T> *priItem=new li<T>;

			if(!fi)
			{
				cout<<endl<<"This is an empty list."<<endl<<endl;
			}
			else
			{
				priItem=fi;
				cout<<endl<<"The elements: ";
				while(priItem!=nullptr)
				{
					cout<<priItem->v<<" ";
					priItem=priItem->neXt;
				}
				cout<<endl<<endl;
			}
		}

		// search the number, then delete the node
		void delitem()
		{
			li<T> *hoItem=nullptr;
			li<T> *traItem=nullptr;

			if(!fi)
			{
				cout<<endl<<"The list is empty."<<endl<<endl;
				return;
			}
			else
			{
				double num;
				cout<<endl<<"Please input a number: ";
				cin>>num;
				cout<<endl<<endl;
				if(fi->v==num)
				{
					hoItem=fi->neXt;
					delete fi;
					fi=hoItem;
					hoItem->preVious=NULL;
					cout<<endl<<"The element has been deleted."<<endl<<endl;
				}
				else
				{
					hoItem=fi;
					while(hoItem!=nullptr && hoItem->v!=num)
					{
						traItem=hoItem;
						hoItem=hoItem->neXt;
					}
					if(hoItem)
					{
						if(hoItem->neXt)
						{
							traItem->neXt=hoItem->neXt;
							traItem->neXt->preVious=traItem;
						}
						else
						{
							la=traItem;
							traItem->neXt=nullptr;

						}
						delete hoItem;
						cout<<endl<<"The element has been deleted."<<endl<<endl;
					}
					else
					{
						cout<<endl<<"The element doesn`t exit."<<endl<<endl;
					}
				}
			}
		}

		//return a bool value to determine if the number is in the list
		bool seitem(T num)
		{
			li<T> *hoItem=nullptr;
			bool result=false;

			if(!fi)
			{
				result=false;
			}
			else if(fi->v==num)
			{
				result=true;
			}
			else
			{
				hoItem=fi;
				while(hoItem!=nullptr)
				{
					if(hoItem->v==num)
					{
						result=true;
					}
					hoItem=hoItem->neXt;
				}
				if(hoItem==nullptr && result==false)
					result=false;
			}
			return result;
		}

		//empty the list
		void emlist()
		{
			fi=NULL;
			la=NULL;
			cout<<endl<<"The list is empty now."<<endl<<endl;
		}

		//judege if the list is empty
		void isemlist()
		{
			if(fi==nullptr)
			{
				cout<<endl<<"It is an empty list."<<endl<<endl;
			}
			else
			{
				cout<<endl<<"It isn`t an empty list."<<endl<<endl;
			}
		}

		//checek the length of the list
		void lelist()
		{
			li<T> *llist1;
			li<T> *llist2;
			int count=0;

			if(!fi)
			{
				cout<<endl<<"The length is 0"<<endl<<endl;
			}
			else
			{
				llist1=fi;
				while(llist1!=nullptr)
				{
					llist2=llist1;
					llist1=llist1->neXt;
					count++;
				}
				cout<<endl<<"The length is "<<count<<endl<<endl;
			}
		}

		//insert a number in the front of the list
		void insertlinkedlistf (T num)
		{
			li<T> *newNode;
			li<T> *traItem=nullptr;

			newNode=new li<T>;
			newNode->v=num;
			newNode->neXt=nullptr;
			newNode->preVious=nullptr;

			if(!fi)
			{
				fi=newNode;
				la=newNode;
			}
			else
			{
				newNode->neXt=fi;
				fi=newNode;
				traItem=la;
				while(traItem->preVious)
				{
					traItem=traItem->preVious;
				}
				traItem->preVious=newNode;
			}
			cout<<endl<<"The number has been inserted."<<endl<<endl;
		} 

		//insert a number in the back of the  list
		void insertlinkedlistb (T num)
		{
			li<T> *newNode;
			li<T> *traNode=nullptr;

			newNode=new li<T>;
			newNode->v=num;
			newNode->neXt=nullptr;
			newNode->preVious=nullptr;


			if(!la)
			{
				fi=newNode;
				la=newNode;
			}
			else
			{
				traNode=fi;
				while(traNode->neXt)
				{
					traNode=traNode->neXt;
				}
				traNode->neXt=newNode;
				newNode->preVious=traNode;
				la=newNode;
			}
			cout<<endl<<"The number has been inserted."<<endl<<endl;
		}

		//this function is for iterator. it is used to return the firt node data
		iteratorlinkedlist<T> begin()
		{
			iteratorlinkedlist<T> it(fi);
			return it;
		}

		//this function is for iterator. it is used to return the last node data
		iteratorlinkedlist<T> end()
		{
			iteratorlinkedlist<T> it(la);
			return it;
		}
};

int main()
{
	string c; //set up a variable for user to choose options
	char chOice;    //set up a char variable for changing c to chOice
	double num;     // set up a varialbe for user to input number
	linkedlist <double> a;     //set up a double linked list

	//set up a menu with do-loop,so user continue to choose options .
	cout<<endl<<"*********The list is empty, please input numbers first!*********"<<endl;

	do
	{
		//main menu
		cout<<endl<<"A: Insert a numbers."<<endl<<"B: Print the numbers."
	            <<endl<<"C: Delete a number."<<endl<<"D: Search a number."
	            <<endl<<"E: Empty the list."<<endl<<"F: Checek if the list is empty."
		    <<endl<<"G: Check the length of the list."<<endl<<"H: Insert a number at the front."
		    <<endl<<"I: Insert a number at the back."<<endl<<"J: Iterate from the front to the end"
	            <<endl<<"K: Iterate from the end to the front"<<endl<<"L: Exit"<<endl;	    
		cout<<endl<<"Please select from the above options: ";
		cin>>c;           // ask user to choose the options
		
		//the program jude the user`s choice
		if(c=="A"||c=="a")
			chOice='a';
		else if(c=="B"||c=="b")
			chOice='b';
		else if(c=="C"||c=="c")
			chOice='c';
		else if(c=="D"||c=="d")
			chOice='d';
		else if(c=="E"||c=="e")
			chOice='e';
		else if(c=="F"||c=="f")
			chOice='f';
		else if(c=="G"||c=="g")
			chOice='g';
		else if(c=="H"||c=="h")
			chOice='h';
		else if(c=="I"||c=="i")
			chOice='i';
		else if(c=="J"||c=="j")
			chOice='j';
		else if(c=="K"||c=="k")
			chOice='k';
		else if(c=="L"||c=="l")
			chOice='l';
		else
			chOice='m';

		switch (chOice)
		{
			case 'a':
				cout<<endl<<"Please input a number: ";
				cin>>num;
				a.initem(num);
				break;

			case 'b':
				a.pritem();
				break;

			case 'c':
				a.delitem();
				break;

			case 'd':
				cout<<endl<<"Please input a numer: ";
				cin>>num;
				if(a.seitem(num))
				{
					cout<<endl<<"The number is in the list."<<endl<<endl;
				}
				else
				{
					cout<<endl<<"The number isn`t in the list."<<endl<<endl;
				}
				break;

			case 'e':
				a.emlist();
				break;

			case 'f':
				a.isemlist();
				break;

			case 'g':
				a.lelist();
				break;

			case 'h':
				cout<<endl<<"Please input a number: ";
				cin>>num;
				a.insertlinkedlistf(num);
				break;					 

			case 'i':
				cout<<endl<<"Please input a number: ";
				cin>>num;
				a.insertlinkedlistb(num);
				break;

			case 'j':
				if(a.begin()==NULL || a.end()==NULL)
				{
					cout<<endl<<"This is an empty list.";
				}
				else
				{
					cout<<endl;
					cout<<"The elements: ";
					for(auto i=a.begin();i!=NULL;++i)
					{
						cout<<*i<<" ";
					}
				}
				cout<<endl<<endl;
				break;

			case 'k':
				if(a.begin()==NULL || a.end()==NULL)
				{
					cout<<endl<<"This is an empty list.";
				}
				else
				{
					cout<<endl;
					cout<<"The elements: ";
					for(auto i=a.end();i!=NULL;--i)
					{
						cout<<*i<<" ";
					}
				}
				cout<<endl<<endl;
				break;

			case 'l':
				cout<<endl<<"The program has exited."<<endl<<endl;
				break;

			default:
				cout<<endl<<"Invalid input"<<endl<<endl;
		}
		cout<<endl<<"****************************************************************"<<endl<<endl;
	}while(chOice!='l');

	return 0;
}
