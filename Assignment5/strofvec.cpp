/*Program for Polynomial equation manipulation.*/
// left work: throw error if input comes for existing exponent; work for fractional values. *done*
#include <algorithm>
#include <vector>
#include <iostream>

extern void exit();

using namespace std;

struct poly{
	int exp;
	int coeff;
	poly(int e, int c):exp(e),coeff(c){}
};
bool sorting(const poly& d1, const poly& d2)
{
  return d1.exp < d2.exp;
}
vector<poly> v;
void insert(int e, int c);
void edit(int);
void print();
void del(vector<poly> & v, int exp) {
	if(v.empty()==true){
		cout<<"Delete not possible, equation is empty!";
	}
    v.erase(
        std::remove_if(v.begin(), v.end(), [&](poly const & v) {
            return v.exp == exp;
        }),v.end());
}
int main(){
	int ch,e,c,inexp;
	do{

		cout<<"\n\nPolynomial Equation Menu\n";
		cout<<"============================\n\n";
		cout<<"1. Create()\n";
		cout<<"2. Edit()\n";
		cout<<"3. Print()\n";
		cout<<"4. Delete()\n";
		cout<<"5. exit\n";
		cout<<"Enter your choice: ";
		cin>>ch;
		switch(ch){
			case 1: cout<<"Enter Exponent: ";
					cin>>e;
					cout<<"Enter Coefficent: ";
					cin>>c;
					insert(e,c);
					sort(v.begin(), v.end(), sorting);
					break;
			case 2:	cout<<"Enter exponent of the term to be edited: ";
					cin>>inexp;
					edit(inexp);
					break;
			case 3: print();
					break;
			case 4: cout<<"Enter exponent of the term to be deleted: ";
					cin>>inexp; 
					del(v,inexp);
					break;
			case 5: exit(1);
		}
	}while(1);
return 0;
}
void insert(int e, int c){
	/*for(vector<poly>::const_iterator it=v.begin(); it!=v.end(); it++)
	{
		if((*it).exp==e){ 
			cout<<"Yes";
		}
   else*/
	vector<poly>::iterator it;
    for (it = v.begin(); it != v.end(); it++)
    {
        if (it->exp == e)
        {
			cout<<"Term already exists";
			return;
				}
		}
	
	v.push_back(poly(e,c));
}
void print(){
	if(v.empty()==true){
		cout<<"equation is empty!";}
for(int i=0;i<v.size();i++){
		cout<<"+"<<v[i].coeff<<"*x^"<<v[i].exp;
	}
}
void edit(int inexp){
	//finding whether exponent exists or not, if yes then find the associated coefficient
	
	int flag=0,ncoeff;
		/*for(vector<poly>::const_iterator it=v.begin(); it!=v.end(); it++)
	{
		if((*it).exp==inexp){
			
			flag=1;
			cout<<"\nOld value: "<<(*it).coeff;
			cout<<"\nEnter new value:";
			cin>>nexp;
			}*/
	vector<poly>::iterator it;
    for (it = v.begin(); it != v.end(); it++)
    {
        if (it->exp == inexp)
        {
            cout<<"\nOld value: "<<(*it).coeff;
			cout<<"\nEnter new value:";
			cin>>ncoeff;
            it->coeff = ncoeff;
            flag=1;
            break;
        }
	}
		if(!flag)
		{
			cout<<"The term does not exist";
		}

	}
 
	





/*void sort(){
	//sort(v.begin(), v.end());
	//sort(vec.begin(), vec.end(), CompareByMember<poly,std::int>(&poly::exp));

}*/