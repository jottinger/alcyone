#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

#include <ncurses.h>
#include "mcp23008.h"
#include "debounce.h"
#include "wiringPi.h"
#include "serial.h"

std::vector<MCP23008> mcps;
Debouncer debouncer[13];
SerialDevice midiOut;
int previousState[13];
int octave=2;
int transposition=0;
int channel=1;
int velocity=127;
int exitAlcyone=0;

void setup();
void shutdown();
void flare();
void loop();
void noteOn(int note);
void noteOff(int note);

void drawConstellation(WINDOW*win, int maxx, int maxy);
void showStatus(WINDOW* win, int octave, int transposition);

int maxx, maxy;

int main(int argc, char **argv) {
    setup();
    while(!exitAlcyone) {
        loop();
    }
    shutdown();
    return 0;
}

void shutdown() {
    endwin();
}

void showStatus(WINDOW* win, int octave, int transposition) {
    attron(COLOR_PAIR(3));
    mvwprintw(win, 13, 8, "%2d", octave);
    mvwprintw(win, 13, 33, "%3d", transposition);
}

void drawConstellation(WINDOW* win, int maxx, int maxy) {
    // ordinary stars; alcyone is at 9,4
    int starx[]= {2, 1, 5, 6, 7, 9,  8, 9,11,12};
    int stary[]= {3, 6, 5, 7, 7, 8, 10,11, 8, 9};
    attron(COLOR_PAIR(1));
    for(int index=0; index<10; index++) {
        mvwaddch(win, stary[index], starx[index], '.');
    }
    attron(COLOR_PAIR(2));
    mvwprintw(win, 4, 9, "* Alcyone");
    attron(COLOR_PAIR(3));

    mvwprintw(win, 13, 0, "Octave:    (O/L)  Transposition:     (I/K)");
    mvwprintw(win, 14, 25, "Reset, Quit (R/Q)");
}

void setup() {
    initscr();
    if(has_colors()==FALSE) {
        std::cout << "Terminal does not support color." << std::endl;
        exit(1);
    }
    start_color();
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_WHITE, COLOR_BLACK);

    nodelay(stdscr, true);
    getmaxyx(stdscr, maxy, maxx); // macro so no pointers
    drawConstellation(stdscr, maxx, maxy);
    showStatus(stdscr, octave, transposition);
    refresh();
    noecho();

// set up the two input I2C chips
    for(int i=0; i<2; i++) {
        MCP23008 mcp(i);
        mcp.modeAll(MODE_INPUT);
        mcps.push_back(mcp);
    }
    MCP23008 util(2);
    util.pinMode(0, MODE_OUTPUT);
    util.pinMode(1, MODE_OUTPUT);
    util.pinMode(2, MODE_OUTPUT);
    util.pinMode(3, MODE_INPUT);
    mcps.push_back(util);
    flare();
    for(int i=0; i<13; i++) {
        previousState[i]=0;
    }
}

void loop() {
    int key=getch();
    if(key!=ERR) {
        switch(key) {
        case 'q':
        case 'Q':
            exitAlcyone=1;
            break;
        case 'o':
        case 'O':
            octave-=(octave>2?1:0);
            showStatus(stdscr, octave, transposition);
            refresh();
            break;
        case 'l':
        case 'L':
            octave+=(octave<8?1:0);
            showStatus(stdscr, octave, transposition);
            refresh();
            break;
        case 'i':
        case 'I':
            transposition-=(transposition>-12?1:0);
            showStatus(stdscr, octave, transposition);
            refresh();
            break;
        case 'k':
        case 'K':
            transposition+=(transposition<12?1:0);
            showStatus(stdscr, octave, transposition);
            refresh();
            break;
        }
    }
    int data[2];
    data[0]=mcps[0].read();
    data[1]=mcps[1].read();
    for(int pin=0; pin<13; pin++) {
        int datum=data[pin/8];
        int state=debouncer[pin].debounce(decode(datum, pin%8));
        if(state!=previousState[pin]) {
            if(previousState[pin]) { // new state: OFF
                 noteOff(pin);
            } else {
                 noteOn(pin);
            }
            previousState[pin]=state;
        }
    }
}

int state=1;

void flare() {
    MCP23008 mcp=mcps.at(2);
    for(int count=0; count<4; count++) {
        for(int state=1; state>-1; state--) {
            for(int pin=0; pin<3; pin++) {
                mcp.writePin(pin, state);
                delay(75);
            }
        }
    }
}

void noteOn(int note) {
    midiOut.send(0x90);
    midiOut.send(note+octave*12+transposition);
    midiOut.send(127);

}
void noteOff(int note) {
    midiOut.send(0x80);
    midiOut.send(note+octave*12+transposition);
    midiOut.send(127);
}

