#include<iostream>
using namespace std;

struct llist
{
	int num;
	llist *next;
};

class insertionsort
{
	private:
	       	llist *list = nullptr;
	public:
		insertionsort(int a[])  // inserting array into the singly linked list
		{
			llist *temp = nullptr, *newNode = nullptr;

			for(int i=0;i<4;i++)
			{
				newNode = new llist;
				newNode->num = a[i];
				newNode->next = nullptr;

				if(!list)
				{
					list = newNode;
				}
				else
				{
					temp = list;
					while(temp->next)
					{
						temp = temp->next;
					}
					temp->next = newNode;
				}
			}
			cout<<endl<<"Before the sorting in the singly linked list: ";
			printlist();
			sort();
		}

		void sort()  //insertion sort
		{
			llist *tra, *cur, *lo, *fuo;  // tra: traverse in th list, cur: current pointer, lo: the last order pointer
			                              // fuo: first unorder pointer
			lo = list;
			while(lo->next != NULL)
			{
				fuo = lo->next;
				if(list->num > fuo->num)
				{
					lo->next = fuo->next;
					fuo->next = list;
					list = fuo;
				}
				else
				{
					tra = list;
					cur = list->next;
					while(fuo->num > cur->num)
					{
						tra = cur;
						cur = cur->next;
					}

					if(cur != fuo)
					{
						lo->next = fuo->next;
						fuo->next = cur;
						tra->next = fuo;
					}
					else
						lo = lo->next;
				}

			}
		
			cout<<endl<<"After the sorting in the singly linked list: ";
			printlist();

		}
		
		void printlist()  //output the list
		{
			llist *temp;
			temp = list;
			cout<<temp->num<<" ";
			while(temp->next != NULL)
			{
				temp = temp->next;
				cout<<temp->num<<" ";
			}	
			cout<<endl<<endl;
		}
};

int main()
{
	int a[4] = {1,3,2,4};
	insertionsort b(a);
}


