#include "include/raylib.h"
#define PLAYER_HEIGHT 80
#define PLAYER_WIDTH  80
#define AMO_HEIGHT 16
#define AMO_WIDTH 8
#define NUM_SHOOT 6

typedef struct{
    Rectangle rec;
    Vector2 speed;
    Color Color;
} Player;

typedef struct{
    Rectangle rec;
    Vector2 speed;
    bool active;
    Color Color;
}shoot;

static Player player={0};
static shoot amo[NUM_SHOOT] ={0};
static int shootRate = 0;
static int bulit_speed = 16;

int main(){
    int Width = 800,Height=400;

    InitWindow(Width*2,Height*2,"bisc window");
    SetTargetFPS(60);
    // define plyer
    player.rec.x=Width;
    player.rec.y=(Height-PLAYER_HEIGHT)*2;
    player.rec.height=PLAYER_HEIGHT;
    player.rec.width=PLAYER_WIDTH;
    player.Color = RED;
    player.speed.x = 5;

    // amo specse
    for (int i = 0; i < NUM_SHOOT; i++){
        amo[i].active=false;
        amo[i].rec.height=AMO_HEIGHT;
        amo[i].rec.width=AMO_WIDTH;
        amo[i].speed.y = bulit_speed;
        amo[i].Color = BLACK;
    }
    
    while (!WindowShouldClose())
    {
        if (IsKeyDown(KEY_A)) player.rec.x -= player.speed.x;
        if (IsKeyDown(KEY_D)) player.rec.x += player.speed.x;
        if(IsKeyDown(KEY_SPACE)){
            shootRate += 1;
            for (int i = 0; i < NUM_SHOOT; i++)
            {
                if(!amo[i].active && shootRate%4==0){
                    amo[i].rec.x = player.rec.x + (player.rec.width-AMO_WIDTH)/2;
                    amo[i].rec.y = player.rec.y;
                    amo[i].active=true;
                    break;
                }
            }
        }
        BeginDrawing();
        ClearBackground(WHITE);
        DrawRectangleRec(player.rec,player.Color);
        for (int i = 0; i < NUM_SHOOT; i++){
            if(amo[i].active){
                amo[i].rec.y-=amo[i].speed.y;
                DrawRectangleRec(amo[i].rec,amo[i].Color);
                if((amo[i].rec.y + AMO_HEIGHT/2) == 0){
                    amo[i].active=false;
                }
            }
        }
        
        EndDrawing();

    }
    
    return 0;
}