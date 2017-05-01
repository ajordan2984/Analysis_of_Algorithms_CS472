/* Andrew Jordan
 * 472 Analysis of Algorithms
 * Athens State University
 * Dr.Lewis
 * Due: 2/27/2017
 * Problem 1 - Brute for convex hull
 * Sources used:
 * A. http://www.cs.cmu.edu/~quake/robust.html
 * B. http://stackoverflow.com/questions/21347879/how-i-can-convert-text-file-into-list-of-int-array
 * Purpose of sources:
 * A. Using the determinant as defined in linear algebra to find if point "C"
 *      exist to the left,right,or on the line between points "A" and "B".
 * B. Reading points from file,split each line with a space,convert to int,stores into array and put into list.
 * Strategy:
 * A. Prompt user for number of points
 * B. Generate random points to a file
 * C. Read points in and store in a list
 * D. Use three for loops to check all points to see if they lie on the hull
 * E. Draw hull on screen once calculations have finished
 * Problem 2 - Tromino
 * Trominos are represented by letters in a 2D matrix.
 * Strategy: 
 * A. Prompt user for matrix size and convert to power of two
 * B. Scan matrix for missing tile
 * C. Place tromino in matrix based on where tile is at
 * D. Devide matrix into smaller submatrix using indexes
 * E. Repeat A - C until matrix is size 2x2
 * F. Fill in tromino of puzzle 2x2 then leave
 * G. Base case is matrix size 2x2
 * H. Associate color with letter in the matrix and store in a map
 * I. Go through matrix with letters and draw squares on
 *      screen of color associated with that letter.
 *
 * Resubmission: Minor changes to the for loops
 * in the convex hull algorithm
 */
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;
using System.Windows.Forms;

namespace prj3source
{
    class Tromino
    {
      // Data sturctures used to hold and fill in trominos
      private char[,] A;
      private char cell;
      private int matrix_dim;

      // Tools for graphics
      public Random rnd;
      public Graphics drawpoint;
      System.Drawing.SolidBrush myBrush;
      private Color Background;
      private Dictionary<char, Color> map;
      private int drawingMAX;
      private int TileSize;

      public Tromino(int max, PictureBox drawAREA)
      {
          // Set data members
          cell = 'A';
          matrix_dim = max;
          
          // Set tools for graphics
          rnd = new Random();   // Create new random object to pick color of trominos
          drawpoint = drawAREA.CreateGraphics(); // Set area to draw trominos
          myBrush = new System.Drawing.SolidBrush(System.Drawing.Color.Red);// Create new brush to draw trominos
          Background = drawAREA.BackColor;      // Set background color
          map = new Dictionary<char, Color>(); // Create new map to map colors to letters
          drawingMAX = drawAREA.Size.Height;
       // TileSize set in start()
      }
      public void start()
        {
           // Set correct valuse for tile size and length of matrix
           int resized = pow2(matrix_dim);
           TileSize = drawingMAX / resized; // Set size of tromino tile
           matrix_dim = resized; // Set length of matrix based on power of 2
           // Start work
           A = new char[resized, resized]; // Create new matrix
           int[] corners = new int[2]{ 0, 0 }; // Create new corners
           fill(A, resized); // Fill matrix with '-' characters
           split(A, corners, resized); // Start recursive algorithm to fill with trominos
        } 
      private int pow2(int data)
      {
          int i = 1;
          while (i < data)
              i = i * 2;
          return i;
      }
      /* Fills matrix with '-' characters 
       * representing unmarked tiles and 
       * marks the missing tile with an 'x'.
       * The missing tile 'x' is associated
       * in the map with the color black.
       */
      private void fill(char[,]A,int max)
      {
          // Fill matrix 
          for (int i = 0; i < max; i++)
              for (int j = 0; j < max; j++)
                  A[i, j] = '-';
          // Set random tile
          A[rnd.Next(0,max),rnd.Next(0,max)]='x';
          map['x'] = Color.Black;
      }
      
      // Recursive function that spits the matrix into
      // smaller submatrix based on index ranges.
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
      
      // Locates the section of the missing tile  
      private int scan(char[,] A, int[] corners, int max)
      {
          int start_row = corners[0];
          int start_col = corners[1];
          int row = 0;
          int col = 0;
          int half = max / 2;
          for (int i = 0; i < max; i++)
              for (int j = 0; j < max; j++)
                  if (A[i + start_row,j + start_col] != '-')
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
      
      /* Adds letters to a 2D matrix in the heap
       * representing trominos. Letters are added\
       * based upon where the missing tile is at.
       * Calls add_color() to associate a color with
       * a letter.
      */
      private void mark(char[,] A, int[] corners, int tile, int max)
      {
          //[row][col]
          int half = max / 2;
          int row = corners[0];
          int col = corners[1];
          //A11
          if (tile == 1)
          {
              A[row + half - 1,col + half] = cell;
              A[row + half,col + half] = cell;
              A[row + half,col + half - 1] = cell;
              add_color();
          }
          //A12
          if (tile == 2)
          {
              A[row + half - 1,col + half - 1] = cell;
              A[row + half,col + half] = cell;
              A[row + half,col + half - 1] = cell;
              add_color();
          }
          //A21
          if (tile == 3)
          {
              A[row + half - 1,col + half] = cell;
              A[row + half,col + half] = cell;
              A[row + half - 1,col + half - 1] = cell;
              add_color();
          }
          //A22
          if (tile == 4)
          {
              A[row + half - 1,col + half] = cell;
              A[row + half - 1,col + half - 1] = cell;
              A[row + half,col + half - 1] = cell;
              add_color();
          }
          cell++;
          if (cell == 'x')
             cell++;
 
      }//end mark
     
      // Adds a color associated with a letter to the map
      // for drawing different color trominos
      private void add_color()
      {
          if (!map.ContainsKey(cell))
                map[cell] = Color.FromArgb(rnd.Next(1, 256), rnd.Next(1, 256), rnd.Next(1, 256));
      }//end add_color
      
      /* Draws trominos to the form. Color
       * is based upon what is in the map
       * data structure. Color is selected beford
       * hand in the add_color()->mark()->split() 
       */
      public void run()
      {
          int row = 0;
          int col = 0;
          // column|row|width|height
          for (int i = 0; i < matrix_dim; i++)
          {
              for (int j = 0; j < matrix_dim; j++)
              {
                  myBrush.Color = map[A[i,j]];
                  drawpoint.FillRectangle(myBrush, new Rectangle(col, row, TileSize, TileSize));
                  // Update column 
                  col += TileSize;
              }
              // Update row and column
              row += TileSize;
              col = 0;
          }
      } // end run()
    }//end class Tromino
}
