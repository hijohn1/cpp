#include<iostream>
#include<fstream>
#include<string>
using namespace std;

int tswaps, tcomps, *array1, *array2, count1=0, count2=0;

template<class T>
class sortinglist
{
	private:
		T *slist;
		int n;
	public:
		void setuparray(T *tlist, int tn)
		{
			slist = new T [tn];
			n=tn;
			for(int i=0;i<n;i++)
			{
				slist[i]=tlist[i];
			}
		}

		void swap(int fvalue, int svalue)
		{
			T tvalue;
			tvalue=slist[fvalue];
			slist[fvalue]=slist[svalue];
			slist[svalue]=tvalue;
			tswaps++;
		}

		//selection sort
		int minvalues(int fvalue, int lvalue)
		{
			int m=fvalue;
			for(int i=fvalue+1;i<=lvalue;i++)
			{
				tcomps++;
				if(slist[m]>slist[i])
					m=i;
			}
			return m;
		}

		void ssarray()
		{
			int m;
			tswaps=0;
			tcomps=0;

			for(int i=0;i<(n-1);i++)
			{
				m=minvalues(i, n-1);
				swap(i,m);
			}

			cout<<endl<<"-------------------------------------------------"<<endl<<endl;
			cout<<"The sorted list: "<<endl<<endl;
			for(int i=0;i<n;i++)
				cout<<slist[i]<<" ";
			cout<<endl<<endl<<"The total swaps: "<<tswaps;
			cout<<endl<<endl<<"The total comparisons: "<<tcomps<<endl;
		}

		//Insertion sort
		void isarray()
		{
			int l,tvalue;
			tswaps=0;
			tcomps=0;

			for(int i=1;i<n;i++)
			{
				tcomps++;
				if(slist[i]<slist[i-1])
				{
					tvalue=slist[i];
					l=i;
					do
					{
						tswaps++;
						slist[i]=slist[i-1];
						i--;
					}while(i>0 && slist[i-1]>tvalue);
					slist[i]=tvalue;
				}
			}

			cout<<endl<<"-------------------------------------------------"<<endl<<endl;
			cout<<"The sorted list: "<<endl<<endl;
			for(int i=0;i<n;i++)
				cout<<slist[i]<<" ";
			cout<<endl<<endl<<"The total swaps: "<<tswaps;
			cout<<endl<<endl<<"The total comparisons: "<<tcomps<<endl;
		}

		//Heap sort
		void heapifyarray(int l, int h)
		{
			int lv, temp;
			
			temp=slist[l];
			lv=2*l+1;

			while(lv<=h)
			{
				tcomps++;
				if(lv<h)
					if(slist[lv]<slist[lv+1])
						lv=lv+1;
				if(temp>slist[lv])
					break;
				else
				{
					tswaps++;
					slist[l]=slist[lv];
					l=lv;
					lv=2*l+1;
				}
			}

			slist[l]=temp;
		}	

		void buildheap()
		{
			for(int i=n/2-1;i>=0;i--)
			{
				heapifyarray(i,n-1);
			}
		}

		void hsarray()
		{
			int temp;
			tswaps=0;
			tcomps=0;

			buildheap();

			for(int i=n-1;i>=0;i--)
			{
				tswaps++;
				temp=slist[i];
				slist[i]=slist[0];
				slist[0]=temp;
				heapifyarray(0,i-1);
			}

			cout<<endl<<"-------------------------------------------------"<<endl<<endl;
			cout<<"The sorted list: "<<endl<<endl;
			for(int i=0;i<n;i++)
				cout<<slist[i]<<" ";
			cout<<endl<<endl<<"The total swaps: "<<tswaps;
			cout<<endl<<endl<<"The total comparisons: "<<tcomps<<endl;
		}

		//mergesort
		void msarray(int f, int l)
		{
			if(f<l)
			{
				int m=(f+l)/2;
				msarray(f,m);
				msarray(m+1,l);
				merge(f,m,m+1,l);
			}
		}

		void merge(int lf, int ll, int rf, int rl)
		{
			T *temp;
			temp=new  T [n];
			int i=lf,s=lf;
		
			while( (lf<=ll) && (rf<=rl) )
			{
				tcomps++;
				if( slist[lf] < slist[rf] )
					temp[i++]=slist[lf++];
				else
					temp[i++]=slist[rf++];
			}

			while(lf<=ll)
				temp[i++]=slist[lf++];

			while(rf<=rl)
				temp[i++]=slist[rf++];

			for(i=s;i<=rl;i++)
			{
				tswaps++;
				slist[i]=temp[i];
			}
		}

		void msarrayoutput()
		{
			tswaps=0;
			tcomps=0;
			msarray(0,n-1);

			cout<<endl<<"-------------------------------------------------"<<endl<<endl;
			cout<<"The sorted list: "<<endl<<endl;
			for(int i=0;i<n;i++)
				cout<<slist[i]<<" ";
			cout<<endl<<endl<<"The total swaps: "<<tswaps;
			cout<<endl<<endl<<"The total comparisons: "<<tcomps<<endl;
		}

		//quicksort
		void qsarray(int f, int l)
		{
			int p;

			if(f<l)
			{
				p=partition(f,l);
				qsarray(f,p-1);
				qsarray(p+1,l);
			}
		}

		int partition(int f, int l)
		{
			int pi,i,s;

			swap(f,(f+l)/2);
			pi=slist[f];
			s=f;

			for(i=f+1;i<=l;i++)
			{
				tcomps++;
				if(slist[i]<pi)
				{
					s++;
					swap(s,i);
				}
			}

			swap(f,s);

			return s;
		}

		void qsarrayoutput()
		{
			tswaps=0;
			tcomps=0;
			qsarray(0,n-1);

			cout<<endl<<"-------------------------------------------------"<<endl<<endl;
			cout<<"The sorted list: "<<endl<<endl;
			for(int i=0;i<n;i++)
				cout<<slist[i]<<" ";
			cout<<endl<<endl<<"The total swaps: "<<tswaps;
			cout<<endl<<endl<<"The total comparisons: "<<tcomps<<endl;
		}
};

//set up two arrays for comparison
void arraysmenu();

int main()
{
	string choicesorting;
	int n;

	//The menu for users to set two arrays for comparing
	cout<<endl<<"**********Different sorting performance**********"<<endl<<endl;

	arraysmenu();
	sortinglist<int>a1;
	sortinglist<int>a2;

	//sorting two arrays which the users set up
	do
	{
		cout<<endl<<"-------------------------------------------------"<<endl<<endl;
		cout<<endl<<endl<<"A: Selection Sort."<<endl<<"B: Insertion Sort."<<endl<<"C: Heap Sort."<<endl<<"D: Merge Sort."
		    <<endl<<"E: Quick Sort."<<endl<<"F: Reset the arrays."<<endl<<"G: Exit the program."<<endl<<endl;
		cout<<"Please choose from the options above for sorting: ";
		cin>>choicesorting;

		// transferring users`input into intger (this is for avoiding users`mistaken input)
		if( choicesorting=="A" || choicesorting=="a" )
			n=1;
		else if( choicesorting=="B"|| choicesorting=="b" )
			n=2;
		else if( choicesorting=="C"|| choicesorting=="c" )
			n=3;
		else if( choicesorting=="D"|| choicesorting=="d" ) 
			n=4;
		else if( choicesorting=="E"|| choicesorting=="e" )
			n=5;
		else if( choicesorting=="F"|| choicesorting=="f" ) 
			n=6;
		else if( choicesorting=="G"|| choicesorting=="g" )
			n=7;
		else 
			n=8;

		switch(n)
		{
			case 1:
				a1.setuparray(array1,count1);
				a2.setuparray(array2,count2);
				a1.ssarray();
				a2.ssarray();
				break;
			case 2:
				a1.setuparray(array1,count1);
				a2.setuparray(array2,count2);
				a1.isarray();
				a2.isarray();
				break;
			case 3:
				a1.setuparray(array1,count1);
				a2.setuparray(array2,count2);
				a1.hsarray();
				a2.hsarray();
				break;
			case 4:
				a1.setuparray(array1,count1);
				a2.setuparray(array2,count2);
				a1.msarrayoutput();
				a2.msarrayoutput();
				break;
			case 5:
				a1.setuparray(array1,count1);
				a2.setuparray(array2,count2);
				a1.qsarrayoutput();
				a2.qsarrayoutput();
				break;
			case 6:
				delete [] array1;
				count1=0;
				delete [] array2;
				count2=0; 
				arraysmenu();
				break;
			case 7:
				cout<<endl<<"-------------------------------------------------"<<endl<<endl;
				cout<<endl<<endl<<"Exit suscessfully."<<endl<<endl;
				break;
			default:
				cout<<endl<<"-------------------------------------------------"<<endl<<endl;
				cout<<endl<<"Invalid input."<<endl<<endl;
		}
	}while(n!=7);
	cout<<endl<<"*************************************************"<<endl<<endl;

	return 0;
}

//set up two arrays for comparison
void arraysmenu()
{
	int num, n=-1;
	bool c;
	string f1, f2, a;
	fstream inputf1, inputf2;

	//set up the first array
	cout<<endl<<"-------------------------------------------------"<<endl<<endl;
	cout<<endl<<"Please choose the arrays type you want to sort: "<<endl;
	cout<<endl<<"Arrays 1:"
	    <<endl<<"A) Completely random arrays."
	    <<endl<<"B) Almost sorted in ascending order. (90% are in orders, 10% are random)"
	    <<endl<<"C) Sorted in opposing order. (descending)"<<endl<<endl; 
	do{
		cout<<"Array 1: ";
		cin>>a;
		if(a=="A" || a=="a")
		{
			f1="f/randomnumbers1.txt";
			c=true;
		}
		else if(a=="B" || a=="b")
		{
			f1="f/alsort1.txt";
			c=true;
		}
		else if(a=="C" || a=="c")
		{
			f1="f/oporder1.txt";
			c=true;
		}
		else
		{			
			cout<<endl<<"Invalid input."<<endl<<endl;
			c=false;
		}
	}while(c==false);

	//input array1 from the file
	inputf1.open(f1,ios::in);
	while(inputf1>>num)
	{
		count1++;
	}
	array1=new int[count1];
	inputf1.close();
	inputf1.open(f1, ios::in);
	while(inputf1>>num)
	{
		n++;
		array1[n]=num;
	}
	inputf1.close();
	n=-1;

	//set up the second array
	cout<<endl<<"-------------------------------------------------"<<endl<<endl;
	cout<<endl<<endl<<"Arrays 2:"
	    <<endl<<"A) Completely random arrays."
	    <<endl<<"B) Almost sorted in ascending order. (90% are in orders, 10% are random)"
	    <<endl<<"C) Sorted in opposing order. (descending)"<<endl<<endl; 
	do{
		cout<<"Array 2: ";
		cin>>a;
		if(a=="A" || a=="a")
		{
			f2="f/randomnumbers2.txt";
			c=true;
		}
		else if(a=="B" || a=="b")
		{
			f2="f/alsort2.txt";
			c=true;
		}
		else if(a=="C" || a=="c")
		{
			f2="f/oporder2.txt";
			c=true;
		}
		else
		{			
			cout<<endl<<"Invalid input."<<endl<<endl;
			c=false;
		}
	}while(c==false); 

	//input array2 from the file
	inputf2.open(f2,ios::in);
	while(inputf2>>num)
	{
		count2++;
	}
	array2=new int[count2];
	inputf2.close();
	inputf2.open(f2, ios::in);
	while(inputf2>>num)
	{
		n++;
		array2[n]=num;
	}
	inputf2.close();
}
