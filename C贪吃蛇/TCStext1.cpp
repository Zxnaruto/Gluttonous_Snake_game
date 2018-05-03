#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<Windows.h>
#include<time.h>


#define LEN 30
#define WID 25

int snake[LEN][WID]={0};
char snake_dir='a';                                   //��¼��ͷ���ƶ�����
int snake_point_x,snake_point_y;                      //��¼��ͷ��λ��
int snake_len=3;                                      // ��¼�ߵĳ���
clock_t now_time;                                     //��¼��ǰʱ��
int waiting_time=300;                                 //��¼�Զ��ƶ���ʱ����
int eat_apple=1;                                      //�Ե�ƻ����ʾΪ0
int bake_raod=0;                                      //������ɫ
int level=1;
int score=-1;
int apple=-1;


HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);

void Set_Color(int color)                             //������ɫ
{
	SetConsoleTextAttribute(hConsole,color);
}

void hid_guanbiao()                                   //���ع��
{
	CONSOLE_CURSOR_INFO cursor_info = {1,0};
	SetConsoleCursorInfo(hConsole,&cursor_info);
}

void goto_point(int x,int y)                          //���ù��
{
	COORD point;
	point.X=x;
	point.Y=y;
	SetConsoleCursorPosition(hConsole,point);
}

void game_over()                                      //��Ϸ����
{
	goto_point(30,7);
	printf("GAME OVER!!!");
	Sleep(1000);
	system("pause>nul");
	exit(0);
}

void clear_snake()                                   //���̰����
{
	int x,y;
	for(y=0;y<WID;y++)
	{
		for(x=0;x<LEN;x++)
		{
			goto_point(x*2,y);
			if(snake[x][y]==snake_len)
				printf("  ");
		}
	
	}
		
}

void rand_apple()                                   //���ʳ��
{
	int x,y;
	do{
	     x=(rand()%(LEN-2))+1;
		 y=(rand()%(WID-2))+1;

      }while(snake[x][y]);
	snake[x][y]=-1;
	goto_point(x*2,y);
	Set_Color(rand()%8+1);
	printf("#");
	eat_apple=0;
}


void  Pri_News()                                     //��ӡ��Ϣ
{
	Set_Color(0xe);
	goto_point(63,4);
	score+=level;
	printf("����: ");
	printf("%d",score);
	goto_point(63,6);
	printf("�ȼ�: ");
	printf("%d",level);
	goto_point(63,8);
	printf("����: ");
	printf("%d",snake_len);
	goto_point(63,10);
	printf("�ٶ�: ");
	printf("0.%dm/s",100-waiting_time/10);
	goto_point(63,12);
	printf("��ʵ: ");
	printf("%d",apple);

}


void level_snake()
{
	if((apple-1)/10==level)
	{
		++level;
		if(waiting_time>100)
			waiting_time-=100;
		else
			if(waiting_time>50)
				waiting_time-=50;
			else
				if(waiting_time>10)
					waiting_time-=10;
				else
					waiting_time-=1;
	
	}

}


void move_snake()
{
	int x,y;
	for(x=0;x<LEN;x++){
	for(y=0;y<WID;y++)
	{
		if(snake[x][y]==1)
		{
			switch(snake_dir)
			{
			case 'w':
				if(y==1)
					snake_point_y=WID-2;
				else
					snake_point_y=y-1;
			snake_point_x=x;
			break;
			
			case 's':
				if(y==WID-2)
					snake_point_y=1;
				else
					snake_point_y=y+1;
				snake_point_x=x;
				break;

			case 'a':
				if(x==1)
				snake_point_x=LEN-2;
				else
					snake_point_x=x-1;
				snake_point_y=y;
				break;

			case 'd':
				if(x==LEN-2)
					snake_point_x=1;
				else
					snake_point_x=x+1;
					snake_point_y=y;
					break;
			default:break;
				
				}
	}
	}
}
	if(snake[snake_point_x][snake_point_y]!=0 && snake[snake_point_x][snake_point_y]!=-1)           //�ж��߹���
		game_over();
	if(snake[snake_point_x][snake_point_y]<0)                                                       //��ƻ��
		{++snake_len;
	eat_apple=1;}

	for(x=0;x<LEN;x++)
{
	for(y=0;y<WID;y++){
	
		if(snake[x][y]>0){
		
		if(snake[x][y]!=snake_len)
			snake[x][y]+=1;
		else
			snake[x][y]=0;
		}
	
	}
}
   snake[snake_point_x][snake_point_y]=1;


}

void print_snake()
{
	int x,y,color;
	for(y=0;y<WID;y++){
	
		for(x=0;x<LEN;x++){
			if(snake[x][y]==1){
			Set_Color(0xe);
			goto_point(x*2,y);
			printf("@");
			
			}
			if(snake[x][y]==2){
			
			color=rand()%15+1;
			if(color==14)
				color-=rand()%13+1;
			Set_Color(color);
			goto_point(x*2,y);
			printf("#");
			}
			if(snake[x][y]==snake_len){
			goto_point(x*2,y);
			Set_Color(0xe);
			printf("0");
			}
		}
	}


}

void get_input()
{
	if(kbhit())
	{
	   switch(getch())
	   {
	   case 'w':
	   case 72:
		   if(snake_dir!='s')snake_dir='w';break;
	   case 's':
	   case 80:
		   if(snake_dir!='w')snake_dir='s';break;
	   case 'a':
	   case 75:
		   if(snake_dir!='d')snake_dir='a';break;
	   case 'd':
	   case 77:
		   if(snake_dir!='a')snake_dir='d';break;
	   default:break;
     }
	
	}
	if(clock()-now_time>waiting_time)
	{
		clear_snake();
		move_snake();
		print_snake();
		now_time= clock();
}
}


void set_out()
{
	int i,j;
	Set_Color(3);
	for(i=0;i<LEN;i++)
	{
		goto_point(i*2,0);
		printf("*");
		goto_point(i*2,WID-1);
		printf("*");
	
	}
	for(j=0;j<WID;j++)
	{
		goto_point(0,j);
		printf("*");
		goto_point(2*(LEN-1),j);
		printf("*");
	
	}
}


void inset()
{
	system("title:Zx-first little game'snake.");
	system("mode con:cols=80 lines=25");
	hid_guanbiao();
	goto_point(61,4);//����
	goto_point(61,6);//�ȼ�
	goto_point(61,8);//����
	goto_point(61,10);//�ٶ�
	goto_point(61,12);//��ʵ
	
	int i;
	for(i=0;i<snake_len;i++)
	{
	snake[10+i][15]=i+1;
	}
	int x,y;
	for(y=0;y<WID;y++)
	{
		for(x=0;x<LEN;x++)
		{
			Set_Color(snake[x][y]+bake_raod);         //���ñ�����ɫ
		   goto_point(x*2,y);
		   printf("*");
		}
	
	}
	
	set_out();
}

void main()
{
	inset();
	srand((unsigned)time(NULL));       //���������������
	now_time=clock();
	while(1)
	{
		if(eat_apple)
		{
			++apple;
			rand_apple();
			level_snake();
			Pri_News();
		
		}
	get_input();
	Sleep(10);
	}

}