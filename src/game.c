#include "aicu.h"

void	print_number(int n)
{
	char	buffer[16];
	int		len;
	int		i;

	len = 0;
	if (n == 0)
	{
		write(STDOUT_FILENO, "0", 1);
		return;
	}
	while (n > 0)
	{
		buffer[len++] = (n % 10) + '0';
		n /= 10;
	}
	i = len - 1;
	while (i >= 0)
	{
		write(STDOUT_FILENO, &buffer[i], 1);
		i--;
	}
}

void	display_board(int *board, int num_heaps)
{
	int	i;
	int	j;

	i = 0;
	while (i < num_heaps)
	{
		if (board[i] > 0)
		{
			j = 0;
			while (j < board[i])
			{
				write(STDOUT_FILENO, "|", 1);
				if (j < board[i] - 1)
					write(STDOUT_FILENO, " ", 1);
				j++;
			}
			write(STDOUT_FILENO, "\n", 1);
		}
		i++;
	}
}

int	find_last_heap(int *board, int num_heaps)
{
	int	i;

	i = num_heaps - 1;
	while (i >= 0)
	{
		if (board[i] > 0)
			return (i);
		i--;
	}
	return (-1);
}

int	count_nonempty_heaps(int *board, int num_heaps)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (i < num_heaps)
	{
		if (board[i] > 0)
			count++;
		i++;
	}
	return (count);
}

int	ai_move(int *board, int num_heaps)
{
	int	last_heap;
	int	nim_sum;
	int	i;
	int	take;
	int	nonempty_heaps;

	last_heap = find_last_heap(board, num_heaps);
	if (last_heap == -1)
		return (0);
	
	nonempty_heaps = count_nonempty_heaps(board, num_heaps);
	
	nim_sum = 0;
	i = 0;
	while (i < num_heaps)
	{
		nim_sum ^= board[i];
		i++;
	}
	
	if (nonempty_heaps == 1)
	{
		if (board[last_heap] <= 3)
			take = board[last_heap] - 1;
		else if (board[last_heap] % 4 == 1)
			take = 1;
		else
			take = (board[last_heap] - 1) % 4;
		if (take < 1)
			take = 1;
		if (take > 3)
			take = 3;
		return (take);
	}
	
	take = 1;
	i = 1;
	while (i <= 3 && i <= board[last_heap])
	{
		int new_nim_sum = nim_sum ^ board[last_heap] ^ (board[last_heap] - i);
		if (new_nim_sum == 0)
		{
			take = i;
			break;
		}
		i++;
	}
	
	if (nim_sum != 0 && take == 1)
	{
		if (board[last_heap] >= 3)
			take = 3;
		else if (board[last_heap] >= 2)
			take = 2;
		else
			take = 1;
	}
	
	return (take);
}

int	read_number_from_input(void)
{
	char	buffer[32];
	int		i;
	int		num;
	int		bytes;

	i = 0;
	while (i < 31)
	{
		bytes = read(STDIN_FILENO, &buffer[i], 1);
		if (bytes <= 0)
			return (-1);
		if (buffer[i] == '\n')
			break;
		i++;
	}
	buffer[i] = '\0';
	
	if (i == 0)
		return (-1);
	
	num = 0;
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		if (buffer[i] < '0' || buffer[i] > '9')
			return (-1);
		num = num * 10 + (buffer[i] - '0');
		i++;
	}
	return (num);
}

int	get_player_move(int *board, int num_heaps)
{
	int	last_heap;
	int	max_take;
	int	choice;

	last_heap = find_last_heap(board, num_heaps);
	if (last_heap == -1)
		return (0);
	
	max_take = board[last_heap];
	if (max_take > 3)
		max_take = 3;
	
	while (1)
	{
		write(STDOUT_FILENO, "Please choose between 1 and ", 29);
		print_number(max_take);
		write(STDOUT_FILENO, " items\n", 7);
		
		choice = read_number_from_input();
		
		if (choice >= 1 && choice <= max_take)
			return (choice);
		
		print_number(choice);
		write(STDOUT_FILENO, " - Invalid choice\n", 18);
	}
}

int	is_game_over(int *board, int num_heaps)
{
	int	i;

	i = 0;
	while (i < num_heaps)
	{
		if (board[i] > 0)
			return (0);
		i++;
	}
	return (1);
}

void	play_game(int *board, int num_heaps)
{
	int	ai_turn;
	int	move;
	int	last_heap;

	ai_turn = 1;
	
	while (!is_game_over(board, num_heaps))
	{
		display_board(board, num_heaps);
		
		if (ai_turn)
		{
			move = ai_move(board, num_heaps);
			last_heap = find_last_heap(board, num_heaps);
			board[last_heap] -= move;
			
			write(STDOUT_FILENO, "AI took ", 8);
			print_number(move);
			write(STDOUT_FILENO, "\n", 1);
		}
		else
		{
			move = get_player_move(board, num_heaps);
			last_heap = find_last_heap(board, num_heaps);
			board[last_heap] -= move;
		}
		
		ai_turn = !ai_turn;
	}
	
	display_board(board, num_heaps);
	
	if (ai_turn)
		write(STDOUT_FILENO, "You are the winner! Congratulations!\n", 37);
	else
		write(STDOUT_FILENO, "AI wins! Better luck next time.\n", 33);
}
