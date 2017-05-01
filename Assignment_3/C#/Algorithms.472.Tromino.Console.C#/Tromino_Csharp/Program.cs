using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
namespace Tromino_Csharp
{
    class Program
    {
        static void Main(string[] args)
        {
            Tromino puzzle = new Tromino();
            char[,] A = puzzle.Solved_Puzzle(16);
        }
    }
    class Tromino
    {
        private char[,] A;
        private char cell = 'A';
        public Tromino() { }
        public char[,] Solved_Puzzle(int max)
        {
            start_puzzle(max);
            return A;
        }
        private void start_puzzle(int max)
        {
            int resized = pow2(max);
            A = new char[resized, resized];
            int[] corners = new int[2] { 0, 0 };
            fill(A, resized);
            split(A, corners, max);
            printM(A, max);
        }
        private int pow2(int data)
        {
            int i = 1;
            while (i < data)
                i = i * 2;
            return i;
        }
        private void fill(char[,] A, int max)
        {
            Random rnd = new Random();
            // Fill matrix 
            for (int i = 0; i < max; i++)
                for (int j = 0; j < max; j++)
                    A[i, j] = '-';
            // Set random tile
            A[rnd.Next(0, max), rnd.Next(0, max)] = 'x';
        }
        private void split(char[,] A, int[] corners, int max)
        {
            //[row][column]
            int half = max / 2;
            int row = corners[0];
            int col = corners[1];

            int tile = scan(A, corners, max);
            mark(A, corners, tile, max);
            if (half > 1)
            {
                int[] A11 = new int[2] { row, col };
                int[] A12 = new int[2] { row, col + half };
                int[] A21 = new int[2] { row + half, col };
                int[] A22 = new int[2] { row + half, col + half };
                split(A, A11, half);
                split(A, A12, half);
                split(A, A21, half);
                split(A, A22, half);
            }
        }//end void split
        private int scan(char[,] A, int[] corners, int max)
        {
            int start_row = corners[0];
            int start_col = corners[1];
            int row = 0;
            int col = 0;
            int half = max / 2;
            for (int i = 0; i < max; i++)
                for (int j = 0; j < max; j++)
                    if (A[i + start_row, j + start_col] != '-')
                    {
                        row = i;
                        col = j;
                        break;
                    }
            // Tile in A11
            if (row < half && col < half)
                return 1;
            // Tile in A12
            if (row < half && col >= half)
                return 2;
            // Tile in A21
            if (row >= half && col < half)
                return 3;
            // Tile in A22
            if (row >= half && col >= half)
                return 4;
            return 0;
        }//end scan
        private void mark(char[,] A, int[] corners, int tile, int max)
        {
            //[row][col]
            int half = max / 2;
            int row = corners[0];
            int col = corners[1];
            //A11
            if (tile == 1)
            {
                A[row + half - 1, col + half] = cell;
                A[row + half, col + half] = cell;
                A[row + half, col + half - 1] = cell;
            }
            //A12
            if (tile == 2)
            {
                A[row + half - 1, col + half - 1] = cell;
                A[row + half, col + half] = cell;
                A[row + half, col + half - 1] = cell;
            }
            //
            if (tile == 3)
            {
                A[row + half - 1, col + half] = cell;
                A[row + half, col + half] = cell;
                A[row + half - 1, col + half - 1] = cell;
            }
            if (tile == 4)
            {
                A[row + half - 1, col + half] = cell;
                A[row + half - 1, col + half - 1] = cell;
                A[row + half, col + half - 1] = cell;
            }
            cell++;
            if (cell == 'x')
                cell++;
            if (cell >= 'z')
                cell = 'A';
        }//end mark
        private void printM(char[,] A, int max)
        {
            for (int i = 0; i < max; i++)
                for (int j = 0; j < max; j++)
                {
                    Console.Write(A[i, j] + " ");
                    if ((j + 1) == max)
                        Console.WriteLine();
                }
        }//end printM
    }//end class Tromino
}
