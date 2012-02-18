// MINIGAME.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "password.h"
#include "console.h"
#include "game.h"

void renderheader();
void renderauthenticator();
void rendergame(int level);
void rendersettings();
bool processmenu();
void addmenuitem(char*,bool,bool);
void rendermenu();
void renderaboutpage();


void renderheader()
{
	console::textcolor(4|2);
	system("cls"); //used instead of clrscr()
	cout<<"********************************************************************************";
	cout<<"************************************MINIGAME************************************";
	cout<<"********************************************************************************";
}

void renderauthenticator()
{
	char input[max];
	int chance=1;
	bool correct=FALSE;
	cout<<endl<<endl<<endl<<"Note:-You will be given only three chances to enter the valid password.And in case you are using this software for the first time,the password is - robin"<<endl<<endl;
	while(chance<=3)
	{
		console::textcolor(4|2);
		cout<<"\nENTER THE PASSWORD"<<endl;
		console::textcolor(1|2);
		for (int i=0;i<max-1;i++)
		{
			if (i<0) i=0;
			input[i]=getch();
			if (input[i]=='\b')
			{
				i-=2;
				console::gotoxy(console::getcursorx()-1,console::getcursory());
				cout.put(' ');
				console::gotoxy(console::getcursorx()-1,console::getcursory());
				continue;
			}
			if (input[i]=='\r')
			{
				input[i]=0;
				break;
			}
			cout<<"*";
			Beep(800,100);
			input[i+1]=0;
		}
		if (password::check(input)==TRUE)
		{
			correct=TRUE;
			break;
		}
		else
		{
			console::textcolor(4);
			chance++;
			cout<<endl<<"\nYou have entered an incorrect password. "<<"You have "<<4-chance<<" chances left.\n";
			Beep(2000,200);
		}
	}
	if (correct==FALSE)
	{
		console::textcolor(4);
		cout<<"\n\nAll your three chances are lost"<<endl<<"\nThe program will be terminated now."<<endl<<"\nPress any key to exit";
		getch();
		exit(0);
	}
}

void addmenuitem(char* item,bool header=FALSE,bool footer=FALSE)
{
	console::gotoxy(20,console::getcursory());
	console::drawHline(console::getcursorx(),60);
	console::gotoxy(20,console::getcursory()+1);
	cout<<"|";
	if (header==TRUE) console::gotoxy(38,console::getcursory());
	else console::gotoxy(25,console::getcursory());
	cout<<item;
	if (footer)
	{
		int inpx=console::getcursorx();
		int inpy=console::getcursory();
		console::gotoxy(60,console::getcursory());
		cout<<"|";
		cout<<"\n";
		console::gotoxy(20,console::getcursory());
		console::drawHline(console::getcursorx(),60);
		console::gotoxy(inpx,inpy);
	}
	else
	{
		console::gotoxy(60,console::getcursory());
		cout<<"|";
		cout<<"\n";
	}

}

void rendermenu()
{
	system("cls");
	renderheader();
	console::textcolor(4|2);
	cout<<"\n\n\n";
	addmenuitem("MENU",TRUE);
	addmenuitem("1) VERY EASY LEVEL");
	addmenuitem("2) EASY LEVEL");
	addmenuitem("3) BEGINNER LEVEL");
	addmenuitem("4) INTERMEDIATE LEVEL");
	addmenuitem("5) ADVANCED LEVEL");
	addmenuitem("6) CHANGE SETTINGS");
	addmenuitem("7) ABOUT THE DEVELOPER");
	addmenuitem("8) QUIT APPLICATION");
	addmenuitem("ENTER OPTION : ",FALSE,TRUE);
	while(!processmenu());
}

bool processmenu()
{
	console::textcolor(4|2);
	bool validchoice=TRUE;
	switch (char option=getche())
	{
	case '1':
		Beep(800,100);
		game::init(1);
		rendermenu();
		break;
	case '2':
		Beep(800,100);
		game::init(2);
		rendermenu();
		break;
	case '3':
		Beep(800,100);
		game::init(3);
		rendermenu();
		break;
	case '4':
		Beep(800,100);
		game::init(4);
		rendermenu();
		break;
	case '5':
		Beep(800,100);
		game::init(5);
		rendermenu();
		break;
	case '6':
		Beep(800,100);
		rendersettings();
		break;
	case '7':
		Beep(800,100);
		renderaboutpage();
		break;
	case '8':
		Beep(800,100);
		exit(0);
		break;
	default:
		Beep(2000,200);
		int inpx=console::getcursorx();
		int inpy=console::getcursory();
		console::textcolor(4);
		cout<<"\n\n\n Please select a valid option. Valid options are; 1,2,3,4,5,6,7,8.";
		console::gotoxy(inpx-1,inpy);
		validchoice=FALSE;
	}
	return validchoice;
}

void rendersettings()
{
	char oldinput[max],newinput[max];
	system("CLS");
	renderheader();
	cout<<"\n\n\n";
	cout<<"Enter the old password\n";
	console::textcolor(1|2);
	for (int i=0;i<max-1;i++)
	{
		if (i<0) i=0;
		oldinput[i]=getch();
		if (oldinput[i]=='\b')
		{
			i-=2;
			console::gotoxy(console::getcursorx()-1,console::getcursory());
			cout.put(' ');
			console::gotoxy(console::getcursorx()-1,console::getcursory());
			continue;
		}
		if (oldinput[i]=='\r')
		{
			oldinput[i]=0;
			break;
		}
		cout<<"*";
		Beep(800,100);
		oldinput[i+1]=0;
	}
	console::textcolor(4|2);
	if (password::check(oldinput))
	{
		cout<<"\nEnter new password\n";
		console::textcolor(1|2);
		for (int i=0;i<max-1;i++)
		{
			if (i<0) i=0;
			newinput[i]=getch();
			if (newinput[i]=='\b')
			{
				i-=2;
				console::gotoxy(console::getcursorx()-1,console::getcursory());
				cout.put(' ');
				console::gotoxy(console::getcursorx()-1,console::getcursory());
				continue;
			}
			if (newinput[i]=='\r')
			{
				newinput[i]=0;
				break;
			}
			cout<<"*";
			Beep(800,100);
			newinput[i+1]=0;
		}
		console::textcolor(4|2);
		if (password::change(newinput)) cout<<"\n\nPassword has been changed successfully\n\n\nPress any key to continue\n";
		else cout<<"There was an error saving the new password\n\n\nPress any key to continue\n";
	}
	else
	{
		Beep(2000,200);
		console::textcolor(4);
		cout<<"\n\n\nWrong password entered\n\n";
		console::textcolor(4|2);
		cout<<"\nPress any key to continue\n";
	}
	getch();
	rendermenu();
}

void renderaboutpage()
{
	char tmp[1000];
	system("cls");
	renderheader();
	ifstream in("robin.rob");
	if (!in)
	{
		cout<<"Error in processing file";
	}
	else
	{
		cout<<"\n\n\n\n\n";
		console::textcolor(4);
		while(!in.eof())
		{
			char ch;
			in.get(ch);
			cout.put(ch);
		}
	}
	console::textcolor(4|2);
	cout<<"\n\n\n\n\n\nPress any key to continue\n";
	getch();
	rendermenu();
}

void _tmain(int argc, _TCHAR* argv[])
{
	renderheader();
	renderauthenticator();
	rendermenu();
	getch();
}

