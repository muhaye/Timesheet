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

    /* print the lines of the page. */
    HPDF_Page_SetLineWidth (page, 1);
    HPDF_Page_Rectangle (page, 50, 50, HPDF_Page_GetWidth(page) - 100,
                HPDF_Page_GetHeight (page) - 110);
    HPDF_Page_Stroke (page);

    /* print the title of the page (with positioning center). */
    HPDF_Page_SetFontAndSize (page, font, 10);
    //tw = HPDF_Page_TextWidth (page, text);
    HPDF_Page_BeginText (page);
    char day[3]; 
    char hours[12];
    int line_spane =  12;
    HPDF_REAL p_top = HPDF_Page_GetHeight(page) - 50;
    for(int i = 0; i <table.total; i++ ) { 

        sprintf(day, "%2d", table.day_hours[i].day);
        sprintf(hours, "%10.1f", table.day_hours[i].hours);
        HPDF_Page_TextOut (page, 30, p_top - (i * line_spane ), day);
        HPDF_Page_TextOut (page, 60, p_top - (i * line_spane ), hours);
    }

    HPDF_Page_EndText (page);
    HPDF_SaveToFile (pdf, "bin/test.pdf");

    return 0;
}
