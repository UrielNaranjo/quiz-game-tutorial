#include <unistd.h>
#include <ncurses.h>

#include <cstdint>
#include <string>

#include "game.h"



WINDOW* wnd;



int init() {

    wnd = initscr();
    cbreak();
    noecho();
    clear();
    refresh();
    setFrame();

    // enable function keys
    keypad(wnd, true);

    // disable input blocking
    nodelay(wnd, true);

    // enable color
    if(!has_colors()) {
        endwin();
        printf("ERROR: Terminal does not support color.\n");
        exit(1);
    }

    start_color();

    setColorscheme(COLOR_WHITE, COLOR_BLACK);

    return 0;
}



void run() {

    getmaxyx(wnd, cur_width, cur_height);

    // define area for movement
    rect game_area = { { 1, 1}, { 20, 80 } };
    
    player.disp_char = '0';
    player.pos = {1, 6};
    int in_char;
    bool exit_requested = false;
    curs_set(0);

    while(1) {
    
        winResize(cur_width, cur_height);
    
        in_char = wgetch(wnd);

        mvaddch(player.pos.y, player.pos.x, ' ');

        switch(in_char) {
            case 'q': 
                exit_requested = true; 
                break;
            case KEY_UP:
            case 'w':
                if(player.pos.y > game_area.top())
                    player.pos.y -= 1;
                break;
            case KEY_DOWN:
            case 's':
                if(player.pos.y <= game_area.bot())
                    player.pos.y += 1;
                break;
            case KEY_LEFT: 
            case 'a':
                if(player.pos.x > game_area.left())
                    player.pos.x -= 1;
                break;
            case KEY_RIGHT: 
            case 'd':
                if(player.pos.x <= game_area.right())
                    player.pos.x += 1; 
                break;
            default: 
                break;
        }

        mvaddch(player.pos.y, player.pos.x, player.disp_char); // (y, x)
        refresh();

        if(exit_requested) break;

        //nanosleep({0, 1000000000}, NULL);
        usleep(10000);
    };

    endwin();
}



void setColorscheme(short fg, short bg) {
    init_pair(1, fg, bg);
    wbkgd(wnd, COLOR_PAIR(1));
}



void setFrame(){
    // creates simple frame around window composed of vertical and horizontal lines
    box(wnd, 0, 0);
    
    // border characters can be set manually using the border function
    // border( wnd, leftside, rightside, topside, bottom side, tlcorner, 
    //                                      trcorner, blcorner, brcorner);
    
}



void winResize(int &orig_width, int &orig_height){
    int new_width, new_height;

    getmaxyx(wnd, new_width, new_height); 

    // if window dimensions have changed, update border
    if(new_width != orig_width || new_height != orig_height){
        orig_width = new_width;
        orig_height = new_height;
        
        wresize(wnd, new_height, 0);
        mvwin(wnd, new_height, 0);
        
        wclear(wnd);
        setFrame();
    }

}
