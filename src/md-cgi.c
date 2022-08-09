#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "md4c/md4c-html.h"

void getdir(char *exepath) {
    char *p;
    p = strrchr(exepath, '/');
    if (p != NULL) {
        *p = '\0';
    } else {
        p = strrchr(exepath, '\\');
        if (p != NULL) {
            *p = '\0';
        } else {
            exepath[0] = '\0';
        }
    }
}

void printFile(char *dir, char *filename) {
    char c;
    char *path = malloc(strlen(dir) + strlen(filename) + 2);
    strcpy(path, dir);
    strcat(path, "/");
    strcat(path, filename);
    FILE *fp = fopen(path, "r");
    free(path);
    if (fp != NULL) {
        while ((c = fgetc(fp)) != EOF) {
            printf("%c", c);
        }
        fclose(fp);
    }
}

static void
process_output(const MD_CHAR* text, MD_SIZE size, void* userdata)
{
   printf("%.*s", (int)size, text);
   return;
}

int main(int argc, char* argv[], char *envp[]) {
    printf("Content-type: text/html\r\n");
    printf("\r\n");

    char *path_translated = getenv("PATH_TRANSLATED");
    char *self_path = argv[0];

    getdir(self_path);
    char* css_file = "md-cgi.css";
    char* js_file = "md-cgi.js";
    char* favicon_file = "md-cgi.png.base64";

    printf("<!DOCTYPE HTML>");
    printf("<html>");
    printf("<head>");
    printf("<meta charset=\"utf-8\">");
    printf("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">");
    printf("<title>");

    if (path_translated != NULL) {
        int slash = 0;
        for(int i = strlen(path_translated) - 1; i >= 0; i--) {
            if (path_translated[i] == '/' || path_translated[i] == '\\') {
                slash = i;
                break;
            }
        }
        printf("%s", path_translated + slash + 1);
    } else {
        printf("md-cgi");
    }

    printf("</title>");
    printf("<link rel=\"shortcut icon\" href=\"");

    printFile(self_path, favicon_file);
    
    printf("\" />");
    printf("</head>");
    printf("<body>");
    printf("<style>");

    printFile(self_path, css_file);

    printf("</style>");
    printf("<main>");

    FILE *mdfile = fopen(path_translated, "r");
    if (mdfile == NULL)
    {
        printf("Error while opening the file.\n");
        printf("</main>");
        printf("</body>");
        printf("</html>");
        return 404;
    }

    fseek(mdfile, 0, SEEK_END);
    MD_SIZE size = ftell(mdfile);
    rewind(mdfile);
    MD_CHAR* buffer = malloc(size * sizeof(char));
    fread(buffer, sizeof(char), size, mdfile);
    fclose(mdfile);

    unsigned parser_flags = MD_DIALECT_GITHUB | MD_FLAG_UNDERLINE | MD_FLAG_WIKILINKS | MD_FLAG_LATEXMATHSPANS;
    unsigned renderer_flags = MD_DIALECT_COMMONMARK;

    md_html(buffer, size, process_output, NULL, parser_flags, renderer_flags);

    printf("</main>");
    printf("<script type=\"text/javascript\">");

    printFile(self_path, js_file);

    printf("</script>");
    printf("</body>");
    printf("</html>");
    return 0;
}