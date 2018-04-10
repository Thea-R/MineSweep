#include<iostream>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<cmath>
#include<algorithm>
const int n=4, m=4;
const char ch[2]={'X', 'O'};
using namespace std;

class Chess
{
	public:
		int x, y;
		char mmp[n][m];

	public:
		void Init();
		bool Read(int d);
		bool Win(int d);
		void Rules();
		void Board();
		void Errors();
		void Winer(int d);
		void Draws();
		void Choose(char opt[2]);
		void Status(int fir, int sec, int draws);
}A;

void Chess::Init()
{
	for(int i=0; i<n; i++)
		for(int j=0; j<m; j++)
			mmp[i][j]=' ';
	return ;
}

bool Chess::Read(int d)
{
	printf("Now it's turn for the %s player(%c), please input the coordinates(x y):\n", d?"second":"first", ch[d]);
	string s;
	cin>>s;
	if(s.size()>1)	return false;
	if(s[0]<'0' || s[0]>'9')	return false;
	x=s[0]-'0';

	cin>>s;
	if(s.size()>1)	return false;
	if(s[0]<'0' || s[0]>'9')	return false;
	y=s[0]-'0';

	--x, --y;
	if(x<0 || x>=n || y<0 || y>=m || mmp[x][y]!=' ')	return false;
	printf("\n");
	mmp[x][y]=ch[d];
	return true;
}

bool Chess::Win(int d)
{
	bool fx1=true, fx2=true, fy1=true, fy2=true, fd1=true, fd2=true, fd3=true, fd4=true;
	for(int i=0; i<3; i++)	fx1&=(mmp[0+i][y]==mmp[x][y]), fx2&=(mmp[1+i][y]==mmp[x][y]);
	for(int j=0; j<3; j++)	fy1&=(mmp[x][0+j]==mmp[x][y]), fy2&=(mmp[x][1+j]==mmp[x][y]);
	for(int i=0; i<3; i++)	fd1&=(mmp[i][i]==mmp[x][y]), fd2&=(mmp[i][n-i-1]==mmp[x][y]);
	for(int i=1; i<n; i++)	fd3&=(mmp[i][i]==mmp[x][y]), fd4&=(mmp[i][n-i-1]==mmp[x][y]);
	return fx1 || fx2 || fy1 || fy2 || fd1 || fd2 || fd3 || fd4;
}

void Chess::Rules()
{
	printf("The first player is represented by 'X', and the second by 'O'.\n");
	printf("When a row , column or diagonal is whole occupid by one player, he wins.\n\n");
	return ;
}

void Chess::Board()
{
	printf("   1   2   3   4\n");
	for(int i=0; i<n; i++)
	{
		if(i)	printf("  ---|---|---|---\n");
		printf("%d ", i+1);
		for(int j=0; j<m; j++) printf(" %c %c", mmp[i][j], "|\n"[j==m-1]);
	}
	printf("\n");
	return ;
}

void Chess::Errors()
{
	printf("Invalid coordinates. Please make another input.\n");
	return ;
}

void Chess::Winer(int d)
{
	printf("The %s player wins!\n\n", d?"second":"first");
	return ;
}

void Chess::Draws()
{
	printf("It's a tie!\n\n");
	return ;
}

void Chess::Choose(char opt[2])
{
	printf("Please input 'Y' to play agian.\n");
	printf("Ohterwise, press any other key to exit.\n");
	scanf("%s", opt);
	printf("\n");
	return ;
}

void Chess::Status(int fir, int sec, int draws)
{
	printf("The first player wins %d times.\n", fir);
	printf("The second player wins %d times.\n", sec);
	printf("There are %d draws.\n\n", draws);
	printf("Thanks for using :)\n");
	return ;
}

int main()
{
	int fir=0, sec=0, draws=0;
	char opt[2]={'Y'};

	A.Rules();
	while(opt[0]=='Y')
	{
		A.Init();
		A.Board();

		int step=0, lim=n*m;
		while(step<lim)
		{
			while(!A.Read(step&1))	A.Errors();
			A.Board();

			if(A.Win(step&1))
			{
				A.Winer(step&1);
				(step&1)?(++sec):(++fir);
				step=-1;
				break;
			}
			++step;
		}
		if(step!=-1)
		{
			A.Draws();
			++draws;
		}

		A.Choose(opt);
	}
	A.Status(fir, sec, draws);
	return 0;
}
