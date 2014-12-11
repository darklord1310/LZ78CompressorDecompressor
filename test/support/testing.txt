//Author: Wong Yan Yin
//Date: 7/6/2013
//Purpose: Train Ticketing System

#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>
#include <fstream>
#include <windows.h>
using namespace std;

struct node5{
	
	char store_departure_date[11];
	char store_departure_time[6];
	node5 *next;
};

struct node{
	char store_train_code[5];
	char store_departure_date[11];
	char store_departure_time[6];
	char store_boarding_location[11];
	char store_destination[10];
	node *next;
};

struct node4{
	
	char classes[2];
	char coach[3];
	char traincode[5];
	double sales;
	double occupancy;
	node4 *next;
};

struct node3{
	
	char classes[2];
	char coach[3];
	char traincode[5];
	double sales;
	node3 *next;
};

struct salesnode{
	char store_train_code[5];
	char store_departure_date[11];
	char store_departure_time[6];
	char store_boarding_location[11];
	char store_destination[10];
	salesnode *next;
};

struct node2{
	
	char store_departure_date[11];
	char store_departure_time[6];
	node2 *next;
};

struct details    // structure used to store train details
{
	string departure_date,departure_time, arrive_date,arrive_time,destination,coach;                                                                             
	char boarding_location[30];
	char classes;
	char train_code[5];
			
};

double superiorclass(int ticket_array[4][6]); //function to display seat occupancy for superior class
double economyclass(int ticket_array1[6][8]); //function to display seat occupancy for economy class
void salereport_superior(int ticket_array[4][6],struct ticket_info TICKET_INFO[24],string seat_superior[4][6],struct details ticket_details, double occupancyratesuperior); // function to display sales report for superior class
void salereport_economy(int ticket_array1[6][8], struct ticket_info TICKET_INFO1[48], string seat_economy[6][8] , struct details ticket_details, double occupancyrateeco); // function to display sales report for economy class
void logo(); // function to display logo
void endmessage(); // function to display end message
int seatchecking_superior(int ticket_array[4][6]); // function to check the seats available for superior class
int seatchecking_economy(int ticket_array1[6][8]); // function to check the seats available for economy class
int addtrain();
int viewtrain();
int modifytrain();
void mainmenu();
void staffmenu();
void managementmenu();
int ticket_selling();
int monthlysalesreport();
void train_maintenance();
int train_occupancy_rate();
int viewtrain1();
void password_checking();
void modify_password();

struct ticket_info  // structure used to store ticket information
{
	char adultorchild;
	string seatID;
	double price;
	double tax;
	int type;
	
};

void salereport_superior(int ticket_array[4][6],struct ticket_info TICKET_INFO[24],string seat_superior[4][6], struct details ticket_details, double occupancyratesuperior)
{
	int z=0;
	int	y=0;
	int	f=0;
	int h=0;
	int value;
	double sales_total;
	double total_price_ver[4]={0}; // variable used to store all the price in row
	double total_price_hor[6]={0}; // variable used to store all the price in column
	ofstream out_sales_superior;
	ofstream outfile;
	char ch='S';
	
	 cout<<endl;
	 cout<<"©°©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©´"<<endl;
	 cout<<"©¦    Total Sales - by Seat Layout                        "<<" Superior Class   ©¦"<<endl;
	 cout<<"©¦    "<<setw(20)<<right<<ticket_details.boarding_location<<"-"<<left<<setw(20)<<ticket_details.destination<<right<<setw(21)<<ticket_details.departure_date<<setw(8)<<ticket_details.departure_time<<"©¦"<<endl;
	 cout<<"©¦      01    "<<"    02    "<<"    03    "<<"    04    "<<"    05    "<<"    06    "<<"   Sales(RM)©¦"<<endl;
	
	
for(int x=0;x<6;x++)  // All of the following is to print output format
{
	z++;
	if ( x==0)
	{		
		cout<<"©¦  ©°©¤©¤©¤©¤©Ð";
	for(int j=0;j<5;j++)
		{
			 if( j==4)
		  {
			  cout<<"©¤©¤©¤©¤©´"<<"          "<<"©¦";
			  cout<<endl;
		  }
			 else

	          cout<<"©¤©¤©¤©¤©Ð";
		 
		}
	}

	else if(x==5)
	{
		y=0;
		cout<<"©¦D ";
			for( int n=0;n<7;n++)
	{
		if(n==6)
		{
			cout<<"©¦ "<<setw(8)<<total_price_ver[z-3]<<" "<<"©¦";
			cout<<endl;
		}
		else

		   {cout<<"©¦   "<<ticket_array[z-3][y] <<"    ";
		    if(ticket_array[z-3][y] == 1)
			  for(int m=0;m<24;m++)
			 {
              if (TICKET_INFO[m].seatID == seat_superior[z-3][y]) //Accumulate all the price for the 4th row
				  total_price_ver[z-3]+=TICKET_INFO[m].price;
			 }
		    y++;
		   }
	}
	for( int i=0;i<6;i++)
	{
		if(i==0)
		  cout<<"©¦  ©¸©¤©¤©¤©¤©Ø";
		else if(i==5)
		  cout<<"©¤©¤©¤©¤©¼"<<"          "<<"©¦"<<endl;
		else 
	      cout<<"©¤©¤©¤©¤©Ø";
	}
	cout<<"©¦Sales"<<setw(59)<<" "<<setw(10)<<"------"<<"©¦"<<endl;
	for(int g=0;g<6;g++)
	{
	   for(int i=0; i<4;i++)
	    {
		   if (ticket_array[i][g]==1)
		  { 
			  for(int m=0;m<24;m++)
			 {
              if (TICKET_INFO[m].seatID == seat_superior[i][g]) //Accumulate all the price for the same column
				  total_price_hor[g]+=TICKET_INFO[m].price;
			 }
		   }
	    }
	  
	}
	cout<<"©¦(RM)    ";
	for(int i=0;i<6;i++)
	{
	 cout<<left<<setw(8)<<total_price_hor[i]<<"  ";
	}
	cout<<right<<setw(5)<<total_price_ver[0]+total_price_ver[1]+total_price_ver[2]+total_price_ver[3]<<" ©¦"<<endl; // total up the price 
	cout<<"©¦"<<setw(63)<<" "<<setw(11)<<"======"<<"©¦"<<endl;
	cout<<"©¸©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¼"<<endl<<endl;

	sales_total=total_price_ver[0]+total_price_ver[1]+total_price_ver[2]+total_price_ver[3];
	
	out_sales_superior.open("Sales Date.txt" ,ios::app);

	if (!out_sales_superior)
	{
		cout<<"Error opening File!";
		exit(1);
	}
	
	out_sales_superior<<ticket_details.departure_date<<"|";
	out_sales_superior<<ticket_details.departure_time<<endl;
	out_sales_superior.close();

	outfile.open("Sales File.txt", ios::app);
	
	if (!outfile)
	{
		cout<<"Error opening File!";
		exit(1);
	}
	
	outfile<<ch<<"|";
	outfile<<ticket_details.coach<<"|";
	outfile<<ticket_details.train_code<<"|";
	outfile<<fixed<<setprecision(2)<<sales_total<<"|";
	value= seatchecking_superior(ticket_array);
	outfile<<occupancyratesuperior<<endl;

	outfile.close();
	}

	else if(x==2)
	{
		y=0;
		cout<<"©¦B ";
		for( int n=0;n<7;n++)
	{
		if(n==6)
		{
			cout<<"©¦ "<<setw(8)<<total_price_ver[z-2]<<" "<<"©¦";
			cout<<endl;
		}
		else

		   {cout<<"©¦   "<<ticket_array[z-2][y] <<"    ";
		    if(ticket_array[z-2][y] == 1)
				  for(int m=0;m<24;m++)
			 {
              if (TICKET_INFO[m].seatID == seat_superior[z-2][y]) //Accumulate all the price for the 2nd row
				  total_price_ver[z-2]+=TICKET_INFO[m].price;
			 }
		    y++;
		   }
	}
	for( int i=0;i<6;i++)
	{
		if(i==0)
		 cout<<"©¦  ©À©¤©¤©¤©¤©Ø";
		else if(i==5)
			{cout<<"©¤©¤©¤©¤©È"<<"          "<<"©¦";
		     cout<<endl;
		    }
		else 
	     cout<<"©¤©¤©¤©¤©Ø";

	}
	f++;
	}

	else if(x==3)
	{
		for( int n=0;n<56;n++)
	{
		if(n==55)
		{
			cout<<"©¦ "<<"         "<<"©¦";
			cout<<endl;
		}
		else if(n==0)
		   cout<<"©¦  ©¦";
		else if(n==28)
		   cout<<"Aisle";
		else
		   cout<<" ";
	}
	for( int i=0;i<6;i++)
	{
		if(i==0)
		cout<<"©¦  ©À©¤©¤©¤©¤©Ð";
		else if(i==5)
			{cout<<"©¤©¤©¤©¤©È"<<"          "<<"©¦";
		     cout<<endl;
		    }
		else 
	     cout<<"©¤©¤©¤©¤©Ð";

	}
		}
		
	else if(x==1)
			{cout<<"©¦A ";
		     y=0;
			for( int n=0;n<7;n++)
	{
		
		
		if(n==6)
		{
			cout<<"©¦ "<<right<<setw(8)<<setprecision(1)<<fixed<<setfill(' ')<<total_price_ver[z-2]<<" "<<"©¦";       
			cout<<endl;
		}
		else

		   {cout<<"©¦   "<<ticket_array[z-2][y] <<"    ";
		    if(ticket_array[z-2][y] == 1)
				 for(int m=0;m<24;m++)
			 {
              if (TICKET_INFO[m].seatID == seat_superior[z-2][y]) //Accumulate all the price for the 1st row
				  total_price_ver[z-2]+=TICKET_INFO[m].price;
			 }
		         y++;
		   }
	}
	for( int i=0;i<6;i++)
	{
		if(i==0)
		cout<<"©¦  ©À©¤©¤©¤©¤©à";
		else if(i==5)
			{cout<<"©¤©¤©¤©¤©È"<<"          "<<"©¦";
		     cout<<endl;
		    }
		else 
	     cout<<"©¤©¤©¤©¤©à";

	}
	f++;
		}

	else if( x==4)
		{cout<<"©¦C ";
		y=0;
		for( int n=0;n<7;n++)
	{
		if(n==6)
		{
			cout<<"©¦ "<<setw(8)<<total_price_ver[z-3]<<" "<<"©¦";       
			cout<<endl;
		}
		else

		   {cout<<"©¦   "<<ticket_array[z-3][y] <<"    ";
		    if(ticket_array[z-3][y] == 1)
				 for(int m=0;m<24;m++)
			 {
              if (TICKET_INFO[m].seatID == seat_superior[z-3][y]) //Accumulate all the price for the 3rd row
				  total_price_ver[z-3]+=TICKET_INFO[m].price;
			 }
		         y++;
		   }
	}
	for( int i=0;i<6;i++)
	{
		if(i==0)
		cout<<"©¦  ©À©¤©¤©¤©¤©à";
		else if(i==5)
			{cout<<"©¤©¤©¤©¤©È"<<"          "<<"©¦";
		     cout<<endl;
		}
		else 
	     cout<<"©¤©¤©¤©¤©à";

	}
	f++;
	}

}
	
}

void salereport_economy(int ticket_array1[6][8], struct ticket_info TICKET_INFO1[48], string seat_economy[6][8] , struct details ticket_details, double occupancyrateeco)
{
	int b=0;
	int	g=0;
	int value;
	double total_price_ver[6]={0}; // variable used to store all the price in row
	double total_price_hor[8]={0}; // variable used to store all the price in column
	double sales_total;
	ofstream out_sales_eco;
	ofstream outdata;
	char ch='E';
		
	 cout<<"©°©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©´"<<endl;
	 cout<<"©¦    Total Sales - by Seat Layout                        "<<" Economy Class    ©¦"<<endl;
	 cout<<"©¦    "<<setw(20)<<right<<ticket_details.boarding_location<<"-"<<left<<setw(20)<<ticket_details.destination<<right<<setw(21)<<ticket_details.departure_date<<setw(8)<<ticket_details.departure_time<<"©¦"<<endl;
	 cout<<"©¦      01  "<<"   02 "<<"   03 "<<"   04 "<<"   05 "<<"   06 "<<"   07 "<<"   08"<<"      Sales(RM)"<<"        ©¦"<<endl;
	

	for(int a=0;a<8;a++) // All the codes following is to produce the format of output
{
	if ( a==0)
	{
		cout<<"©¦    ©°©¤©¤©Ð";
	for(int j=0;j<7;j++)
		{
			 if( j==6)
		  {
			  cout<<"©¤©¤©´"<<"                    "<<"©¦";
			  cout<<endl;
		  }
			 else

	          cout<<"©¤©¤©Ð";
		 
		}
	}
	
	else if(a==7)
	{
		b=0;
		cout<<"©¦ F ";
		for( int n=0;n<9;n++)
	{
		if(n==8)
		{
			cout<<" ©¦       "<<setw(5)<<right<< total_price_ver[a-2]<<"        "<<"©¦";
			cout<<endl;
		}
		else

		   {cout<<" ©¦"<<ticket_array1[a-2][b] <<"  ";
		    if (ticket_array1[a-2][b] == 1)
		   {
		      for(int m=0;m<24;m++)
			 {
              if (TICKET_INFO1[m].seatID == seat_economy[a-2][b]) //Accumulate all the price for the 6th row
				  total_price_ver[a-2]+=TICKET_INFO1[m].price;
			 }
		   }
		    b++;
		    
		   }
	}
	for( int i=0;i<8;i++)
	{
		if(i==0)
		cout<<"©¦    ©¸©¤©¤©Ø";
		else if(i==7)
			{cout<<"©¤©¤©¼"<<"                    "<<"©¦";
		     cout<<endl;
		}
		else 
	     cout<<"©¤©¤©Ø";

	} 
	cout<<"©¦Sales"<<setw(51)<<" "<<setw(10)<<"------"<<"        ©¦"<<endl;
	for(int g=0;g<8;g++)
	{
	   for(int i=0; i<6;i++)
	    {
		   if (ticket_array1[i][g]==1)
		  { 
			  for(int m=0;m<24;m++)
			 {
              if (TICKET_INFO1[m].seatID == seat_economy[i][g])
				  total_price_hor[g]+=TICKET_INFO1[m].price;
			 }
		   }
	    }
	  
	}
	cout<<"©¦(RM)"<<" ";
	for(int i=0;i<8;i++)
	{
	 cout<<right<<setw(5)<<total_price_hor[i]<<" ";
	}
	cout<<setw(13)<<total_price_ver[0]+ total_price_ver[1] + total_price_ver[2] + total_price_ver[3] + total_price_ver[4] + total_price_ver[5]<<"        ©¦"<<endl; // To total up all the price
	cout<<"©¦"<<setw(55)<<" "<<setw(11)<<"======"<<"        ©¦"<<endl;
	cout<<"©¸©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¼"<<endl<<endl;

	sales_total=total_price_ver[0]+ total_price_ver[1] + total_price_ver[2] + total_price_ver[3] + total_price_ver[4] + total_price_ver[5];
	
	out_sales_eco.open("Sales Date.txt" ,ios::app);

	if (!out_sales_eco)
	{
		cout<<"Error opening File!";
		exit(1);
	}

	out_sales_eco<<ticket_details.departure_date<<"|";
	out_sales_eco<<ticket_details.departure_time<<endl;

	out_sales_eco.close();

	outdata.open("Sales File.txt", ios::app);
	
	if (!out_sales_eco)
	{
		cout<<"Error opening File!";
		exit(1);
	}

	outdata<<ch<<"|";
	outdata<<ticket_details.coach<<"|";
	outdata<<ticket_details.train_code<<"|";
	outdata<<fixed<<setprecision(2)<<sales_total<<"|";
	value= seatchecking_economy(ticket_array1);
	outdata<<occupancyrateeco<<endl;
	outdata.close();
	}

	else if(a==3)
	{
		b=0;
		cout<<"©¦ C ";
			for( int n=0;n<9;n++)
	{
		if(n==8)
		{
			cout<<" ©¦       "<<setw(5)<<right<<total_price_ver[a-1]<<"        "<<"©¦";
			cout<<endl;
		}
		else

		   {cout<<" ©¦"<<ticket_array1[a-1][b] <<"  ";
		    if (ticket_array1[a-1][b] == 1)
			{	 
				for(int m=0;m<24;m++)
			 {
              if (TICKET_INFO1[m].seatID == seat_economy[a-1][b]) //Accumulate all the price for the 3rd row
				  total_price_ver[a-1]+=TICKET_INFO1[m].price;
			 }

			}	
		
		    b++;
		   }
	}
	for( int i=0;i<8;i++)
	{
		if(i==0)
		cout<<"©¦    ©À©¤©¤©Ø";
		else if(i==7)
			{cout<<"©¤©¤©È"<<"                    "<<"©¦";
		     cout<<endl;
		}
		else 
	     cout<<"©¤©¤©Ø";

	}
	g++;
	}
	else if(a==2)
	{
		b=0;
		cout<<"©¦ B ";
			for( int n=0;n<9;n++)
	{
		if(n==8)
		{
			cout<<" ©¦       "<<setw(5)<<right<<total_price_ver[a-1]<<"        "<<"©¦";
			cout<<endl;
		}
		else

		   {cout<<" ©¦"<<ticket_array1[a-1][b] <<"  ";
		    if (ticket_array1[a-1][b] == 1)
			{
				
				for(int m=0;m<24;m++)
			 {
              if (TICKET_INFO1[m].seatID == seat_economy[a-1][b]) //Accumulate all the price for the 2nd row
				  total_price_ver[a-1]+=TICKET_INFO1[m].price;
			 }
			}
		    b++;
		   }
	}
	for( int i=0;i<8;i++)
		{
		if(i==0)
		cout<<"©¦    ©À©¤©¤©à";
		else if(i==7) 
			{cout<<"©¤©¤©È"<<"                    "<<"©¦";
		     cout<<endl;
		}
		else 
	     cout<<"©¤©¤©à";

	}
		
	g++;
	}

	else if(a==4)
	{
		
		for( int n=0;n<44;n++)
	{
		if(n==43)
		{
			cout<<"©¦ "<<"                   "<<"©¦";
			cout<<endl;
		}
		else if(n==0)
			cout<<"©¦    ©¦";
		else if(n==21)
			cout<<"Aisle";
		else

		   cout<<" ";
	}
	for( int i=0;i<8;i++)
	{
		if(i==0)
		cout<<"©¦    ©À©¤©¤©Ð";
		else if(i==7)
			{cout<<"©¤©¤©È"<<"                    "<<"©¦";
		     cout<<endl;
		}
		else 
	     cout<<"©¤©¤©Ð";

	}
		}
		
	else if(a==1)
	{	
		b=0;
		cout<<"©¦ A ";
		for( int n=0;n<9;n++)
	 {
		if(n==8)
		{
			cout<<" ©¦       "<<setw(5)<<right<<total_price_ver[a-1]<<"        "<<"©¦";
			cout<<endl;
		}
		else

		   {cout<<" ©¦"<<ticket_array1[a-1][b] <<"  ";
		    if (ticket_array1[a-1][b] == 1)
		   {
		      for(int m=0;m<24;m++)
			 {
              if (TICKET_INFO1[m].seatID == seat_economy[a-1][b]) //Accumulate all the price for the 1st row
				  total_price_ver[a-1]+=TICKET_INFO1[m].price;
			 }
		   }
		    b++;
		   }
	}
	for( int i=0;i<8;i++)
	{
		if(i==0)
		cout<<"©¦    ©À©¤©¤©à";
		else if(i==7)
			{cout<<"©¤©¤©È"<<"                    "<<"©¦";
		     cout<<endl;
		}
		else 
	     cout<<"©¤©¤©à";

	}
	g++;
	
	}
		
	else if( a==5)
	{
		b=0;
		cout<<"©¦ D ";
		for( int n=0;n<9;n++)
	   {
			
		if(n==8)
		{
			cout<<" ©¦       "<<setw(5)<<right<<total_price_ver[a-2]<<"        "<<"©¦";
			cout<<endl;
		}
		else

		   {cout<<" ©¦"<<ticket_array1[a-2][b] <<"  ";
		if (ticket_array1[a-2][b] == 1)
			{
		      for(int m=0;m<24;m++)
			 {
              if (TICKET_INFO1[m].seatID == seat_economy[a-2][b]) //Accumulate all the price for the 4th row
				  total_price_ver[a-2]+=TICKET_INFO1[m].price;
			 }
		   }
		    b++;
		   }
	   }
	   for( int i=0;i<8;i++)
	 {
		if(i==0)
		cout<<"©¦    ©À©¤©¤©à";
		else if(i==7)
			{cout<<"©¤©¤©È"<<"                    "<<"©¦";
		     cout<<endl;
		}
		else 
	     cout<<"©¤©¤©à";

	}
	   g++;
	}

	else if (a==6)
	{cout<<"©¦ E ";
	 b=0;
			for( int n=0;n<9;n++)
	   {
			
		if(n==8)
		{
			cout<<" ©¦       "<<setw(5)<<right<<total_price_ver[a-2]<<"        "<<"©¦"<<endl;
		}
		else

		   {cout<<" ©¦"<<ticket_array1[a-2][b] <<"  ";
		    if (ticket_array1[a-2][b] == 1)
			{
		      for(int m=0;m<24;m++)
			 {
              if (TICKET_INFO1[m].seatID == seat_economy[a-2][b]) //Accumulate all the price for the 5th row
				  total_price_ver[a-2]+=TICKET_INFO1[m].price;
			 }
		   }
		    b++;
		   }
	   }
	   for( int i=0;i<8;i++)
	 {
		if(i==0)
		cout<<"©¦    ©À©¤©¤©à";
		else if(i==7)
			{cout<<"©¤©¤©È"<<"                    "<<"©¦";
		     cout<<endl;
		}
		else 
	     cout<<"©¤©¤©à";

	}
	   g++;
	}

	}
	

}

void logo()
{
	cout << "           |=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-|" << endl;
	cout << "           |  SSSSSS  #######    PPPPPPPP  @@@@@@@@ |" << endl;
	cout << "           | SS    SS ##     ##  PP     PP    @@    |" << endl;
	cout << "           | SS       ##     ##  PP     PP    @@    |" << endl;
	cout << "           |  SSSSSS  ##     ##  PPPPPPPP     @@    |" << endl;
	cout << "           |       SS ##     ##  PP           @@    |" << endl;
	cout << "           | SS    SS ##     ##  PP           @@    |" << endl;
	cout << "           |  SSSSSS  #######    PP           @@    |" << endl;
	cout << "           |=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-|" << endl << endl;
	cout<<"         ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    cout<<"              .......WELCOME TO SDPT RAILWAY..........\n";
    cout<<"         ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"<<endl;
}
	
int monthlysalesreport()
{
	ifstream indata;
	ifstream infile;
	ofstream outfile;
	char month[3],year[5];
	char reply;
	char ans;
	char train_code[5],departure_date[11],departure_time[6],boarding_location[11],destination[10],ch;
	node2 *newnode5, *travel5, *head5= NULL;
	node3 *newnode1,*head1=NULL,*travel1;
	int j=0;
	bool check=false;
	bool check1=false;
	char classes[2],coach[3],traincode[5];
	double sales;
	double occupancy_rate;
	string month1,time;
	double total_sale=0.0;
		
	system("CLS");
	cout<<"Please enter the month (in number): ";
	cin.get(ch);
	cin.get(month,3);
	cin.get(ch);
	
	cout<<"Please enter the year (in number): ";
	cin.get(year,5);
	cin.get(ch);

	indata.open("Sales Date.txt");

	if (!indata)
	{
		cout<<"Error opening file!";
		return -1;
	}
	
	indata.get(departure_date,11);
	indata.get(ch);
	indata.get(departure_time,6);
	indata.get(ch);

	newnode5 = new node2; 
	
	strcpy(newnode5->store_departure_date , departure_date);
	strcpy(newnode5->store_departure_time , departure_time);
	newnode5 ->next = NULL; 

	head5=newnode5;
		
	while (!indata.eof())
	{    
    indata.get(departure_date,11);
	indata>>ch;
	indata.get(departure_time,6);
	indata.get(ch);

	newnode5 = new node2;
	strcpy(newnode5->store_departure_date , departure_date);
	strcpy(newnode5->store_departure_time , departure_time);
	newnode5 ->next = NULL; 

	        travel5 = head5;      
			while (travel5 ->next != NULL)
			{
				travel5 = travel5 ->next;
			}
			travel5 ->next = newnode5;
				 
	}
	
	indata.close();

    infile.open("Sales File.txt");
	
	 if (!infile)
	{
		cout<<"Error opening file!";
		exit(1);
	}
	
	infile.get(classes,2);
    infile.get(ch);
	infile.get(coach,3);
	infile.get(ch);
	infile.get(traincode,5);
	infile.get(ch);
	infile>>sales;
	infile>>ch;
	infile>>occupancy_rate;
	infile.get(ch);

	newnode1 = new node3; 
	strcpy(newnode1->classes,classes);
	strcpy(newnode1->coach,coach);
	strcpy(newnode1->traincode,traincode);
	newnode1->sales=sales;
	newnode1->next=NULL;

	head1=newnode1;
			
	while (!infile.eof())
	{    
    infile.get(classes,2);
    infile.get(ch);
	infile.get(coach,3);
	infile.get(ch);
	infile.get(traincode,5);
	infile.get(ch);
	infile>>sales;
	infile.get(ch);
	infile>>occupancy_rate;
	infile.get(ch);
	
	newnode1 = new node3;
	strcpy(newnode1->classes,classes);
	strcpy(newnode1->coach,coach);
	strcpy(newnode1->traincode,traincode);
	newnode1->sales=sales;
	newnode1->next = NULL; 

	        travel1 = head1;      
			while (travel1->next != NULL)
			{
				travel1 = travel1->next;
			}

			travel1->next = newnode1;
	}

	infile.close();
	
	if( month[0]== '0' && month[1]== '1')
		month1="January";
	else if( month[0]== '0' && month[1]== '2')
		month1="February";
	else if( month[0]== '0' && month[1]== '3')
		month1="March";
	else if( month[0]== '0' && month[1]== '4')
		month1="April";
	else if( month[0]== '0' && month[1]== '5')
		month1="May";
	else if( month[0]== '0' && month[1]== '6')
		month1="June";
	else if( month[0]== '0' && month[1]== '7')
		month1="July";
	else if( month[0]== '0' && month[1]== '8')
		month1="August";
	else if( month[0]== '0' && month[1]== '9')
		month1="September";
	else if( month[0]== '1' && month[1]== '0')
		month1="October";
	else if( month[0]== '1' && month[1]== '1')
		month1="November";
	else if( month[0]== '1' && month[1]== '2')
	    month1="December";

	 outfile.open("MonthlySalesReport.txt", ios::app);

	if (!outfile)
	{
		cout<<"Error opening file!";
		return -1;
	}
	
	outfile<<"Monthly Sales Report"<<"\t"<<"-"<<month1<<" "<<year[0]<<year[1]<<year[2]<<year[3]<<endl;
	outfile<<"Class"<<"\t"<<"Departure Date"<<"\t"<<"Departure time"<<"\t"<<"Train Code"<<"\t"<<"Sales(RM)"<<endl;
	cout<<"Monthly Sales Report"<<"\t"<<"-"<<month1<<" "<<year[0]<<year[1]<<year[2]<<year[3]<<endl;
	cout<<"Class"<<"\t"<<"Departure Date"<<"\t"<<"Departure time"<<"\t"<<"Train Code"<<"\t"<<"Sales(RM)"<<endl;
	cout<<fixed<<setprecision(2);
		
	travel5=head5;
	for(travel1 = head1; travel1!= NULL; travel1 = travel1 ->next)
	{
		        if( travel5->store_departure_date[3] == month[0] && travel5->store_departure_date[4] == month[1])
			    {
					check=true;
				}
				else
					check=false;
			 			   
			 if(travel5->store_departure_date[6] == year[0] && travel5->store_departure_date[7] == year[1] && travel5->store_departure_date[8] == year[2] && travel5->store_departure_date[9] == year[3])
			  	{
					check1=true;
			    }
			 else
				 check1=false;
						 
	        if(travel5->store_departure_time[0]<= '1' )
		        time="AM";
			else
		        time="PM";
				
			 if( check1== true && check==true)
		  {
			  outfile<<fixed<<setprecision(2);
			  outfile<<travel1->classes<<"       ";
			  outfile<<travel5->store_departure_date<<"      ";
			  outfile<<travel5->store_departure_time<<" "<<time<<"         ";
			  outfile<<travel1->traincode<<"        ";
			  outfile<<travel1->sales<<endl;
			  cout<<travel1->classes<<"        ";
			  cout<<travel5->store_departure_date<<"     ";
			  cout<<travel5->store_departure_time<<" "<<time<<"         ";
			  cout<<travel1->traincode<<"           ";
			  cout<<travel1->sales<<endl;
			  total_sale+=travel1->sales;
		  }
			 
			 travel5=travel5->next;
	}

	cout<<"                                      Total Sales : RM "<<total_sale<<endl;
	outfile<<"                                   Total Sales : RM "<<total_sale<<endl;
	cout<<"Check another sales report? (Y/N):";
	cin>>ans;
	ans=toupper(ans);
	if(ans == 'Y')
		monthlysalesreport();

	outfile<<endl<<endl;
	outfile.close();

	cout<<"Return to Management Menu? (Y/N): ";
	cin>>reply;
	reply=toupper(reply);
	if(reply== 'Y')
		managementmenu();
	else
		exit(1);

}

void train_maintenance()
{
	int choice;

	system("CLS");
	logo();
	cout<<"                          Loading";
	cout <<".";
    Sleep( 1000 );
    cout << "."; 
    Sleep( 1000 );
    cout << "."; 
    Sleep( 1000 );
	cout<<"  Done! "<<endl;
	cout<<"             ======================================"<<endl;
	cout<<"             |                                    |"<<endl;
	cout<<"             |        1. Add Train                |"<<endl;
	cout<<"             |        2. View Train               |"<<endl;
	cout<<"             |        3. Modify Train             |"<<endl;
	cout<<"             |        4. Back to Management Menu  |"<<endl;
	cout<<"             |                                    |"<<endl;
	cout<<"             ======================================"<<endl;
	cout<<"Please select according to the number :";
	cin>>choice;

	while(choice != 1 && choice != 2 && choice != 3 && choice != 4)
	{
		cout<<"Please enter a valid input!: ";
		cin>>choice;
	}

	if (choice == 1)
	{
		system("CLS");
		addtrain();
	}
	else if(choice ==2)
	{
		system("CLS");
		viewtrain1();
	}
	else if(choice == 3)
	{
		system("CLS");
		modifytrain();
		
	}
	else
	{
		system("CLS");
		managementmenu();
	}

}

int train_occupancy_rate()
{
	char classes[2],coach[3],traincode[5],ch;
	double sales;
	double occupancy_rate,total=0.0;
	int sum=0;
	char train_code[5];
	char ans,reply;
	ifstream infile;
	ifstream data;
	node4 *travel2, *head2=NULL,*newnode2;
	bool condition=false;
	node5 *travel3, *first=NULL,*link;
	char departure_date[11],departure_time[6];

	system("CLS");

	cout<<"Enter a train code: ";
	cin.get(ch);
	cin.get(train_code,5);
	cout<<endl<<endl;

	infile.open("Sales File.txt");
	
	 if (!infile)
	{
		cout<<"Error opening file!";
		return -1;
	}

	infile.get(classes,2);
    infile.get(ch);
	infile.get(coach,3);
	infile.get(ch);
	infile.get(traincode,5);
	infile.get(ch);
	infile>>sales;
	infile>>ch;
	infile>>occupancy_rate;
	infile.get(ch);

	newnode2 = new node4; 
	strcpy(newnode2->classes,classes);
	strcpy(newnode2->coach,coach);
	strcpy(newnode2->traincode,traincode);
	newnode2->sales=sales;
	newnode2->occupancy=occupancy_rate;
	newnode2->next=NULL;

	head2=newnode2;
		
	while (!infile.eof())
	{    
    infile.get(classes,2);
    infile.get(ch);
	infile.get(coach,3);
	infile.get(ch);
	infile.get(traincode,5);
	infile.get(ch);
	infile>>sales;
	infile>>ch;
	infile>>occupancy_rate;
	infile.get(ch);
	
	newnode2 = new node4;
	strcpy(newnode2->classes,classes);
	strcpy(newnode2->coach,coach);
	strcpy(newnode2->traincode,traincode);
	newnode2->sales=sales;
	newnode2->occupancy=occupancy_rate;
	newnode2->next = NULL; 

	        travel2 = head2;      
			while (travel2->next != NULL)
			{
				travel2 = travel2->next;
			}

			travel2->next = newnode2;
	}

	infile.close();
	
	data.open("Sales Date.txt");

	if (!data)
	{
		cout<<"Error opening file!";
		return -1;
	}

	data.get(departure_date,11);
	data.get(ch);
	data.get(departure_time,6);
	data.get(ch);

	link = new node5; 
	
	strcpy(link->store_departure_date , departure_date);
	strcpy(link->store_departure_time , departure_time);
	link ->next = NULL; 

	first=link;
		
	while (!data.eof())
	{    
    data.get(departure_date,11);
	data>>ch;
	data.get(departure_time,6);
	data.get(ch);

	link = new node5;
	strcpy(link->store_departure_date , departure_date);
	strcpy(link->store_departure_time , departure_time);
	link ->next = NULL; 

	        travel3 = first;      
			while (travel3 ->next != NULL)
			{
				travel3 = travel3->next;
			}
			travel3->next = link;
	}
	
	data.close();
	int n=0;
	travel3= first;
	for(travel2 = head2; travel2!= NULL; travel2 = travel2->next)
	{
		 if(strcmp(train_code,travel2->traincode)==0)
		{
			if(n==0)
			{
			
			cout<<"                Train Code: "<<travel2->traincode<<endl;
			cout<<"                Departure Date: "<<travel3->store_departure_date<<endl;
			cout<<"                Departure Time: "<<travel3->store_departure_time<<endl;
			cout<<"            Class                   "<<"Occupancy (%)"<<endl;
			}
			cout<<fixed<<setprecision(2);
			cout<<"            "<<travel2->classes<<"           ";
			cout<<"            "<<travel2->occupancy<<endl;
			condition=true;
			total+= travel2->occupancy;
			sum++;
			n++;
		}
		travel3=travel3->next;
	}
	cout<<endl<<endl;
	if(condition == true)
		cout<<"                      Average = "<<total/sum<<endl<<endl<<"\n";
	
	if( condition == false)
	{
		cout<<"The train code entered has no record!"<<endl<<endl;
	}

	cout<<"Enter another train code? (Y/N): ";
	cin>>reply;
	reply=toupper(reply);
	if(reply=='Y')
		train_occupancy_rate();
	else
	{
	cout<<"Back to Management Menu? (Y/N): ";
	cin>>ans;
	ans=toupper(ans);
	if(ans== 'Y')
		managementmenu();
	else
		exit(1);
	}
}

double superiorclass(int ticket_array[4][6])
{
	int z=0;
	int	y=0;
	int	seats_available[4]={0}; //variable used to store the seats available in each row
	double	total_seat_available; // variable used to store total available seat
	
	int	f=0;
	

	 cout<<"                   Seats Occupancy - Superior Class"<<endl<<endl;
	 cout<<endl;
	 
	cout<<"        01    "<<"    02    "<<"    03    "<<"    04    "<<"    05    "<<"    06    "<<"Seats available"<<endl;
	
for(int x=0;x<6;x++)
{
	z++;
	if ( x==0)
	{
		
		cout<<"   ©°©¤©¤©¤©¤©Ð";
	for(int j=0;j<5;j++)
		{
			 if( j==4)
		  {
			  cout<<"©¤©¤©¤©¤©´";
			  cout<<endl;
		  }
			 else

	          cout<<"©¤©¤©¤©¤©Ð";
		 
		}
	}

	else if(x==5)
	{
		y=0;
		cout<<" D ";
			for( int n=0;n<7;n++)
	{
		if(n==6)
		{
			cout<<"©¦ "<<"      "<<seats_available[f]; // To display the total seats available in the same row
			cout<<endl;
		}
		else

		   {cout<<"©¦   "<<ticket_array[z-3][y] <<"    "; 
		    if(ticket_array[z-3][y] == 0) // To total up the seats available in the same row
				seats_available[f]++;
		    y++;
		   }
	}
	for( int i=0;i<6;i++)
	{
		if(i==0)
		cout<<"   ©¸©¤©¤©¤©¤©Ø";
		else if(i==5)
			{cout<<"©¤©¤©¤©¤©¼";
		     cout<<endl<<endl;
		}
		else 
	     cout<<"©¤©¤©¤©¤©Ø";

	}
	total_seat_available= seats_available[0]+seats_available[1]+seats_available[2]+seats_available[3]; // to total up all the seats available in superior class
	double occupancy_rate_superior=100-(total_seat_available*100/24);
	cout<<"Occupancy Rate = "<<setprecision(1)<<fixed<<occupancy_rate_superior<<"%"<<"                   "<<"Total Seats available: "<<setprecision(0)<<fixed<<total_seat_available<<endl<<endl;
	                                                                                                        //to display total seats available
	return occupancy_rate_superior;
													 
	}
	else if(x==2)
	{
		y=0;
		cout<<" B ";
			for( int n=0;n<7;n++)
	{
		if(n==6)
		{
			cout<<"©¦ "<<"      "<<seats_available[f]; // To display the total seats available in the same row
			cout<<endl;
		}
		else

		   {cout<<"©¦   "<<ticket_array[z-2][y] <<"    ";
		    if(ticket_array[z-2][y] == 0) // To total up the seats available in the same row
				seats_available[f]++;
		    y++;
		   }
	}
	for( int i=0;i<6;i++)
	{
		if(i==0)
		cout<<"   ©À©¤©¤©¤©¤©Ø";
		else if(i==5)
			{cout<<"©¤©¤©¤©¤©È";
		     cout<<endl;
		}
		else 
	     cout<<"©¤©¤©¤©¤©Ø";

	}
	f++;
	}

	else if(x==3)
	{
			for( int n=0;n<56;n++)
	{
		if(n==55)
		{
			cout<<"©¦ ";
			cout<<endl;
		}
		else if(n==0)
			cout<<"   ©¦";
		else if(n==28)
			cout<<"Aisle";
		else

		   cout<<" ";
	}
	for( int i=0;i<6;i++)
	{
		if(i==0)
		cout<<"   ©À©¤©¤©¤©¤©Ð";
		else if(i==5)
			{cout<<"©¤©¤©¤©¤©È";
		     cout<<endl;
		}
		else 
	     cout<<"©¤©¤©¤©¤©Ð";

	}
		}
		
	else if(x==1)
			{cout<<" A ";
		y=0;
			for( int n=0;n<7;n++)
	{
		
		
		if(n==6)
		{
			cout<<"©¦ "<<"      "<<seats_available[f];    // To display the total seats available in the same row    
			cout<<endl;
		}
		else

		   {cout<<"©¦   "<<ticket_array[z-2][y] <<"    ";
		    if(ticket_array[z-2][y] == 0) // To total up the seats available in the same row
				seats_available[f]++;
		         y++;
		   }
	}
	for( int i=0;i<6;i++)
	{
		if(i==0)
		cout<<"   ©À©¤©¤©¤©¤©à";
		else if(i==5)
			{cout<<"©¤©¤©¤©¤©È";
		     cout<<endl;
		}
		else 
	     cout<<"©¤©¤©¤©¤©à";

	}
	f++;
		}

	else if( x==4)
			{cout<<" C ";
		y=0;
		for( int n=0;n<7;n++)
	{
		if(n==6)
		{
			cout<<"©¦ "<<"      "<<seats_available[f];    // To display the total seats available in the same row    
			cout<<endl;
		}
		else

		   {cout<<"©¦   "<<ticket_array[z-3][y] <<"    ";
		    if(ticket_array[z-3][y] == 0) // To total up the seats available in the same row
				seats_available[f]++;
		         y++;
		   }
	}
	for( int i=0;i<6;i++)
	{
		if(i==0)
		cout<<"   ©À©¤©¤©¤©¤©à";
		else if(i==5)
			{cout<<"©¤©¤©¤©¤©È";
		     cout<<endl;
		}
		else 
	     cout<<"©¤©¤©¤©¤©à";

	}
	f++;
	}

}
	
}

double economyclass(int ticket_array1[6][8])
{
	int b=0;
	int	seats_available1[6]={0}; //variable used to store the seats available in each row for economy class
	int	g=0;
	double total_seat_available1; // variable used to store total available seat
	
	
	 cout<<"                Seat Occupancy - Economy"<<endl<<endl;
	 cout<<"      01  "<<"  02  "<<"  03  "<<"  04  "<<"  05  "<<"  06  "<<"  07  "<<"  08 "<<"    Seats available"<<endl;

	for(int a=0;a<8;a++)
{
	if ( a==0)
	{
		cout<<"   ©°©¤©¤©Ð";
	for(int j=0;j<7;j++)
		{
			 if( j==6)
		  {
			  cout<<"©¤©¤©´";
			  cout<<endl;
		  }
			 else

	          cout<<"©¤©¤©Ð";
		 
		}
	}
	
	else if(a==7)
	{
		b=0;
		cout<<" F ";
		for( int n=0;n<9;n++)
	{
		if(n==8)
		{
			cout<<"©¦       "<<seats_available1[g]; // To display the total seats available in the same row
			cout<<endl;
		}
		else

		   {cout<<"©¦ "<<ticket_array1[a-2][b] <<"  ";
		    if (ticket_array1[a-2][b] == 0) // To total up the seats available in the same row
				seats_available1[g]++;
		    b++;
		    
		   }
	}
	for( int i=0;i<8;i++)
	{
		if(i==0)
		cout<<"   ©¸©¤©¤©Ø";
		else if(i==7)
			{cout<<"©¤©¤©¼";
		     cout<<endl;
		}
		else 
	     cout<<"©¤©¤©Ø";

	}
	}

	else if(a==3)
	{
		b=0;
		cout<<" C ";
			for( int n=0;n<9;n++)
	{
		if(n==8)
		{
			cout<<"©¦       "<<seats_available1[g]; // To display the total seats available in the same row
			cout<<endl;
		}
		else

		   {cout<<"©¦ "<<ticket_array1[a-1][b] <<"  ";
		    if (ticket_array1[a-1][b] == 0) // To total up the seats available in the same row
				seats_available1[g]++;
		    b++;
		   }
	}
	for( int i=0;i<8;i++)
	{
		if(i==0)
		cout<<"   ©À©¤©¤©Ø";
		else if(i==7)
			{cout<<"©¤©¤©È";
		     cout<<endl;
		}
		else 
	     cout<<"©¤©¤©Ø";

	}
	g++;
	}
	else if(a==2)
	{
		b=0;
		cout<<" B ";
			for( int n=0;n<9;n++)
	{
		if(n==8)
		{
			cout<<"©¦       "<<seats_available1[g]; // To display the total seats available in the same row
			cout<<endl;
		}
		else

		   {cout<<"©¦ "<<ticket_array1[a-1][b] <<"  ";
		    if (ticket_array1[a-1][b] == 0) // To total up the seats available in the same row
				seats_available1[g]++;
		    b++;
		   }
	}
	for( int i=0;i<8;i++)
		{
		if(i==0)
		cout<<"   ©À©¤©¤©à";
		else if(i==7)
			{cout<<"©¤©¤©È";
		     cout<<endl;
		}
		else 
	     cout<<"©¤©¤©à";

	}
		
	g++;
	}

	else if(a==4)
	{
		
		for( int n=0;n<44;n++)
	{
		if(n==43)
		{
			cout<<"©¦ ";
			cout<<endl;
		}
		else if(n==0)
			cout<<"   ©¦";
		else if(n==21)
			cout<<"Aisle";
		else

		   cout<<" ";
	}
	for( int i=0;i<8;i++)
	{
		if(i==0)
		cout<<"   ©À©¤©¤©Ð";
		else if(i==7)
			{cout<<"©¤©¤©È";
		     cout<<endl;
		}
		else 
	     cout<<"©¤©¤©Ð";

	}
		}
		
	else if(a==1)
	{	
		b=0;
		cout<<" A ";
		for( int n=0;n<9;n++)
	 {
		if(n==8)
		{
			cout<<"©¦       "<<seats_available1[g]; // To display the total seats available in the same row
			cout<<endl;
		}
		else

		   {cout<<"©¦ "<<ticket_array1[a-1][b] <<"  ";
		    if (ticket_array1[a-1][b] == 0) // To total up the seats available in the same row
				seats_available1[g]++;
		    b++;
		   }
	}
	for( int i=0;i<8;i++)
	{
		if(i==0)
		cout<<"   ©À©¤©¤©à";
		else if(i==7)
			{cout<<"©¤©¤©È";
		     cout<<endl;
		}
		else 
	     cout<<"©¤©¤©à";

	}
	g++;
	
	}
		
	else if( a==5)
	{
		b=0;
		cout<<" D ";
		for( int n=0;n<9;n++)
	   {
			
		if(n==8)
		{
			cout<<"©¦       "<<seats_available1[g]; // To display the total seats available in the same row
			cout<<endl;
		}
		else

		   {cout<<"©¦ "<<ticket_array1[a-2][b] <<"  ";
		if (ticket_array1[a-2][b] == 0) // To total up the seats available in the same row
				seats_available1[g]++;
		    b++;
		   }
	   }
	   for( int i=0;i<8;i++)
	 {
		if(i==0)
		cout<<"   ©À©¤©¤©à";
		else if(i==7)
			{cout<<"©¤©¤©È";
		     cout<<endl;
		}
		else 
	     cout<<"©¤©¤©à";

	}
	   g++;
	}

	else if (a==6)
	{cout<<" E ";
	 b=0;
			for( int n=0;n<9;n++)
	   {
			
		if(n==8)
		{
			cout<<"©¦       "<<seats_available1[g]; // To display the total seats available in the same row
			cout<<endl;
		}
		else

		   {cout<<"©¦ "<<ticket_array1[a-2][b] <<"  ";
		    if (ticket_array1[a-2][b] == 0) // To total up the seats available in the same row
				seats_available1[g]++;
		    b++;
		   }
	   }
	   for( int i=0;i<8;i++)
	 {
		if(i==0)
		cout<<"   ©À©¤©¤©à";
		else if(i==7)
			{cout<<"©¤©¤©È";
		     cout<<endl;
		}
		else 
	     cout<<"©¤©¤©à";

	}
	   g++;
	}

	}
	total_seat_available1= seats_available1[0]+seats_available1[1]+seats_available1[2]+seats_available1[3]+seats_available1[4]+seats_available1[5]; //to display the total seats available in economy class
	double occupancy_rate_eco=100-(total_seat_available1*100/48);
	cout<<"Occupancy Rate = "<<setprecision(1)<<occupancy_rate_eco<<"%"<<"                   "<<"Total Seats available: "<<setprecision(0)<<fixed<<total_seat_available1<<endl<<endl;
	                                                                                                                   // to display the total seats available
	return occupancy_rate_eco;
												    
}

void endmessage()
{
	cout<<endl;
	cout<<"                          The ticket sales today has ended"<<endl<<endl;

	cout<<" TTTTTTTT  HH  HH      A      NN   NN KK    K    YYY   YYY  UUUUUU  OO    OO"<<endl;
	cout<<"   TTT     HH  HH     AAA     NNN  NN KK  KK       YY  YY  UU    UU OO    OO"<<endl;
	cout<<"   TTT     HHHHHH    AAAAA    NNNNNNN KKK            YY    UU    UU OO    OO "<<endl;
	cout<<"   TTT     HH  HH   AA A AA   NN  NNN KK  KK         YY    UU    UU OO    OO"<<endl;
	cout<<"   TTT     HH  HH  AA     AA  NN   NN KK    K        YY      UUUUU    OOOO"<<endl<<endl;
	
}

int seatchecking_superior(int ticket_array[4][6])
{
	int	seat_available=0;

	for(int i=0;i<4;i++)
{
	for(int j=0;j<6;j++)
	{
		if(ticket_array[i][j]==0) //to check for the seats available
			seat_available++;
	}
}
	if (seat_available ==0)
	{
		return 1;
	}
	else
		return seat_available;
}

int seatchecking_economy(int ticket_array1[6][8])
{
	int	seat_available=0;

	for(int i=0;i<6;i++)
{
	for(int j=0;j<8;j++)
	{
		if(ticket_array1[i][j]==0) //to check for the seats available
			seat_available++;
	}
}
	if (seat_available ==0)
	{
		return 1;
	}
	else
		return seat_available;
	
}

int ticket_selling()
{
	int ticket_number=0001; 
	int number=1; //variable used to store the number of customer, initialize to 1
	int	b=0;
	int	seat_wanted; //variable used to store the seat wanted by customer
	int seat; // variable used to store the value return in function seatchecking_superior 
	int j=0;
	int z=0;
	int ticket_type[48];
	char ans; // variable used to store the user response for class
	char ch; // variable used to store the value for toupper case of ans
	char ch1[24]; // variable used to store the character 'A' or 'C' for superior class
	char ch2[48]; // variable used to store the character 'A' or 'C' for economy class
	char get_train_code[5];
	ticket_info TICKET_INFO1[48]; //structure array that used to all the ticket information for economy class
	ticket_info TICKET_INFO[24]; //structure array that used to all the ticket information for superior class
	details ticket_details; //strucutre to store the ticket details
	int ticket_array1[6][8]={0}; // array that represent the seats in economy class, initialize with all zero
	int ticket_array[4][6]= {0}; // array that represent the seats in superior class, initialize with all zero
	double fees; 
	double cash_paid; // variable to get the input of the cash paid by customer
	double total_fees_eco[48]={0}; //variable to store the amount of money needed to buy the tickets wanted by customer
	double tax;
	int u=0;
	int o=0;
	bool seat_verification; // checking for seat ID is invalid or not
	int seat1; //  variable used to store the value return in function seatchecking_economy
	bool seat_avaibility_superior[4][6]={
		                                  {true,true,true,true,true,true}, /* check for the seats avaibility for superior class,initialize with all true*/
										  {true,true,true,true,true,true},
										  {true,true,true,true,true,true},
										  {true,true,true,true,true,true}
	                                     };
	bool seat_avaibility_economy[6][8]={
		                                  {true,true,true,true,true,true,true,true}, /* check for the seats avaibility for economy class,initialize with all true*/
										  {true,true,true,true,true,true,true,true},
										  {true,true,true,true,true,true,true,true},
										  {true,true,true,true,true,true,true,true},
										  {true,true,true,true,true,true,true,true},
										  {true,true,true,true,true,true,true,true}
	                                    };
	string Class; 
	string seat_superior[4][6]={
		                         {"A01","A02","A03","A04","A05","A06"}, 
								 {"B01","B02","B03","B04","B05","B06"},
								 {"C01","C02","C03","C04","C05","C06"},
								 {"D01","D02","D03","D04","D05","D06"}
	                           };
	string seat_economy[6][8]={
		                         {"A01","A02","A03","A04","A05","A06","A07","A08"},
								 {"B01","B02","B03","B04","B05","B06","B07","B08"},
								 {"C01","C02","C03","C04","C05","C06","C07","C08"},
								 {"D01","D02","D03","D04","D05","D06","D07","D08"},
								 {"E01","E02","E03","E04","E05","E06","E07","E08"},
								 {"F01","F02","F03","F04","F05","F06","F07","F08"}
	                           };
	ifstream indata;
	salesnode *travel, *newnode,*head= NULL;
	char departure_date[11],departure_time[6],boarding_location[11],destination[10];
	char train_code[5];
	bool checking;
	double total_fees_superior[24]={0};
	double total_fees=0;
	double occupancyratesuperior;
	double occupancyrateeco;
	char yes_no;

	logo();
	cout<<"Enter the train details:"<<endl;
	cout<<"======================= "<<endl<<endl;
	cout<<"Train Code: ";
	cin.ignore();
	cin.getline(get_train_code,5);

	indata.open("Train File.txt");
	if (!indata)
	{
		cout<<"Error opening file!";
		exit(1);
	}
		
	indata.get(train_code,5);
	indata.get(ch);
	indata.get(departure_date,11);
	indata.get(ch);
	indata.get(departure_time,6);
	indata.get(ch);
	indata.get(boarding_location,11);
	indata.get(ch);
	indata.get(destination,10);
	indata.get(ch);

	newnode = new salesnode; 
	strcpy(newnode->store_train_code , train_code);
	strcpy(newnode->store_departure_date , departure_date);
	strcpy(newnode->store_departure_time , departure_time);
	strcpy(newnode->store_boarding_location , boarding_location);
	strcpy(newnode->store_destination , destination);
	newnode ->next = NULL; 

	head=newnode;

	
	while (!indata.eof())
	{   
		indata.get(train_code,5);
	    indata.get(ch);
	    indata.get(departure_date,11);
	    indata.get(ch);
	    indata.get(departure_time,6);
	    indata.get(ch);
	    indata.get(boarding_location,11);
	    indata.get(ch);
	    indata.get(destination,10);
	    indata.get(ch);

		newnode = new salesnode; 
	    strcpy(newnode->store_train_code , train_code);
	    strcpy(newnode->store_departure_date , departure_date);
	    strcpy(newnode->store_departure_time , departure_time);
	    strcpy(newnode->store_boarding_location , boarding_location);
	    strcpy(newnode->store_destination , destination);
	    newnode ->next = NULL; 


			travel = head;      
			while (travel ->next != NULL)
			{
				travel = travel ->next;
			}
			travel ->next = newnode;
			
	}

	indata.close();

	  for(travel = head; travel != NULL; travel = travel ->next)
	  {
		  if(strcmp(travel->store_train_code , get_train_code)==0)
		  {
			  strcpy(ticket_details.boarding_location,travel->store_boarding_location);
			  ticket_details.departure_date=travel->store_departure_date;
			  ticket_details.departure_time=travel->store_departure_time;
			  ticket_details.destination=travel->store_destination;
			  strcpy(ticket_details.train_code,travel->store_train_code);
				  
			 checking = true;
		  }
	  }
    
	  while (checking!=true)
	{
		cout<<"Please re-enter a valid Train Code! : ";
	    cin.getline(get_train_code,5);
		  for(travel = head; travel != NULL; travel = travel ->next)
	  {
		  if(strcmp(travel->store_train_code , get_train_code)==0)
		  {
			  strcpy(ticket_details.boarding_location,travel->store_boarding_location);
			  ticket_details.departure_date=travel->store_departure_date;
			  ticket_details.departure_time=travel->store_departure_time;
			  ticket_details.destination=travel->store_destination;
			  strcpy(ticket_details.train_code,travel->store_train_code);
				  
			 checking = true;
		  }
	  }
	}
	         
	
	cout<<"Arrive date (dd/mm/yyyy): ";
	cin>>ticket_details.arrive_date;	
	cout<<"Arrive time (24 hour format): ";
	cin>>ticket_details.arrive_time;
	cin.ignore();
	cout<<"Coach : ";
	cin>>ticket_details.coach;
	cout<<endl;
	system("CLS");

	do{
		total_fees=0;
		seat=seatchecking_superior(ticket_array);  // check for the seats available for superior class
		seat1=seatchecking_economy(ticket_array1);  // check for the seats available for economy class

		if ( seat ==1)   //condition for this loop to break, if both superior and economy has no seats available
		{
			if(seat1==1)
				break;
		}
		
 	fees=0; // set the fees to zero, so that previous loop value of fees will be overwrite

	if ( seat == 1)
	 cout<<"Train available: Economy "<<endl;
	else if( seat1 == 1)
	 cout<<"Train available: Superior "<<endl;
	else
	 cout<<"Train available: Superior / Economy "<<endl;

	cout<<"Customer no."<<number<<endl;
	if ( seat!=1 && seat1!=1)  // check to see whether seat ID input is valid or not
	{
	 cout<<"Please select the classes : Superior or Economy"<<endl;
	 cout<<"Press S for Superior class, E for Economy class"<<endl;
	 cin>>ans;
	 ch = toupper(ans);
	while (ch != 'S' && ch!= 'E')
	{
		cout<<"Please re-enter a valid input! ";
	    cin>>ans;
	    ch = toupper(ans);
	}
	if( ch == 'S' )                      // display the seat occupancy according to user input
		{
			occupancyratesuperior=superiorclass(ticket_array);
	    }
	else
	{
		   occupancyrateeco=economyclass(ticket_array1);
	}
	}

	else if( seat !=1)
	{
		cout<<"All tickets for economy class are sold out! only superior class left"<<endl<<endl;
		superiorclass(ticket_array);
		ch ='S';
	}
	else if( seat1 !=1)
	{
		cout<<"All tickets for superior class are sold out! only economy class left"<<endl;
		economyclass(ticket_array1);
		ch='E';
	}

	
	cout<<"How many seats required? If want exit the program, enter -1: "; // prompt user to input seat required
    cin>>seat_wanted;
	
	
	if (ch == 'S')     // check the seat wanted by user is valid or not for superior class
       {
		   if ( seat_wanted>seat || seat_wanted ==0)
	   {
		while ( seat_wanted>seat || seat_wanted ==0)
		{
		while( seat_wanted==0)
          { cout<<"Please re-enter a valid seat required! :";
            cin>>seat_wanted;
          }

		while( seat_wanted>seat)
          { cout<<"Not enough seats! "<<"Only "<<seat<<" seats available! "<<"Please re-enter seat required :";
            cin>>seat_wanted;
          }
		}
	}

	else if( seat_wanted == -1) 
	{
		break;
		cout<<endl<<endl;
	}
		}
	   
	else       // check the seat wanted by user is valid or not for economy class
		{
			     
	  if ( seat_wanted>seat1 || seat_wanted ==0)
	{
		while ( seat_wanted>seat1 || seat_wanted ==0)
		{
		while( seat_wanted==0)
          { cout<<"Please re-enter a valid seat required! :";
            cin>>seat_wanted;
          }

		while( seat_wanted>seat1)
          { cout<<"Not enough seats! "<<"Only "<<seat<<" seats available! "<<"Please re-enter seat required :";
            cin>>seat_wanted;
          }
		}
	}

	else if( seat_wanted == -1)
	{
		break;
		cout<<endl<<endl;
	}
	}
	

 for(int d=0;d<seat_wanted;d++)
{
	u++;
	cin.ignore();
	cout<<"Seat"<<d+1<<endl;
	cout<<"Seat ID : ";

	if ( ch == 'S')      // To verify the user input for seat ID is valid or not for superior class
	{
		seat_verification= false;
		cin>>TICKET_INFO[d+o].seatID;
		do
	 { 
	  
	for( int i=0;i<4;i++)
	{
		for(int n=0;n<6;n++)
	  {
		  if (TICKET_INFO[d+o].seatID == seat_superior[i][n])
			 seat_verification= true;
	  }

	}
	if (seat_verification!= true)
		{
			cout<<"Please re-enter a valid seat ID: ";
			cin>>TICKET_INFO[d+o].seatID;
	    } 
	    
	 }while (seat_verification!= true);
	}

	else  // To verify the user input for seat ID is valid or not for economy class
	{
		seat_verification= false;
		cin>>TICKET_INFO1[d+o].seatID;
		do
	{
	  
	for( int i=0;i<6;i++)
	{
		for(int h=0;h<8;h++)
	  {
		  if (TICKET_INFO1[d+o].seatID == seat_economy[i][h])
			  seat_verification= true;
	  }

	}
	if (seat_verification!= true)
		{
			cout<<"Please re-enter a valid seat ID: ";
			cin>>TICKET_INFO1[d+o].seatID;
	    } 
	    
	}while (seat_verification!= true);
	}

		
	if (ch == 'S')  // check to see whether seat ID is still available or not for superior class
	{
		z=0;
		for( int i=0;i<4;i++)
	    {
		  for(int n=0;n<6;n++)
	     {
		  if (TICKET_INFO[d+o].seatID == seat_superior[i][n])
		  {

			   if(seat_avaibility_superior[i][n] == false)
			  	  z=1;
		  }
		 }
		}

		while (z==1)
		{
			z=0;
			cout<<"Seat already occupied! Please choose another seat: ";
		    cin>>TICKET_INFO[d+o].seatID;
				
			seat_verification= false;
				
		do
	 { 
	  
	for( int i=0;i<4;i++)
	{
		for(int n=0;n<6;n++)
	  {
		  if (TICKET_INFO[d+o].seatID == seat_superior[i][n])
			 seat_verification= true;
	  }

	}
	if (seat_verification!= true)
		{
			cout<<"Please re-enter a valid seat ID: ";
			cin>>TICKET_INFO[d+o].seatID;
	    } 
	    
	 }while (seat_verification!= true);

	  for( int i=0;i<4;i++)
	    {
		  for(int n=0;n<6;n++)
	     {
		  if (TICKET_INFO[d+o].seatID == seat_superior[i][n])
		  {
			  if(seat_avaibility_superior[i][n] == false)
			      z=1;
		   }
		  }
		}

	 }

	}

	
	else    // check to see whether seat ID is still available or not for economy class
	{
		z=0;
		for( int i=0;i<6;i++)
	    {
		  for(int n=0;n<8;n++)
	     {
		  if (TICKET_INFO1[d+o].seatID == seat_economy[i][n])
		  {

			   if(seat_avaibility_economy[i][n] == false)
			  	  z=1;
		  }
		 }
		}

		while (z==1)
		{
			z=0;
			cout<<"Seat already occupied! Please choose another seat: ";
		    cin>>TICKET_INFO1[d+o].seatID;

			seat_verification= false;
		do
	{
	  
	for( int i=0;i<6;i++)
	{
		for(int h=0;h<8;h++)
	  {
		  if (TICKET_INFO1[d+o].seatID == seat_economy[i][h])
			  seat_verification= true;
	  }

	}
	if (seat_verification!= true)
		{
			cout<<"Please re-enter a valid seat ID: ";
			cin>>TICKET_INFO1[d+o].seatID;
	    } 
	    
	}while (seat_verification!= true);

		 for( int i=0;i<6;i++)
	    {
		  for(int n=0;n<8;n++)
	     {
		  if (TICKET_INFO1[d+o].seatID == seat_economy[i][n])
		  {
			  if(seat_avaibility_economy[i][n] == false)
			      z=1;
		   }
		  }
		}
	}

	}


	if (ch == 'S')  // update the seats occupancy for superior class
	{
		for(int h=0;h<4;h++)
		{
			for(int i=0;i<6;i++)
			{
				if (TICKET_INFO[d+o].seatID == seat_superior[h][i])
					{
						ticket_array[h][i]++;
				        seat_avaibility_superior[h][i]=false;
				   }
			}
		}
	}
	else  // update the seats occupancy for economy class
	{
		for(int h=0;h<6;h++)
		{
			for(int i=0;i<8;i++)
			{
				if (TICKET_INFO1[d+o].seatID== seat_economy[h][i])
				{
					ticket_array1[h][i]++;
				    seat_avaibility_economy[h][i]=false;
				}
			}
		}
	}

	cout<<"Ticket Type (1-way/2-way) Select 1 for 1 way, 2 for 2 way : ";
	cin>>ticket_type[d+o];
	while (ticket_type[d+o] != 1 && ticket_type[d+o]!=2)
	{
		cout<<"Please re-enter ticket_type! :";
		cin>>ticket_type[d+o];
	}

	cout<<"Adult(A)/Child(C)/Senior Citizen(S): ";
	if ( ch == 'S')   // check whether the user input is valid or not
	{
		cin>>TICKET_INFO[d+o].adultorchild;
	    ch1[d+o] = toupper(TICKET_INFO[d+o].adultorchild);
		while (ch1[d+o] !='A' && ch1[d+o]!='C' && ch1[d+o]!='S')
		{
			cout<<"Please re-enter a valid input! :";
			cin>>TICKET_INFO[d+o].adultorchild;
	        ch1[d+o] = toupper(TICKET_INFO[d+o].adultorchild);
	    }
		if(ch1[d+o] == 'A')
		 {	
			 if(ticket_type[d+o] ==1)
			 {
			   tax = ceil(45.0*0.05*10)/10;
			   fees= (45.0+tax);
			   total_fees_superior[d+o]+=fees; 
			   TICKET_INFO[d+o].price=fees;
			   TICKET_INFO[d+o].tax=tax;
			   TICKET_INFO[d+o].type=ticket_type[d+o];
			 } 
			 else 
			{
				tax= (45.0*2*0.05);
				fees= ((45.0*2)+tax);
				total_fees_superior[d+o]+=fees;
				TICKET_INFO[d+o].price=fees;
				TICKET_INFO[d+o].tax=tax;
				TICKET_INFO[d+o].type=ticket_type[d+o];
			 }
					// to calculate the fees needed for tickets
			
	     }
		else if (ch1[d+o] == 'C')
		 {
			 if( ticket_type[d+o] ==1)
			 {
			  tax= ceil(22.5*10*0.03)/10;
              fees=(22.5+tax);
			  total_fees_superior[d+o]+=fees; // to calculate the fees needed for tickets
			  TICKET_INFO[d+o].price=fees;
			  TICKET_INFO[d+o].tax=tax;
			  TICKET_INFO[d+o].type=ticket_type[d+o];
	         }
			 else
			 {
			   tax= ceil(22.5*2*10*0.03)/10;
			   fees=(22.5*2)+tax;
			   total_fees_superior[d+o]+=fees; 
			   TICKET_INFO[d+o].price=fees;
			   TICKET_INFO[d+o].tax=tax;
			   TICKET_INFO[d+o].type=ticket_type[d+o];
			 }
	     }
		else
		{
			if(ticket_type[d+o]==1)
			{
			  fees=45.0;
			  total_fees_superior[d+o]+=fees;
			  TICKET_INFO[d+o].price=fees;
			  TICKET_INFO[d+o].tax=0.0;
			  TICKET_INFO[d+o].type=ticket_type[d+o];
			}
			else
			{
			  fees=45.0*2;
			  total_fees_superior[d+o]+=fees;
			  TICKET_INFO[d+o].price=fees;
			  TICKET_INFO[d+o].tax=0.0;
			  TICKET_INFO[d+o].type=ticket_type[d+o];
			}

		}
	
	}
	else
	{
		cin>>TICKET_INFO1[d+o].adultorchild;
	    ch2[d+o] = toupper(TICKET_INFO1[d+o].adultorchild);
		while (ch2[d+o] !='A' && ch2[d+o]!='C' && ch2[d+o]!='S')
		{
			cout<<"Please re-enter a valid input! :";
			cin>>TICKET_INFO1[d+o].adultorchild;
	        ch2[d+o] = toupper(TICKET_INFO1[d+o].adultorchild);
		}
			if(ch2[d+o] == 'A')
		{
			if(ticket_type[d+o]==1)
			{
			  tax= ceil(25.0*0.05*10)/10;
			  fees = 25.0+tax;
			  total_fees_eco[d+o]+=fees; // to calculate the fees needed for tickets
			  TICKET_INFO1[d+o].price=fees;
			  TICKET_INFO1[d+o].tax=tax;
			  TICKET_INFO1[d+o].type=ticket_type[d+o];
		    }
			else
			{
			  tax = (25.0*2*0.05);
			  fees = (25.0*2)+tax;
			  total_fees_eco[d+o]+=fees; // to calculate the fees needed for tickets
			  TICKET_INFO1[d+o].price=fees;
			  TICKET_INFO1[d+o].tax=tax;
			  TICKET_INFO1[d+o].type=ticket_type[d+o];
		    }

		}
		 else if (ch2[d+o] == 'C')
		{
			if(ticket_type[d+o]==1)
			{
			  tax= ceil(12.5*10*0.03)/10;
			  fees =  12.5+tax;
			  total_fees_eco[d+o]+=fees; // to calculate the fees needed for tickets
			  TICKET_INFO1[d+o].price=fees;
			  TICKET_INFO1[d+o].tax=tax;
			  TICKET_INFO1[d+o].type=ticket_type[d+o];
	        }
			else
			{
			  tax = ceil(12.5*2*10*0.03)/10;
			  fees = (12.5*2)+tax;
			  total_fees_eco[d+o]+=fees; // to calculate the fees needed for tickets
			  TICKET_INFO1[d+o].price=fees;
			  TICKET_INFO1[d+o].tax=tax;
			  TICKET_INFO1[d+o].type=ticket_type[d+o];
	        }

	    
	    }
		 else
		 {
			 if(ticket_type[d+o]==1)
			 {
			   fees=25.0;
			   total_fees_eco[d+o]+=fees;
			   TICKET_INFO1[d+o].price=fees;
			   TICKET_INFO1[d+o].tax=0.0;
			   TICKET_INFO1[d+o].type=ticket_type[d+o];
			 }
			 else
			 {
				 fees=25.0*2;
				 total_fees_eco[d+o]+=fees;
			     TICKET_INFO1[d+o].price=fees;
				 TICKET_INFO1[d+o].tax=0.0;
				 TICKET_INFO1[d+o].type=ticket_type[d+o];
			 }

		}
	

 }

 if(ch == 'S')
	total_fees+=total_fees_superior[d+o];
else
	total_fees+=total_fees_eco[d+o];
}


cout<<fixed<<setprecision(2)<<"Total amount to pay: RM"<<total_fees<<endl;
cout<<"Cash Paid: RM";
cin>>cash_paid;
while (cash_paid<total_fees)  //validation for cash paid
{
	cout<<"Not enough money! Please enter a larger amount: RM";
	cin>>cash_paid;
}
cout<<"Change: RM"<<cash_paid-total_fees<<endl<<endl;

if (ch == 'S')
{
	ticket_details.classes='S';
    Class= "(Superior)";
}
		
else
	{
		ticket_details.classes='E';
		Class= "(Economy)";
}






for(int e=0;e<seat_wanted;e++)   //output all the ticket bought in the format given
{
	
    cout<<"©°©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©´"<<endl;
    cout<<"©¦ ----- SDPT Train Ticket-----"<<"                                             ©¦"<<endl;
	cout<<setw(21)<<setfill(' ')<<left<<"©¦ Ticket Number"<<": "<<setw(22)<<ticket_number<<setw(10)<<"Class:"<<": "<<ticket_details.classes<<setw(18)<<Class<<"©¦"<<endl;
	if (ch == 'S')
	 cout<<setw(21)<<"©¦ Coach"<<": "<<setw(22)<<ticket_details.coach<<setw(10)<<"Seat ID."<<": "<<setw(19)<<TICKET_INFO[e+o].seatID<<"©¦"<<endl;
	else
	 cout<<setw(21)<<"©¦ Coach"<<": "<<setw(22)<<ticket_details.coach<<setw(10)<<"Seat ID."<<": "<<setw(19)<<TICKET_INFO1[e].seatID<<"©¦"<<endl;
	cout<<setw(21)<<"©¦ From"<<": "<<setw(22)<<ticket_details.boarding_location<<setw(10)<<"To"<<": "<<setw(19)<<ticket_details.destination<<"©¦"<<endl;
	cout<<setw(21)<<"©¦ Departure"<<": "<<setw(12)<<ticket_details.departure_date<<setw(10)<<ticket_details.departure_time<<setw(10)<<"Arrive"<<": "<<setw(12)<<ticket_details.arrive_date<<setw(7)<<ticket_details.arrive_time<<"©¦"<<endl;
	if (ch=='S')
	 cout<<setw(19)<<"©¦ Adult (A)/Child(C)/Senior Citizen(S)"<<": "<<setw(4)<<ch1[e+o]<<setw(10)<<"Price"<<": "<<"RM "<<setw(12)<<TICKET_INFO[e+o].price<<"    ©¦"<<endl;
	else
	 cout<<setw(19)<<"©¦ Adult (A)/Child(C)/Senior Citizen(S)"<<": "<<setw(4)<<ch2[e+o]<<setw(10)<<"Price"<<": "<<"RM "<<setw(12)<<TICKET_INFO1[e+o].price<<"    ©¦"<<endl;
	if(ch=='S')
	 cout<<setw(19)<<"©¦ Tax"<<"  : RM"<<setw(6)<<TICKET_INFO[e+o].tax<<"              "<<"Ticket Type(1-way/2-way)"<<": "<<TICKET_INFO[e+o].type<<" way©¦"<<endl;
	else
	 cout<<setw(19)<<"©¦ Tax"<<"  : RM"<<setw(6)<<TICKET_INFO1[e+o].tax<<"              "<<"Ticket Type(1-way/2-way)"<<": "<<TICKET_INFO1[e+o].type<<" way©¦"<<endl;
	cout<<"©¸©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¼"<<endl<<endl;

	
	
ticket_number++; //increase the ticket number by 1 each time
}

number++; // increase the number of customer
o=u;

}while ( seat!= 0 );


system("CLS");
salereport_superior(ticket_array,TICKET_INFO, seat_superior,ticket_details,occupancyratesuperior); // display sales report for superior class
salereport_economy(ticket_array1, TICKET_INFO1,  seat_economy , ticket_details,occupancyrateeco); // display sales report for economy class

endmessage(); //display end message


cout<<"Back to Staff Menu? (Y/N): ";
cin>>yes_no;
yes_no=toupper(yes_no);
if (yes_no == 'Y')
	staffmenu();
else
	exit(1);

system("pause");

return 0;
}

int addtrain()
{
	string train_code,departure_date,departure_time,destination,boarding_location;
	ofstream outdata;
	char ans;
	outdata.open("Train File.txt",ios::app);

	if (!outdata)
	{
		cout<<"Error opening file!";
		return 1;
	}

		
	do
	{
	cout<<"Enter a new train details"<<endl;
	cout<<"Train code: ";
	cin>>train_code;
	outdata<<train_code<<"|";
	cout<<"Departure date (dd/mm/yyyy): ";
	cin>>departure_date;
	outdata<<departure_date<<"|";
	cout<<"Departure time (24h format): ";
	cin>>departure_time;
	outdata<<departure_time<<"|";
	cin.ignore();
	boarding_location= "KL Central";
	outdata<<boarding_location<<"|";
	destination= "Singapore";
	outdata<<destination;
	outdata<<endl;
	cout<<endl;
	cout<<"Is there any more train details to key in? (Y/N):";
	cin>>ans;
	ans=toupper(ans);

	system("CLS");
	}while (ans != 'N');
	
	
	outdata.close();

	cout<<"Back to Train Maintenance Menu? (Y/N): ";
	cin>>ans;
	ans=toupper(ans);
	if(ans== 'Y')
		{train_maintenance();
	     system("CLS");
	    }
	else
		exit(1);

}

int viewtrain()
{
	char ch;
	char train_code[5],departure_date[11],departure_time[6],boarding_location[11],destination[10];
	char ans;
	ifstream indata;
	
	indata.open("Train File.txt");

	if (!indata)
	{
		cout<<"Error opening file!";
		exit(1);
	}

	cout<<"Code"<<"\t"<<"Departure date"<<"\t"<<"Departure time"<<"\t\t"<<"From"<<"\t\t"<<"To"<<"\t"<<endl;
	indata.get(train_code,5);
	indata>>ch;
	indata.get(departure_date,11);
	indata>>ch;
	indata.get(departure_time,6);
	indata>>ch;
	indata.get(boarding_location,11);
	indata>>ch;
	indata.get(destination,10);
	indata.get(ch);

	
	cout<<train_code<<"\t"<<departure_date<<"\t"<<departure_time<<"\t\t\t"<<boarding_location<<"\t"<<destination<<endl;
	
	while (!indata.eof())
	{
	       
	indata.get(train_code,5);
	indata>>ch;
	indata.get(departure_date,11);
	indata>>ch;
	indata.get(departure_time,6);
	indata>>ch;
	indata.get(boarding_location,11);
	indata>>ch;
	indata.get(destination,10);
	indata.get(ch);
	cout<<train_code<<"\t"<<departure_date<<"\t"<<departure_time<<"\t\t\t"<<boarding_location<<"\t"<<destination<<endl;
		 
	}

	indata.close();
	
	cout<<"Back to Staff Menu? (Y/N): ";
	cin>>ans;
	ans=toupper(ans);
	if(ans== 'Y')
		{
			system("CLS");
			staffmenu();
			
	}
	else
		exit(1);
}

int viewtrain1()
{
	char ch;
	char train_code[5],departure_date[11],departure_time[6],boarding_location[11],destination[10];
	char ans;
	ifstream indata;
	
	indata.open("Train File.txt");

	if (!indata)
	{
		cout<<"Error opening file!";
		exit(1);
	}

	cout<<"Code"<<"\t"<<"Departure date"<<"\t"<<"Departure time"<<"\t\t"<<"From"<<"\t\t"<<"To"<<"\t"<<endl;
	indata.get(train_code,5);
	indata>>ch;
	indata.get(departure_date,11);
	indata>>ch;
	indata.get(departure_time,6);
	indata>>ch;
	indata.get(boarding_location,11);
	indata>>ch;
	indata.get(destination,10);
	indata.get(ch);

	
	cout<<train_code<<"\t"<<departure_date<<"\t"<<departure_time<<"\t\t\t"<<boarding_location<<"\t"<<destination<<endl;
	
	while (!indata.eof())
	{
	       
	indata.get(train_code,5);
	indata>>ch;
	indata.get(departure_date,11);
	indata>>ch;
	indata.get(departure_time,6);
	indata>>ch;
	indata.get(boarding_location,11);
	indata>>ch;
	indata.get(destination,10);
	indata.get(ch);
	cout<<train_code<<"\t"<<departure_date<<"\t"<<departure_time<<"\t\t\t"<<boarding_location<<"\t"<<destination<<endl;
		 
	}

	indata.close();
	
	cout<<"Back to Train Maintenance Menu? (Y/N): ";
	cin>>ans;
	ans=toupper(ans);
	if(ans== 'Y')
		{
			system("CLS");
			train_maintenance();
			
	}
	else
		exit(1);
}

void mainmenu()
{
	int choice,integer;
	char confirmation;

	
	logo();
	cout<<"                          Loading";
	cout <<".";
    Sleep( 1000 );
    cout << "."; 
    Sleep( 1000 );
    cout << "."; 
    Sleep( 1000 );
		
	cout<<"  Done! "<<endl;
	cout<<"             ======================================"<<endl;
	cout<<"             |                                    |"<<endl;
	cout<<"             |        1. Staff Menu               |"<<endl;
	cout<<"             |        2. Managament Menu          |"<<endl;
	cout<<"             |        3. Exit                     |"<<endl;
	cout<<"             |                                    |"<<endl;
	cout<<"             ======================================"<<endl;
	cout<<"Please select according to the number :";
	cin>>choice;

	while (choice!= 1 && choice!= 2 && choice!= 3)
	{
		cout<<"Invalid input! Please select the inputs available on screen: ";
		cin>>choice;
	}

	if( choice == 1)
	{
		system("CLS");
		staffmenu();
	}
	else if(choice == 2)
	{
		system("CLS");
		managementmenu();
		
	}
	else
	{
		cout<<"Exit ! Confirm? (Y/N): ";
		cin>>confirmation;
		confirmation=toupper(confirmation);
		if(confirmation== 'Y')
			exit(1);
		else
			mainmenu();
	}

	

}

void staffmenu()
{
	int choice;

	system("CLS");
	logo();
	cout<<"                          Loading";
	cout <<".";
    Sleep( 1000 );
    cout << "."; 
    Sleep( 1000 );
    cout << "."; 
    Sleep( 1000 );
		
	cout<<"  Done! "<<endl;
	cout<<"             ======================================"<<endl;
	cout<<"             |                                    |"<<endl;
	cout<<"             |        1. View Trains              |"<<endl;
	cout<<"             |        2. Ticket Selling           |"<<endl;
	cout<<"             |        3. Back to Main Menu        |"<<endl;
	cout<<"             |                                    |"<<endl;
	cout<<"             ======================================"<<endl;
	cout<<"Please select according to the number :";
	cin>>choice;

	while (choice!= 1 && choice!= 2 && choice!= 3)
	{
		cout<<"Invalid input! Please select the inputs available on screen: ";
		cin>>choice;
	}
	if ( choice == 1)
	{
		system("CLS");
		viewtrain();
	}
	else if (choice == 2)
	{
		system("CLS");
		ticket_selling();
	}
	else
	{
		system("CLS");
		mainmenu();
	}
}

void managementmenu()
{
	string password,correct_password;
	int choice;
	char reply='N';
	ifstream File;
	ofstream ofile;
	File.open("Password.txt");

	if(!File)
	{
		cout<<"Error opening file!";
		exit(1);
	}

	system("CLS");
	logo();
	
	File.seekg(0,std::ios::end);
	unsigned int size = File.tellg();
	if(!size)
	{
		cout<<"No password is set up! Do you want to setup now? (Y/N):";
	    cin>>reply;
		reply=toupper(reply);
		
	}

	else
	{
		password_checking();
	}

	File.close();

	
	if(reply=='Y')
	    {
				ofile.open("Password.txt");
	          if(!ofile)
	         {
		      cout<<"Error opening file!";
		      exit(1);
	         }
			cout<<"Please enter a password: ";
			cin>>password;
			ofile<<password;
			cout<<endl<<endl;
			cout<<"Your new password is successfully setup. The password is "<<password<<endl;
			cout<<"This screen will reload now in ";
			cout <<"3 ";
            Sleep( 1000 );
            cout << "2 "; 
            Sleep( 1000 );
            cout << "1"; 
            Sleep( 1000 );
			ofile.close();
			system("CLS");
	        logo();
			cout<<endl;
			
	    }

	
	cout<<"             ======================================"<<endl;
	cout<<"             |                                    |"<<endl;
	cout<<"             |        1. Train Maintenance        |"<<endl;
	cout<<"             |        2. Monthly Sales Report     |"<<endl;
	cout<<"             |        3. Train Occupancy Rate     |"<<endl;
	cout<<"             |        4. Modify Password          |"<<endl;
	cout<<"             |        5. Back to Main Menu        |"<<endl;
	cout<<"             |                                    |"<<endl;
	cout<<"             ======================================"<<endl;
	cout<<"Please select according to the number :";
	cin>>choice;

	while(choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5)
	{
		cout<<"Please enter a valid input!: ";
		cin>>choice;
	}

	if (choice == 1)
	{
		system("CLS");
		train_maintenance();
	}
	else if(choice == 2)
	{
		
		monthlysalesreport();
	}
	else if(choice == 3)
	{
		
		train_occupancy_rate();
	}

	else if(choice == 4)
	{
		system("CLS");
		modify_password();
	}
	else 
	{
		system("CLS");
		mainmenu();
	}

}

int modifytrain()
{
	char train_code[5],departure_date[11],departure_time[6],boarding_location[11],destination[10],ch,new_departure_date[11],new_departure_time[6],reply_train_code[5];
	bool checking=false;
	int date_or_time;
	char reply;
	char value;
	char ans;
	ifstream indata;
	ofstream outfile;
	node *head = NULL; 
	node *newnode, *travel; 
	indata.open("Train File.txt");

	if (!indata)
	{
		cout<<"Error opening file!";
		return -1;
	}

	indata.get(train_code,5);
	indata.get(ch);
	indata.get(departure_date,11);
	indata.get(ch);
	indata.get(departure_time,6);
	indata.get(ch);
	indata.get(boarding_location,11);
	indata.get(ch);
	indata.get(destination,10);
	indata.get(ch);

	newnode = new node; 
	strcpy(newnode->store_train_code , train_code);
	strcpy(newnode->store_departure_date , departure_date);
	strcpy(newnode->store_departure_time , departure_time);
	strcpy(newnode->store_boarding_location , boarding_location);
	strcpy(newnode->store_destination , destination);
	newnode ->next = NULL; 

	head=newnode;
		
	while (!indata.eof())
	{   
		indata.get(train_code,5);
	    indata.get(ch);
	    indata.get(departure_date,11);
	    indata.get(ch);
	    indata.get(departure_time,6);
	    indata.get(ch);
	    indata.get(boarding_location,11);
	    indata.get(ch);
	    indata.get(destination,10);
	    indata.get(ch);

		newnode = new node; 
		strcpy(newnode->store_train_code , train_code);
	    strcpy(newnode->store_departure_date , departure_date);
	    strcpy(newnode->store_departure_time , departure_time);
	    strcpy(newnode->store_boarding_location , boarding_location);
	    strcpy(newnode->store_destination , destination);
	    newnode ->next = NULL; 

			travel = head;      
			while (travel ->next != NULL)
			{
				travel = travel ->next;
			}
			travel ->next = newnode;
	}
	
	indata.close();
	do
	{
	cout<<"What you want to make changes to? :"<<endl;
	cout<<" 1. Departure date"<<endl;
	cout<<" 2. Departure time"<<endl;
	cout<<"Please select 1 or 2 : ";
	cin>>date_or_time;
	
	while (date_or_time != 1 && date_or_time != 2)
	{
		cout<<"Please select a valid input!: ";
		cin>>date_or_time;
	}

	if (date_or_time == 1)
	{ 
		 cout<<"Please key in train code: ";
		 cin.ignore();
	     cin.getline(reply_train_code,5);
		 	
	   for(travel = head; travel != NULL; travel = travel ->next)
	  {
		  if(strcmp(travel->store_train_code , reply_train_code)==0)
		  {
			 cout<<"Enter the new departure date: ";
			 cin.getline(new_departure_date,12);
			 strcpy(travel->store_departure_date,new_departure_date);
			 checking = true;
		  }
	  }

	   while (checking != true)
	   {
		    cout<<"Please key in a valid train code!: ";
	        cin.getline(reply_train_code,5);

	   for(travel = head; travel != NULL; travel = travel ->next)
	  {
		  if(strcmp(travel->store_train_code , reply_train_code)==0)
		  {
			 cout<<"Enter the new departure date: ";
			 cin.getline(new_departure_date,11);
			 strcpy(travel->store_departure_date,new_departure_date);
			 checking = true;
		}
	  }
	   }
	}
	else
	{
		 cout<<"Please key in the train code that you want to edit: ";
		 cin.ignore();
	     cin.getline(reply_train_code,5);

	   for(travel = head; travel != NULL; travel = travel ->next)
	  {
		  if(strcmp(travel->store_train_code , reply_train_code)==0)
		  {
			 cout<<"Enter the new departure time: ";
			 cin.get(new_departure_time,11);
			 strcpy(travel->store_departure_time, new_departure_time);
			 checking = true;
			
		  }
	  }
	    while (checking != true)
	   {
		    cout<<"Please key in a valid train code! : ";
	        cin.getline(reply_train_code,5);
		
	   for(travel = head; travel != NULL; travel = travel ->next)
	  {
		  if(strcmp(travel->store_train_code , reply_train_code)==0)
		  {
			 cout<<"Enter the new departure time: ";
			 cin.getline(new_departure_date,11);
			 strcpy(travel->store_departure_date,new_departure_date);
			 checking = true;
			
		  }
	  }
	   }
	}
	
	cout<<"Is there any more modifications? (Y/N):";
	cin>>reply;
	reply= toupper(reply);
	value=isalpha(reply);
	while (value ==0)
	{
		cout<<"Please re-enter a valid input!: ";
		cin>>reply;
	    reply= toupper(reply);
	    value=isalpha(reply);
	}

	}while (reply!= 'N');

	outfile.open("Train File.txt");

	if (!outfile)
	{
		cout<<"File opening error!";
		return -1;
	}
	
	   for(travel = head; travel != NULL; travel = travel ->next)
	  {
		  outfile<<travel->store_train_code<<"|";
		  outfile<<travel->store_departure_date<<"|";
		  outfile<<travel->store_departure_time<<"|";
		  outfile<<travel->store_boarding_location<<"|";
		  outfile<<travel->store_destination<<endl;
	  }

	   outfile.close();
	   
	cout<<"Back to Train Maintenance Menu? (Y/N): ";
	cin>>ans;
	ans=toupper(ans);
	if(ans== 'Y')
		{
			train_maintenance();
			system("CLS");
	}
	else
		exit(1);
}

void password_checking()
{
	ifstream inf;
	string password,correct_password;

	inf.open("Password.txt");
	if(!inf)
	{
		cout<<"Error opening file!";
		exit(1);
	}

	inf>>correct_password;

	cout<<"Please enter password to log into management menu: ";
	cin>>password;
	
	while ( password != correct_password)
	{
		cout<<"Wrong password! Please re-enter!: ";
		cin>>password;
					
	}

	inf.close();
	cout<<endl<<endl;
	cout<<"Password correct! Logging in";
	cout <<".";
    Sleep( 1000 );
    cout << "."; 
    Sleep( 1000 );
    cout << "."; 
    Sleep( 1000 );
	cout<<endl;
	system("CLS");
	logo();
}

void modify_password()
{
	logo();
	string password,new_password;
	char reply;
	ifstream infile;
	ofstream outfile;
	infile.open("Password.txt");

	if(!infile)
	{
		cout<<"Error opening file!";
		exit(1);
	}

	infile>>password;

	cout<<"Your password now is "<<password<<endl;
	cout<<"Do you want to modify it? (Y/N):";
	cin>>reply;
	reply=toupper(reply);
	infile.close();

	if(reply== 'Y')
	{
		outfile.open("Password.txt",ios::trunc);
		if(!outfile)
	{
		cout<<"Error opening file!";
		exit(1);
	}
		cout<<"Enter your new password: ";
		cin>>new_password;
		cout<<endl;
		while( password == new_password)
		{
			cout<<"The password entered is same as previous password!"<<endl;
			cout<<"Please enter another password: ";
			cin>>new_password;
		}
		cout<<"Your new password is now "<<new_password<<endl;
		outfile<<new_password;
		cout<<"You will now back to Management Menu in ";
		cout <<"3 ";
        Sleep( 1000 );
        cout << "2 "; 
        Sleep( 1000 );
        cout << "1"; 
        Sleep( 1000 );
		outfile.close();
	}
	else
	{
		cout<<"You will now back to Management Menu in ";
		cout <<"3 ";
        Sleep( 1000 );
        cout << "2 "; 
        Sleep( 1000 );
        cout << "1"; 
        Sleep( 1000 );
	}
	managementmenu();
}

int main()
{
	mainmenu();	
	system("pause");
	return 0;
}






