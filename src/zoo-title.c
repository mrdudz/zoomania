

void makesprites(void)
{
    memset((char*)0xcf00,0,0x40);
    memset((char*)0xcf00+(19*3),0x55,(1*3));
    memset((char*)0xcf00+(20*3),0xff,(1*3));
    memset((char*)0xcff8,0x3c,8);
    *(unsigned char*)0xd010=0x60;
    *(unsigned char*)0xd000=28;
    *(unsigned char*)0xd002=28+(1*48);
    *(unsigned char*)0xd004=28+(2*48);
    *(unsigned char*)0xd006=28+(3*48);
    *(unsigned char*)0xd008=28+(4*48);
    *(unsigned char*)0xd00a=28+(5*48);
    *(unsigned char*)0xd00c=28+(6*48);
    *(unsigned char*)0xd001=0xa5;
    *(unsigned char*)0xd003=0xa5;
    *(unsigned char*)0xd005=0xa5;
    *(unsigned char*)0xd007=0xa5;
    *(unsigned char*)0xd009=0xa5;
    *(unsigned char*)0xd00b=0xa5;
    *(unsigned char*)0xd00d=0xa5;
    *(unsigned char*)0xd017=0;
    *(unsigned char*)0xd01d=0x7f;
    *(unsigned char*)0xd01c=0x7f;
    *(unsigned char*)0xd01b=0;

    *(unsigned char*)0xd025=0;
    *(unsigned char*)0xd026=1;
}

void killsprites(void)
{
    *(unsigned char*)0xd015=0;
}

void __fastcall__ title_wipe(unsigned char l)
{
    unsigned char *ptr1 = (unsigned char*)0xcc00+(l);
    unsigned char *ptr2 = (unsigned char*)0xd800+(l);
    l = 18;
    while (l--) {
        *ptr1 = 0;
        *ptr2 = 0;
        ptr1 += 40;
        ptr2 += 40;
    }

}

void title_dofade(void)
{
    fld_done = 0;
    while (fld_done < 56) {
        waitframe();
        fld(fld_done);
        if(fld_done<40) {
            title_wipe(fld_done);
        }
        if(fld_done<32) {
        *(char*)0x101b = 0x0f - (fld_done>>1); /* fade music */
        }
        fld_done++;

    }
}

void title_init(void)
{
    memmove((char*)0xe000,&bmp_data,TITLE_LINES*320);
    memmove((char*)0xcc00,(char*)(&bmp_data + TITLE_LINES*320),TITLE_LINES*40);
    memmove((char*)0xd800,(char*)(&bmp_data + TITLE_LINES*40 + TITLE_LINES*320),TITLE_LINES*40);
    makesprites();
}

void title_screen(void)
{
    unsigned char j1,j2,k,c,choice = 0;

    while(1) {
        stop = 1;
        players = pl = team = demo = choice = tt = 0;
        screen_off();
        killsprites();
        cursor_off();
        title_init();
        fill();
        memset((unsigned char*)0x400,0,40*TITLE_LINES);
        revers(1);
        textcolor(1);cputsxy(12,18,     "one player game");
        textcolor(0x0d);cputsxy(12,19,  "two player team");
        textcolor(7); cputsxy(11,20,    "two player battle");
        textcolor(0x0d); cputsxy(15,21, "highscores");
        textcolor(9); cputsxy(1,22,    "final");
        textcolor(9);
        if(*(char*)0x2a6) {
            cputsxy(35,22,"pal");
        } else {
            cputsxy(34,22,"ntsc");
        }
        init_msx(2);
        fld(0);
        do_bar(0);
        title_irq();

        while (!demo) {
            waitframe();
            do_bar(choice);

            j1 = *(char*)0xdc01; /* joy #1 */
            j2 = *(char*)0xdc00; /* joy #2 */
            c = *(char*)0xc5; /* matrix value of key */

            if ((j1 == 239)||(j2 == 111)||(c == 1)||(getshift())) {
                /* fire or enter selects menu item */
                if(!((choice==0)&&(j1 == 239))) {
                    break;
                }
            } else if ((c == 18)) {
                /* "d" enters demo mode */
                demo = 1;
                break;
            } else if ((j1 == 254)||(j2 == 126)||(c == 9)) {
                /* joy up or "w" - menu item up */
                if (choice){
                    for (k=0;k<8;++k){
                        waitframe();
                        do_bar(--choice);
                    }
                }
            } else if ((j1 == 253)||(j2 == 125)||(c == 13)){
                /* joy down or "s" - menu item down */
                if (choice < 24){
                    for (k=0;k<8;++k){
                        waitframe();
                        do_bar(++choice);
                    }
                }
            }
        }

        if (demo) {
            break;
        } else {
            choice>>=3;

            if (choice == 0){
                break;
            } else if (choice == 1){
                team = 1;
                break;
            } else if (choice == 2){
                players = 1;
                break;
            } else if (choice == 3){
                title_dofade();
                killsprites();
                show_highscores();
            }
        }
    }

    /* exit title screen */
    title_dofade();
    killsprites();
    game_irq();

    fill();
    *(char*)0xd016 = 0x10;

    if (demo) {
        txt_mode();
        print2x2_centered("demo mode",7,8,10);
        delay(DEMO_START_DELAY);
    }
}
 
