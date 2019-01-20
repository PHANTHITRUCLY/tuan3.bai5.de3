#include<iostream>
#include<conio.h>
#include<graphics.h> // thu vien do hoa
#include<string.h>
#include<fstream>
using namespace std;

#define ESC 27
#define ENTER 13
#define RIGHT 77
#define UP 72
#define DOWN 80
#define LEFT 75
#define HOME 71
#define END 79
#define INSERT 82 // van chua su dung dc
#define DEL 83
#define BKSP 8
#define TXW 12
#define TXH 12
#define CtrC 3 // van chua su dung dc
#define CtrV 22 // van chua su dung dc

char *chuoistr; // chuoi hien ra man hinh

class TextField
{
    private:
        char str[80];
        int startx,starty,size; // startx:luu toa do chung cua x 
        						//starty:toa do chung cua y 
								//size: do dai cua chuoi nhap vao
       
	    void draw(char *strin);
    public:
        TextField1(int x1,int y1,int s,char *str1)
        {
            startx=x1+2;
            starty=y1+2;
            strcpy(str,str1);
            size=s;
        }
        void setText(char *str1);
        void draw();
        char *getText();
        void cursor(int x,int y,char ch);
};

void TextField::setText(char *str1)
{
    strcpy(str,str1);
}

void TextField::draw()
{
    setcolor(YELLOW);
    setfillstyle(SOLID_FILL,BLACK);
    bar(startx-2,starty-2,startx+size*TXW+1000,starty+TXH+50);
    outtextxy(startx,starty,str);
}

// ham hien thi vi tri con tro
void TextField::cursor(int x,int y,char ch) 
{
	char ngang[] ="_";
    y+=2;
    char str[2];
    str[0]=ch;
    str[1]='\0';
    while(!kbhit()) // trong khi chua co phim nao duoc nhan
    {
        setcolor(GREEN); // mau ban dau cua con tro
        outtextxy(x,y,ngang);
        delay(500);
        setcolor(WHITE); // con tro doi sang mau trang
        outtextxy(x,y,ngang);
        setcolor(RED);  // mau cua ky tu bi doi sang do
        if (ch!=0)
        outtextxy(x,y-2,str);
        delay(500);
    }
    setcolor(GREEN);
    outtextxy(x,y,ngang);
    setcolor(RED);
    if (ch!=0)
        outtextxy(x,y-2,str);
}

char* TextField::getText()
{
    draw();
    int cur_x,cur_y,xend,len;
    char cur_ch,ch;
    cur_x=xend=textwidth(str); // do rong cua chuoi str
    cur_y=starty;
    cur_ch=str[cur_x/12];
    cursor(cur_x+startx,starty,cur_ch); // hien thi con tro o vi tri cuoi cung cua chuoi str
    ch=getch(); // cho` den khi phim bat ki dc nhan
    while (ch!=ENTER) // trong khi chu nhan ENTER
    {
    	// ch != 0 la gia tri trong bang ma ASCII ( bao gom chu va so )
        if ((ch!=0)&&((isalnum(ch) != 0)||(ch=='.')||(ch==' '))) 
		// isalnum() kiem tra ki tu co phai la so hoac chu hay khong, neu dung thi gia tri khac 0
        {
            if (xend/TXW<size)
            {
                len=strlen(str);
                if (cur_x==xend){
                    strncat(str,&ch,1);
				}
                else
                {
                    str[len+1]='\0'; // do dai tang len 1 va ki tu cuoi cung la ket thuc
                    cur_x += TXW; // tang con tro them 12 ( de chen chu phia ben phai cua con tro ban dau )
                    for (int i=len;i>=cur_x/TXW;i--)
                        str[i]=str[i-1];
                    str[cur_x/TXW]=ch;
                }
                xend+=TXW;
            }
        }
        else if (ch==ESC)
        {
        	char trong[] = "";
            setText(trong);
            cur_x=xend=0;
        }
        else if ((ch==BKSP)&&(cur_x>0))
        {
            len=strlen(str);
            for (int i=(cur_x-1)/TXW;i<len;i++)
                str[i]=str[i+1];
            str[len]='\0';  
            xend-=TXW; // giam toa do cuoi cung
            cur_x-=TXW;
        }
        else if (ch==0) // cac ki tu dac biet cua ban phim nhu LEFT, UP, RIGHT, DOWN, F1, F2,....
        {
            ch=getch(); 
            if ((ch==LEFT)&&(cur_x>0))
                cur_x-=TXW;
            else if ((ch==RIGHT)&&(cur_x<xend))
                cur_x+=TXW;
            else if (ch==HOME)
                cur_x=0;
            else if (ch==END)
                cur_x=xend;
            else if ((ch==DEL)&&(cur_x<xend))
            {
                len=strlen(str);
                for (int i=(cur_x+1)/TXW;i<len;i++)
                    str[i]=str[i+1];
                str[len]='\0';
                xend-=TXW;
            }
            
        }
        if (cur_x==xend)
            cur_ch=0;
        else
            cur_ch=str[cur_x/12];
        draw(); // de len khung cu
        cursor(cur_x+startx,cur_y,cur_ch);
        ch=getch();
    }
    return str;
 }

int main(){
    initwindow(700,800);
    fstream doc,ghi;
    int chon;
    char st[80];
    char stt[160]=""; // tam cua st
    settextstyle(BOLD_FONT, HORIZ_DIR,2); // dinh nghia font chu
    do{
    	do{
    		
    cout<<endl<<"Nhap tu file ( 1 ) hoac nhap tu ban phim ( 0 ): ";
    cin>>chon;
     } while(chon !=1 && chon !=0);
    if(chon == 1){
    	doc.open("bai5text.txt");
    	doc.getline(st,80);
    	doc.close();
	}
    else {
    	cout<<endl<<"Nhap vao chu muon hien (enter la dung): ";
	    fflush(stdin);
	    cin.getline(st,80);
	}
    if(strcmp(st,"\0")!=0){
    	cout<<endl<<"Vo cua so Windows BGI va bam Enter de ket thuc Windows BGI va tiep tuc viec nhap";
    	strcat(stt,st); // copy chuoi st vao phia sau chuoi stt
    	TextField t1;
    	t1.TextField1(100,100,160,stt);
  		t1.draw();
 	  	chuoistr=t1.getText();
 		cout<<endl<<"Ban da nhap: "<<chuoistr;
 		strcpy(stt,chuoistr);
    }
	}while(strcmp(st,"\0")!=0);
	ghi.open("bai5out.txt",ios::out);
	ghi<<chuoistr;
	ghi.close();
    closegraph();
    system("pause");
}

