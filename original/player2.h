// player2.h: player 2 agent.
// Author:    <your name>
// Date:	  <date>
// MS Visual C++
#ifndef PLAYER2_H
#define PLAYER2_H

class Player2 : public Player
{
public:
	Move get_move(unsigned short p, board game_board);
};

Move Player2::get_move(unsigned short p, board game_board)
{
	Move move;

	move.player = p;

	if (gettype()) {
		cout << "Enter move (old_x old_y new_x new_y): ";
		cin >> move.src_x;
		cin >> move.src_y;
		cin >> move.dst_x;
		cin >> move.dst_y;
	}
	else {
		do {
			move.src_x = rand() % 4;
			move.src_y = rand() % 4;
			move.dst_x = rand() % 4;
			move.dst_y = rand() % 4;
		} while (!validmove(move, game_board));
	}

	return move;
}
#endif