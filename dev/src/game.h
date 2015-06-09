#ifndef QUIZ_H
#define QUIZ_H



// minimum 16-bit unsigned int 2D vector
typedef struct {
    uint_fast16_t x;
    uint_fast16_t y;
} vec2ui;


// at least 16-bit int 2D vector
typedef struct {
    uint_fast16_t x;
    uint_fast16_t y;
} vec2i;


// simple rectangle type
typedef struct {
    vec2i offset;
    vec2i bounds;

    uint_fast16_t top() { return offset.x; }
    uint_fast16_t left() { return offset.y; }
    uint_fast16_t right() { return bounds.y; }
    uint_fast16_t bot() { return bounds.x; }
} rect;


struct {
    vec2i pos;
    vec2i dir;
    char disp_char;
} player;


int cur_width = 0, cur_height = 0;



int init();
void run();

void skipMenu(bool);
void setDifficulty(int);
void setTime(int);

void setColorscheme(short fg, short bg);
void winResize(int &orig_x, int &orig_y);
void setFrame();

#endif
