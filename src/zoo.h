// zoo.h

#include <stdio.h>
#include <cbm.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <stdlib.h>
#include <ctype.h>

#define DEBUG 0

#define EMPTY_SYMB      0xff
#define JOKER_SYMB      0xb0

#define DEMO_DELAY            (50/4)
#define DEMO_START_DELAY      (50*2)
#define DEMO_TIMEOUT_DELAY    (50*2)

#define MATRIX_HIT_DELAY      (50/2)
#define MATRIX_SCORE_DELAY    (50/3)
#define START_DELAY           (50/2)
#define TIMEOUT_BLINK_DELAY   (50/2)

#define XOFFS           2
#define TIME_BONUS      2

#define fire_up         110
#define fire_down       109
#define fire_left       107
#define fire_right      103
#define port2_fire      111
#define nothing         127

#define TITLE_LINES     17

// globals

extern char cue[16];
extern char cue_max,demo;

extern struct hs{
    char name[11];
    char level;
    unsigned long score;
} highscore[10];

// extern variables & function prototypes from assembler file "zoo_ass.s"

extern char bmp_data;
extern unsigned char is_title,animals,joystick_delay,key,keyboard,up,down,left,right,matrix[8][8],colortab[8];
extern unsigned char timer_delay,time_out,stop,joker,joker_tmp,players;
extern unsigned char joker_x,joker_y;
extern unsigned int time1;
extern signed char xdir1,ydir1,xdir2,ydir2,xpos1,ypos1,xpos2,ypos2;
extern unsigned char level,pm_x1,pm_x2,pm_y1,pm_y2,pl,fld_done;
extern unsigned char team,tt;

void title_irq(void);
void game_irq(void);
void inter_irq(void);
void hs_irq(void);

void __fastcall__ init_msx(unsigned char tune);
void __fastcall__ setgfx(int);
void __fastcall__ waitframe(void);
void __fastcall__ detectvideo(void);
void random_init(void);
unsigned char random(void);
unsigned char __fastcall__ pet2scr(unsigned char);
unsigned char isstop(void);
void wait_for_key_or_joy(void);
void __fastcall__ print2x2_centered(char *str,char color1, char color2,char line);
void __fastcall__ plot2x2_xy (char c,char x,char y,char color1,char color2);
void ass_setup(void);
void sprites_setup(void);
void cursor_on(void);
void cursor_off(void);

void gfx_setup(void);
void gfx_mode(void);
void txt_mode(void);
void __fastcall__ setxy(char x,char y);
void __fastcall__ plot_score(unsigned s,char x,char y);
void __fastcall__ print_num(unsigned long sc,char n,char x,char y);
void __fastcall__ print3x3(char symb,char x, char y);
void print_hits(void);
void print_matrix(void);
void broesel(void);
void no_more_moves(void);
void show_highscores(void);
void title_screen(void);
void level_up_screen(void);
void time_out_screen(void);
void pause_screen(void);
void display_time(void);
void kill_joker(void);
unsigned char __fastcall__ check_moves(void);
void move_matrix(void);
void __fastcall__ check_matrix(unsigned char fo);
void fill_matrix(void);
void __fastcall__ clone(char i, char j,char s);
void __fastcall__ swap(char x, char y,char xswap,char yswap);
unsigned char yesno(void);
void fill(void);
void load_hs(void);
void save_hs(void);
void appear(void);
unsigned char getkey(void);
unsigned char getshift(void);
void __fastcall__ print2spr(char*,char);
void __fastcall__ put2cue(char);
void __fastcall__ do_bar(char);
void __fastcall__ delay(char);
void __fastcall__ fld(char);
void screen_on(void);
void screen_off(void);
void sync_irq_timer(void);
void __fastcall__ joker_hit(char pl);
