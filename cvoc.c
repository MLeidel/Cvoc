/*
   ______   ______  _____
  / ___/ | / / __ \/ ___/
 / /__ | |/ / /_/ / /__
 \___/ |___/\____/\___/

cvoc.c
"command-line voice, c voice, curl voice"
Uses: curl, play, OpenAI API
default API parameters in ~/.config/cvoc.ini
    sample cvoc.ini
        output=speech
        voice=nova
        format=mp3
        speed=0.95
        model=tts-1
*/

#include <myc.h>

char *c1 = "curl https://api.openai.com/v1/audio/speech"
 " -H \"Authorization: Bearer $GPTKEY\""
 " -H \"Content-Type: application/json\""
 " -d '{"
 " \"input\": \"%s\","
 " \"model\": \"%s\","
 " \"voice\": \"%s\","
 " \"speed\": %s,"
 " \"response_format\": \"%s\"}'"
 " --output %s\n";

char input[100000] = "{\0}";
char outfile[1024] = "{\0}";
char outpath[1024] = "{\0}";

char p_input[100000] = "{\0}";
char p_model[32]    = "tts-1";
char p_voice[32]    = "alloy";
char p_speed[32]    = "0.95";
char p_format[32]   = "mp3";

void showsettings() {
    puts(clr_fg.yellow);
    puts(p_voice);
    puts(p_format);
    puts(p_speed);
    puts(p_model);
    puts(p_input);
    puts(outfile);
    puts(clr_fg.dft);
}

void getparms() {

    printf("Enter output file (%s) no ext: ", outfile);
    fgets(input, 1024, stdin);
    if (strlen(input) > 2)
        strncpy(outfile, chomp(input), 1024);

    printf("Enter voice (%s): ", p_voice);
    fgets(input, 30, stdin);
    if (strlen(input) > 2)
        strncpy(p_voice, chomp(input), 30);

    printf("Enter audio format (%s): ", p_format);
    fgets(input, 30, stdin);
    if (strlen(input) > 2)
        strncpy(p_format, chomp(input), 30);

    printf("Enter speed (%s) .25 - 4.0: ", p_speed);
    fgets(input, 30, stdin);
    if (strlen(input) > 2)
        strncpy(p_speed, chomp(input), 30);

    printf("Enter model (%s) tts-1 or tts-1-hd: ", p_model);
    fgets(input, 30, stdin);
    if (strlen(input) > 2)
        strncpy(p_model, chomp(input), 30);

    printf("Enter Text to speek: ");
    fgets(input, 100000, stdin);
    if (strlen(input) > 2)
        strncpy(p_input, chomp(input), 100000);
}

/***
 *    █▀▄▀█     ██       ▄█        ▄
 *    █ █ █     █ █      ██         █
 *    █ ▄ █     █▄▄█     ██     ██   █
 *    █   █     █  █     ▐█     █ █  █
 *       █         █      ▐     █  █ █
 *      ▀         █             █   ██
 *               ▀
 */

int main(int argc, char *argv[]) {

    char inifile[256] = "{\0}";
    sprintf(inifile, "%s/.config/cvoc.ini", getenv("HOME"));

    // set the params from the cvoc.ini file
    getini(p_model, inifile, "model");
    getini(p_voice, inifile, "voice");
    getini(p_speed, inifile, "speed");
    getini(p_format, inifile, "format");
    getini(outfile, inifile, "output");

    // Get input and build text string for curl
    if (argc < 2) {
        getparms();
    } else {
    // Concatenate all arguments with a space in between
        for (int i = 1; i < argc; i++) {
            strcat(p_input, argv[i]);
            if (i < argc - 1) {
                strcat(p_input, " ");
            }
        }
    }

    // build output file path
    concat(outfile, ".", p_format, END);

    showsettings();

    char ctxt[1000000] = {"\0"}; // 1M

    sprintf(ctxt, c1, p_input, p_model, p_voice, p_speed, p_format, outfile);

    system(ctxt);

    strncpy(outpath, "play ", 1020);
    strncat(outpath, outfile, 1020);

    system(outpath);

    return 0;
}
