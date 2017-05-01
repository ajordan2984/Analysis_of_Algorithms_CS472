using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Collections;
using Microsoft.VisualBasic;
namespace prj3source
{
    public partial class Form1 : Form
    {
        // Global declarations
        public Graphics drawpoint;
        public Pen MyPen = new Pen(Color.Red);
        Random random = new Random();

        public Form1()
        {
            InitializeComponent();
            Init();
            // Assign where to draw lines
            drawpoint = drawAREA.CreateGraphics();
        }
        private void Init()
        {
            List<Item> items = new List<Item>();
            items.Add(new Item() { Text = "Tromino", Value = "mode0" });
            items.Add(new Item() { Text = "ConvexHull", Value = "mode1" });
            comboBox1.DataSource = items;
            comboBox1.DisplayMember = "Text";
            comboBox1.ValueMember = "Value";  
        }
        public class Item
        {
            public Item() { }
            public string Value { set; get; }
            public string Text { set; get; }
        }
        private void button1_Click(object sender, EventArgs e)
        {
            int index = comboBox1.SelectedIndex;
            if (index == 0)
                generate_tromino();
            if (index == 1)
                generate_convexhull();
        }
        
        private void generate_convexhull()
        {
            bool isnum;
            int n_of_points;
            string input = Interaction.InputBox("Enter a number from 10 - 4000");
            isnum = int.TryParse(input, out n_of_points);

            while (n_of_points < 10 || n_of_points > 4000 || !isnum)
            {
                input = Interaction.InputBox("Enter a number from 10 - 4000");
                isnum = int.TryParse(input, out n_of_points);
            }

            ConvexHull hull = new ConvexHull(drawAREA,n_of_points);
            hull.findHULL();
        }
        private void generate_tromino()
        {
            bool isnum;
            int gridsize;
            string forward = Interaction.InputBox("Enter a number from 2 - 256");
            isnum = int.TryParse(forward, out gridsize);

            while (gridsize <2 || gridsize>256 || !isnum)
            {
               forward = Interaction.InputBox("Enter a number from 2 - 256");
               isnum = int.TryParse(forward, out gridsize);
            }
            Tromino puzzle = new Tromino(gridsize,drawAREA);
            puzzle.start();
            puzzle.run();
        }

        private void button2_Click(object sender, EventArgs e)
       {
           drawAREA.Image = null;
           drawAREA.BackColor = Color.White;
           drawAREA.Width = 900;
           drawAREA.Height = 900;
       }
    }//end form1
}// end 
