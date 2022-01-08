#include <iostream>
#include<string>
using namespace std;

template <class T>
class stackcal               // set up stack class for storing data
{ 
	private:
		T *istring=nullptr;
		int numcount;
	public:
		stackcal(int a)
		{
			istring = new T[a];
			numcount=-1;
		}
		~stackcal()
		{
			delete [] istring;
		}
		stackcal(const stackcal &right)
		{
			istring=right.istring;			
			numcount=right.numcount;
		} 
		void push(T a)
		{
			numcount++;
			istring[numcount]=a;
		}
		void pop(T &a)
		{
			a=istring[numcount];
			numcount--;
		}		
		bool ifempty()
		{
			if(numcount==-1)
				return true;
			return false;
		}
};

double tacstring(char [],int);            // this function for transfer data to double and char, then caluculate
void cal(stackcal<double> &, char);      //  this function for caluculation
int chpri(char);   // this function for checking the precedence of operator             
bool isdi(char);   // this function for checking if charcter is digit   

int main()
{
	string ai;           // set up a string variable 
	int an1=0,an2=0;  // set up int number for counting characters
	char *af;    // set up a char pointer for transfering string into char array
	cout<<endl<<"Pleas input an arithematic expression: ";
	getline(cin,ai);
   
	for(int i=0;i<ai.size();i++)
	{
		if( (ai[i]>='0' && ai[i]<='9') || ai[i]=='+' || ai[i]=='-' || ai[i]=='*' || ai[i]=='/' ||
   		     ai[i]=='(' || ai[i]==')' || ai[i]=='.' )
			an1++;
	}

	af=new char[an1];

	for(int i=0;i<ai.size();i++)
	{
		if( (ai[i]>='0' && ai[i]<='9') || ai[i]=='+' || ai[i]=='-' || ai[i]=='*' || ai[i]=='/' ||
		     ai[i]=='(' || ai[i]==')' || ai[i]=='.')
		{
			af[an2]=ai[i];
			an2++;
		}
	}

	// output the reuslt
	cout<<endl<<endl<<"The result is "<<tacstring(af,an1)<<endl<<endl; 
	
	return 0;
}

double tacstring(char a[],int b)
{
	stackcal<double> n(b);
        stackcal<char> o(b);
	double num1=0, num2=0,nreturn;
	int dotn=1, chp;
	char toperator, tno1,tno2;
	for(int i=0;i<b;i++)
	{
		if(a[i]>='0' && a[i]<='9')
		{
			if(  i==1 && a[0]=='-' && ( a[1]>='0' && a[1]<='9') )
			{
				o.pop(toperator);
				while(isdi(a[i]))
				{
					num2=num2*10;
					num1=0-(static_cast<double>(a[i])-48);
					num2=num2+num1;
					i++;
				}
				if(a[i]=='.')
				{
					i++;
					while(isdi(a[i]))
					{
						num1=0-(static_cast<double>(a[i])-48);
						num1=num1/(10*dotn);
						num2=num2+num1;
						i++;
						dotn++;
					}
				}
				n.push(num2);
				num2=0;
				dotn=1;
				i--;
			}
			else
			{
				tno1=a[i-1];
				tno2=a[i-2];
				if((tno2=='-' && tno1=='-') || (tno2=='(' && tno1=='-') || (tno2=='*' && tno1=='-') ||
				   (tno2=='/' && tno1=='-') || (tno2=='+' && tno1=='-')) 
				{
					while(isdi(a[i]))
					{
						num2=num2*10;
						num1=0-(static_cast<double>(a[i])-48);
						num2=num2+num1;
						i++;
					}
					if(a[i]=='.')
					{
						i++;
						while(isdi(a[i]))
						{
							num1=0-(static_cast<double>(a[i])-48);
							num1=num1/(10*dotn);
							num2=num2+num1;
							i++;
							dotn++;
						}
					}
					n.push(num2);
					num2=0;
					o.pop(toperator);
					dotn=1;
					i--;
				}
				else
				{
					while(isdi(a[i]))
					{
						num2=num2*10;
						num1=static_cast<double>(a[i])-48;
						num2=num2+num1;
						i++;
					}
					if(a[i]=='.')
					{
						i++;
						while(isdi(a[i]))
						{
							num1=static_cast<double>(a[i])-48;
							num1=num1/(10*dotn);
							num2=num2+num1;
							i++;
							dotn++;
						}
					}
					n.push(num2);
					num2=0;
					dotn=1;
					i--;
				}
			}
		}
		if(a[i]=='+'|| a[i]=='-'|| a[i]=='*'|| a[i]=='/' || a[i]=='(' || a[i]==')')
		{
			chp=chpri(a[i]);
			if(o.ifempty())
			{
				o.push(a[i]);
			}
			else
			{
				chp=chpri(a[i]);
				if(chp==1)
				{		
					o.pop(toperator);
					chp=chpri(toperator);
					if(chp==2 && (a[i-1]>='0' && a[i-1]<='9') )
					{
						if(toperator=='(')
						{
							o.push(toperator);
							o.push(a[i]);
						}
						else
						{
							cal(n,toperator);
							o.push(a[i]);
						}
					}
					else
					{
						o.push(toperator);
						o.push(a[i]);
					}
				}
				else if(chp==2)
				{	
					o.pop(toperator);
					chp=chpri(toperator);
					if( chp==2 )
					{
						cal(n,toperator);
					}
					else
					{
						o.push(toperator);
					}
					o.push(a[i]);
				}
				else
				{
					if(a[i]=='(')
					{
						o.push(a[i]);
					}
					else 
					{
						o.pop(toperator);
						while(toperator!='(')					
						{
							cal(n,toperator);
							o.pop(toperator);
						}
					}
				}
			}				
		}
	}
	while(!o.ifempty())
	{
		o.pop(toperator);
		if(toperator!='(' || !o.ifempty())		
			cal(n,toperator);
	}
	n.pop(nreturn);
	return nreturn;
}

void cal(stackcal<double> &nt, char a)
{
	double num1,num2,num3;
	nt.pop(num1);
	nt.pop(num2);
	if(a=='+')
		num3=num2+num1;
	if(a=='-')
		num3=num2-num1;
	if(a=='*')
		num3=num2*num1;
	if(a=='/')
		num3=num2/num1;
	nt.push(num3); 
}

int chpri(char a)
{
	int i;
	if(a=='+'||a=='-')
		i=1;
	else if(a=='*'||a=='/')
		i=2;
	else if(a=='(' || a== ')')
		i=3;
	return i;
}

bool isdi(char a)
{
	bool result;
	if(a>='0'&& a<='9' )
		result = true;
	else
		result =false;
	return result;
}
