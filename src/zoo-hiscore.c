void __fastcall__ highscores_wipe(unsigned char l)
{
    unsigned char *ptr2 = (unsigned char*)0xd800+(l);
    l = 25;
    while (l--) {
        *ptr2 = 0;
        ptr2 += 40;
    }

}

void highscores_dofade(void)
{
unsigned char done = 0;
    while (done < 40) {
        waitframe();
        highscores_wipe(done);
        if (done < 32) {
            *(char*)0x101b = 0x0f - (done>>1); /* fade music */
        }
        done++;
    }
}

/* show the highscore table.
   - leaves the screen blanked!
*/
void show_highscores(void)
{
    static unsigned char i,j,k;

    screen_off();
    init_msx(0);
    fill();
    hs_irq();
    txt_mode();

    print2x2_centered("highscores",1,15,0);
    for (i=0;i<10;++i) {
        sprintf(str_dummy,"%-10s %06lu-%02d",highscore[i].name,highscore[i].score,highscore[i].level);
        print2x2_centered(str_dummy,hs_coltab1[i],hs_coltab2[i],3+(i<<1));
    }
    revers(1);textcolor(15);
    cputsxy(9,24,"[s] to save highscores");
    screen_on();

    while(1) {

        waitframe();

        ++j;
        if ((j & 3) == 0) {
            ++i;
            memset((char*)0xdbc9,hs_coltab3[i&7],22);
        }

        k = getkey();
        if (k == 's') {
            screen_off();
            save_hs();
            screen_on();
        } else if (k == 13) {
            break;
        }

        if (*(char*)0xdc00 == 111) {
            break;
        }
        if (*(char*)0xdc01 == 239) {
            break;
        }
        if (getshift()) {
            break;
        }
    }

    highscores_dofade();
    screen_off();
    fill();
}
 
void time_out_screen(void)
{
    char *s;
    unsigned char i,l,p;
    unsigned char c = 0;
    static unsigned char blink = 0;

    if (demo) {
        return;
    }

    for (p=0;p<players+1;++p){
        for (i=0;i<10;++i){
                if (score[p] > highscore[i].score)
                        break;
        }
        if (i != 10){
            for (l=9;l>i;--l){
                    strcpy(highscore[l].name,highscore[l-1].name);
                    highscore[l].score = highscore[l-1].score;
                    highscore[l].level = highscore[l-1].level;
            }
            hs_irq();
            txt_mode();
            init_msx(5);
            if (team)
                    sprintf(str_dummy,"well done, team!");
            else
                    sprintf(str_dummy,"well done player %d",p+1);
            print2x2_centered(str_dummy,7,8,8);
            sprintf(str_dummy,"#%d score: %06lu",i+1,score[p]);
            print2x2_centered(str_dummy,10,2,10);
            print2x2_centered("enter your name:",4,3,14);
            l = 0;
            s = highscore[i].name;
            *s = '\0';

            while(1){
                waitframe();
                ++blink;
                if(blink&0x20) {
                    plot2x2_xy(0x20,20+(l),17,15,12);
                } else {
                    plot2x2_xy(0x3c,20+(l),17,1,15);
                }
                if (*(char*)0xdc00 == 111 && l == 0){
                    strcpy(highscore[i].name,"mr. button");
                    print2x2_centered(highscore[i].name,15,12,17);
                    delay(50);
                    break;
                }
                c = getkey();
                if (c == 13) {
                    break;
                } else if (c == 20) {
                    if (l) {
                        *(--s) = '\0';
                        --l;
                        memset((char*)(0x0400 + 17*40),0xff,80);
                    }
                } else if (!isprint(c)) {
                    continue;
                } else if (++l == 11) {
                    l = 10;
                    continue;
                } else {
                    *s++ = c;
                    *s = '\0';
                }
                print2x2_centered(highscore[i].name,15,12,17);
            }
            highscore[i].score = score[p];
            highscore[i].level = level;
            show_highscores();
        }
    }
}

