// player1.h: player 1 agent.
// Author:    <Ting Wang>
// Date:	  <3/24/2018>
// MS Visual C++
#ifndef PLAYER1_H
#define PLAYER1_H

class Player1 : public Player
{
private:
	int heu_me[XYDIM][XYDIM], hue_op[XYDIM][XYDIM], move_pri[XYDIM][XYDIM];

 //   int win, lost;

public:
    Move get_move(unsigned short player, board game_board);
    bool moveable(unsigned short from_X, unsigned short  from_Y, unsigned short to_X, unsigned short to_Y, board game_board, unsigned short player);
};

Move Player1::get_move(unsigned short player, board game_board)
{
    Move move;
    unsigned short from_X, from_Y, to_X, to_Y;

    unsigned short me, op;
    bool find_move = false;
    // bool find_des = false;

    if (player == 1)
    {
        me = 1;
        op = 2;
    }
    else
    {
        me = 2;
        op = 1;
    }

    move.player = me;

   //initialize move priority of piece to 5
    for (int i = 0; i < XYDIM; i++) 
    {
        for (int j = 0; j < XYDIM; j++) 
        {
            if (game_board.layout[i][j] == me)
                move_pri[i][j] = 5;
            else
                move_pri[i][j] = -1;
        }
    }

    //initialize H-value of empty space to 200

    for (int i = 0; i < XYDIM; i++)
    {
        for (int j = 0; j < XYDIM; j++)
        {
            if (game_board.layout[i][j] == EMPTY)
                heu_me[i][j] = 200;
            else
                heu_me[i][j] = -1;

        }
    }

    //set H-value of empty space close to pice to 100, if in the middle of 2 pieces set to 40
    for (int i = 0; i < XYDIM; i++) 
    {
        for (int j = 0; j < XYDIM; j++)
        {
            if (game_board.layout[i][j] == me)
            {

				if (j < XYDIM - 1 && game_board.layout[i][j + 1] == EMPTY)
				{
					heu_me[i][j + 1] = 100;
					if (j < XYDIM - 2 && game_board.layout[i][j + 2] == me)
						heu_me[i][j + 1] = 40;
				}
				if (i < XYDIM - 1 && game_board.layout[i + 1][j] == EMPTY)
				{
					heu_me[i + 1][j] = 100;
					if (i < XYDIM - 2 && game_board.layout[i+2][j] == me)
						heu_me[i+1][j ] = 40;
				}
				if (j > 0 && game_board.layout[i][j - 1] == EMPTY)
					if (heu_me[i][j - 1] > 100)
						heu_me[i][j - 1] = 100;
                if (i > 0 && game_board.layout[i - 1][j] == EMPTY)
                    if (heu_me[i - 1][j] > 100)
						heu_me[i - 1][j] = 100;
            }
        }
    }

    //set H-value and move priority of connect-togetered pieces
    for (int i = 0; i < XYDIM; i++)
    {
        for (int j = 0; j < XYDIM; j++)
        {
            if (game_board.layout[i][j] == me)
            {
                if (j < (XYDIM - 1) && game_board.layout[i][j + 1] == me)
                {
                    move_pri[i][j] = 4;
                    move_pri[i][j + 1] = 4;

                    if (j < (XYDIM - 2) && game_board.layout[i][j + 2] == me)
                    {
                        move_pri[i][j] = 2;
                        move_pri[i][j + 1] = 1;
                        move_pri[i][j + 2] = 2;


                        if (j < (XYDIM - 3) && heu_me[i][j + 3] == 100)
                        {
                            heu_me[i][j + 3] = 0;
            
                        }
                        else if (j == (XYDIM - 3) && heu_me[i][j - 1] == 100)
                        {
                            heu_me[i][j - 1] = 0;
  
                        }
                        else
                        {
                            ;
                        }
                    }

                    if (j < (XYDIM - 3) && game_board.layout[i][j + 2] == EMPTY)
                    {
                        heu_me[i][j + 2] = 50;
                        if (game_board.layout[i][j + 3] == me)
                        {
                            move_pri[i][j] = 1;
                            move_pri[i][j + 1] = 1;
                            move_pri[i][j + 3] = 3;

                            heu_me[i][j + 2] = 10;

                        }
            
                    }
					if (j == (XYDIM - 2) && game_board.layout[i][j - 1] == EMPTY)
					{
						heu_me[i][j -1] = 50;
						if (game_board.layout[i][j -2] == me)
						{
							move_pri[i][j] = 1;
							move_pri[i][j + 1] = 1;
							move_pri[i][j - 2] = 3;

							heu_me[i][j -1] = 10;
						}
					}



                    if (i < XYDIM - 1)
                    {
                        if (game_board.layout[i + 1][j] == EMPTY)
                            heu_me[i + 1][j] = 50;
                        if (game_board.layout[i + 1][j + 1] == EMPTY)
                            heu_me[i + 1][j + 1] = 50;

                        if (game_board.layout[i + 1][j] == me)
                        {
                            move_pri[i][j] = 1;
                            move_pri[i][j + 1] = 2;
                            move_pri[i + 1][j] = 2;

                            heu_me[i + 1][j + 1] = 0;
                 
                        }

                        if (game_board.layout[i + 1][j + 1] == me)
                        {
                            move_pri[i][j] = 2;
                            move_pri[i][j + 1] = 1;
                            move_pri[i + 1][j + 1] = 2;

                            heu_me[i+1][j ] = 0;
    
                        }

                    }

                    if (i > 0)
                    {
                        if (game_board.layout[i - 1][j] == EMPTY)
                            heu_me[i - 1][j] = 50;
                        if (game_board.layout[i - 1][j + 1] == EMPTY)
                            heu_me[i - 1][j + 1] = 50;

                        if (game_board.layout[i - 1][j] == me)
                        {
                            move_pri[i - 1][j] = 2;
                            move_pri[i][j] = 1;
                            move_pri[i][j + 1] = 2;

                            heu_me[i - 1][j + 1] = 0;
           
                        }

                        if (game_board.layout[i - 1][j + 1] == me)
                        {
                            move_pri[i - 1][j + 1] = 2;
                            move_pri[i][j] = 2;
                            move_pri[i][j + 1] = 1;

                            heu_me[i - 1][j] = 0;
                
                        }

                    }

                }

                if (i < (XYDIM - 1) && game_board.layout[i + 1][j] == me)
                {
					if (move_pri[i][j] > 4)
						move_pri[i][j] = 4;
					if (move_pri[i + 1][j] > 4)
						move_pri[i + 1][j] = 4;

                    if (j < (XYDIM - 1) && game_board.layout[i][j + 1] == EMPTY && heu_me[i][j + 1] >50)
                        heu_me[i][j + 1] = 50;
                    if (j < (XYDIM - 1) && game_board.layout[i + 1][j + 1] == EMPTY && heu_me[i + 1][j + 1] >50)
                        heu_me[i + 1][j + 1] = 50;
                    if (j > 0 && game_board.layout[i][j - 1] == EMPTY && heu_me[i][j - 1] > 50)
                        heu_me[i][j - 1] = 50;
                    if (j > 0 && game_board.layout[i + 1][j - 1] == EMPTY && heu_me[i + 1][j - 1] > 50)
                        heu_me[i + 1][j - 1] = 50;

                    if (i < (XYDIM - 2) && game_board.layout[i + 2][j] == EMPTY)
                    {
						heu_me[i + 2][j] = 50;
                        if (i < (XYDIM - 3) && game_board.layout[i + 3][j] == me)
                        {
                            move_pri[i][j] = 2;
                            move_pri[i + 1][j] = 2;
                            move_pri[i + 3][j] = 3;

                            heu_me[i + 2][j] = 10;
                 

                        }

                    }

                    if (i > 0 && game_board.layout[i - 1][j] == EMPTY)
                    {
						heu_me[i][j] = 50;
						if (i > 1 && game_board.layout[0][j] == me)
                        {
                            heu_me[i - 1][j] = 10;
             

                        }
                    }

                    if (i < (XYDIM - 2) && game_board.layout[i + 2][j] == me)
                    {
                        move_pri[i][j] = 2;
                        move_pri[i + 1][j] = 1;
                        move_pri[i + 2][j] = 2;

                        if (i < (XYDIM - 3) && game_board.layout[i + 3][j] == EMPTY)
                        {
                            heu_me[i + 3][j] = 0;
         
                        }
                        else if (i == (XYDIM - 3) && game_board.layout[i - 1][j] == EMPTY)
                        {
                            heu_me[i - 1][j] = 0;
           
                        }
                        else
                        {
                            ;
                        }

                    }
                }
            }
        }
    }

	int cor = 0;
	int ept = 0;
	for (int i = 0; i < XYDIM; i++)
	{
		for (int j = 0; j < XYDIM; j++)
		{
			if (game_board.layout[i][j] == me)
				cor++;
			else if (game_board.layout[i][j] == EMPTY)
				ept++;
			j = j + 2;
		}
		i = i + 2;
	}
	
    //set H-value of pieces in 4 corner
	if (4 == cor + ept)
	{
		if (cor == 3)
		{
			for (int i = 0; i < XYDIM; i++)
			{
				for (int j = 0; j < XYDIM; j++)
				{
					if (game_board.layout[i][j] == me)
						move_pri[i][j] = 1;
					else if (game_board.layout[i][j] == EMPTY)
						heu_me[i][j] = 0;
					j = j + 2;
				}
				i = i + 2;
			}
		}
		else if(cor == 2)
			for (int i = 0; i < XYDIM; i++)
			{
				for (int j = 0; j < XYDIM; j++)
				{
					if (game_board.layout[i][j] == me)
						move_pri[i][j] = 2;
					else if (game_board.layout[i][j] == EMPTY)
						heu_me[i][j] = 30;
					j = j + 2;
				}
				i = i + 2;
			}
		else if( cor == 1)
			for (int i = 0; i < XYDIM; i++)
			{
				for (int j = 0; j < XYDIM; j++)
				{
					if (game_board.layout[i][j] == me)
						move_pri[i][j] = 4;
					else if (game_board.layout[i][j] == EMPTY)
						heu_me[i][j] = 60;
					j = j + 2;
				}
				i = i + 2;
			}
		else
			for (int i = 0; i < XYDIM; i++)
			{
				for (int j = 0; j < XYDIM; j++)
				{
					if (game_board.layout[i][j] == EMPTY)
						heu_me[i][j] = 80;
					j = j + 2;
				}
				i = i + 2;
			}
	}


	/*
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cout << setw(10) << heu_me[i][j];
		}
		cout << endl;
	}

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cout << setw(10) << move_pri[i][j];
		}
		cout << endl;
	}
	*/



    //set H-value for the other side 
	for (int i = 0; i < XYDIM; i++)
		for (int j = 0; j < XYDIM; j++)
			if (game_board.layout[i][j] != op)
				hue_op[i][j] = 100;

	for (int i = 0; i < XYDIM; i++)
		for (int j = 0; j < XYDIM; j++)
			if (game_board.layout[i][j] == op)
			{
				if (j < XYDIM - 1 && game_board.layout[i][j + 1] == op)
				{
					if (j < XYDIM - 2 && game_board.layout[i][j + 2] == op)
					{
						if (j == 0)
							hue_op[i][3] = 0;
						else
							hue_op[i][0] = 0;
					}
					else if (j == 0 && game_board.layout[i][j + 3] == op)
						hue_op[i][2] = 0;
					else if (j == 2 && game_board.layout[i][0] == op)
						hue_op[i][1] = 0;
					else if (i < XYDIM - 1)
					{
						if (game_board.layout[i + 1][j] == op)
							hue_op[i + 1][j + 1] = 0;
						if (game_board.layout[i + 1][j + 1] == op)
							hue_op[i + 1][j] = 0;
					}
					else if (i > 0)
					{
						if (game_board.layout[i - 1][j] == op)
							hue_op[i - 1][j + 1] = 0;
						if (game_board.layout[i - 1][j + 1] == op)
							hue_op[i - 1][j] = 0;
					}
				}
				if (i < XYDIM - 1 && game_board.layout[i + 1][j] == op)
				{
					if (i < XYDIM - 2 && game_board.layout[i + 2][j] == op)
						if (i == 0)
							hue_op[3][j] = 0;
						else
							hue_op[0][j] = 0;
					else if (i == 0 && game_board.layout[3][j] == op)
						hue_op[2][j] = 0;
					else if (i == 2 && game_board.layout[0][j] == op)
						hue_op[1][j] = 0;

				}
			}

	cor = 0;
	for (int i = 0; i < XYDIM; i++)
	{
		for (int j = 0; j < XYDIM; j++)
		{
			if (game_board.layout[i][j] == op)
				cor++;
			j = j + 2;
		}
		i = i + 2;
	}

	if (cor == 3)
		for (int i = 0; i < XYDIM; i++)
		{
			for (int j = 0; j < XYDIM; j++)
			{
				if (game_board.layout[i][j] != op)
					hue_op[i][j] = 0;
				j = j + 2;
			}
			i = i + 2;
		}

	bool defence = false;
	unsigned short block_X, block_Y;
	for (int i = 0; i < XYDIM; i++)
		for (int j = 0; j < XYDIM; j++)
			if (hue_op[i][j] == 0 && game_board.layout[i][j] == EMPTY)
			{
				defence = true;
				block_X = j;
				block_Y = i;
			}

    //find the lowest H-value point then move my hightest move priority piece to it if posible.
    //If can not find the 1-pace-to-win place and the other side has 1-pace-to-win, try to ocupy it.
    for (int k = 0; k <= 200 &&!find_move; k = k + 10)
    {
        for (int i = 0; i < XYDIM && !find_move; i++)
        {
            for (int j = 0; j < XYDIM && !find_move; j++)
            {
                if (heu_me[i][j] == k && (k<=10 ||!defence))
                {
                    to_X = j;
                    to_Y = i;
                    for (int l=5;l>0 && !find_move;l--)
                        for (int m = 0; m < XYDIM && !find_move; m++)
                            for (int n = 0; n < XYDIM && !find_move; n++)
                            {
                                if (move_pri[m][n] == l && (hue_op[m][n] !=0 || k <= 10))
                                {
									from_X = n;
									from_Y = m;
									for (int ii = 0; ii < XYDIM && !find_move; ii++)
									{
										for (int jj = 0; jj < XYDIM && !find_move; jj++)
										{
											if (heu_me[ii][jj] == k  && !find_move)
											{
												to_X = jj;
												to_Y = ii;
												
												find_move = moveable(from_X, from_Y, to_X, to_Y, game_board, player);
											}
										
										}
									}
                                }
                            }
                }
            }
        }

    }

    if (find_move)
    {
        move.src_x = from_X;
        move.src_y = from_Y;
        move.dst_x = to_X;
        move.dst_y = to_Y;
        //cout << "from_X:" << from_X << "\tfrom_Y:\t" << from_Y << "\tto_X:\t" << to_X << "\tto_Y:" << to_Y << endl;
        return move;
    }

	if (defence)
	{
		to_X = block_X;
		to_Y = block_Y;
		for (int l = 5; l>0 && !find_move; l--)
			for (int i = 0; i < XYDIM && !find_move; i++)
				for (int j = 0; j < XYDIM && !find_move; j++)
					if (move_pri[i][j] == l)
					{
						from_X = j;
						from_Y = i;
						find_move = moveable(from_X, from_Y, to_X, to_Y, game_board,player);
					}
	}

	if (find_move)
	{
		move.src_x = from_X;
		move.src_y = from_Y;
		move.dst_x = to_X;
		move.dst_y = to_Y;
		//cout << "from_X:" << from_X << "\tfrom_Y:\t" << from_Y << "\tto_X:\t" << to_X << "\tto_Y:" << to_Y << endl;
		return move;
	}

    cout << "Not find !\n";


    //can to find other movment then just move the hightest move priority piece to a movable palce 
    for (int l = 5; l>0 && !find_move; l--)
        for (int m = 0; m < XYDIM && !find_move; m++)
            for (int n = 0; n < XYDIM && !find_move; n++)
            {
                if (move_pri[m][n] == l)
                {
                    from_X = n;
                    from_Y = m;
                    to_X = n;
                    to_Y = m;
                    bool find_des = false;

                    while (to_Y < XYDIM - 1 && game_board.layout[to_Y + 1][n] == EMPTY)
                    {
                        to_Y++;
                        find_des = true;
                    }
                    if (!find_des) 
                        while (to_Y > 0 && game_board.layout[to_Y - 1][n] == EMPTY)
                        {
                            to_Y--;
                            find_des = true;
                        }
                    if (!find_des)
                        while (to_X > 0 && game_board.layout[m][to_X-1] == EMPTY)
                        {
                            to_X--;
                            find_des = true;
                        }
                    if (!find_des)
                        while (to_X < XYDIM - 1 && game_board.layout[m][to_X + 1] == EMPTY)
                        {
                            to_X++;
                            find_des = true;
                        }
                    if (!find_des)
                        while (to_X < XYDIM - 1 && to_Y < XYDIM - 1 && game_board.layout[to_Y + 1][to_X + 1] == EMPTY)
                        {
                            to_X++;
                            to_Y++;
                            find_des = true;
                        }
                    cout << "here!\n";

                    find_move = moveable(from_X, from_Y, to_X, to_Y, game_board,player);
                }
            }

    move.src_x = from_X;
    move.src_y = from_Y;
    move.dst_x = to_X;
    move.dst_y = to_Y;
    return move;
}

//check it movable or not
bool Player1::moveable(unsigned short from_X, unsigned short  from_Y, unsigned short to_X, unsigned short to_Y, board game_board, unsigned short player)
{
    bool mov = true;
	unsigned short me, op;
	if (player == 1)
	{
		me = 1;
		op = 2;
	}
	else
	{
		me = 2;
		op = 1;
	}
    cout << "me:" << me << "\top:" << op << endl;

	if (game_board.layout[0][0] == op)
	{
		if (to_X == 1 && to_Y == 0 && game_board.layout[1][1] == me &&game_board.layout[1][0] == me && (from_X != 1 && from_Y != 1) && (from_X != 0 && from_Y != 1))
			return false;
		if (to_X == 1 && to_Y == 1 && game_board.layout[0][1] == me &&game_board.layout[1][0] == me && (from_X != 1 && from_Y != 0) && (from_X != 0 && from_Y != 1))
			return false;
		if (to_X == 0 && to_Y == 1 && game_board.layout[1][1] == me &&game_board.layout[0][1] == me && (from_X != 1 && from_Y != 1) && (from_X != 1 && from_Y != 0))
			return false;
	}
	if (game_board.layout[0][3] == op)
	{
		if (to_X == 2 && to_Y == 0 && game_board.layout[1][2] == me &&game_board.layout[1][3] == me && (from_X != 2 && from_Y != 1) && (from_X != 3 && from_Y != 1))
			return false;
		if (to_X == 2 && to_Y == 1 && game_board.layout[0][2] == me &&game_board.layout[1][3] == me && (from_X != 2 && from_Y != 0) && (from_X != 3 && from_Y != 1))
			return false;
		if (to_X == 3 && to_Y == 1 && game_board.layout[0][2] == me &&game_board.layout[1][2] == me && (from_X != 2 && from_Y != 0) && (from_X != 2 && from_Y != 1))
			return false;
	}
	if (game_board.layout[3][0] == op)
	{
		if (to_X == 0 && to_Y == 2 && game_board.layout[2][1] == me &&game_board.layout[3][1] == me && (from_X != 1 && from_Y != 2) && (from_X != 1 && from_Y != 3))
			return false;
		if (to_X == 1 && to_Y == 2 && game_board.layout[2][0] == me &&game_board.layout[3][1] == me && (from_X != 0 && from_Y != 2) && (from_X != 1 && from_Y != 3))
			return false;
		if (to_X == 1 && to_Y == 3 && game_board.layout[2][0] == me &&game_board.layout[2][1] == me && (from_X != 0 && from_Y != 2) && (from_X != 1 && from_Y != 2))
			return false;

	}
	if (game_board.layout[3][3] == op)
	{
		if (to_X == 3 && to_Y == 2 && game_board.layout[2][2] == me &&game_board.layout[3][2] == me && (from_X != 2 && from_Y != 2) && (from_X != 2 && from_Y != 3))
			return false;
		if (to_X == 2 && to_Y == 2 && game_board.layout[2][3] == me &&game_board.layout[3][2] == me && (from_X != 3 && from_Y != 2) && (from_X != 2 && from_Y != 3))
			return false;
		if (to_X == 2 && to_Y == 3 && game_board.layout[2][2] == me &&game_board.layout[2][3] == me && (from_X != 2 && from_Y != 2) && (from_X != 3 && from_Y != 2))
			return false;

	}

    if (from_X == to_X)
    {
        if (from_Y > to_Y)
        {
            for (int i = from_Y - 1; i >= to_Y && mov; i--)
            {
                if (game_board.layout[i][from_X] != EMPTY)
                    mov = false;
            }
            if (mov)
            {
                if (to_Y > 0 && game_board.layout[to_Y - 1][from_X] == EMPTY)
                    mov = false;
            }
            return mov;
        }
        else if (from_Y < to_Y)
        {
            for (int i = from_Y + 1; i <= to_Y && mov; i++)
            {
                if (game_board.layout[i][from_X] != EMPTY)
                    mov = false;
            }
            if (mov)
            {
                if (to_Y < XYDIM - 1 && game_board.layout[to_Y + 1][from_X] == EMPTY)
                    mov = false;
            }
            return mov;
        }
        else
            return false;
    }


    if (from_Y == to_Y)
    {
        if (from_X > to_X)
        {
            for (int i = from_X - 1; i >= to_X && mov; i--)
            {
                if (game_board.layout[from_Y][i] != EMPTY)
                    mov = false;
            }
            if (mov)
            {
                if (to_X > 0 && game_board.layout[from_Y][to_X-1] == EMPTY)
                    mov = false;
            }
            return mov;
        }
        else if (from_X < to_X)
        {
            for (int i = from_X + 1; i <= to_X && mov; i++)
            {
                if (game_board.layout[from_Y][i] != EMPTY)
                    mov = false;
            }
            if (mov)
            {
                if (to_Y < XYDIM - 1 && game_board.layout[from_Y][to_X+1] == EMPTY)
                    mov = false;
            }
            return mov;
        }
        else
            return false;
    }

    if (abs(to_X - from_X) == abs(to_Y - from_Y))
    {
        int i, j;
        if (from_X < to_X)
        {
            if (from_Y < to_Y)
            {
                for (i = from_X + 1, j=from_Y +1; i <= to_X && mov; i++,j++)
                {
                    if (game_board.layout[j][i] != EMPTY)
                        mov = false;
                }
                if (mov)
                {
                    if (to_Y < XYDIM - 1 && to_X < XYDIM-1 && game_board.layout[to_Y + 1][to_X + 1] == EMPTY)
                        mov = false;
                }
                return mov;
            }
            else
            {
                for (i = from_X + 1,  j = from_Y - 1; i <= to_X && mov; i++, j--)
                {
                    if (game_board.layout[j][i] != EMPTY)
                        mov = false;
                }
                if (mov)
                {
                    if (to_Y > 0 && to_X < XYDIM-1 && game_board.layout[to_Y - 1][to_X + 1] == EMPTY)
                        mov = false;
                }
                return mov;
            }
        }
        else
        {
            if (from_Y < to_Y)
            {
                for ( i = from_X -1,  j = from_Y + 1; i >= to_X && mov; i--, j++)
                {
                    if (game_board.layout[j][i] != EMPTY)
                        mov = false;
                }
                if (mov)
                {
                    if (to_Y < XYDIM - 1 && to_X > 0 && game_board.layout[to_Y + 1][to_X -1] == EMPTY)
                        mov = false;
                }
                return mov;
            }
            else
            {
                for ( i = from_X -1 ,  j = from_Y - 1; i >= to_X && mov; i--, j--)
                {
                    if (game_board.layout[j][i] != EMPTY)
                        mov = false;
                }
                if (mov)
                {
                    if (to_Y > 0 && to_X > 0 && game_board.layout[to_Y - 1][to_X -1] == EMPTY)
                        mov = false;
                }
                return mov;
            }
        }
    }    

    return false;
}

#endif
