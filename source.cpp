// Rắn săn mồi
#include <iostream>
#include "console.h"

#include <ctime>
#define MAX 1000
#define Up 1
#define Down 2
#define Left 3
#define Right 4
#define WALL_LEFT	3
#define WALL_RIGHT	90
#define WALL_UP		3
#define WALL_DOWN	20


using namespace std;

struct ToaDo
{
	int x,y;
};

ToaDo ran[MAX];
int dotRan;
int temp ; 
int n=0;


void init(){
	dotRan = 3;
	temp=-1;
	ran[0].x = 6;
	ran[1].x = 5;
	ran[2].x = 4;
	ran[0].y = ran[1].y = ran[2].y = 5;

}
void show(ToaDo ranCuoi){
	for(int i=0;i<dotRan;i++){
		gotoXY(ran[i].x,ran[i].y);
		cout<<(char)169;
	}
	gotoXY(ranCuoi.x,ranCuoi.y);
	cout<<" ";
}
ToaDo move(int x){
	ToaDo ranCuoi = ran[dotRan-1];
	for(int i=dotRan-1;i>=1;i--){
		ran[i] = ran[i-1];
	}

	switch(x){
		case Up:	ran[0].y--; break;
		case Down:	ran[0].y++; break;
		case Left:	ran[0].x--; break;
		case Right: ran[0].x++; break;
	}
	return ranCuoi;
	
}
void keyInput(int &direct){
	
	int key = inputKey();
	
	if(key=='w' || key=='W'){
		if(temp != 's' ){
			direct = Up;
			temp = 'w';
		}
	}
	if(key=='s' || key=='S'){
		if(temp != 'w' ){
			direct = Down;
			temp = 's';
		}
	}
	if(key=='a' || key=='A'){
		if(temp != 'd' ){
			direct = Left;
			temp = 'a';
		}
	}
	if(key=='d' || key=='D'){
		if(temp != 'a' ){
			direct = Right;
			temp = 'd';
		}
	}

	
	
}
void initWall(){
	setTextColor(WHITE_COLOR);
	for(int i = WALL_LEFT; i <= WALL_RIGHT; i++){
		gotoXY(i,WALL_UP);
		cout<<(char)141;
		gotoXY(i,WALL_DOWN);
		cout<<(char)141;
	}
	for(int i = WALL_UP; i <= WALL_DOWN; i++){
		gotoXY(WALL_LEFT,i);
		cout<<(char)141;
		gotoXY(WALL_RIGHT,i);
		cout<<(char)141;
	}
	for(int i = WALL_UP; i <= WALL_DOWN/3; i++){
		gotoXY(WALL_RIGHT/2,i);
		cout<<(char)141;
		
	}
}
bool checkWall(){

	if(ran[0].y == WALL_UP || ran[0].y == WALL_DOWN){
		return true;
	}
	if(ran[0].x == WALL_RIGHT || ran[0].x == WALL_LEFT){
		return true;
	}

	for(int i=0;i< WALL_DOWN/3;i++){
		if(ran[0].y == WALL_DOWN/3-i  && ran[0].x == WALL_RIGHT/2 ){
			return true;
		}
	}
	for(int i=1;i<dotRan;i++){
		if(ran[0].x == ran[i].x && ran[0].y ==ran[i].y){
			return true;
		}
	}
	return false;
}
void gameOver(){	
	Sleep(500);
	clrscr();
	cout<<"GAME OVER"<<endl;
}
ToaDo baits(){
	srand(time(NULL)); 
	int x = WALL_LEFT+1 + rand()%(WALL_RIGHT-WALL_LEFT-1);
	int y = WALL_UP+1 + rand()%(WALL_DOWN-WALL_UP-1);
	gotoXY(x,y);
	setTextColor(YELLOW_COLOR);
	cout<<(char)169;
	ToaDo temp;
	temp.x = x;
	temp.y = y;
	return temp;
	
}
bool checkBaits(ToaDo bait){
	if(ran[0].x == bait.x && ran[0].y == bait.y){
		return true;
	}
	return false;
}
void addRan(){
	ran[dotRan] = ran[dotRan-1];
	dotRan++;
}
void playGame(){
	int direct = Right;
	int score = 0;
	noCursorType();
	init();
	initWall();
	ToaDo bait = baits();
	gotoXY(WALL_LEFT+5,WALL_UP-2);
	setTextColor(BLUE_COLOR);
	cout<<"Score: "<<score;
	Sleep(1000);
	while(1){
		ToaDo ranCuoi = move(direct);
		setTextColor(YELLOW_COLOR);
		show(ranCuoi);
		keyInput(direct);
		if(checkBaits(bait)){
			bait = baits();
			addRan();
			score++;
			gotoXY(WALL_LEFT+5,WALL_UP-2);
			setTextColor(BLUE_COLOR);
			cout<<"Score: "<<score;
		}
		if(checkWall()) break;
		Sleep(200);
	}
	gameOver();
	setTextColor(GREEN_COLOR);
	cout<<"Score: "<<score<<endl;
	cout<<"Do you want replay: (1-Yes)(0-No)";
	cin>>n;
}
int main(){
	/*playGame();
	clrscr();
	while(n==1){
		n=0;
		playGame();
		clrscr();
	}*/
//	setcolor(5);
	

		
}
