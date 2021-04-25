// player1.h: player 1 agent.
// Author:    <Ting Wang>
// Date:	  <4/8/2018>
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
    bool find_mid(unsigned short from_X, unsigned short  from_Y, unsigned short to_X, unsigned short to_Y, board game_board, unsigned short player, unsigned short& mid_X, unsigned short& mid_Y);
};

Move Player1::get_move(unsigned short player, board game_board)

{
    Move move;
    unsigned short from_X, from_Y, to_X, to_Y;

    unsigned short me, op;
    bool find_move = false;
    bool win_sq = false, win_cor = false, win_line = false;
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
    cout << "Ting Wang's 3rd edition!\n";

   //initialize move priority of piece to 6
    for (int i = 0; i < XYDIM; i++) 
    {
        for (int j = 0; j < XYDIM; j++) 
        {
            if (game_board.layout[i][j] == me)
                move_pri[i][j] = 6;
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

    //set H-value of empty space around pices to 100, if in the middle of 2 pieces set to 60 and move priority to 5
    for (int i = 0; i < XYDIM; i++) 
    {
        for (int j = 0; j < XYDIM; j++)
        {
            if (game_board.layout[i][j] == me)
            {

				if (j < XYDIM - 1 && game_board.layout[i][j + 1] == EMPTY)
				{
                    if (heu_me[i][j + 1] > 100)
                        heu_me[i][j + 1] = 100;
                    if (j < XYDIM - 2 && game_board.layout[i][j + 2] == me)
                    {
                        heu_me[i][j + 1] = 60;
                        move_pri[i][j] = 5;
                        move_pri[i][j+2] = 5;
                    }
                    if (i>0 && game_board.layout[i-1][j+1] == me)
                    {
                        heu_me[i][j + 1] = 60;
                        move_pri[i][j] = 5;
                        move_pri[i-1][j + 1] = 5;
                        
                    }
                    if (i<XYDIM && game_board.layout[i + 1][j + 1] == me)
                    {
                        heu_me[i][j + 1] = 60;
                        move_pri[i][j] = 5;
                        move_pri[i+1][j + 1] = 5;
                        
                    }
						
				}
				if (i < XYDIM - 1 && game_board.layout[i + 1][j] == EMPTY)
				{
                    if (heu_me[i + 1][j] > 100)
                        heu_me[i + 1][j] = 100;
                    if (i < XYDIM - 2 && game_board.layout[i + 2][j] == me)
                    {
                        heu_me[i + 1][j] = 60;
                        move_pri[i][j] = 5;
                        move_pri[i+2 ][j ] = 5;
                    }
                    if (j < XYDIM - 1 && game_board.layout[i + 1][j + 1] == me)
                    {
                        heu_me[i + 1][j] = 60;
                        move_pri[i][j] = 5;
                        move_pri[i + 1][j + 1] = 5;
                    }
						
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
                    if (move_pri[i][j] > 4)
                        move_pri[i][j] = 4;
                    if (move_pri[i][j + 1] > 4)
                        move_pri[i][j + 1] = 4;

                    if (j < (XYDIM - 2) && game_board.layout[i][j + 2] == me)
                    {
                   //     move_pri[i][j] = 2;
                        if (move_pri[i][j + 1] > 3)
                            move_pri[i][j + 1] = 3;
                   //     move_pri[i][j + 2] = 2;


                        if (j < (XYDIM - 3) && game_board.layout[i][j + 3] == EMPTY)
                        {
                            heu_me[i][j + 3] = 0;
                            move_pri[i][j] = 2;
                            move_pri[i][j + 1] = 1;
                            move_pri[i][j + 2] = 2;
                            win_line = true;
            
                        }
                        else if (j == (XYDIM - 3) && game_board.layout[i][j - 1] == EMPTY)
                        {
                            heu_me[i][j - 1] = 0;
                            move_pri[i][j] = 2;
                            move_pri[i][j + 1] = 1;
                            move_pri[i][j + 2] = 2;
                            win_line = true;
  
                        }
                        else
                        {
                            ;
                        }
                    }

                    if (j < (XYDIM - 3) && game_board.layout[i][j + 2] == EMPTY)
                    {
                        if (heu_me[i][j + 2] > 50)
                            heu_me[i][j + 2] = 50;
                        if (game_board.layout[i][j + 3] == me)
                        {
                            move_pri[i][j] = 2;
                            move_pri[i][j + 1] = 2;
                            move_pri[i][j + 3] = 3;

                            heu_me[i][j + 2] = 10;
                            win_line = true;
                        }
            
                    }
					if (j == (XYDIM - 2) && game_board.layout[i][j - 1] == EMPTY)
					{
                        if (heu_me[i][j - 1] > 50)
                            heu_me[i][j - 1] = 50;
						if (game_board.layout[i][j -2] == me)
						{
							move_pri[i][j] = 2;
							move_pri[i][j + 1] = 2;
							move_pri[i][j - 2] = 3;

							heu_me[i][j -1] = 10;
                            win_line = true;
						}
					}



                    if (i < XYDIM - 1)
                    {
                        if (game_board.layout[i + 1][j] == EMPTY && game_board.layout[i + 1][j + 1] == EMPTY)
                        {
                            if (heu_me[i + 1][j] > 50)
                                heu_me[i + 1][j] = 50;
                            if (heu_me[i + 1][j + 1] > 50)
                                heu_me[i + 1][j + 1] = 50;
                        }
    

                        if (game_board.layout[i + 1][j] == me && game_board.layout[i + 1][j + 1] == EMPTY)
                        {
                            move_pri[i][j] = 1;
                            if (move_pri[i][j + 1] > 2)
                                move_pri[i][j + 1] = 2;
                            if (move_pri[i + 1][j] > 2)
                                move_pri[i + 1][j] = 2;

                            heu_me[i + 1][j + 1] = 20;
                            win_sq = true;
                 
                        }

                        if (game_board.layout[i + 1][j + 1] == me && game_board.layout[i + 1][j] == EMPTY)
                        {
                            if (move_pri[i][j] > 2)
                                move_pri[i][j] = 2;
                            move_pri[i][j + 1] = 1;
                            if (move_pri[i + 1][j + 1] > 2)
                                move_pri[i + 1][j + 1] = 2;

                            heu_me[i+1][j ] = 20;
                            win_sq = true;
    
                        }

                    }

                    if (i > 0)
                    {
                        if (game_board.layout[i - 1][j] == EMPTY && game_board.layout[i - 1][j + 1] == EMPTY)
                        {
                            if (heu_me[i - 1][j] > 50)
                                heu_me[i - 1][j] = 50;
                            if (heu_me[i - 1][j + 1] > 50)
                                heu_me[i - 1][j + 1] = 50;
                        }
                            
                            

                        if (game_board.layout[i - 1][j] == me && game_board.layout[i - 1][j + 1] == EMPTY)
                        {
                            if (move_pri[i - 1][j] > 2)
                                move_pri[i - 1][j] = 2;
                            move_pri[i][j] = 1;
                            if (move_pri[i][j + 1] > 2)
                                move_pri[i][j + 1] = 2;

                            heu_me[i - 1][j + 1] = 20;
                            win_sq = true;
                        }

                        if (game_board.layout[i - 1][j + 1] == me && game_board.layout[i - 1][j] == EMPTY)
                        {
                            if (move_pri[i - 1][j + 1] > 2)
                                move_pri[i - 1][j + 1] = 2;
                            if (move_pri[i][j] > 2)
                                move_pri[i][j] = 2;
                            move_pri[i][j + 1] = 1;

                            heu_me[i - 1][j] = 20;
                            win_sq = true;
                        }

                    }

                }

                if (i < (XYDIM - 1) && game_board.layout[i + 1][j] == me)
                {
					if (move_pri[i][j] > 4)
						move_pri[i][j] = 4;
					if (move_pri[i + 1][j] > 4)
						move_pri[i + 1][j] = 4;

                    if (j < (XYDIM - 1) && game_board.layout[i][j + 1] == EMPTY && game_board.layout[i + 1][j + 1] == EMPTY )
                    {
                        if(heu_me[i][j + 1] >50)
                            heu_me[i][j + 1] = 50;
                        if (heu_me[i + 1][j + 1] >50)
                            heu_me[i + 1][j + 1] = 50;
                    }
                        
                   
                        
                    if (j > 0 && game_board.layout[i][j - 1] == EMPTY && game_board.layout[i + 1][j - 1] == EMPTY )
                    {
                        if(heu_me[i][j - 1] > 50)
                            heu_me[i][j - 1] = 50;
                        if(heu_me[i + 1][j - 1] > 50)
                            heu_me[i + 1][j - 1] = 50;
                    }
                        
                    
                        

                    if (i < (XYDIM - 2) && game_board.layout[i + 2][j] == EMPTY)
                    {
                        if (heu_me[i + 2][j] > 50)
                            heu_me[i + 2][j] = 50;
                        if (i < (XYDIM - 3) && game_board.layout[i + 3][j] == me)
                        {
                            move_pri[i][j] = 2;
                            move_pri[i + 1][j] = 2;
                            move_pri[i + 3][j] = 3;

                            heu_me[i + 2][j] = 10;
                            win_line = true;

                        }

                    }

                    if (i > 0 && game_board.layout[i - 1][j] == EMPTY)
                    {
                        if (heu_me[i-1][j] > 50)
                            heu_me[i-1][j] = 50;
						if (i > 1 && game_board.layout[0][j] == me)
                        {
                            move_pri[i][j] = 2;
                            move_pri[i + 1][j] = 2;
                            move_pri[0][j] = 3;

                            heu_me[i - 1][j] = 10;
                            win_line = true;

                        }

                    }

                    if (i < (XYDIM - 2) && game_board.layout[i + 2][j] == me)
                    {
                      //  move_pri[i][j] = 2;
                        move_pri[i + 1][j] = 3;
                      //  move_pri[i + 2][j] = 2;

                        if (i < (XYDIM - 3) && game_board.layout[i + 3][j] == EMPTY)
                        {
                            heu_me[i + 3][j] = 0;
                            if (move_pri[i][j] > 2)
                                move_pri[i][j] = 2;
                            move_pri[i + 1][j] = 1;
                            if (move_pri[i + 2][j] > 2)
                                move_pri[i + 2][j] = 2;
                            win_line = true;
         
                        }
                        else if (i == (XYDIM - 3) && game_board.layout[i - 1][j] == EMPTY)
                        {
                            heu_me[i - 1][j] = 0;
                            if (move_pri[i][j] > 2)
                                move_pri[i][j] = 2;
                            move_pri[i + 1][j] = 1;
                            if (move_pri[i + 2][j] > 2)
                                move_pri[i + 2][j] = 2;
                            win_line = true;
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
            win_cor = true;
		}
		else if(cor == 2)
			for (int i = 0; i < XYDIM; i++)
			{
				for (int j = 0; j < XYDIM; j++)
				{
                    if (game_board.layout[i][j] == me)
                    {
                        if (move_pri[i][j] > 3)
                            move_pri[i][j] = 3;
                    }
						
                    else if (game_board.layout[i][j] == EMPTY)
                    {
                        if (heu_me[i][j] > 40)
                            heu_me[i][j] = 40;
                    }
						
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
                    {
                        if (move_pri[i][j] > 5)
                            move_pri[i][j] = 5;
                    }
						
                    else if (game_board.layout[i][j] == EMPTY)
                    {
                        if (heu_me[i][j] > 80)
                            heu_me[i][j] = 80;
                    }
						
					j = j + 2;
				}
				i = i + 2;
			}
		else
			for (int i = 0; i < XYDIM; i=i+3)
			{
				for (int j = 0; j < XYDIM; j=j+3)
				{
					if (game_board.layout[i][j] == EMPTY)
						heu_me[i][j] = 90;
					
				}
				
			}
	}

  


/*
	
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cout << setw(10) << heu_me[i][j];
		}
		cout << endl << endl << endl;
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
            else
                hue_op[i][j] = 200;

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
					if (j == 0 && game_board.layout[i][j + 3] == op)
						hue_op[i][2] = 0;
					if (j == 2 && game_board.layout[i][0] == op)
						hue_op[i][1] = 0;
					if (i < XYDIM - 1)
					{
						if (game_board.layout[i + 1][j] == op)
							hue_op[i + 1][j + 1] = 0;
						if (game_board.layout[i + 1][j + 1] == op)
							hue_op[i + 1][j] = 0;
					}
					if (i > 0)
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
					if (i == 0 && game_board.layout[3][j] == op)
						hue_op[2][j] = 0;
					if (i == 2 && game_board.layout[0][j] == op)
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

    for (int i = 0; i < XYDIM; i++)
        for (int j = 0; j < XYDIM; j++)
            if (hue_op[i][j] == 0 && game_board.layout[i][j] == op)
            {
                hue_op[i][j] = 200;
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
/*
    //find the lowest H-value point then move my hightest move priority piece to it if posible.
    //If can not find the 1-pace-to-win place and the other side has 1-pace-to-win, try to occupy it.
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
                    for (int l=6;l>0 && !find_move;l--)
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
                                                if (!(defence && k <= 10 && move_pri[m][n] < 3))
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

    */

    //if one shift to win in corner
    //if corner win
    if (win_cor)
    {
        for (int i = 0; i < XYDIM ; i++)
            for (int j = 0; j < XYDIM ; j++)
                if (heu_me[i][j] == 0)
                {
                    to_X = j;
                    to_Y = i;
                }
        for (int k = 6; k>1 && !find_move; k--)
            for (int m = 0; m < XYDIM; m++)
                for (int n = 0; n < XYDIM; n++)
                    if (move_pri[m][n] == k)
                    {
                        from_X = n;
                        from_Y = m;
                        find_move = moveable(from_X, from_Y, to_X, to_Y, game_board, player);
                    }
              
    }
    //if line win
    else if (win_line)
    {
        if (!win_sq)
        {
            for (int k = 0; k <= 10; k = k + 10)
            {
                for (int i = 0; i < XYDIM; i++)
                {
                    for (int j = 0; j < XYDIM; j++)
                    {
                        if (heu_me[i][j] == k)
                        {
                            to_X = j;
                            to_Y = i;
                        }
                    }
                }
            }
            for (int k = 6; k > 3 && !find_move; k--)
                for (int m = 0; m < XYDIM; m++)
                    for (int n = 0; n < XYDIM; n++)
                        if (move_pri[m][n] == k)
                        {
                            from_X = n;
                            from_Y = m;
                            find_move = moveable(from_X, from_Y, to_X, to_Y, game_board, player);
                        }
        }

        else
        {
            ////try squar win
            int w_X, w_Y;
            bool connect3 = false;
            for (int i = 0; i < XYDIM; i++)
                for (int j = 0; j < XYDIM; j++)
                {
                    if (heu_me[i][j] == 0)
                    {
                        to_X = j;
                        to_Y = i;
                        connect3 = true;
                    }
                    if (heu_me[i][j] == 20)
                    {
                        w_X = j;
                        w_Y = i;
                    }

                }

            if (connect3 &&(abs(w_X - to_X) + abs(w_Y - to_Y) == 3))
            {
                for (int i = 0; i < XYDIM; i++)
                    for (int j = 0; j < XYDIM; j++)
                    {
                        if (heu_me[i][j] == 20)
                        {
                            to_X = j;
                            to_Y = i;
                        }
                    }
                for (int m = 0; m < XYDIM; m++)
                    for (int n = 0; n < XYDIM; n++)
                        if (move_pri[m][n] == 2 && (abs(m - to_Y) == abs(n - to_X)))
                        {
                            from_X = n;
                            from_Y = m;
                        }
                find_move = moveable(from_X, from_Y, to_X, to_Y, game_board, player);
                if (find_move)
                {
                    move.src_x = from_X;
                    move.src_y = from_Y;
                    move.dst_x = to_X;
                    move.dst_y = to_Y;
                    return move;
                }

            }


            //try line win
            bool des = false;
            for (int i = 0; i < XYDIM; i++)
                for (int j = 0; j < XYDIM; j++)
                    if (heu_me[i][j] == 10 || heu_me[i][j] == 0)
                    {
                        to_X = j;
                        to_Y = i;
                        des = true;
                    }
            if (des)
            {
                if (to_Y > 0 && to_X > 0 && game_board.layout[to_Y - 1][to_X - 1] == me)
                {
                    from_X = to_X - 1;
                    from_Y = to_Y - 1;
                    find_move = moveable(from_X, from_Y, to_X, to_Y, game_board, player);
                }
                if (to_Y > 0 && to_X < XYDIM - 1 && game_board.layout[to_Y - 1][to_X + 1] == me)
                {
                    from_X = to_X + 1;
                    from_Y = to_Y - 1;
                    find_move = moveable(from_X, from_Y, to_X, to_Y, game_board, player);
                }
                if (to_Y < XYDIM - 1 && to_X > 0 && game_board.layout[to_Y + 1][to_X - 1] == me)
                {
                    from_X = to_X - 1;
                    from_Y = to_Y + 1;
                    find_move = moveable(from_X, from_Y, to_X, to_Y, game_board, player);
                }
                if (to_Y < XYDIM - 1 && to_X < XYDIM - 1 && game_board.layout[to_Y + 1][to_X + 1] == me)
                {
                    from_X = to_X + 1;
                    from_Y = to_Y + 1;
                    find_move = moveable(from_X, from_Y, to_X, to_Y, game_board, player);
                }

            }

        }
    }
    //if squar win    
    else if (win_sq)
    {
        for (int i = 0; i < XYDIM; i++)
            for (int j = 0; j < XYDIM; j++)
                if (heu_me[i][j] == 20)
                {
                    to_X = j;
                    to_Y = i;
                }
/*
        for (int i = 0; i < XYDIM; i++)
        {
            for (int j = 0; j < XYDIM; j++)
                cout << heu_me[i][j] << "\t";
            cout << endl;
        }
 */     



        for (int k = 6; k>2 && !find_move; k--)
            for (int m = 0; m < XYDIM; m++)
                for (int n = 0; n < XYDIM; n++)
                    if (move_pri[m][n] == k)
                    {
                        

                        from_X = n;
                        from_Y = m;
                                                                      
                        find_move = moveable(from_X, from_Y, to_X, to_Y, game_board, player);
                    }
        
    }

    if (find_move)
    {
        
        move.src_x = from_X;
        move.src_y = from_Y;
        move.dst_x = to_X;
        move.dst_y = to_Y;
        return move;
    }

	if (defence)
	{
    //    cout << "defence now!\n";
		to_X = block_X;
		to_Y = block_Y;
		for (int l = 6; l>0 && !find_move; l--)
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
		return move;
	}
    // try 2 movement win
    if (win_cor || win_line || win_sq)
    {
        if (win_cor)
        {
            for (int i = 0; i < XYDIM; i++)
                for (int j = 0; j < XYDIM; j++)
                    if (heu_me[i][j] == 0)
                    {
                        to_X = j;
                        to_Y = i;
                    }
            for (int k = 6; k > 1 && !find_move; k--)
                for (int m = 0; m < XYDIM; m++)
                    for (int n = 0; n < XYDIM; n++)
                        if (move_pri[m][n] == k)
                        {
                            from_X = n;
                            from_Y = m;
                            unsigned short mid_X = 10, mid_Y = 10;
                            if (find_mid(from_X, from_Y, to_X, to_Y, game_board, player, mid_X, mid_Y))
                            {
                                if (hue_op[mid_Y][mid_X] != 0)
                                {
                                    to_X = mid_X;
                                    to_Y = mid_Y;
                                    find_move = true;
                                    //   find_move = moveable(from_X, from_Y, to_X, to_Y, game_board, player);
                                }
                                
                            }

                        }
            if (find_move)
            {
                move.src_x = from_X;
                move.src_y = from_Y;
                move.dst_x = to_X;
                move.dst_y = to_Y;
                return move;
            }

        }

        if (win_line)
        {
            if (!win_sq)
            {
                for (int i = 0; i < XYDIM; i++)
                    for (int j = 0; j < XYDIM; j++)
                        if (heu_me[i][j] == 0 || heu_me[i][j] == 10)
                        {
                            to_X = j;
                            to_Y = i;
                        }
                for (int k = 6; k > 3 && !find_move; k--)
                    for (int m = 0; m < XYDIM; m++)
                        for (int n = 0; n < XYDIM; n++)
                            if (move_pri[m][n] == k)
                            {
                                from_X = n;
                                from_Y = m;
                                unsigned short mid_X = 10, mid_Y = 10;
                                if (find_mid(from_X, from_Y, to_X, to_Y, game_board, player, mid_X, mid_Y))
                                {
                                    if (hue_op[mid_Y][mid_X] != 0)
                                    {
                                        to_X = mid_X;
                                        to_Y = mid_Y;
                                        find_move = true;
                                        //   find_move = moveable(from_X, from_Y, to_X, to_Y, game_board, player);
                                    }
                                }

                            }
                if (find_move)
                {
                    move.src_x = from_X;
                    move.src_y = from_Y;
                    move.dst_x = to_X;
                    move.dst_y = to_Y;
                    return move;
                }
            }
            else
            {
                //   1
                //1011 and
                for (int i = 0; i < XYDIM; i++)
                    for (int j = 0; j < XYDIM; j++)
                        if (heu_me[i][j] == 10)
                        {
                            to_X = j;
                            to_Y = i;
                        }
                for (int m = 0; m < XYDIM; m++)
                    for (int n = 0; n < XYDIM; n++)
                        if (move_pri[m][n] == 2)
                        {
                            from_X = n;
                            from_Y = m;
                            find_move = moveable(from_X, from_Y, to_X, to_Y, game_board, player);
                            if (find_move)
                            {
                                move.src_x = from_X;
                                move.src_y = from_Y;
                                move.dst_x = to_X;
                                move.dst_y = to_Y;
                                return move;
                            }
                        }
                //  1         1
                //0111  or 0111
                int w_X, w_Y;
                for (int i = 0; i < XYDIM; i++)
                    for (int j = 0; j < XYDIM; j++)
                    {
                        if (heu_me[i][j] == 0)
                        {
                            to_X = j;
                            to_Y = i;
                        }
                        if (heu_me[i][j] == 20)
                        {
                            w_X = j;
                            w_Y = i;
                        }

                    }
                if (abs(w_X - to_X) == 3 || abs(w_Y - to_Y) == 3)
                {
                    if (to_X == 0 && w_X == 3)
                    {
                        from_X = 1;
                        from_Y = to_Y;
                    }
                    if (to_X == 3 && w_X == 3)
                    {
                        from_X = 2;
                        from_Y = to_Y;
                    }
                    if (to_Y == 0 && w_Y == 3)
                    {
                        from_Y = 1;
                        from_X = to_X;
                    }
                    if (to_Y == 3 && w_Y == 3)
                    {
                        from_Y = 2;
                        from_X = to_Y;
                    }

                    if (hue_op[from_Y][from_X] != 0)
                        find_move = moveable(from_X, from_Y, to_X, to_Y, game_board, player);
                    
                    if (find_move)
                    {
                        move.src_x = from_X;
                        move.src_y = from_Y;
                        move.dst_x = to_X;
                        move.dst_y = to_Y;
                        return move;
                    }

                }
                else if (abs(w_X - to_X) == 2 || abs(w_Y - to_Y) == 2)
                {
                    //try squar win
                    for (int i = 0; i < XYDIM; i++)
                        for (int j = 0; j < XYDIM; j++)
                        {
                            if (heu_me[i][j] == 20)
                            {
                                to_X = j;
                                to_Y = i;
                            }
                        }
                    for (int m = 0; m < XYDIM; m++)
                        for (int n = 0; n < XYDIM; n++)
                            if (move_pri[m][n] == 2 && (abs(m - to_Y) == abs(n - to_X)))
                            {
                                from_X = n;
                                from_Y = m;
                            }
                    find_move = moveable(from_X, from_Y, to_X, to_Y, game_board, player);
                    if (find_move)
                    {
                        move.src_x = from_X;
                        move.src_y = from_Y;
                        move.dst_x = to_X;
                        move.dst_y = to_Y;
                        return move;
                    }

                    for (int i = 0; i < XYDIM; i++)
                        for (int j = 0; j < XYDIM; j++)
                        {
                            if (heu_me[i][j] == 0)
                            {
                                to_X = j;
                                to_Y = i;
                            }
                        }
                    for (int m = 0; m < XYDIM; m++)
                        for (int n = 0; n < XYDIM; n++)
                            if (move_pri[m][n] == 2 && ((abs(m - to_Y) + abs(n - to_X)) > 1))
                            {
                                from_X = n;
                                from_Y = m;
                            }
                    unsigned short mid_X = 10, mid_Y = 10;
                    if (find_mid(from_X, from_Y, to_X, to_Y, game_board, player, mid_X, mid_Y))
                    {
                        if (hue_op[mid_Y][mid_X] != 0)
                        {
                            to_X = mid_X;
                            to_Y = mid_Y;
                            find_move = true;
                            //   find_move = moveable(from_X, from_Y, to_X, to_Y, game_board, player);
                        }
                    }

                    if (find_move)
                    {
                        move.src_x = from_X;
                        move.src_y = from_Y;
                        move.dst_x = to_X;
                        move.dst_y = to_Y;
                        return move;
                    }

                }

            }
        }

        if (win_sq)
        {
            for (int i = 0; i < XYDIM; i++)
                for (int j = 0; j < XYDIM; j++)
                    if (heu_me[i][j] == 20 )
                    {
                        to_X = j;
                        to_Y = i;
                    }
            for (int k = 6; k > 3 && !find_move; k--)
                for (int m = 0; m < XYDIM; m++)
                    for (int n = 0; n < XYDIM; n++)
                        if (move_pri[m][n] == k)
                        {
                            from_X = n;
                            from_Y = m;
                            unsigned short mid_X = 10, mid_Y = 10;
                            if (find_mid(from_X, from_Y, to_X, to_Y, game_board, player, mid_X, mid_Y))
                            {
                                if (hue_op[mid_Y][mid_X] != 0)
                                {
                                    to_X = mid_X;
                                    to_Y = mid_Y;
                        
                                   // find_move = true;
                                    find_move = moveable(from_X, from_Y, to_X, to_Y, game_board, player);
                                }
                            }

                        }
            if (find_move)
            {
                move.src_x = from_X;
                move.src_y = from_Y;
                move.dst_x = to_X;
                move.dst_y = to_Y;
                return move;
            }

        }



    }
    if (find_move)
    {
        move.src_x = from_X;
        move.src_y = from_Y;
        move.dst_x = to_X;
        move.dst_y = to_Y;
        return move;
    }


    for (int k = 20; k <= 200 && !find_move; k = k + 10)
    {
        for (int i = 0; i < XYDIM && !find_move; i++)
        {
            for (int j = 0; j < XYDIM && !find_move; j++)
            {
                if (heu_me[i][j] == k )
                {
                    to_X = j;
                    to_Y = i;
                    for (int l = 6; l>0 && !find_move; l--)
                        for (int m = 0; m < XYDIM && !find_move; m++)
                            for (int n = 0; n < XYDIM && !find_move; n++)
                            {
                                if (move_pri[m][n] == l &&hue_op[m][n] != 0)
                                {
                                    from_X = n;
                                    from_Y = m;
                                    for (int ii = 0; ii < XYDIM && !find_move; ii++)
                                    {
                                        for (int jj = 0; jj < XYDIM && !find_move; jj++)
                                        {
                                            if (heu_me[ii][jj] == k && !find_move)
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



    //can not find other movment then just move the hightest move priority piece to a movable palce 
    for (int l = 5; l>0 && !find_move; l--)
        for (int m = 0; m < XYDIM && !find_move; m++)
            for (int n = 0; n < XYDIM && !find_move; n++)
            {
                if (move_pri[m][n] == l && hue_op[m][n] != 0)
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

    //do not sucide in 4 corner
    if (game_board.layout[0][0] == op)
    {
        if (to_X == 1 && to_Y == 0 && game_board.layout[1][1] == me &&game_board.layout[1][0] == me && !((from_X == 1 && from_Y == 1) || (from_X == 0 && from_Y == 1)))
            return false;
        if (to_X == 1 && to_Y == 1 && game_board.layout[0][1] == me &&game_board.layout[1][0] == me && !((from_X == 1 && from_Y == 0) || (from_X == 0 && from_Y == 1)))
            return false;
        if (to_X == 0 && to_Y == 1 && game_board.layout[1][1] == me &&game_board.layout[0][1] == me && !((from_X == 1 && from_Y == 1) || (from_X == 1 && from_Y == 0)))
            return false;
    }
    if (game_board.layout[0][3] == op)
    {
        if (to_X == 2 && to_Y == 0 && game_board.layout[1][2] == me &&game_board.layout[1][3] == me && !((from_X == 2 && from_Y == 1) || (from_X == 3 && from_Y == 1)))
            return false;
        if (to_X == 2 && to_Y == 1 && game_board.layout[0][2] == me &&game_board.layout[1][3] == me && !((from_X == 2 && from_Y == 0) || (from_X == 3 && from_Y == 1)))
            return false;
        if (to_X == 3 && to_Y == 1 && game_board.layout[0][2] == me &&game_board.layout[1][2] == me && !((from_X == 2 && from_Y == 0) || (from_X == 2 && from_Y == 1)))
            return false;
    }
    if (game_board.layout[3][0] == op)
    {
        if (to_X == 0 && to_Y == 2 && game_board.layout[2][1] == me &&game_board.layout[3][1] == me && !((from_X == 1 && from_Y == 2) || (from_X == 1 && from_Y == 3)))
            return false;
        if (to_X == 1 && to_Y == 2 && game_board.layout[2][0] == me &&game_board.layout[3][1] == me && !((from_X == 0 && from_Y == 2) || (from_X == 1 && from_Y == 3)))
            return false;
        if (to_X == 1 && to_Y == 3 && game_board.layout[2][0] == me &&game_board.layout[2][1] == me && !((from_X == 0 && from_Y == 2) || (from_X == 1 && from_Y == 2)))
            return false;

    }
    if (game_board.layout[3][3] == op)
    {
        if (to_X == 3 && to_Y == 2 && game_board.layout[2][2] == me &&game_board.layout[3][2] == me && !((from_X == 2 && from_Y == 2) || (from_X == 2 && from_Y == 3)))
            return false;
        if (to_X == 2 && to_Y == 2 && game_board.layout[2][3] == me &&game_board.layout[3][2] == me && !((from_X == 3 && from_Y == 2) || (from_X == 2 && from_Y == 3)))
            return false;
        if (to_X == 2 && to_Y == 3 && game_board.layout[2][2] == me &&game_board.layout[2][3] == me && !((from_X == 2 && from_Y == 2) || (from_X == 3 && from_Y == 2)))
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
                if (to_X < XYDIM - 1 && game_board.layout[from_Y][to_X+1] == EMPTY)
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

bool Player1::find_mid(unsigned short from_X, unsigned short  from_Y, unsigned short to_X, unsigned short to_Y, board game_board, unsigned short player, unsigned short& mid_X, unsigned short& mid_Y)
{
    bool find = false;
    int x = -1, y = -1;
    int  cross[XYDIM][XYDIM];

    for (int i = 0; i < XYDIM; i++)
        for (int j = 0; j < XYDIM; j++)
            cross[i][j] = 0;

   //draw move-from line
    if (from_X > 0)
    {
        //west line
        x = from_X - 1;
        while (x >= 0 && game_board.layout[from_Y][x] == EMPTY )
        {
            cross[from_Y][x]++;
            cross[from_Y][x + 1]--;
            x--;
        }
        //northwest line
        if (from_Y > 0)
        {
            x = from_X - 1;
            y = from_Y - 1;
            while (x >= 0 && y>=0 &&game_board.layout[y][x] == EMPTY)
            {
                cross[y][x]++;
                cross[y + 1][x + 1]--;
                x--;
                y--;
            }
        }
        //southwest line
        if (from_Y <XYDIM -1)
        {
            x = from_X - 1;
            y = from_Y + 1;
            while (x >= 0 && y < XYDIM   && game_board.layout[y][x] == EMPTY)
            {
                cross[y][x]++;
                cross[y - 1][x + 1]--;
                x--;
                y++;
            }
        }
    }
    if (from_X < XYDIM - 1)
    {
        //East line
        x = from_X + 1;
        while (x < XYDIM && game_board.layout[from_Y][x] == EMPTY)
        {
            cross[from_Y][x]++;
            cross[from_Y][x - 1]--;
            x++;
        }
        //NorthEast line
        if (from_Y > 0)
        {
            x = from_X + 1;
            y = from_Y - 1;
            while (x <XYDIM && y >= 0 && game_board.layout[y][x] == EMPTY)
            {
                cross[y][x]++;
                cross[y + 1][x - 1]--;
                x++;
                y--;
            }
        }
        //SouthEast line
        if (from_Y <XYDIM - 1)
        {
            x = from_X + 1;
            y = from_Y + 1;
            while (x <XYDIM && y < XYDIM   && game_board.layout[y][x] == EMPTY)
            {
                cross[y][x]++;
                cross[y - 1][x - 1]--;
                x++;
                y++;
            }
        }

    }

    //North line
    if (from_Y > 0)
    {
        y = from_Y - 1;
        while (y >= 0 && game_board.layout[y][from_X] == EMPTY)
        {
            cross[y][from_X]++;
            cross[y + 1][from_X]--;
            y--;
        }
    }

    //South line
    if (from_Y <XYDIM-1)
    {
        y = from_Y + 1;
        while (y <XYDIM && game_board.layout[y][from_X] == EMPTY)
        {
            cross[y][from_X]++;
            cross[y - 1][from_X]--;
            y++;
        }
    }

    //draw move-to line
    if (to_X > 0)
    {
        //west line
        if (to_X == 3 || game_board.layout[to_Y][to_X + 1] != EMPTY)
        {
            x = to_X - 1;
            while (x >= 0 && game_board.layout[to_Y][x] == EMPTY)
            {
                cross[to_Y][x]++;
                x--;
            }
        }
       
        //northwest line
        if (to_Y > 0)
        {
            if (to_X == 3 || to_Y == 3 || game_board.layout[to_Y + 1][to_X + 1] != EMPTY)
            {
                x = to_X - 1;
                y = to_Y - 1;
                while (x >= 0 && y >= 0 && game_board.layout[y][x] == EMPTY)
                {
                    cross[y][x]++;
                    
                    x--;
                    y--;
                }
            }
            
        }
        //southwest line
        if (to_Y <XYDIM - 1)
        {
            if (to_X == 3 || to_Y == 0 || game_board.layout[to_Y - 1][to_X + 1] != EMPTY)
            x = to_X - 1;
            y = to_Y + 1;
            while (x >= 0 && y < XYDIM   && game_board.layout[y][x] == EMPTY)
            {
                cross[y][x]++;
                
                x--;
                y++;
            }
        }
    }
    if (to_X < XYDIM - 1)
    {
        //East line
        if (to_X == 0 || game_board.layout[to_Y][to_X - 1] != EMPTY)
        {
            x = to_X + 1;
            while (x < XYDIM && game_board.layout[to_Y][x] == EMPTY)
            {
                cross[to_Y][x]++;
                
                x++;
            }
        }
        
        
        //NorthEast line
        if (to_Y > 0)
        {
            if (to_X == 0 || to_Y == 3 || game_board.layout[to_Y + 1][to_X - 1] != EMPTY)
            {
                x = to_X + 1;
                y = to_Y - 1;
                while (x <XYDIM && y >= 0 && game_board.layout[y][x] == EMPTY)
                {
                    cross[y][x]++;
                    
                    x++;
                    y--;
                }

            }
            
        }
        //SouthEast line
        if (to_Y <XYDIM - 1)
        {
            if (to_X == 0 || to_Y == 0 || game_board.layout[to_Y - 1][to_X - 1] != EMPTY)
            {
                x = to_X + 1;
                y = to_Y + 1;
                while (x <XYDIM && y < XYDIM   && game_board.layout[y][x] == EMPTY)
                {
                    cross[y][x]++;
                    
                    x++;
                    y++;
                }
            }
            
        }

    }

    //North line
    if (to_Y > 0)
    {
        if (to_Y == 3 || game_board.layout[to_Y + 1][to_X] != EMPTY)
        {
            y = to_Y - 1;
            while (y >= 0 && game_board.layout[y][to_X] == EMPTY)
            {
                cross[y][to_X]++;
                
                y--;
            }
        }
        
    }

    //South line
    if (to_Y <XYDIM - 1)
    {
        if (to_Y == 0 || game_board.layout[to_Y - 1][to_X] != EMPTY)
        {
            y = to_Y + 1;
            while (y <XYDIM && game_board.layout[y][to_X] == EMPTY)
            {
                cross[y][to_X]++;
                
                y++;
            }
        }
        
    }

    /*
    for (int i = 0; i < XYDIM; i++)
    {
        for (int j = 0; j < XYDIM; j++)
            cout << cross[i][j] << "\t";
        cout << endl;
    }
    */


    for (int i = 0; i < XYDIM; i++)
        for (int j = 0; j < XYDIM; j++)
            if (cross[i][j] == 2)
            {
                mid_X = j;
                mid_Y = i;
                find = true;
                return find;
            }

        
    return find;
}

#endif
