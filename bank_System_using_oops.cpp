#include<bits/stdc++.h>
using namespace std;

struct Detail
{
	int account;
	string name;
	int age;
	float amount;
};


class Bank_System // BANK SYSTEM CLASS
{
	//protected:
	public:
	vector<Detail> Data;
	vector<int> querry_card;
	vector<int> querry_book1;
	vector<int> querry_book2;
	int min_amt;

//	public:
	Bank_System()
	{
		min_amt=100;
	}

	void insert(Detail &cust)
	{
		cust.account=Data.size();
		querry_card.push_back(0);
		querry_book1.push_back(0);
		querry_book2.push_back(0);
		Data.push_back(cust);
	}
	void remove(Detail cust)
	{
		int n=Data.size();
		for(int i=0;i<n;i++)
		{
			if(cust.account==Data[i].account)
			{
				Data.erase(Data.begin()+i);
				querry_card.erase(querry_card.begin()+i);
				querry_book1.erase(querry_book1.begin()+i);
				querry_book2.erase(querry_book2.begin()+i);
				break;
			}
		}
	}

	friend class Employee;
};
Bank_System BS;

class Employee // EMPLOYEE CLASS 
{
	public:
	
	int validate(Detail cust)
	{
		int n=BS.Data.size();
		//cout<<n<<endl;
		for(int i=0;i<n;i++)
		{
			if(cust.account==BS.Data[i].account)
			{
				return 1;
			}
		}
		return 0;
	}
};

class Clerk : public Employee //CLERK CLASS INHERITING EMPLOYEE CLASS
{
	public:
	
	void open(Detail cust)
	{
		if(validate(cust)==0)
		{
			BS.insert(cust);
			cout<<"\n ||--- YOUR ACCOUNT NUMBER --- ||"<<cust.account<<endl;
		}
		else
		{
			cout<<"\n||----- SORRY THIS ACCOUNT ALREADY EXISTS -----||\n"<<endl;
		}
	
	}

	void close(Detail cust,int choice)
	{
		if(choice==2)
			cout<<"\n||---- OPTION CHOSEN BY CUSTOMER TO EXIT----- ||"<<endl;
		else if(choice>=3 || choice<=0)
			cout<<"\n||------ SORRY WRONG CHOICE ENTERD ------|| "<<endl;
		else if(validate(cust)==1)
		{
			BS.remove(cust);
		}
		else
		{
			cout<<"\n||----- SORRY THIS ACCOUNT DOES NOT EXIST -----||\n"<<endl;
		}
	}

	void card_issue(Detail cust,int choice)
	{
		if(choice==1)
		{
			if(BS.querry_card[cust.account]==1)
				cout<<"\n || Already Given ----- ||"<<endl;
			else
			{
				cout<<"\n New Card issued "<<endl;
				BS.querry_card[cust.account]=1;
			}
		}
		else if(choice ==2)
		{
			BS.querry_card[cust.account]=1;
			cout<<"\n || WAIT FOR 15 WORKING DAYS FOR NEW CARD ||"<<endl;
		}
		else
			cout<<"\n||----- SORRY WRONG CHOICE -----||\n"<<endl;
	}

	void passbook(Detail cust , int choice)
	{
		if(choice==1)
		{
			if(BS.querry_book1[cust.account]==1)
				cout<<"\n || Already Given ----- ||"<<endl;
			else
			{
				cout<<"\n New PassBook issued "<<endl;
				BS.querry_book1[cust.account]=1;
			}
		}
		else if(choice ==2)
		{
			BS.querry_book1[cust.account]=1;
			cout<<"\n || WAIT FOR 2 WORKING DAYS FOR NEW ONE ||"<<endl;
		}
		else
			cout<<"\n||----- SORRY WRONG CHOICE -----||\n"<<endl;		
	}

	void chequebook(Detail cust , int choice)
	{
		if(choice==1)
		{
			if(BS.querry_book2[cust.account]==1)
				cout<<"\n || Already Given ----- ||"<<endl;
			else
			{
				cout<<"\n New ChequeBook issued "<<endl;
				BS.querry_book2[cust.account]=1;
			}
		}
		else if(choice ==2)
		{
			BS.querry_book2[cust.account]=1;
			cout<<"\n || WAIT FOR 2 WORKING DAYS FOR NEW ONE ||"<<endl;
		}
		else
			cout<<"\n||----- SORRY WRONG CHOICE -----||\n"<<endl;		
	}
};

class Cashier : public Employee // CASHIER CLASS INHERITING EMPLOYEE CLASS 
{
	protected:
		int amt1;
		int amt2;
		int amt;
	public:
	Cashier()
	{
		amt=5000;
	}
	void deposit(Detail cust,int amt)
	{
		int n=BS.Data.size();
		for(int i=0;i<n;i++)
		{
			if(cust.account==BS.Data[i].account)
			{
				BS.Data[i].amount+=amt;
				cout<<"\n || New Balance ----|| "<<BS.Data[i].amount<<endl;
				cust=BS.Data[i];
				break;
			}
		}
	}

	void withdraw(Detail cust,int amt)
	{
		int n=BS.Data.size();
		for(int i=0;i<n;i++)
		{
			if(cust.account==BS.Data[i].account)
			{
				if(amt+BS.min_amt>BS.Data[i].amount)
				{
					cout<<"\n|| SORRY NOT ENOUGH BALANCE ||" <<endl;
				}
				else
				{
					BS.Data[i].amount-=amt;
					cout<<"\n || New Balance ----|| "<<BS.Data[i].amount<<endl;
					cust=BS.Data[i];
				}
				break;
			}
		}
	}

	void ddmake1(int amt)
	{
		amt1=amt;
	}

	void ddmake2(int amt)
	{
		amt2=amt;
		if(amt2<amt1)
		{
			cout<<"\n\t Sorry but not enough cash to make DD "<<endl;
		}
		else if(amt1>amt)
		{
			cout<<"\n\t Sorry but max DD cash limits exceeded as MAx DD limit is : "<<amt<<endl;

		}
		else if(amt2>amt1)
		{
			cout<<"\n\t CASH GIVEN IS MORE THAN DD AMOUNT : CHANGE: "<<amt2-amt1<<endl;
			cout<<"\n\t DD SUCCESSFUL "<<endl;

		}
		else
		{
			cout<<"\n\t DD SUCCESSFUL "<<endl;
		}
		amt1=amt2=0;
	}
	
	void ddmake3(Detail cust)
	{
		int n=BS.Data.size();
		for(int i=0;i<n;i++)
		{
			if(cust.account==BS.Data[i].account)
			{
				if(amt1+BS.min_amt>BS.Data[i].amount)
				{
					cout<<"\n|| SORRY NOT ENOUGH BALANCE ||" <<endl;
				}
				else
				{
					BS.Data[i].amount-=amt1;
					cout<<"\n || New Balance ----|| "<<BS.Data[i].amount<<endl<<"\n\t DD successfully made "<<endl;
					cust=BS.Data[i];
				}
				break;
			}
		}
	}
};

class Customer // CUSTOMER IS A VIRTUAL CLASS
{
	protected:
	Detail cust;
	int type;
	public:
	Customer()
	{	
	}
	
	void give_detail()
	{	
	}

	
};

class New_Customer : public Customer //NEW CUSTOMER CLASS INHERITING CUSTOMER CLASS
{
	public:
	New_Customer()
	{
		type=1;	
	}
	
	void give_detail()
	{
		Detail current;
		cout<<"\n\t Enter the Personal details"<<endl;
		cout<<"\n\t#Enter Name : ";
		cin>>current.name;
		cout<<"\n\t#Enter Age : ";
		cin>>current.age;
		cust=current;
		
	}
	void open()
	{
		int amt;
		cin>>amt;
		cust.amount=amt;
	}

	int dd1()
	{
		int amt;
		cin>>amt;
		return amt;
	}
	int dd2()
	{
		int amt;
		cin>>amt;
		return amt;
	}
	Detail infoshow()
	{
		return cust;
	}

	int choice()
	{
		int x;
		cin>>x;
		return x;
	}

};


class Old_Customer : public Customer // OLD CUSTOMER CLASS INHERITING CUSTOMER CLASS
{
	public:
	Old_Customer()
	{
		type=2;
	}

	void give_detail()
	{
		Detail current;
		cout<<"\n\t Enter the Personal details"<<endl;
		cout<<"\n\t#Enter Name : ";
		cin>>current.name;
		cout<<"\n\t#Enter Age : ";
		cin>>current.age;
		cout<<"\n\t#Enter Account Number : ";
		cin>>current.account;
		cust=current;
	}
	int deposit()
	{
		int amt;
		cin>>amt;
		return amt;	
	}

	int withdraw()
	{
		int amt;
		cin>>amt;
		return amt;
	}

	int close()
	{
		int chc;
		cin>>chc;	
		return chc;
	}

	int choice()
	{
		int x;
		cin>>x;
		return x;
	}

	Detail infoshow()
	{
		return cust;
	}

	int ddraft()
	{
		int y;
		cin>>y;
		return y;
	}
	int dd1()
	{
		int amt;
		cin>>amt;
		return amt;
	}
	int dd2()
	{
		int amt;
		cin>>amt;
		return amt;
	}
};
int main()
{
Bank_System bb;
	do
	{
		cout<<"\n------------------------------------------------------------------------\n"<<endl;
		cout<<"\n||------      WELCOME TO XYZ BANK      ------||\n\n"<<endl;
		int customer_type;
		cout<<"\n\t[] 1. Old Customer\n\t[] 2. New Customer\n\n\t#Customer Type Choice: ";
		cin>>customer_type;		

		int counter_choice;
		
		Cashier emp;
		Clerk emp2;
			New_Customer customer2;
			Old_Customer customer;
		int xx,chc2,action1,action2,action3,action4,action;
		switch(customer_type)
		{


			case 1://-----------------CASE 1 OF CUSTOMER BEING OLD CUSTOMER--------||
	
				customer.give_detail();
					//---------- Emp validating details of the customer ----||
					if(emp.validate(customer.infoshow()))	
						cout<<"\n\t||----- Details Verified -----||"<<endl;
					else
					{
						cout<<"||----- WRONG DETAILS ENTERED-----||"<<endl;
						return 0;
					}

					//--------- Action processing Starts---------------- //
					
		cout<<"\n\t[] 1. Go to Cashier counter\n\t[] 2. Go to Clerk counter\n\n\t#Counter Choice: ";
					counter_choice=customer.choice();
					cout<<"\n\t||-----CHOOSE FROM THE FOLLOWING CHOICES-----||"<<endl;
				
				switch(counter_choice)
				{
					case 1: // ------ CUSTOMER CHOOSING CASHIER 

					cout<<"\t[] 1.Deposit\n\t[] 2.Withdraw\n\t[] 3.Demand Draft\n\t[] 4.Leave\n";
					action1=customer.choice();
					switch(action1)
					{
						case 1:// CASE 1 OF OLD CUSTOMER CHOOSING DEPOSIT ----------------------------------||
							cout<<"\n\t\t #Enter Amount to be deposited : ";
							emp.deposit(customer.infoshow(),customer.deposit());
							break;
						case 2://CASE 2 OF OLD CUSTOMER CHOOSING WITHDRAW ----------------------------------||
							cout<<"\n\t\t#Enter Amount to be Withdrawn : ";
							emp.withdraw(customer.infoshow(),customer.withdraw());
							break;
						case 3://CASE 3 OF OLD CUSTOMER CHOOSING DEMAND DRAFT ----------------------------------||
							cout<<"\n\t Demand Draft Choice Selected :\n\n\t1.Cheque\n\t2.Cash\n";
							chc2=customer.choice();
							cout<<"\n\tEnter the amount of Demand Draft : ";
							emp.ddmake1(customer.dd1());					
							if(chc2==1)
							{
								emp.ddmake3(customer.infoshow());
							}
							else if(chc2==2)
							{
								cout<<"\n\t Give cash: ";
								emp.ddmake2(customer.dd2());
							}
							else
								cout<<"\n|| -----WRONG CHOICE -----||"<<endl;
							break;
						case 4://CASE 4 OF OLD CUSTOMER FOR LEAVING ----------------------------------||
							cout<<"\n\t||---- YOU CHOOSE TO LEAVE ----||"<<endl;
							return 1;
						break;
						default :
							return 1;

					}
					break;
				
				case 2: // ------ CUSTOMER CHOOSING CLERK
					cout<<"\t[] 1.Debit/Credit Card Issue\n\t[] 2.Passbook/CheckqueBook Issue\n\t[] 3.Close Account\n\t[] 4.Leave\n";
					action=customer.choice();
					switch(action)
					{
						case 1:// OLD CUSTOMER CHOOSING CARD ISSUE ----------------------------------||
							cout<<"\n\t1. New Card Issue\n\t2.Card Lost"<<endl;
							emp2.card_issue(customer.infoshow(),customer.choice());
							break;
						case 2:// OLD CUSTOMER CHOOSING BOOK ISSUE ----------------------------------||
							cout<<"\n\t1.Checkbook Issue\n\t2.PassBook Issue"<<endl;
							xx=customer.choice();
							if(xx==1)
							{
								cout<<"\n\t1.New \n\t2.Lost"<<endl;
								emp2.chequebook(customer.infoshow(),customer.choice());
							}
							else if(xx==2)
							{
								cout<<"\n\t1.New \n\t2.Lost"<<endl;
								emp2.passbook(customer.infoshow(),customer.choice());
							}
							else
								cout<<"\n|| SORRY WRONG CHOICE ||"<<endl;
							break;
						case 3:// OLD CUSTOMER OPTING FOR CLOSING ACCOUNT ----------------------------------||
							cout<<"\n\t1.Close \n\t2. Exit"<<endl;
							emp2.close(customer.infoshow(),customer.close());
							break;
						case 4:// OLD CUSTOMER FOR LEAVING ----------------------------------||
							cout<<"\n\t||---- YOU CHOOSE TO LEAVE ----||"<<endl;
							return 1;
						break;
					}
					break;
				}
			break;	
			case 2:// ------------------------------NEW CUSTOMER CASES-----------------------------------------------------------------||

				customer2.give_detail();
					//---------- Emp validating details of the customer ----||
					if(emp.validate(customer2.infoshow())==1)	
					{
						cout<<"\n\t||----- ThIS ACCOUNT IS ALREADY PRESENT -----||"<<endl;
						return 1;;
					}
					else
					{
						cout<<"||----- WELCOME NEW CUSTOMER-----||"<<endl;
					}
					//--------- Action processing Starts---------------- //

		cout<<"\n\t[] 1. Go to Cashier counter\n\t[] 2. Go to Clerk counter\n\n\t#Counter Choice: ";
					counter_choice=customer.choice();
					cout<<"\n\t||-----CHOOSE FROM THE FOLLOWING CHOICES-----||"<<endl;
				
				switch(counter_choice)
				{
				case 1:// ------ NEW CUSTOMER CHOOSING CASHIER 
					cout<<"\t[] 1.Demand Draft\n\t[] 4.Leave\n";
					cin>>action4;
					switch(action4)
					{			
						case 1:// CASE 1 OF NEW CUSTOMER CHOOSING DEMAND DRAFT ----------------------------------||
							cout<<"\n\tEnter the amount of Demand Draft : ";
							emp.ddmake1(customer2.dd1());
							cout<<"\n\t Give cash: ";
							emp.ddmake2(customer2.dd2());
							break;
						case 2://CASE 2 OF NEW CUSTOMER FOR LEAVING ----------------------------------||
							cout<<"\n\t||---- YOU CHOOSE TO LEAVE ----||"<<endl;
							return 1;
						break;
					}
					break;
				case 2:// ------ NEW CUSTOMER CHOOSING CLERK
					cout<<"\t[] 1.Open Account\n\t[] 2.Leave\n";
					cin>>action2;
					switch(action2)
					{
						case 1:// CASE 1 OF NEW CUSTOMER CHOOSING OPENING ACCOUNT ----------------------------------||
							cout<<"\n\t Minimum Amount to be deposited while opening Account: "<<100<<endl;
							cout<<"\n\t Enter Amount :";
							customer2.open();
							emp2.open(customer2.infoshow());
							break;
						case 4://CASE 2 OF NEW CUSTOMER FOR LEAVING ----------------------------------||
							cout<<"\n\t||---- YOU CHOOSE TO LEAVE ----||"<<endl;
							return 1;
						break;
					}
					break;
				}
			break;	
			default:
				cout<<"\n\n|| ------SORRY WRONG CHOICE ---------|| "<<endl;
				return 0;
		}
	}
	while(1);
}
