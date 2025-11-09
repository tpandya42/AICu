#include "aicu.h"

int main(int argc, char **argv) {
    int fd;
    int *board;
    int num_heaps = 0;

    if (argc > 2) {
        write(STDERR_FILENO, "ERROR: Too many arguments\n", 26);
        return 1;
    } 
    
    else if (argc == 2) {
        fd = open(argv[1], O_RDONLY);
        if (fd < 0) {
            write(STDERR_FILENO, ERROR_MESSAGE, 6);
	    return 1;
        }
    } 
    else {
        fd = STDIN_FILENO;
        write(STDOUT_FILENO, "Reading from STDIN. End input with an empty line (Ctrl+D twice if stuck).\n", 75);
    }
    board = read_board(fd, &num_heaps);
    if (argc == 2)
        close(fd);
    if (board == NULL && num_heaps == 0)
	    return 1; 

    if (board) {
        play_game(board, num_heaps);
        free_board(board);
    }
    return 0;
}
