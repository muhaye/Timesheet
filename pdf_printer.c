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

int my_pdf_printer(char *text) {

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
    /* print the title of the page (with positioning center). */
    HPDF_Page_SetFontAndSize (page, font, 24);
    tw = HPDF_Page_TextWidth (page, text);
    HPDF_Page_BeginText (page);
    HPDF_Page_TextOut (page, (HPDF_Page_GetWidth(page) - tw) / 2,
            HPDF_Page_GetHeight (page) - 50, text);
    HPDF_Page_EndText (page);
    HPDF_SaveToFile (pdf, "test.pdf");

    return 0;
}
