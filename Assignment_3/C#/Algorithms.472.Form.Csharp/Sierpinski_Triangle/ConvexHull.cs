using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;
using System.Windows.Forms;

namespace prj3source
{
    class ConvexHull
    {
        Random rnd;
        private int drawingMAX;
        private int tpoints;
        private List<int[]> points;
        private List<int[]> hullpoints;
        private int Tile;
        // Graphics Tools
        public Graphics drawpoint;
        public Pen MyPen;
        System.Drawing.SolidBrush myBrush;
        PictureBox Grid;

        public ConvexHull(PictureBox drawAREA, int input)
        {
            // Initialize Graphics Tools
            Grid = drawAREA;
            drawpoint = drawAREA.CreateGraphics();
            myBrush = new System.Drawing.SolidBrush(System.Drawing.Color.Red);
            MyPen = new Pen(Color.Black);
            // Set up Grid for finding the convex hull
            Tile = 4;
            drawingMAX = drawAREA.Size.Height;
            rnd = new Random();
            tpoints = input;
            points = new List<int[]>();
            hullpoints = new List<int[]>();
            //Call functions to find the hull.
            generate_points();
            read_in_points();
        }
   
        // Generates number of points inputed by user
        private void generate_points()
        {
            System.IO.StreamWriter pointsout;
            pointsout = new System.IO.StreamWriter("points.txt");
            for (int i = 0; i < tpoints; i++)
                pointsout.WriteLine(rnd.Next(3, drawingMAX-3) + " " + rnd.Next(3, drawingMAX-3));
            pointsout.Close();
        }
        
        // http://stackoverflow.com/questions/21347879/how-i-can-convert-text-file-into-list-of-int-array
        // Reads points from file,splits each line,converts to int,stores into array and put into list
        private void read_in_points()
        {
            points =
                    System.IO.File
                    .ReadAllLines("points.txt")
                    .Select(x => x.Split(' ')
                    .Select(y => int.Parse(y))
                    .ToArray())
                    .ToList();
        }
        
        /* Determines if screen animation will run.
         * > 500 points, the time is to long for screen animation.
         * < 500 points, animation is displayed.
         */ 
        public void findHULL()
        {
            if (tpoints < 500)
                animate_hull();
            else
                non_animate_hull();
        }
        // Finds the convex hull and displays the Hull once calculations have finished
        private void non_animate_hull()
        {
	        // Data in order of [x][y]
            int[] A; int[] B;int[] C;
            int ax = 0; int ay = 0; 
            int bx = 0; int by = 0; 
            int cx = 0; int cy = 0; 
            int answer = 0; 
	        bool pointsleft = false;
	        bool pointsright = false;
        // Draw initial points
           draw_points();
	    for (int i = 0; i < tpoints; i++)
	    {
		    A = points[i];
            ax = A[0];
            ay = A[1];
            for (int k = 0; k < tpoints; k++)
		    {
			    B = points[k];
                bx = B[0];
                by = B[1];  
                for (int j = 0; j < tpoints; j++)
				    {
					    C = points[j];
					    cx = C[0];
					    cy = C[1];
					    answer = ((ax - cx)*(by - cy)) - ((ay - cy)*(bx - cx));
					    // point to the right
					    if (answer > 0)
						    pointsright = true;
					    // points to the left
                        if (answer < 0)
						    pointsleft = true;
				}//end J for
                    
                // There exist only points on the left of the line
				// but not on the right of the line
				if (pointsleft && !pointsright)
                    draw_line(ax, ay, bx, by);
				// There exist only points on the right of the line
				// but not on the left of the line
				if (!pointsleft && pointsright)
                    draw_line(ax, ay, bx, by);
				// Reset values for detemining if hull point
				pointsright = false;
				pointsleft = false;
		    }//end K for
        }// end I for
      }//end non_animate_hull()
        
        // Displays bruteforce animation of search for convex hull
        private void animate_hull()
        {
            // Data in order of [x][y]
            int[] A; int[] B; int[] C;
            int ax = 0; int ay = 0;
            int bx = 0; int by = 0;
            int cx = 0; int cy = 0;
            int answer = 0;
            bool pointsleft = false;
            bool pointsright = false;

            // Draw initial points
            draw_points();

            for (int i = 0; i < tpoints; i++)
            {
                A = points[i];
                ax = A[0];
                ay = A[1];
                for (int k = 0; k < tpoints; k++)
                {
                    B = points[k];
                    bx = B[0];
                    by = B[1];
                    for (int j = 0; j < tpoints; j++)
                    {
                        C = points[j];
                        cx = C[0];
                        cy = C[1];
                        answer = ((ax - cx) * (by - cy)) - ((ay - cy) * (bx - cx));
                        // point to the right
                        if (answer > 0)
                            pointsright = true;
                        // points to the left
                        if (answer < 0)
                            pointsleft = true;
                    }//end J for

                    // Draw line from A -> B
                    draw_line(ax, ay, bx, by);

                    // There exist only points on the left of the line
                    // but not on the right of the line
                    if (pointsleft && !pointsright)
                    {
                        hullpoints.Add(A);
                        hullpoints.Add(B);
                        draw_hull();
                    }
                    // There exist only points on the right of the line
                    // but not on the left of the line
                    if (!pointsleft && pointsright)
                    {
                        hullpoints.Add(A);
                        hullpoints.Add(B);
                        draw_hull();
                    }
                    // Reset values for detemining if hull point
                    pointsright = false;
                    pointsleft = false;
                }//end K for

                // Clear off old lines drawn for points searching for hull points
                clear_lines();
                draw_hull();
            }// end I for
        }//end animate_hull()   
        
        // Clears off lines drawn while anamation search for hull
        private void clear_lines()
        {
            Grid.Image = null;
            Grid.BackColor = Color.White;
            Grid.Refresh();
        }
        // Draws line animating search for hull
        private void draw_line(int x1,int y1, int x2, int y2)
        {
             drawpoint.DrawLine(MyPen, x1, y1, x2, y2);
        }// draw_line()
        // Draws points generated by gernerate_points()
        private void draw_points()
        {
            int[] A;
            for (int i=0;i<tpoints;i++)
            {
                A = points[i];
                drawpoint.FillRectangle(myBrush, new Rectangle(A[0],A[1], Tile, Tile));
            }
        }// end draw_points()
        // Draws the convex hull as it is found in segments
        private void draw_hull()
        {
            MyPen.Color = Color.Black;
            int[] A;
            int[] B;
            int max = hullpoints.Count;
            draw_points();
            for (int i = 0; i < max; i+=2)
            {
                A = hullpoints[i];
                B = hullpoints[i+1];
                drawpoint.DrawLine(MyPen, A[0],A[1],B[0],B[1]);
                drawpoint.FillRectangle(myBrush, new Rectangle(A[0], A[1], Tile + 2, Tile + 2));
            }
          // Change color of pen used to draw lines
            MyPen.Color = Color.FromArgb(rnd.Next(1, 256), rnd.Next(1, 256), rnd.Next(1, 256));
        }// end draw_hull()
    }// end Class ConvexHull
}
   