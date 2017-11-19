#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <mpd/client.h>
#include <mpd/status.h>
#include <mpd/player.h>

#define BUFSIZE 255

int signaled;
int done;
pid_t feh;

void on_click(int sig) {
    signaled = 1;
}

void on_quit(int sig) {
    done = 1;
}

pid_t window() {
    pid_t p = fork();
    if (p != 0) {
        return p;
    }
    char *argv[] = {"bspc", "rule", "-a", "feh", "state=floating", "sticky=on", "focus=off", "rectangle=600x600+2600+30", "-o", NULL};
    execvp("bspc", argv);
    return 0;
}

pid_t display(char *album, char *artist) {
    pid_t p = fork();
    if (p != 0) {
        return p;
    }
    pid_t b = window();
    char path[BUFSIZE] = {};
    strncat(path, getenv("HOME"), BUFSIZE - strlen(path) - 1);
    strncat(path, "/",            BUFSIZE - strlen(path) - 1);
    strncat(path, "Music/",       BUFSIZE - strlen(path) - 1);
    strncat(path, artist,         BUFSIZE - strlen(path) - 1);
    strncat(path, "/",            BUFSIZE - strlen(path) - 1);
    strncat(path, album,          BUFSIZE - strlen(path) - 1);
    char *argv[] = {"feh", "-q", path, "-g", "600x600", NULL};
    waitpid(b, NULL, 0);
    execvp("feh", argv);
    return 0;
}

int main(int argc, char *argv[]) {
    struct sigaction click, quit;
    click.sa_handler = on_click;
    quit.sa_handler = on_quit;
    sigemptyset(&click.sa_mask);
    sigemptyset(&quit.sa_mask);
    sigaction(SIGUSR1, &click, NULL);
    sigaction(SIGTERM, &quit,  NULL);
    sigaction(SIGINT,  &quit,  NULL);

    struct mpd_connection *conn = mpd_connection_new(NULL, 0, 0);
    struct mpd_status *status;
    struct mpd_song *song;
    char album[BUFSIZE], artist[BUFSIZE];
    int song_id = 0, new_id;
    feh = 0;
    while (!done) {
        status = mpd_run_status(conn);
        new_id = mpd_status_get_song_id(status);
        if (new_id > 0 && new_id != song_id) {
            song_id = new_id;
            song = mpd_run_current_song(conn);
            strncpy(album,  mpd_song_get_tag(song, MPD_TAG_ALBUM,  0), BUFSIZE);
            strncpy(artist, mpd_song_get_tag(song, MPD_TAG_ARTIST, 0), BUFSIZE);
            mpd_song_free(song);
            if (feh) {
                if (waitpid(feh, NULL, WNOHANG) == 0) {
                    kill(feh, SIGTERM);
                    waitpid(feh, NULL, 0);
                    feh = display(album, artist);
                }
            }
        }
        mpd_status_free(status);
        if (signaled) {
            if (feh) {
                if (waitpid(feh, NULL, WNOHANG) == 0) {
                    kill(feh, SIGTERM);
                    waitpid(feh, NULL, 0);
                    feh = 0;
                }
                else {
                    waitpid(feh, NULL, 0);
                    feh = display(album, artist);
                }
            }
            else {
                feh = display(album, artist);
            }
            signaled = 0;
        }
    }
    if (feh) {
        kill(feh, SIGTERM);
        waitpid(feh, NULL, 0);
    }
    mpd_connection_free(conn);
}

