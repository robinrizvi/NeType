// password.h : Defines the password class.
//

class password
{
	static void encrypt(char* input)
	{
		for (int i=0;input[i]!=0;i++) input[i]+=1;
	}

	static void decrypt(char* input)
	{
		for (int i=0;input[i]!=0;i++) input[i]-=1;
	}
public:

	bool static check(char* input)
	{
		char pwd[max];
		char* decipher;
		ifstream in("pwd.rob");
		if (!in)
		{
			char default[]="robin";
			encrypt(default);
			ofstream out("pwd.rob");
			if (!out) return false;
			out<<default;
			out.close();
			in.open("pwd.rob");
		}
		in>>pwd;
		in.close();
		decrypt(pwd);
		if (strcmp(pwd,input)==0) return true;
		else return false;
	}

	bool static change(char* input)
	{
		char* cipher;
		encrypt(input);
		ofstream out("pwd.rob");
		if (!out) return false;
		out<<input;
		out.close();
		return true;
	}
};