#include <iostream>
#include <chrono>
#include <thread>
#include "getch.c"
#include "kbhit.c"

using namespace std;

bool game_over;
bool blink;
const int height = 18;
const int width = 30;
const int y = height-1;
int x;
int no_of_obstacles = 1;
int obstacle_x1, obstacle_x2, obstacle_x3;
int obstacle_y1, obstacle_y2, obstacle_y3;
int score = 0;
enum eControl {STOP=0, LEFT, RIGHT};
eControl dir;

void Setup(){
    dir = STOP;
    game_over = false;
    blink = true;
    x = width/2;
    obstacle_x1 = rand()%(width-2)+1;
    obstacle_y1 = 0;
    obstacle_x2 = rand()%(width-2)+1;
    obstacle_y2 = -3;
    obstacle_x3 = rand()%(width-2)+1;
    obstacle_y3 = -4;
    
}
void Draw(){
    system("clear");
    blink = !blink;
    
    for(int i = 0; i<width+1; i++){
        cout<<"#"<<flush;
    }
    cout<<endl<<flush;      
    for(int i = 0; i<height; i++){
        for(int j = 0; j<width; j++){
            if(j == 0)
                cout<<"#"<<flush;
            else if(i == obstacle_y1 && j == obstacle_x1)
                cout<<"@"<<flush;
            else if(i == y && j == x)
                cout<<"=";
            else if(no_of_obstacles > 1 && j == obstacle_x2 && i == obstacle_y2)
                cout<<"@"<<flush;
            else if(no_of_obstacles > 2 && j == obstacle_x3 && i == obstacle_y3)
                cout<<"@"<<flush;
            else if(i%2 == 0 && j%2 == 0 && blink == true)
                cout<<"."<<flush;
            else if(i%2 != 0 && j%2 != 0 && blink == false)
                cout<<"."<<flush;
            else
                cout<<" "<<flush;
            if(j == width-1){
                cout<<"#"<<flush;
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
            case 'a':
                dir = LEFT;
                break;
            case 'd':
                dir = RIGHT;
                break;
            case 'x':
                game_over = true;
        }
        
    }
}

void Logic(){
    switch(dir){
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;    
    }
    if(x == 0 || x == width-1)
        game_over = true;
    if(obstacle_y1 < height)
        obstacle_y1++;
    if(obstacle_y1 == height){
        obstacle_x1 = rand()%(width-2)+1;
        obstacle_y1 = 0;
        score++;    
    }
    if(obstacle_y2 < height && no_of_obstacles > 1)
        obstacle_y2++;
    if(obstacle_y2 == height && no_of_obstacles > 1){
        obstacle_x2 = rand()%(width-2)+1;
        obstacle_y2 = -3;
        score++;    
    }
    if(obstacle_y3 < height && no_of_obstacles > 2)
        obstacle_y3++;
    if(obstacle_y3 == height && no_of_obstacles > 2){
        obstacle_x3 = rand()%(width-2)+1;
        obstacle_y3 = -4;
        score++;    
    }
    if(score == 2)
        no_of_obstacles = 2;
    if(score == 4)
        no_of_obstacles = 3;
    if((x == obstacle_x1 && y == obstacle_y1)||( x == obstacle_x2 && y == obstacle_y2)) 
       game_over = true;
    }

int main(){
    Setup();
    while(!game_over){
        Draw();
        Input();
        Logic();
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
    }
    return 0;
}