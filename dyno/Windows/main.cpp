#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <windows.h>

using namespace std;

bool game_over;
bool blink;
const int height = 10;
const int width = 40;
const int x = width/4;
int y = height-1;
int no_of_obstacles = 1;
int obstacle_x1, obstacle_x2, obstacle_x3;
int obstacle_y1, obstacle_y2, obstacle_y3;
int score = 1;
enum eControl {STOP=0, UP, DOWN};
eControl dir;

void Setup(){
    dir = STOP;
    game_over = false;
    blink = true;
    obstacle_x1 = width-1;
    obstacle_y1 = height-1;
    obstacle_x2 = width+7;
    obstacle_y2 = height-1;
    obstacle_x3 = width+9;
    obstacle_y3 = height-1;

}
void Draw(){
    system("CLS");
    blink = !blink;

    for(int i = 0; i<width+1; i++){
        cout<<"@"<<flush;
    }
    cout<<endl<<flush;
    for(int i = 0; i<height; i++){
        for(int j = 0; j<width; j++){
            if(j == 0)
                cout<<"@"<<flush;
            else if(i == obstacle_y1 && j == obstacle_x1)
                cout<<"|"<<flush;
            else if(i == y && j == x)
                cout<<"#";
            else if(no_of_obstacles > 1 && j == obstacle_x2 && i == obstacle_y2)
                cout<<"|"<<flush;
            else if(no_of_obstacles > 2 && j == obstacle_x3 && i == obstacle_y3)
                cout<<"|"<<flush;
//            else if(i%2 == 0 && j%2 == 0 && blink == true)
//                cout<<"."<<flush;
//            else if(i%2 != 0 && j%2 != 0 && blink == false)
//                cout<<"."<<flush;
            else
                cout<<" "<<flush;
            if(j == width-1){
                cout<<"@"<<flush;
            }
        }
        cout<<endl;
    }

    for(int i = 0; i<width+1; i++){
        cout<<"#"<<flush;
    }
    cout<<endl;
    cout<<"score:"<<score<<endl;
}

void Input(){
     if(kbhit()){
        switch(getch()){
            case 'w':
                dir = UP;
                break;
            case 'x':
                game_over = true;
        }

    }
}

void Logic(){
    switch(dir){
        case UP:
            if(y>=height-2)
                y--;
            break;
        case DOWN:
            y++;
            break;
    }
    if(y<height-2)
        dir = DOWN;

    if(y == height-1)
        dir = STOP;
    if(obstacle_x1 > 0)
        obstacle_x1--;
    if(obstacle_x1 == 0){
        obstacle_x1 = width-1;
        obstacle_y1 = height-1;
        score++;
    }
    if(obstacle_x2 > 0 && no_of_obstacles > 1)
        obstacle_x2--;
    if(obstacle_x2 == 0 && no_of_obstacles > 1){
        obstacle_x2 = width+2;
        obstacle_y2 = height-1;
        score++;
    }
    if(obstacle_x3 > 0 && no_of_obstacles > 1)
        obstacle_x3--;
    if(obstacle_x3 == 0 && no_of_obstacles > 1){
        obstacle_x3 = width+5;
        obstacle_y3 = height-1;
        score++;
    }
    if(score == 2)
        no_of_obstacles = 2;
    if(score == 5)
        no_of_obstacles = 3;
    if((x == obstacle_x1 && y == obstacle_y1) || (x == obstacle_x2 && y == obstacle_y2) || (x == obstacle_x3 && y == obstacle_y3 ))
       game_over = true;
}

int main(){
    Setup();
    while(!game_over){
        Draw();
        Input();
        Logic();
        Sleep(80-(4*score));
    }
    return 0;
}
