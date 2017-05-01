using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Backtracking
{
    public partial class Form1 : Form
    {
        Label[,] sudoku;
        
        public Form1()
        {
            InitializeComponent();
        }
    private void button1_Click(object sender, EventArgs e)
        {
            sudoku = generate_lables();
            int[,] puzzle = readIN();
            bool y = solve_puzzle(puzzle, 0, 0);
        }
    private Label[,] generate_lables()
       {
            Label[,] temp = new Label[9, 9];
            int Xstart = 10;
            int Ystart = 9;

            for (int i = 0; i < 9; i++)
            {
                for (int j = 0; j < 9; j++)
                {
                    Label a = new Label();
                    a.Name = "L" + Convert.ToString(i);
                    a.Location = new System.Drawing.Point(Xstart+=25, Ystart);
                    a.TabIndex = 0;
                    a.AutoSize = false;
                    a.Size = new System.Drawing.Size(10, 14);
                    this.Controls.Add(a);
                    a.Text = "0";
                    temp[i, j] = a;
                }
                Xstart = 12;
                Ystart += 25;
            }
            return temp;
        }// end generate_lables
    private bool solve_puzzle(int [,] puzzle,int row,int col)
     {
	    if (col == 9)
	    {
		    col = 0;
		    row++;
	    }
	    if (row == 9)
		    return true;
	
	    for (int i = 1; i < 10; i++)
	    {
		   if (puzzle[row,col] == 0)
		    {
			   if (good_number(puzzle, i, row, col))
			    {
				    puzzle[row,col] = i;
                    sudoku[row, col].Text = Convert.ToString(i);
                    sudoku[row, col].Refresh();
				    if (solve_puzzle(puzzle, row, col+1))
					    return true;
				    puzzle[row,col] = 0;
                    sudoku[row, col].Text = Convert.ToString(0);
                    //sudoku[row, col].Refresh();
			    }
		    }//end if valid position
		    if (puzzle[row,col] != 0)
			    return solve_puzzle(puzzle, row, col+1);
	    }//end for
	    // Back track here
	    return false;
    }//end solve puzzle   
    private bool good_number(int [,] puzzle,int number,int row,int col)
    {
	    // check row
	    for (int i = 0; i < 9; i++)
		    if (number == puzzle[row,i])
			    return false;
	    // check col	
	    for (int j = 0; j < 9; j++)
		    if (number == puzzle[j,col])
			    return false;
	    // row and col are good, check small puzzle
	    int Srow = row - row % 3;
	    int Scol = col - col % 3;
	
	    for (int i = 0; i < 3; i++) 
		    for (int j = 0; j < 3; j++)
			    if (puzzle[i + Srow,j + Scol] == number)
				    return false;
	    return true;
    }// end good_number
    private int[,] readIN()
    {
        List<int[]> points =
                    System.IO.File
                    .ReadAllLines("puzzle1.txt")
                    .Select(x => x.Split(' ')
                    .Select(y => int.Parse(y))
                    .ToArray())
                    .ToList();
        
        int[,] temp = new int[9, 9];

        for (int i = 0; i < 9; i++)
            for (int j = 0; j < 9; j++)
            {
                temp[i, j] = points[i][j];
                sudoku[i, j].Text = Convert.ToString(temp[i, j]);
                sudoku[i, j].Refresh();
            }

        return temp;
    }// end readIN

    }// end Form1
}// end Backtracking
