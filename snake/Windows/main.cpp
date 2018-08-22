#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <conio.h>

using namespace std;
bool game_over;
const int height = 20;
const int width = 20;
int x, y, FruitX, FruitY;
int score;
enum eDirection {STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;

void Setup(){
    game_over = false;
    dir = STOP;
    x = width/2;
    y = height/2;
    FruitX = rand()%width;
    FruitY = rand()%height;
    score = 0;
}

void Draw(){
    system("CLS");
    // do try the other method that you experimented with.
    for(int i = 0; i<width+2; i++){
        cout<<"#";
    }
    cout<<endl<<flush;
    for(int i = 0; i<height; i++){
        for(int j = 0; j<width; j++){
            if(j == 0)
                cout<<"#"<<flush;
            if(i == y && j == x)
                cout<<"O";
            else if(i == FruitY && j == FruitX)
                cout<<"F"<<flush;
            else
                cout<<" "<<flush;
            if(j == width-1){
                cout<<"#"<<flush;
            }
        }
        cout<<endl;
    }

    for(int i = 0; i<width+2; i++){
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
            case 's':
                dir = DOWN;
                break;
            case 'd':
                dir = RIGHT;
                break;
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
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
    }
    if(x<0 || x>width || y>height || y<0)
        game_over = true;
    if(x == FruitX && y == FruitY){
        score+= 5;
        FruitX = rand()%width;
        FruitY = rand()%height;
    }
}

int main(){
    Setup();
//    cout<<dir<<endl;
    while(!game_over){
        Draw();
        Input();
        Logic();
        Sleep(100);

    }
    return 0;
}
