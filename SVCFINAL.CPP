#include<iostream.h>
#include<fstream.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
class svc
{
  public:
	void copyfile();
	void append();
	void delet();
	void display();
	int trial_v();
	void operations();
	int getdata();
};
fstream fp;
fstream log;
fstream cntr;
char buff[20],filename[20],fname[20],ver[25],version[5],temp[20];
void svc::copyfile()
{
	fstream fp11,fp22;
	char ch;
	fp11.open(filename,ios::in);
	fp22.open(fname,ios::out);
	fp11.get(ch);
	while(!fp11.eof())
	{
		fp22.put(ch);
		fp11.get(ch);
	}
	fp11.close();
	fp22.close();
}
void svc::append()
{
	ofstream fp1;
	//char buff[10];

	int p,count=0;
	char buffer[10];
	char buffer1[10];
	fp1.open(fname,ios::app);
	cout<<"\n how many lines append(less than 20):";
	cin>>p;
	if(p<=20)

	for(int i=1;i<=p;i++)
	{
	cout<<"\nEnter line of text to append::";
	cin>>buffer;
	strcpy(buff,temp);
	strcat(buff,"_log.txt");
	log.open(buff,ios::app);
	log<<"APPENDED DATA:"<<buffer<<"\n";
	log.close();
	count++;
	if(count>19)
	   break;
	//buffer1=buffer;
	fp1<<"\n";
	fp1<<buffer;
	}
	else
	   cout<<"\n enter valid number";
	fp1.close();

}

void svc::display()
{
       int line=1;
	fp.open(filename,ios::in);

			if(fp.fail())
			{
				cout<<"\n***File Does Not Exist***\n";
			}
			else
			{
				char x[20];
				cout<<"\nLine\tContent";
				cout<<"\n--------------------------";
				while(!fp.eof())
				{
				   fp.getline(x,20);
				   cout<<"\n"<<line<<"\t"<<x;

				   line++;
				}
			}
			cout<<"\n---------End Of File---------\n";
			fp.close();
}


void svc::delet()
{
	int lno;
	char buffer[20];
	fstream fp11,fp22;

	display();
	cout<<"\nSelect line number to delete:";
	cin>>lno;
	fp11.open(filename,ios::in);
	fp22.open(fname,ios::out);

	for(int i=0;i<lno-1;i++)
	{
		fp11.getline(buffer,20);
		if(i==0)
		fp22<<buffer;
		else
		fp22<<"\n"<<buffer;
	}
	fp11.getline(buffer,20);
	strcpy(buff,temp);
	strcat(buff,"_log.txt");
	log.open(buff,ios::app);
	log<<"DELETED DATA:"<<buffer<<"\n";
	log.close();
	while(!fp11.eof())
	{
	      fp11.getline(buffer,20);
	      if(lno==1)
	      fp22<<buffer;
	      else
		fp22<<"\n"<<buffer;
	}
	fp11.close();
	fp22.close();
}

void svc::operations()
{
	int ch1;

	cout<<"\n\nEnter operation to perform on file"
		<<"\n1>Append line to the File"
		<<"\n2>Delete line from File";
	cin>>ch1;

	switch(ch1)
	{
		case 1: copyfile();
			append();
			break;

		case 2:delet();
			break;
	}

}

int svc::getdata()
{
   char buff[25];
   fstream test;
   cout<<"\nEnter filename:";
   cin>>filename;
   strcpy(buff,filename);
   strcat(buff,"(0).txt");
   test.open(buff,ios::in);
   if(test.fail())
   {
	cout<<"\nNo such File exists";
	return(1);
   }
   else
   {
   cout<<"Enter file version number:";
   cin>>version;
   }
   return(0);
}

int svc::trial_v()
{
     char  buff[25],testcnt[3];
     fstream test;

     strcpy(buff,filename);
     strcat(buff,"_vfn.txt");
     test.open(buff,ios::in);
     test.getline(testcnt,3);
     if(atoi(version)>atoi(testcnt))
     {
	cout<<"File version non-exist";
	return(1);
     }
   return(0);
}

void main()
{
	int ch;
	char newver[3];
	char buffer[10];
	clrscr();
	svc s;
	do
	{
	cout<<"\n\n\t\t********SVC**********";
	cout<<"\n\t\t1.Create new file\n\t\t2.Open existing file\n\t\t3.display file contents\n\t\t4.Exit";
	cin>>ch;
	switch(ch)
	{
		case 1: cout<<"\nEnter filename : ";
			cin>>filename;
			strcpy(temp,filename);
			strcpy(ver,filename);
			strcat(ver,"_vfn.txt");
			strcat(filename,"(0).txt");

			cntr.open(ver,ios::out);
			cntr<<"0";
			cntr.close();
			cout<<"Enter a line of text:";
			cin>>buffer;
			fp.open(filename,ios::out);
			fp<<buffer;
			fp.close();
			break;

		case 2: int y;
			y=s.getdata();

			if(y==0)
			{
			y=s.trial_v();
			if(y==0)
			{
			strcpy(ver,filename);
			strcat(ver,"_vfn.txt");
			strcat(filename,"(");
			strcpy(fname,filename);
			strcat(filename,version);
			cntr.open(ver,ios::in);
			char wd;
			cntr.getline(newver,3);
			cntr.close();
			strcat(fname,itoa(atoi(newver)+1,newver,10));
			strcat(filename,").txt");
			strcat(fname,").txt");
			cntr.open(ver,ios::out);
			cntr<<newver;
			cntr.close();
			cout<<"\nEdited File version::"<<filename;
			cout<<"\nNew File version::"<<fname;
			s.operations();
			}
			}
			break;

		case 3: s.getdata();
			strcat(filename,"(");
			strcat(filename,version);
			strcat(filename,").txt");
			s.display();
			break;
	    }

	}while(ch!=4);
	getch();
	clrscr();
}