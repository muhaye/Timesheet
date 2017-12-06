#include <stdlib.h>
#include <stdlib.h>
#include <stdio.h>  
#include <setjmp.h>
#include "hpdf.h"
#include "read_rc_file.h"
#include "pdf_printer.h"

jmp_buf env;

void error_handler (HPDF_STATUS error_no, HPDF_STATUS detail_no, void *user_data) {
        printf ("ERROR: error_no=%04X, detail_no=%d\n",
                      (unsigned int) error_no, (int) detail_no);
            longjmp (env, 1); /* invoke longjmp() on error */
}

const int LINE_SPACE = 12;

typedef struct frm frm;
struct frm {
    int x;
    int y;    
};

typedef struct range range;
struct range {
    int from;
    int to;
};

frm frm_position[3] = {
    { .x = 100, .y = 300},
    { .x = 200, .y = 300},
    { .x = 300, .y = 300} };

void print_frame(HPDF_Page page,  int x, int y, int height) {
    /* print the lines of the page. */
    HPDF_Page_SetLineWidth (page, 1);
    HPDF_Page_Rectangle (page, x, y, 60, height);
    HPDF_Page_Stroke (page);
}

void print_value(HPDF_Page page, 
        HPDF_Font font, 
        Table table, 
        range from_to,  
        int x, int y) {

    struct nlist* result = read_rc_config();

    int num_elem = from_to.to - from_to.from + 1 ;

    print_frame(page, 
            x,
            400 - num_elem * LINE_SPACE,
            (num_elem * LINE_SPACE) + 20
            );

    print_frame(page, 
            x,
            400 - num_elem * LINE_SPACE,
            num_elem * LINE_SPACE
            );

    int top = 390; 

    for(int i=0; i<2; i++ ) {
        print_frame(page, 
                300,
                400 - 2 * LINE_SPACE,
                (2 + i) * LINE_SPACE
                );
    }

    /* print the title of the page (with positioning center). */
    HPDF_Page_SetFontAndSize (page, font, 10);
    HPDF_Page_BeginText (page);
    char day[3]; 
    char hours[7];

    for(int i = from_to.from; i < from_to.to; i++ ) { 
        sprintf(day, "%2d", table.day_hours[i].day);
        sprintf(hours, "%3.1f", table.day_hours[i].hours);
        int t = top - (i - from_to.from) * LINE_SPACE ;
        HPDF_Page_TextOut (page, x + 10, t, day);
        HPDF_Page_TextOut (page, x + 40, t, hours);
    }

    float sum_h = 0.0;
    for( int i = 0; i < table.total; i++) 
        sum_h += table.day_hours[i].hours;
    
    sprintf(hours, "%5.1f", sum_h );
    HPDF_Page_TextOut (page, 320, 380, hours);
    HPDF_Page_TextOut (page, 105, 405, "Date  Hours");
    HPDF_Page_TextOut (page, 205, 405, "Date  Hours");
    HPDF_Page_TextOut (page, 330, 405, "Total");

    
    HPDF_Page_SetFontAndSize (page, font, 7);
    HPDF_Page_TextOut(page, 40, 80,lookup("note")->defn);

    HPDF_Page_SetFontAndSize (page, font, 11);
    int cursor_height = HPDF_Page_GetHeight(page) - 30 ;
    HPDF_Page_TextOut(page, 40, cursor_height  , "TimeSheet") ;

    HPDF_Page_SetFontAndSize (page, font, 10);
    cursor_height -= 20;
    HPDF_Page_TextOut(page, 40, cursor_height ,lookup("agency_name")->defn) ;

    cursor_height -= 12;
    HPDF_Page_TextOut(page, 40, cursor_height ,lookup("agency_address")->defn) ;

    cursor_height -= 12;
    HPDF_Page_TextOut(page, 40, cursor_height ,lookup("agency_location")->defn) ;

    cursor_height -= 12;
    HPDF_Page_TextOut(page, 40, cursor_height ,lookup("agency_postal_code")->defn) ;

    result = lookup("agency_phone");
    cursor_height -= 12;
    HPDF_Page_TextOut(page, 40, cursor_height ,result->defn) ;

    result = lookup("client");
    cursor_height -= 40;
    HPDF_Page_TextOut(page, 40, cursor_height , "Client:") ;
    HPDF_Page_TextOut(page, 200, cursor_height , result->defn) ;

    cursor_height -= 12;
    HPDF_Page_TextOut(page, 40, cursor_height , "Client Contact Name:") ;
    HPDF_Page_TextOut(page, 200, cursor_height ,lookup("contact")->defn) ;

    cursor_height -= 12;
    HPDF_Page_TextOut(page, 40, cursor_height , "Consultant Name:") ;
    HPDF_Page_TextOut(page, 200, cursor_height ,lookup("name")->defn) ;

    HPDF_Page_TextOut(page, 400, 160, "Consultant Signature:") ;
    HPDF_Page_TextOut(page, 500, 160, "____________________________") ;

    HPDF_Page_TextOut(page, 420, 130, "Client Signature:") ;
    HPDF_Page_TextOut(page, 500, 130, "____________________________") ;

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
    HPDF_Page_SetSize (page, HPDF_PAGE_SIZE_A4, HPDF_PAGE_LANDSCAPE);

    range range[2] = { { .from = 0, .to = 15 },
                       { .from = 15, .to = table.total }
                         };
    for(int i=0; i < 2; i++ ) {

        print_value(page, 
                font,
                table,
                range[i], 
                frm_position[i].x,
                frm_position[i].y);
    }

    HPDF_SaveToFile (pdf, "bin/test.pdf");

    return 0;
}
