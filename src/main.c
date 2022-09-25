#include "headers.h"
#include "prompt.h"
#include "parse.h"
#include "history.h"
#include "finishbg.h"
#include "redirect.h"
#include "signals.h"
#include "autocomplete.h"

char *home;
char *prev_dir;
char **history;
char *history_path;
int shell_grpid;
processList process_list[MAX_LINE];
processList fg_process;
int bg_idx;
int time_taken_fg;
int storage_in, storage_out;
char *input_buffer;


void die(const char *s) {
    perror(s);
    exit(1);
}

struct termios orig_termios;

void disableRawMode() {
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1)
        die("tcsetattr");
}

/**
 * Enable row mode for the terminal
 * The ECHO feature causes each key you type to be printed to the terminal, so you can see what you’re typing.
 * Terminal attributes can be read into a termios struct by tcgetattr().
 * After modifying them, you can then apply them to the terminal using tcsetattr().
 * The TCSAFLUSH argument specifies when to apply the change: in this case, it waits for all pending output to be written to the terminal, and also discards any input that hasn’t been read.
 * The c_lflag field is for “local flags”
 */
void enableRawMode() {
    if (tcgetattr(STDIN_FILENO, &orig_termios) == -1) die("tcgetattr");
    atexit(disableRawMode);
    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ICANON | ECHO);
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) die("tcsetattr");
}

/**
 * stdout and stdin are buffered we disable buffering on that
 * After entering in raw mode we read characters one by one
 * Up arrow keys and down arrow keys are represented by 3 byte escape codes
 * starting with ascii number 27 i.e. ESC key
 * This way we interpret arrow keys
 * Tabs are usually handled by the term, but here we are simulating tabs for the sake of simplicity
 * Backspace move the cursor one control character to the left
 * @return
 */

int main() {
    char *inp = malloc(sizeof(char) * 100);
    char c;

    // store home directory
    home = getcwd(NULL,0);
    prev_dir = NULL;

    time_taken_fg = 0;

    history_path = malloc(MAX_SIZE*sizeof (char)); 
    sprintf(history_path,"%s/src/history.txt",home);
    // history_path ="./history.txt";

    history = malloc(MAX_HISTORY*sizeof(char *));

    load_history();

    init_process_list();
    shell_grpid = getpgid(getpid());
    signal(SIGCHLD,finish_bg);
    signal(SIGINT,ctrlC);
    signal(SIGTSTP,ctrlZ);

    while (1) {
        setbuf(stdout, NULL);
        enableRawMode();

        fg_process.pid = -1;
        fg_process.process_name = NULL;

        prompt();

        memset(inp, '\0', 100);
        input_buffer = inp;
        int pt = 0;
        while (read(STDIN_FILENO, &c, 1) == 1) {
            input_buffer = inp;
            if (iscntrl(c)) {
                if (c == 10) break;
                else if (c == 27) {
                    char buf[3];
                    buf[2] = 0;
                    if (read(STDIN_FILENO, buf, 2) == 2) { // length of escape code
                        // printf("\rarrow key: %s", buf);
                    }
                } else if (c == 127) { // backspace
                    if (pt > 0) {
                        if (inp[pt-1] == 9) {
                            for (int i = 0; i < 7; i++) {
                                printf("\b");
                            }
                        }
                        inp[--pt] = '\0';
                        printf("\b \b");
                    }
                } else if (c == 9) { // TAB character
                    // int temp = strlen(inp);
                    autocomplete(inp);
                    // inp = input_buffer;
                    pt = strlen(inp);
                    // printf("\nhiih %s\n", inp);
                    // printf("\nhuuiih %s\n", input_buffer);
                } else if (c == 4) {
                    exit(0);
                } else {
                    printf("%d\n", c);
                }
            } else {
                inp[pt++] = c;
                printf("%c", c);
            }
        }
        disableRawMode();

        // add \n at the end of inp
        inp[pt++] = '\n';
        store_history(inp);
        printf("\n");
        parse(inp);


    }
    free(history);
    free(history_path);
    return 0;
}