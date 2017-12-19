#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int main() {
   int err;
   regex_t preg;
   const char *str_request = "r11-31";
   const char *str_regex = "r([0-3]?[0-9]{1})-([0-3]?[0-9]{1})()";

   err = regcomp (&preg, str_regex, REG_EXTENDED);
   if (err == 0)
   {
      int match, match_count;
      match_count = 3;
      size_t nmatch = 0;
      regmatch_t *pmatch = NULL;
      
      nmatch = preg.re_nsub;
      pmatch = malloc (sizeof (*pmatch) * nmatch);
      if (pmatch)
      {
         match = regexec (&preg, str_request, nmatch, pmatch, 0);
         regfree (&preg);
         if (match == 0)
         {
            char *word[match_count];
            int start[match_count]; 
            int end[match_count];
            size_t size[match_count];
            
            for (int i = 0; i < match_count  ; i++) {
                start[i]= pmatch[i].rm_so;
                end[i] = pmatch[i].rm_eo;
                size[i] = end[i] - start[i];
                
                printf ("match: [%i-%i] %i => %.*s\n", 
                start[i], 
                end[i], 
                i, 
                size[i],
                &str_request[start[i]]);

            }
            
         }
         else if (match == REG_NOMATCH)
         {
            printf ("%s n\'est pas une adresse internet valide\n", str_request);
         }
         else
         {
            char *text;
            size_t size;

            size = regerror (err, &preg, NULL, 0);
            text = malloc (sizeof (*text) * size);
            if (text)
            {
               regerror (err, &preg, text, size);
               fprintf (stderr, "%s\n", text);
               free (text);
            }
            else
            {
               fprintf (stderr, "Memoire insuffisante\n");
               exit (EXIT_FAILURE);
            }
         }
      }
      else
      {
         fprintf (stderr, "Memoire insuffisante\n");
         exit (EXIT_FAILURE);
      }
   }
   puts ("\nPress any key\n");
/* Dev-cpp */
   getchar ();
   return (EXIT_SUCCESS);
}
