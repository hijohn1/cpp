#include<iostream>
#include<fstream>
#include<string>
#include<cctype>
#include<vector>
using namespace std;

int tnw;  //storing how many times a word is used

template<class T>
struct btn
{
	T iword;
	int n;
	btn<T> *l;
	btn<T> *r;
};

template<class T>
class analyzereport
{
	private:
		btn<T> *hn;
	public:
		analyzereport()
		{
			hn=nullptr;
		}
		
		~analyzereport()
		{
			destoryhn(hn);
		}

		void destoryhn(btn<T> *&t)
		{
			if(t)
			{
				destoryhn(t->l);
				destoryhn(t->r);
				delete t;
			}
		}

		//insert data into tree
		void inserthn(const T a)
		{
			btn<T> *newnode;  //set up a new node
			btn<T> *curnode;  // set up a node for pointing current pointer
			btn<T> *tranode;  // a node for traversing the tree

			newnode = new btn<T>;
			newnode->iword=a;
			newnode->n=1;
			newnode->l=nullptr;
			newnode->r=nullptr;

			if(!hn)
				hn=newnode;
			else
			{
				curnode=hn;

				while(curnode)
				{
					tranode=curnode;
				
					if(curnode->iword>a)
						curnode=curnode->l;
					else if(curnode->iword<a)
						curnode=curnode->r;
					else
					{
						curnode->n++;
						return;
					}
				}

				if(tranode->iword>a)
					tranode->l=newnode;
				else
					tranode->r=newnode;
			}
		}

		//Search the tree
		bool searchhn(const T a)
		{
			btn<T> *curnode;
			bool r=false;

			if(hn)
			{
				curnode=hn;

				while(curnode && !r)
				{
					if(curnode->iword==a)
					{
						r=true;
						tnw=curnode->n;
						return r;
					}
					else if(curnode->iword>a)
						curnode=curnode->l;
					else
						curnode=curnode->r;
				}
			}

			return r;
		}

		//delete the iterm
		void deletehn(const T a)
		{
			btn<T> *curnode;
			btn<T> *tranode;
			bool r=false;

			if(hn)
			{
				curnode=hn;

				while(curnode && !r)
				{
					if(curnode->iword==a)
						r=true;
					else
					{
						tranode=curnode;
						if(curnode->iword>a)
							curnode=curnode->l;
						else
							curnode=curnode->r;
					}
				}

				if(r)
				{
					if(curnode==hn)
						deletehntree(hn);
					else if(tranode->iword>a)
						deletehntree(tranode->l);
					else
						deletehntree(tranode->r);
				}
			}
		}

		//delete iterm from the tree
		void deletehntree(btn<T> *&a)
		{
			btn<T> *curnode;
			btn<T> *tranode;
			btn<T> *temnode;

			if(!a)
				return;
		        else if(!a->l && !a->r)
			{
				temnode=a;
				a=NULL;
				delete temnode;
			}
			else if(!a->l)
			{
				temnode=a;
				a=temnode->r;
				delete temnode;
			}
			else if(!a->r)
			{
				temnode=a;
				a=temnode->l;
				delete temnode;
			}
			else
			{
				curnode=a->l;
				tranode=NULL;

				while(curnode->r)
				{
					tranode=curnode;
					curnode=curnode->r;
				}

				a->iword=curnode->iword;
				a->n=curnode->n;

				if(tranode==NULL)
					a->l=curnode->l;
				else
					tranode->r=curnode->l;
				delete curnode;
			}
		}
};

void oftenunqiuewords(vector<string>,fstream&); //print often used unqiue words
void indexunqiuewords(vector<string>,fstream&); //print index unqiue words

int main()
{
	//variables for total sentences,total words, averge words, averge sentences, total length of words, unqiue words,                     often used unique words, total used three words, 5% used words
	int tsentences=0, twords=0,awords=0, asentences=0, tlwords=0, uwords=0, ouwords=0, countthreeletters=0, f5threeletters=0;
	double o5words=0;  // calculation for 5% used words
	char *trfwords;  //transfer words from string data type to char data type
	string fname,rwords;
	vector<string> souwords, suwords;
	analyzereport<string> t;
	fstream rfile,ofile;

	cout<<endl<<"*******************************************************"<<endl<<endl
	    <<endl<<"Please input the file name (end with .txt): ";
	cin>>fname;
	cout<<endl<<endl;

	rfile.open(fname, ios::in);
	if(rfile.fail())
	{
		cout<<"Invalid file."<<endl<<endl;
	}
	else
	{
		// read words from the file and then store it in the tree
		// first time to read the file to extract words
		while(rfile>>rwords)
		{
			int tnumber=0, lwords=0;
			for(int i=0;i<rwords.length();i++)
			{
				if( isalpha(rwords[i]) )
				{					
					lwords++;
					tlwords++;
				}
				if( (rwords[i]=='.' || rwords[i]=='?' || rwords[i]=='!' ) )
					tsentences++;	
			}

			trfwords=new char[lwords];

			for(int i=0;i<rwords.length();i++)
			{
				if( isalpha(rwords[i]) )
				{
					trfwords[tnumber]=tolower(rwords[i]);
					tnumber++;	
				}
			}		
			
			if(isalpha(trfwords[0]))
			{
				twords++;
				rwords=trfwords;
				if(rwords.length()>=3)
				       	countthreeletters++;
				t.inserthn(rwords);
			}

			delete [] trfwords;
		}
		rfile.close();

		//calculation for the average length of word and how many words (5% used words) is 	
		if(twords>0)
		{
			awords = tlwords/twords;
			o5words = countthreeletters*0.05;
		}

		//second time to read the file for search unique words and words wich are used too often
		rfile.open(fname, ios::in);
		while(rfile>>rwords)
		{
			int tnumber=0, lwords=0;
			for(int i=0;i<rwords.length();i++)
			{
				if( isalpha(rwords[i]) )
				{					
					lwords++;
				}
			}
		
			trfwords=new char[lwords];
		
			for(int i=0;i<rwords.length();i++)
			{
				if( isalpha(rwords[i]) )
				{
					trfwords[tnumber]=tolower(rwords[i]);
					tnumber++;
				}
			}		
		
			if(isalpha(trfwords[0]))
			{
				rwords=trfwords;
			}
			
			//search word for checking if a unqiue word
         		if(t.searchhn(rwords))
			{
				if(tnw>=2)
				{
					uwords++;
					suwords.push_back(rwords);
					
					if(rwords.length()>=3)
						ouwords++;

					if( tnw>=o5words && rwords.length()>=3 )
					{
						souwords.push_back(rwords);
						f5threeletters++;
					}
					t.deletehn(rwords);
				}
			}

			delete [] trfwords;
		}
		rfile.close();

		//calculation for the average length of sentence
		if(tsentences>0)
			asentences = twords/tsentences;

		//print the first part of the report -- statistical summary

		ofile.open("report.txt", ios::out);
    
		ofile<<"File name: "<<fname<<endl<<endl
		     <<"                  Statistical Summary                  "<<endl<<endl
		     <<"Total number of words: "<<twords<<endl
		     <<"Total number of \"unqiue\" words: "<<uwords<<endl
		     <<"Total number of \"unqiue\" words of more than three letters: "<<ouwords<<endl
		     <<"Averge word length: "<<awords<<endl
		     <<"Averge Sentence length: "<<asentences<<endl<<endl<<endl;
		
		//print the second part of the report -- style warnings
		if( asentences>=12 || awords>=8 || f5threeletters>0)
		{
			ofile<<"                    Style Warnings                    "<<endl<<endl;
			if(f5threeletters>0)	
	     			oftenunqiuewords(souwords,ofile);
			if(asentences>=12)
				ofile<<"Average sentence length too long -- "<<asentences<<endl;
			if(awords>=8)
				ofile<<"Average worth length too long -- "<<awords<<endl;

		}

		//print the third part of the report -- index of unique words
	        if(uwords>0)
		{
			indexunqiuewords(suwords,ofile);
		}
		
		ofile.close();

		cout<<"Report has been output.";

	}
	cout<<endl<<endl<<endl<<"*******************************************************"<<endl<<endl;

	return 0;
}

void oftenunqiuewords(vector<string> a, fstream &ofile)
{
	ofile<<"Words used too often (words of more than 3 letters that are used more than 5\% of the total numbers ): "
    	     <<endl<<endl;

	for(int i=0;i<a.size();i++)
	{
		ofile<<i+1<<")"<<a[i]<<"   ";
	}

	ofile<<endl<<endl;
}

void indexunqiuewords(vector<string> a, fstream &ofile)
{
	string t;
	char tc;
	vector<char> c;

	ofile<<endl<<endl<<"                Index of unique words                    "<<endl<<endl;
	for(int i=0;i<a.size();i++)
	{
		for(int j=0;j<a.size();j++)
		{
			if(a[i]<a[j])
			{
				t=a[i];
				a[i]=a[j];
				a[j]=t;
			}
		}
	}

	for(int i=0;i<a.size();i++)
	{
		t=a[i];
		tc=toupper(t[0]);
		c.push_back(tc);
	}
	
	for(int i=0;i<a.size();i++)
	{
		ofile<<endl<<"  "<<c[i]<<endl<<" "<<a[i]<<"  ";

		i++;
		if(c[i-1]==c[i])
		{
			while(c[i-1]==c[i])
			{
				ofile<<a[i]<<"  ";
				i++;
			}
			i--;
		}
		else
			i--;
		ofile<<endl<<endl;	
	}
}	
