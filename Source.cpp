#include<iostream>
#include<sstream>
#include<fstream>
#include <string>
using namespace std;
class cnode
{
public:
	
	cnode* pnext;
	string id="";
	string name="";
	string pass="";
	string stock="";
	string price="";
};
class clist
{
public:
	cnode* phead;
	cnode* ptail;

	clist()
	{
		phead = NULL;
		ptail = NULL;
	}
	~clist()
	{
		/*cnode* ptrav;
		ptrav = phead;
		while (ptrav != NULL)
		{
			phead = phead->pnext;
			delete[] ptrav;
			ptrav = phead;
		}*/
	}
	void attach(cnode* pnn)
	{
		if (phead == NULL)
		{
			phead = pnn;
			ptail = pnn;
		}
		else
		{
			ptail->pnext = pnn;
			ptail = pnn;
		}
	}
	void display()
	{
		cnode* trav = phead;
		while (trav!=NULL)
		{
			//cout << trav->val << " ";
			cout << trav->id<<'|';
			cout << trav->name << '|';
			cout << trav->price << '|';
			cout << trav->stock << '|';
			cout << trav->pass;
			trav = trav->pnext;
			cout << endl;
		}
	}

};  
int signin(clist& customer,clist& product, clist& receipt,string& nname)
{

	int signf = 0, stocki,fb;
	cnode* pnn;
	cnode* ptrav = customer.phead;
	string buy;
	string password;
	cout << "name:";cin >> nname;
	cout << "password:";cin >> password;
	ptrav = customer.phead;
	while (ptrav != NULL)
	{

		if (ptrav->name == nname && ptrav->pass == password)
		{
			cout << "==================================" << endl;
			cout << "welcome MR/MRS:" << ptrav->name << endl;
			cout << "==================================" << endl;
			signf = 1;
		}
		ptrav = ptrav->pnext;
	}

	if (signf == 1)
	{
		ptrav = product.phead;
		cout << "choose what you want to buy" << endl;
		cout << "==================================" << endl;
		while (ptrav != NULL)
		{
			stocki = stoi(ptrav->stock);

			if (stocki > 0)
			{
				
				cout << ptrav->id<<':';
				cout << ptrav->name << ":";
				cout <<"L.E"<< ptrav->price << endl;
				
			}
			ptrav = ptrav->pnext;
		}
		cout << "==================================" << endl;
		while (1)
		{
			cin >> buy;
			ptrav = product.phead;
			while (ptrav != NULL)
			{
				if (ptrav->id == buy)
				{
					stocki = stoi(ptrav->stock);
					stocki--;
					ptrav->stock = "";
					ptrav->stock = to_string(stocki);
					pnn = new cnode;
					pnn->pnext = NULL;
					pnn->id = ptrav->id;
					pnn->name = ptrav->name;
					pnn->price = ptrav->price;
					receipt.attach(pnn);
					break;
				}
				ptrav = ptrav->pnext;
			}
			cout << "if you finish byuing press 0 else press 1" << endl;
			cin >> fb;
			if (fb == 0)
			{
				cout << "====================" << endl;
				cout << " your receipt " << endl;
				receipt.display();
				cout << "====================" << endl;
				cnode* ptrav = receipt.phead;
				int h, tot = 0;
				while (ptrav != NULL)
				{
					h = stoi(ptrav->price);
					tot += h;
					ptrav = ptrav->pnext;
				}
				cout << "--------------------" << endl;
				cout <<"total :" <<tot<<'"'<<endl;
				cout << "--------------------" << endl;
				break;
			}
			else
			{
				cout << "what you want to buy more" << endl;
			}
		}
	}
	else
	{
		cout << "you don't have an account" << endl;  
	}
	return signf;
}
int returnprod(clist& receipt, clist& product)
{
	int fflag = 0;
	int retf = 1;
	while (retf == 1)
	{
		cnode* ptrav2 = product.phead;
		int falseret = 0;
		cnode* ptrav = receipt.phead;
		cnode* pb = receipt.phead;
		string ret;
		cout << "which product you want to return " << endl;
		cin >> ret;
		for (int i = 0;ptrav != NULL;i++)
		{
			if (i == 0)
			{
				i++;
				if (ptrav->id == ret)
				{
					if (ptrav->pnext == NULL)
					{
						 fflag = 1;
						falseret = 1;
						delete ptrav;
						break;
					}
					receipt.phead = ptrav->pnext;
					ptrav->pnext = NULL;
					delete ptrav;
					falseret = 1;
					break;
				}
				else
				{
					ptrav = ptrav->pnext;
					continue;
				}
			}

			else if (ptrav->id == ret)
			{
				pb->pnext = ptrav->pnext;
				delete ptrav;
				falseret = 1;
				break;
			}
			ptrav = ptrav->pnext;
			pb = pb->pnext;
		}
		if (falseret == 1)
		{
			for (int i = 0;ptrav2 != NULL;i++)
			{
				if (ptrav2->id == ret)
				{
					int change = stoi(ptrav2->stock);
					change++;
					ptrav2->stock = "";
					ptrav2->stock = to_string(change);
				}
				ptrav2 = ptrav2->pnext;
			}
			if (fflag == 1)
			{
				
				cout << "no receipt you already returned all products" << endl;
				return 0;
			}
			cout << "if you want to return something else press 1 else press 0" << endl;
			cin >> retf;
		}
		else
		{
			cout << "you didn't buy this product, press 1 to return another product else press 0" << endl;
			cin >> retf;
		}
	}

	cout << "your final receipt is" << endl;
	cout << "------------------" << endl;
	receipt.display();
	cout << "------------------" << endl;
	cnode* ptrav = receipt.phead;
	int h, tot = 0;
	while (ptrav != NULL)
	{
		h = stoi(ptrav->price);
		tot += h;
		ptrav = ptrav->pnext;
	}
	cout << "==========" << endl;
	cout <<"total :"<< tot<<'"'<<endl;
	cout << "==========" << endl;
	tot = 0;
}
void registerr(clist& customer)
{
	
	cnode* pnn;
	pnn = new cnode;
	pnn->pnext = NULL;
	cout << "registeration" << endl;
	cout << "name :";cin >> pnn->name;
	cout << "password :";cin >> pnn->pass;
	if (customer.phead == NULL)
	{
		pnn->id = '1';
		cout << "your ID is:" << 1 << endl;
	}
	else
	{
		int incid = stoi(customer.ptail->id);
		incid++;
		pnn->id = to_string(incid);
		cout << "your ID is:"<<incid<<endl;
	}
	
	customer.attach(pnn);
	
	
}
void signinadmin(clist& product, clist& admin,clist counter,ifstream& shopaty)
{
	int signf = 0, stockorprice, choose,flag,adjust=1,i=0,Delete=1, inc,quant,ct=0;
	cnode* ptrav;
	cnode* pb;
	cnode* pnn;
	string nname,prod,custid;
	string password,line;
	cout << "name:";cin >> nname;
	cout << "password:";cin >> password;
	ptrav = admin.phead;
	while (ptrav != NULL)
	{

		if (ptrav->name == nname && ptrav->pass == password)
		{
			cout << "================================" << endl;
			cout << "welcome MR/MRS:" << ptrav->name << endl;
			cout << "================================" << endl;
			signf = 1;
		}
		ptrav = ptrav->pnext;
	}
	if (signf == 0)
	{
		cout<<"you are not an admin"<<endl;
	}
	if (signf == 1)
	{
		while (1)
		{
			cout << "========================================================================" << endl;
			cout << "1.display products" << endl;
			cout << "2.adjust product" << endl;
			cout << "3.Delete product" << endl;
			cout << "4.add new product" << endl;
			cout << "5.display all products that the stock is less than a specific quantity" << endl;
			cout << "6.display how many orders done by a specific customer" << endl;
			cout << "7.logout"<< endl;
			cout << "========================================================================" << endl;
			cin >> choose;
			if (choose == 1)
			{
				product.display();
			}
			if (choose == 2)
			{
				while (adjust==1)
				{
				   cout<<"which product you want to adjust"<<endl;
				   cin >> prod;
				   cout << "press 1 if you want to adjust the stock ,2 if you want to adjust the price" << endl;
				   cin >> flag;
				   ptrav = product.phead;
				   while (ptrav != NULL)
				   {
					   if (ptrav->id == prod)
					   {
						   if (flag == 1)
						   {
							   cout << "Enter the new value of the stock" << endl;
							   cin >> stockorprice;
							   ptrav->stock = to_string(stockorprice);
							   break;
						   }
						   if (flag == 2)
						   {
							   cout << "Enter the new price" << endl;
							   cin >> stockorprice;
							   ptrav->price = to_string(stockorprice);
							   break;
						   }
					   }
					   ptrav = ptrav->pnext;
				   }
				   cout << "if you want to adjust another product press 1 else press 0";
				   cin >> adjust;
				}
			}
			if (choose == 3)
			{
				Delete = 1;
				
				while (Delete==1)
				{
					i = 0;
					cout << "which product you want to delete" << endl;
					cin >> prod;
					ptrav = product.phead;
					pb = product.phead;
					while (ptrav != NULL)
					{
						if (i == 0)
						{
							i++;
							if (ptrav->id == prod)
							{
								
								product.phead = ptrav->pnext;
								ptrav->pnext = NULL;
								delete ptrav;
								break;
							}
							ptrav = ptrav->pnext;
							continue;
						    
						}
						else
						{
							if (ptrav->id == prod)
							{
								if (ptrav != product.ptail)
								{
									pb->pnext = ptrav->pnext;
									delete ptrav;
									break;
								}
								else
								{
									pb->pnext = NULL;
									delete ptrav;
									break;
								}
							}
						}
						ptrav = ptrav->pnext;
						pb = pb->pnext;
					}

					cout << "if you want to delete another product press 1 else press 0" << endl;
				  	cin >> Delete;

				}
				ptrav = product.phead;
				while (ptrav->pnext != NULL)
				{
					int ss = stoi(ptrav->id);
					int gg = stoi(ptrav->pnext->id);
					if (ss + 1 == gg)
					{
						continue;
					}
					else
					{
						gg = ss + 1;
						ptrav->pnext->id = to_string(gg);
					}
					ptrav = ptrav->pnext;
				}


			}
			if (choose == 4)
			{
				inc=stoi(product.ptail->id);
				inc++;
				pnn = new cnode;
				pnn->pnext = NULL;
				pnn->id = to_string(inc);
				cout << "product name :";cin >> pnn->name;
				cout << "product price :";cin >> pnn->price;
				cout << "product stock :";cin >> pnn->stock;
				product.attach(pnn);
			}
			if (choose == 5)
			{
				cout << "Enter a value to see all products less than the value" << endl;
				cin >> quant;
				ptrav = product.phead;
				while (ptrav != NULL)
				{
					inc = stoi(ptrav->stock);
					if (inc < quant)
					{
						cout << ptrav->id<<':';
						cout << ptrav->name<<':';
						cout << ptrav->price << ':';
						cout << ptrav->stock << endl;

					}
					ptrav = ptrav->pnext;
				}
			}
			if (choose == 6)
			{
				cout << "enter the cusomer id :" << endl;
				cin >> custid;   
				ct = 0;
				while (shopaty.peek() != EOF)
				{
					
					string line;
					string st;
					int f1 = 0;
					getline(shopaty, line);
					for (int i = 0;i < line.length();i++)
					{
						if (line[i] == ':')
						{
							f1 = 1;
							i++;
						}
						if (line[i] == ','&&f1==1)
						{
							break;
						}
						if (f1 == 1)
						{
							st += line[i];
						}
					}
					//cout << st;
					
					if (st == custid)
					{
						
						///////////
						ct++;

					}
				}
				/*ptrav = counter.phead;
				while (ptrav!=NULL)
				{
					if (custid == ptrav->id)
					{
						ct++;
					}
					ptrav = ptrav->pnext;
				}*/

				cout <<"this customer orders are :"<< ct << endl;

			}
			if (choose == 7)
			{
				break;
			}

		}
		
	}
}
int main()
{
	int pop = 0;
	int signf;
	clist receipt;
	clist counter;
	int stocki;
	cnode* ptrav;
	string idd,password;
	char c=' ';
	int g,lorr;
	clist product;
	clist admin;
	clist customer;
	ifstream fileprod;
	ifstream filecust;
	ifstream fileadmin;
	ofstream fileshop;
	
	cnode* pnn;
	string line,nname;
	int ct = 0;
	
	fileprod.open("product.txt");
	filecust.open("customer.txt");
	fileadmin.open("admin.txt");
	while (fileprod.peek() != EOF)
	{
		getline(fileprod, line);  // e7na n7ot f linked list 3la toool
		pnn = new cnode;
		pnn->pnext = NULL;
		for (int i = 0;i < line.length();i++)
		{
			if (ct == 0)
			{
				if (line[i] != ' ')
				{
					pnn->id += line[i];
				}
			}
			if (ct == 1)
			{
				if (line[i] != ' ')
				{
					pnn->name += line[i];
				}
			}
			if (ct == 2)
			{
				if (line[i] != ' ')
				{
					pnn->price += line[i];
				}
			}
			if (ct == 3)
			{
				if (line[i] != ' ')
				{
					pnn->stock += line[i];
				}
			}
			if (line[i] == ' ')
			{
				ct++;
			}
		}
		product.attach(pnn);
		ct = 0;
	}
	
	
	while (filecust.peek() != EOF)
	{
		getline(filecust, line);  // e7na n7ot f linked list 3la toool
		pnn = new cnode;
		pnn->pnext = NULL;
		for (int i = 0;i < line.length();i++)
		{
			if (ct == 0)
			{
				if (line[i] != ' ')
				{
					pnn->id += line[i];
				}
			}
			if (ct == 1)
			{
				if (line[i] != ' ')
				{
					pnn->name += line[i];
				}
			}
			if (ct == 2)
			{
				if (line[i] != ' ')
				{
					pnn->pass += line[i];
				}
			}
			if (line[i] == ' ')
			{
				ct++;
			}
		}
		customer.attach(pnn);
		ct = 0;
	}
	//int limit = stoi(customer.ptail->id);
	//cout<<customer.phead->id;
	//cout << endl;
	//cout << customer.phead->pass;
	while (fileadmin.peek() != EOF)
	{
		getline(fileadmin, line);  // e7na n7ot f linked list 3la toool
		pnn = new cnode;
		pnn->pnext = NULL;
		for (int i = 0;i < line.length();i++)
		{
			if (ct == 0)
			{
				if (line[i] != ' ')
				{
					pnn->id += line[i];
				}
			}
			if (ct == 1)
			{
				if (line[i] != ' ')
				{
					pnn->name += line[i];
				}
			}
			if (ct == 2)
			{
				if (line[i] != ' ')
				{
					pnn->pass += line[i];
				}
			}
			if (line[i] == ' ')
			{
				ct++;
			}
		}
		admin.attach(pnn);
		ct = 0;
	}
	while (c != 'z')
	{
		cout << "press C if you are a customer and press A if you are admin" << endl;
		cin >> c;
		
		if (c == 'C' || c == 'c')
		{
			while (1)
			{
				if (receipt.phead != NULL)
				{
					
					ptrav = receipt.phead;
					while (ptrav != NULL)
					{
						if (receipt.phead == receipt.ptail)
						{
							receipt.phead = NULL;
							delete receipt.phead;
							break;
						}
						else
						{
							receipt.phead = ptrav->pnext;
							delete ptrav;
							ptrav = receipt.phead;
						}
					}
				}
				cout << "1.sign in" << endl;
				cout << "2.register" << endl;
				cin >> g;
				if (g == 1)
				{
					signf = signin(customer, product, receipt, nname);
					if (signf == 0)
					{
						continue;
					}
					cout << "if you want to logout press 0 if you want to return something press 1" << endl;
					cin >> lorr;
					if (lorr == 1)
					{
						returnprod(receipt, product);
						if (receipt.phead != NULL)
						{
							cout << endl;
							ptrav = customer.phead;
							pop++;
							fileshop.open("shop.txt", ios::app);
							while (ptrav != NULL)
							{
								if (ptrav->name == nname)
								{
									fileshop << "\ncustomer id :" << ptrav->id << ',';
									pnn = new cnode;
									pnn->pnext = NULL;
									pnn->id = ptrav->id;
									counter.attach(pnn);
								}
								ptrav = ptrav->pnext;
							}
							ptrav = receipt.phead;
							fileshop << "product" << ',';
							while (ptrav != NULL)
							{
								fileshop << ptrav->id;
								ptrav = ptrav->pnext;
							}
							fileshop.close();
							////////////////////////////////////////

							break;
						}
					}
					if (lorr == 0)
					{
						if (receipt.phead != NULL)
						{
							ptrav = customer.phead;
							fileshop.open("shop.txt", ios::app);
							while (ptrav != NULL)
							{
								if (ptrav->name == nname)
								{
									fileshop << "\ncustomer id :" << ptrav->id << ',';
									pnn = new cnode;
									pnn->pnext = NULL;
									pnn->id = ptrav->id;
									counter.attach(pnn);
								}
								ptrav = ptrav->pnext;
							}
							ptrav = receipt.phead;
							fileshop << "product" << ':';
							while (ptrav != NULL)
							{
								fileshop << ptrav->id << ',';
								ptrav = ptrav->pnext;
							}
							fileshop.close();
							//////////////////////

							continue;
						}
					}

				}
				if (g == 0)
				{
					break;
				}
				if (g == 2)
				{
					registerr(customer);
				}

			}
			
		}
		ifstream shopat;
		shopat.open("shop.txt");
		if (c == 'a' || c == 'A')
		{
			signinadmin(product, admin,counter,shopat);
		}

		if (islower(c) == 'z')
		{
			break;
		}
	}
	fileadmin.close();
	filecust.close();
	fileprod.close();

	ofstream fileproduct;
	ofstream filecustomer;
	

	
	fileproduct.open("product.txt");
	filecustomer.open("customer.txt");
	

	ptrav = product.phead;
	while (ptrav != NULL)
	{
		fileproduct << ptrav->id << ' ' << ptrav->name << ' ' << ptrav->price << ' ' << ptrav->stock<<endl;
		ptrav = ptrav->pnext;
	}

	ptrav = customer.phead;
	while (ptrav != NULL)
	{
		filecustomer << ptrav->id << ' ' << ptrav->name << ' ' << ptrav->pass<<endl;
		ptrav = ptrav->pnext;
	}	
}