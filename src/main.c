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
        write(STDOUT_FILENO, "\nSuccessfully loaded board with ", 32);
        char count_str[16];
        int len = 0;
        int temp_count = num_heaps;
        if (temp_count == 0) {
            count_str[0] = '0';
            len = 1;
        } else {
            while (temp_count > 0) {
                count_str[len++] = (temp_count % 10) + '0';
                temp_count /= 10;
            }
            write(STDOUT_FILENO, "heaps:\n", 7);
        }

        int i = 0;
	while (i < num_heaps) {
            write(STDOUT_FILENO, "Heap ", 5);
            
            char index_str[16];
            int idx_len = 0;
            int temp_idx = i + 1;
            while (temp_idx > 0) {
                index_str[idx_len++] = (temp_idx % 10) + '0';
                temp_idx /= 10;
            }
            int j = idx_len - 1;
            while (j >= 0) {
                write(STDOUT_FILENO, &index_str[j], 1);
                j--;
            }
            
            write(STDOUT_FILENO, ": ", 2);
            
            // Print heap size
            char size_str[16];
            int size_len = 0;
            int temp_size = board[i];
            if (temp_size == 0) {
                size_str[0] = '0';
                size_len = 1;
            } else {
                while (temp_size > 0) {
                    size_str[size_len++] = (temp_size % 10) + '0';
                    temp_size /= 10;
                }
            }
            j = size_len - 1;
            while (j >= 0) {
                write(STDOUT_FILENO, &size_str[j], 1);
                j--;
            }
            write(STDOUT_FILENO, "\n", 1);
            i++;
        }
        
        free_board(board);
    }
    return 0;
}
