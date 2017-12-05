#include <stdlib.h>
#include <stdlib.h>
#include <stdio.h>  
#include <setjmp.h>
#include "hpdf.h"
#include "pdf_printer.h"

jmp_buf env;

void error_handler (HPDF_STATUS error_no, HPDF_STATUS detail_no, void *user_data)
{
        printf ("ERROR: error_no=%04X, detail_no=%d\n",
                      (unsigned int) error_no, (int) detail_no);
            longjmp (env, 1); /* invoke longjmp() on error */
}

int LINE_SPACE = 12;

typedef struct frm frm;
struct frm {
    int x;
    int y;    
};

frm frm_position[2] = {
    { .x = 100, .y = 300},
    { .x = 200, .y = 300} };

void print_frame(HPDF_Page page,  int x, int y) {
    /* print the lines of the page. */
    HPDF_Page_SetLineWidth (page, 1);
    HPDF_Page_Rectangle (page, x, y, 60, LINE_SPACE * 20);
    HPDF_Page_Stroke (page);
}

void print_value(HPDF_Page page, HPDF_Font font, Table table, int x, int y) {

    /* print the title of the page (with positioning center). */
    HPDF_Page_SetFontAndSize (page, font, 10);
    HPDF_Page_BeginText (page);
    char day[3]; 
    char hours[5];
    int top = y - 10 + table.total * LINE_SPACE;
    for(int i = 0; i <table.total; i++ ) { 
        sprintf(day, "%2d", table.day_hours[i].day);
        sprintf(hours, "%3.1f", table.day_hours[i].hours);
        HPDF_Page_TextOut (page, x + 10, top - (i * LINE_SPACE ), day);
        HPDF_Page_TextOut (page, x + 40, top - (i * LINE_SPACE ), hours);
    }
    HPDF_Page_EndText (page);
}

int pdf_printer(Table table) {

    HPDF_Doc pdf;
    HPDF_Font font;
    float tw;

    pdf = HPDF_New (error_handler, NULL);
    if (!pdf) {
        printf ("ERROR: cannot create pdf object.\n");
        return 1;
    }

    if (setjmp(env)) {
        HPDF_Free (pdf);
        return 1;
    }

    /* set compression mode */
    HPDF_SetCompressionMode (pdf, HPDF_COMP_ALL);

    /* create default-font */
    font = HPDF_GetFont (pdf, "Helvetica", NULL);

    HPDF_Page page;

    page = HPDF_AddPage (pdf);

    for(int i=0; i < 2; i++ ) {
        print_frame(page, 
                frm_position[i].x,
                frm_position[i].y);

        print_value(page, 
                font,
                table,
                frm_position[i].x,
                frm_position[i].y);
    }


    HPDF_SaveToFile (pdf, "bin/test.pdf");

    return 0;
}
