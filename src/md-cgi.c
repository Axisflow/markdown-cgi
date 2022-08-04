#include<stdio.h>
#include<stdlib.h>
#include "md4c/md4c-html.h"

static void
process_output(const MD_CHAR* text, MD_SIZE size, void* userdata)
{
   printf("%.*s", (int)size, text);
   return;
}

int main(int argc, char* argv[], char *envp[]) {
    printf("Content-type: text/html\r\nStatus: 200 OK\r\n");
    printf("\r\n");

    char *query_string = getenv("QUERY_STRING");
    char *content_length = getenv("CONTENT_LENGTH");
    char *request_method = getenv("REQUEST_METHOD");
    char *http_user_agent = getenv("HTTP_USER_AGENT");
    char *http_referer = getenv("HTTP_REFERER");
    char *http_cookie = getenv("HTTP_COOKIE");
    char *http_host = getenv("HTTP_HOST");
    char *http_accept = getenv("HTTP_ACCEPT");
    char *http_accept_language = getenv("HTTP_ACCEPT_LANGUAGE");
    char *http_accept_encoding = getenv("HTTP_ACCEPT_ENCODING");
    char *http_connection = getenv("HTTP_CONNECTION");
    char *http_upgrade_insecure_requests = getenv("HTTP_UPGRADE_INSECURE_REQUESTS");
    char *http_cache_control = getenv("HTTP_CACHE_CONTROL");
    char *http_dnt = getenv("HTTP_DNT");
    char *http_sec_fetch_mode = getenv("HTTP_SEC_FETCH_MODE");
    char *http_sec_fetch_site = getenv("HTTP_SEC_FETCH_SITE");
    char *http_sec_fetch_user = getenv("HTTP_SEC_FETCH_USER");
    char *http_sec_fetch_dest = getenv("HTTP_SEC_FETCH_DEST");
    char *http_sec_ch_ua = getenv("HTTP_SEC_CH_UA");
    char *http_sec_ch_ua_mobile = getenv("HTTP_SEC_CH_UA_MOBILE");
    char *http_sec_ch_ua_platform = getenv("HTTP_SEC_CH_UA_PLATFORM");
    char *http_sec_ch_ua_full_version = getenv("HTTP_SEC_CH_UA_FULL_VERSION");
    char *http_sec_ch_ua_arch = getenv("HTTP_SEC_CH_UA_ARCH");
    char *http_sec_ch_ua_model = getenv("HTTP_SEC_CH_UA_MODEL");
    char *http_sec_ch_ua_vendor = getenv("HTTP_SEC_CH_UA_VENDOR");
    char *script_name = getenv("SCRIPT_NAME");
    char *path_translated = getenv("PATH_TRANSLATED");

    printf("<!DOCTYPE HTML><html><head><meta charset=\"utf-8\"><title>md-cgi</title></head><body>");

    char ch;
    FILE *mdfile = fopen(path_translated, "r");
    if (mdfile == NULL)
    {
        printf("Error while opening the file.\n");
        printf("</body></html>");
        return 404;
    }

    fseek(mdfile, 0, SEEK_END);
    MD_SIZE size = ftell(mdfile);
    rewind(mdfile);
    MD_CHAR* buffer = malloc(size * sizeof(char));
    fread(buffer, sizeof(char), size, mdfile);
    fclose(mdfile);

    unsigned parser_flags, renderer_flags;

    if(size < 2 * sizeof(unsigned)) {
        /* We interpret the 1st 8 bytes as parser flags and renderer flags. */
        return 0;
    }

    /* parser_flags = *(unsigned*)buffer;
    buffer += sizeof(unsigned); size -= sizeof(unsigned);

    renderer_flags = *(unsigned*)buffer;
    buffer += sizeof(unsigned); size -= sizeof(unsigned); */

    md_html(buffer, size, process_output, NULL, 0, 0);

    printf("</body></html>");
    return 0;
}