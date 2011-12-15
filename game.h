//Earlier I made a class nameg game with static memeber but I dun know for some reasons when I assigned a value to private static members of the class the
//complier showed an error saying unresolved externals so I switched to namespaces for semantic reasons.

//all functions were parameterized that the did not take global variable for the chosen word etc tht gave me better extensibility but tht created confusion
//for me so i removed them for now

namespace game
{
	int level;
	int const numberofwords=5;
	bool stopgame;

	struct status
	{
		int score,correct,wrong;
	}status;

	struct statusloc
	{
		int correctstatusX,correctstatusY;
		int wrongstatusX,wrongstatusY;
		int scorestatusX,scorestatusY;
	}statusloc;

	struct word
	{
		int wordstartX,wordstartY;
		int wordendX,wordendY;
		int length;
		int speedofanimation;
		bool bothcases;//upper and lower cases both?
	}word;

	struct currentword
	{
		char shabd[max];
		int correctcharactercount;
		bool timeover;
		bool done;
	}currentword;



	int getrandom(int range_min,int range_max)
	{
		int random;
		do
		{
			random = (double)rand() / (RAND_MAX + 1) * (range_max - range_min) + range_min;
		}while(random>=91 && random<=96);
		return random;
	}

	void generateword(int length)
	{
		char randomword[max];
		srand((unsigned int)time(NULL));
		for (int i=0;i<length;i++)
		{
			if (word.bothcases)	randomword[i]=getrandom(65,123);
			else randomword[i]=getrandom(97,123);
			randomword[i+1]=0;
		}
		strcpy(currentword.shabd,randomword);
	}

	void renderword(int x,int y)
	{
		console::gotoxy(x,y);
		int i;
		for (i=0;i<currentword.correctcharactercount;i++)
		{
			console::textcolor(FOREGROUND_GREEN);
			cout.put(currentword.shabd[i]);
		}
		console::textcolor(FOREGROUND_RED);
		for (;i<word.length;i++) cout.put(currentword.shabd[i]);
	}

	void renderheader(int level)
	{
		console::textcolor(4|2);
		console::gotoxy(34,2);
		switch(level)
		{
		case 1:
			cout<<"VERY EASY\n\n";
			break;
		case 2:
			cout<<"EASY\n\n";
			break;
		case 3:
			cout<<"BEGINNER\n\n";
			break;
		case 4:
			cout<<"INTERMEDIATE\n\n";
			break;
		case 5:
			cout<<"ADVANCED\n\n";
			break;
		default:
			cout<<"Invalid Level Selected\n";
			cout<<"The application will exit now\n";
			getch();
			exit(0);
		}
		console::drawHline(1,80);
	}

	void rendercorrectbox()
	{
		console::textcolor(4|2);
		console::gotoxy(5,console::getcursory()+1);
		console::drawHline(console::getcursorx(),console::getcursorx()+15);
		console::gotoxy(5,console::getcursory()+1);
		cout<<"| CORRECT :    |\n";
		int correctinptxy[]={17,console::getcursory()-1};
		console::gotoxy(5,console::getcursory());
		console::drawHline(console::getcursorx(),console::getcursorx()+15);
		statusloc.correctstatusX=correctinptxy[0];
		statusloc.correctstatusY=correctinptxy[1];
	}

	void renderwrongbox()
	{
		console::textcolor(4|2);
		console::gotoxy(5,console::getcursory()+1);
		console::drawHline(console::getcursorx(),console::getcursorx()+13);
		console::gotoxy(5,console::getcursory()+1);
		cout<<"| WRONG :    |\n";
		int correctinptxy[]={5+10,console::getcursory()-1};
		console::gotoxy(5,console::getcursory());
		console::drawHline(console::getcursorx(),console::getcursorx()+13);
		statusloc.wrongstatusX=correctinptxy[0];
		statusloc.wrongstatusY=correctinptxy[1];
	}

	void renderscorebox()
	{
		console::textcolor(4|2);
		console::gotoxy(60,statusloc.correctstatusY-1);
		console::drawHline(console::getcursorx(),console::getcursorx()+13);
		console::gotoxy(60,console::getcursory()+1);
		cout<<"| SCORE :    |\n";
		int correctinptxy[]={60+10,console::getcursory()-1};
		console::gotoxy(60,console::getcursory());
		console::drawHline(console::getcursorx(),console::getcursorx()+13);
		statusloc.scorestatusX=correctinptxy[0];
		statusloc.scorestatusY=correctinptxy[1];
	}

	void renderseparators()
	{
		console::textcolor(4|2);
		console::gotoxy(0,56);
		console::drawHline(console::getcursorx(),console::getcursorx()+79);
		//add more separators to make the game look beautiful
	}

	void renderfooter(int level)
	{
		console::textcolor(4|2);
		console::gotoxy(0,48);
		console::drawHline(1,80);
		rendercorrectbox();
		renderwrongbox();
		renderscorebox();
		renderseparators();
	}

	void animateword(void* dummy)
	{
		int startY=word.wordstartY;
		int endY=word.wordendY;
		int startX=word.wordstartX;
		for(int i=startY;i<=endY;i+=word.speedofanimation)
		{
			if (stopgame) _endthread();
			renderword(startX,i);
			Beep(800,100);
			Sleep(300);
			if (currentword.done==TRUE) 
			{
				renderword(startX,i);
				Beep(800,100);
				_endthread();
			}
		}
		currentword.timeover=TRUE;
		console::gotoxy(25,47);
		cout<<"TIME OVER. Press anny key to continue.";
		_endthread();
	}

	void updatestatus(int score,int correct,int wrong)
	{
		console::gotoxy(statusloc.correctstatusX,statusloc.correctstatusY);
		cout<<correct;
		console::gotoxy(statusloc.wrongstatusX,statusloc.wrongstatusY);
		cout<<wrong;
		console::gotoxy(statusloc.scorestatusX,statusloc.scorestatusY);
		cout<<score;
	}

	void start()
	{
		HANDLE threadhandle;
		
		threadhandle=(HANDLE) _beginthread(animateword,0,NULL);//creating a new thread here and starting it which does the animation of the word
		char ch;
		for (int i=0;i<word.length;i++)
		{
			if (currentword.timeover)
			{
				updatestatus(status.score,status.correct,++status.wrong);
				return;
			}
			if ((ch=getch())==currentword.shabd[i]) currentword.correctcharactercount++;
			else
			{
				if (ch==27)//to RETURN TO MENU WHEN USER PRESSES ESC KEY
				{
					stopgame=TRUE;
					return;
				}
				i--;
			}
		}
		currentword.done=TRUE;
		WaitForSingleObject(threadhandle,INFINITE);
		//Sleep(1000);//this is bad technique Im letting this thread sleep so tht the animateword thread gets finished. I shoud use some sync techniques
		//new I have used a proper sync operation waitforsingleobject will wait unless _endthread is called on animate thread.
		//I dun hav multiple threading sharing a resource like if I had to cout from 2 different threads I would have to use mutex sync objects.
		updatestatus(++status.score,++status.correct,status.wrong);
		console::gotoxy(25,47);
		cout<<"Press any key to continue.";
		getch();
	}

	void setlevelparameters(int level)
	{
		switch (level)
		{
		case 1:
			word.length=3;
			word.speedofanimation=1;
			word.bothcases=FALSE;
			break;
		case 2:
			word.length=5;
			word.speedofanimation=1;
			word.bothcases=FALSE;
			break;
		case 3:
			word.length=5;
			word.speedofanimation=3;
			word.bothcases=FALSE;
			break;
		case 4:
			word.length=7;
			word.speedofanimation=5;
			word.bothcases=FALSE;
			break;
		case 5:
			word.length=10;
			word.speedofanimation=7;
			word.bothcases=TRUE;
		}
	}

	void inline setwordstartendcords()
	{
		word.wordstartX=34;
		word.wordstartY=5;
		word.wordendX=34;
		word.wordendY=45;
	}

	void resetcurrentwordstats()
	{
		currentword.correctcharactercount=0;
		currentword.done=FALSE;
		currentword.timeover=FALSE;
	}
	
	void newwordinit()
	{
		system("CLS");
		resetcurrentwordstats();
		renderheader(level);
		renderfooter(level);
		updatestatus(status.score,status.correct,status.wrong);
		generateword(word.length);
	}

	void reset()
	{
		status.correct=0;
		status.score=0;
		status.wrong=0;
		stopgame=FALSE;
		currentword.correctcharactercount=0;
		currentword.done=FALSE;
		currentword.timeover=FALSE;
	}

	void init(int level)
	{
		system("CLS");
		reset();
		game::level=level;
		setlevelparameters(game::level);
		setwordstartendcords();
		renderheader(level);
		renderfooter(level);
		console::gotoxy(25,47);
		cout<<"Press any key to start the game";
		getch();
		console::gotoxy(25,47);
		cout<<"                               ";
		generateword(word.length);
		for (int i=0;i<numberofwords;i++)
		{
			if (stopgame) return;
			start();
			newwordinit();
		}
		console::gotoxy(25,25);
		console::textcolor(FOREGROUND_RED);
		cout<<"THANK YOU FOR PLAYING THE GAME";
		console::gotoxy(25,25+2);
		console::textcolor(4|2);
		cout<<"YOUR SCORE IS : "<<status.score;
		getch();
	}
}