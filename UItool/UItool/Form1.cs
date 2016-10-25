using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using System.Drawing.Drawing2D;

namespace UItool
{
    public partial class Form1 : Form
    {
        public int x, y, w, h, sx, sy, sw, sh;
        public FileStream sr;
        public string filename;
        public int MAX_X, MAX_Y;

        public Form1()
        {
            InitializeComponent();
        }
    //----------------------------------------------------------------------------------------
    //          値入力部分
    //----------------------------------------------------------------------------------------

        private void textBox1_TextChanged(object sender, EventArgs e)
        {
            int.TryParse(textBox1.Text, out x);
            trackBar1.Value = x;
        }

        private void textBox2_TextChanged(object sender, EventArgs e)
        {
            int.TryParse(textBox2.Text, out y);
            trackBar2.Value = y;
        }

        private void textBox3_TextChanged(object sender, EventArgs e)
        {
            int.TryParse(textBox3.Text, out w);
            trackBar3.Value = w;
        }

        private void textBox4_TextChanged(object sender, EventArgs e)
        {
            int.TryParse(textBox4.Text, out h);
            trackBar4.Value = h;
        }
        
        private void textBox5_TextChanged(object sender, EventArgs e)
        {
            int.TryParse(textBox5.Text, out sx);
            trackBar5.Value = sx;
        }

        private void textBox6_TextChanged(object sender, EventArgs e)
        {
            int.TryParse(textBox6.Text, out sy);
            trackBar6.Value = sy;
        }

        private void textBox7_TextChanged(object sender, EventArgs e)
        {
            int.TryParse(textBox7.Text, out sw);
            trackBar7.Value = sw;
        }

        private void textBox8_TextChanged(object sender, EventArgs e)
        {
            int.TryParse(textBox8.Text, out sh);
            trackBar8.Value = sh;
        }


        //----------------------------------------------
        //      数値のみ入力にさせる。
        //----------------------------------------------
        private void textBox1_KeyPress(object sender, KeyPressEventArgs e)
        {
            //0～9と、バックスペース以外の時は、イベントをキャンセルする
            if ((e.KeyChar < '0' || '9' < e.KeyChar) && e.KeyChar != '\b')
            {
                e.Handled = true;
            }
        }

        private void textBox2_KeyPress(object sender, KeyPressEventArgs e)
        {
            //0～9と、バックスペース以外の時は、イベントをキャンセルする
            if ((e.KeyChar < '0' || '9' < e.KeyChar) && e.KeyChar != '\b')
            {
                e.Handled = true;
            }
        }

        private void textBox3_KeyPress(object sender, KeyPressEventArgs e)
        {
            //0～9と、バックスペース以外の時は、イベントをキャンセルする
            if ((e.KeyChar < '0' || '9' < e.KeyChar) && e.KeyChar != '\b')
            {
                e.Handled = true;
            }
        }

        private void textBox4_KeyPress(object sender, KeyPressEventArgs e)
        {
            //0～9と、バックスペース以外の時は、イベントをキャンセルする
            if ((e.KeyChar < '0' || '9' < e.KeyChar) && e.KeyChar != '\b')
            {
                e.Handled = true;
            }
        }

        private void textBox5_KeyPress(object sender, KeyPressEventArgs e)
        {
            //0～9と、バックスペース以外の時は、イベントをキャンセルする
            if ((e.KeyChar < '0' || '9' < e.KeyChar) && e.KeyChar != '\b')
            {
                e.Handled = true;
            }
        }

        private void textBox6_KeyPress(object sender, KeyPressEventArgs e)
        {
            //0～9と、バックスペース以外の時は、イベントをキャンセルする
            if ((e.KeyChar < '0' || '9' < e.KeyChar) && e.KeyChar != '\b')
            {
                e.Handled = true;
            }
        }

        private void textBox7_KeyPress(object sender, KeyPressEventArgs e)
        {
            //0～9と、バックスペース以外の時は、イベントをキャンセルする
            if ((e.KeyChar < '0' || '9' < e.KeyChar) && e.KeyChar != '\b')
            {
                e.Handled = true;
            }
        }

        private void textBox8_KeyPress(object sender, KeyPressEventArgs e)
        {
            //0～9と、バックスペース以外の時は、イベントをキャンセルする
            if ((e.KeyChar < '0' || '9' < e.KeyChar) && e.KeyChar != '\b')
            {
                e.Handled = true;
            }
        }
    //----------------------------------------------------------------------------------------
    //          出力部分
    //----------------------------------------------------------------------------------------



        private void Form1_Load(object sender, EventArgs e)
        {

            //  ボタンのテキスト変更
            button1.Text = "出力";
            button2.Text = "ファイル読み込み";

            //  picturebox1の最大幅を獲得
            MAX_X = pictureBox1.Size.Width;
            MAX_Y = pictureBox1.Size.Height;

            //  Trackbar
            trackInitializeX(trackBar1);        //  x
            trackInitializeY(trackBar2);        //  y
            trackInitializeX(trackBar3);        //  w
            trackInitializeY(trackBar4);        //  h
            trackInitializeX(trackBar5);        //  sx
            trackInitializeY(trackBar6);        //  sy
            trackInitializeX(trackBar7);        //  sw
            trackInitializeY(trackBar8);        //  sh

            timer1.Interval = 100;
            timer1.Start();


           // img = Image.FromFile("..\\chano2.png");
            
        }

        private void button1_Click(object sender, EventArgs e)
        {
            string temp_x = x.ToString();
            string temp_y = y.ToString();
            string temp_w = w.ToString();
            string temp_h = h.ToString();
            string temp_sx = sx.ToString();
            string temp_sy = sy.ToString();
            string temp_sw = sw.ToString();
            string temp_sh = sh.ToString();
            label1.Text = "x={" + temp_x + "},y={" + temp_y + "},w={ " + temp_w + "},h={ " + temp_h + "},sx={" + temp_sx + "},sy={" + temp_sy + "},sw={ " + temp_sw + "},sh={ " + temp_sh + "}";

            RenderData();

          //  //  描画先とするImageオブジェクトを作成する
          //  Bitmap canvas = new Bitmap(pictureBox1.Width, pictureBox1.Height);
          //  //  ImageオブジェクトのGraphicsオブジェクトを作成する
          //  Graphics g = Graphics.FromImage(canvas);
            
          //  //  画像ファイルを読み込んで、Imageオブジェクトとして取得する
          ////  Bitmap img = new Bitmap("..\\chano2.png");
          //  Bitmap img = new Bitmap(filename);

          //  //  切り取る部分の範囲を決定する。位置x,y、大きさ 値ｘ値
          //  Rectangle srcRect = new Rectangle( sx, sy, sw, sh );
          //  //  描画する部分の範囲を決定する。位置x,y、大きさ 値ｘ値
          //  Rectangle desRect = new Rectangle( x, y, w, h );


          //  //  画像のサイズを与えられた値にしてcanvasに描画する
          //  g.DrawImage(img, desRect, srcRect, GraphicsUnit.Pixel);

          //  //  Graphicsオブジェクトのリソースを解放する
          //  g.Dispose();
          //  //  pictureBox1に表示する
          //  pictureBox1.Image = canvas;


            //--------------------------------------------------------------------------------------------
            //sr = new FileStream("..\\chano2.png", FileMode.Open, FileAccess.Read);
            //Bitmap bmp = (Bitmap)Bitmap.FromStream(sr);     //  Bitmapクラスオブジェクトへ読み込み
            //sr.Close();                                     //  ストリームを閉じる
            //pictureBox1.Image = new Bitmap(bmp);            //  ピクチャーボックスの画像イメージをBitmapオブジェクトから創成
            //bmp.Dispose();                                  //  Bitmapオブジェクトの廃棄
            //--------------------------------------------------------------------------------------------

        }

        //  描画処理
        private void RenderData()
        {
            //  描画先とするImageオブジェクトを作成する
            Bitmap canvas = new Bitmap(pictureBox1.Width, pictureBox1.Height);
            //  ImageオブジェクトのGraphicsオブジェクトを作成する
            Graphics g = Graphics.FromImage(canvas);

            //  画像ファイルを読み込んで、Imageオブジェクトとして取得する
            //  Bitmap img = new Bitmap("..\\chano2.png");
            Bitmap img = new Bitmap(filename);

            //  切り取る部分の範囲を決定する。位置x,y、大きさ 値ｘ値
            Rectangle srcRect = new Rectangle( sx, sy, sw, sh );
            //  描画する部分の範囲を決定する。位置x,y、大きさ 値ｘ値
            Rectangle desRect = new Rectangle( x, y, w, h );


            //  画像のサイズを与えられた値にしてcanvasに描画する
            g.DrawImage(img, desRect, srcRect, GraphicsUnit.Pixel);

            //  Graphicsオブジェクトのリソースを解放する
            g.Dispose();
            //  pictureBox1に表示する
            pictureBox1.Image = canvas;

        }

        private void panel1_Paint(object sender, PaintEventArgs e)
        {
            
        }

        private void pictureBox1_Click(object sender, EventArgs e)
        {

        }

        private void button2_Click(object sender, EventArgs e)
        {
            //  OpenFileDialogクラスのインスタンスを作成
            OpenFileDialog ofd = new OpenFileDialog();

            //  はじめのファイル名を指定する
            //  はじめに「ファイル名」で表示される文字列を指定する
            ofd.FileName = "";

            //  はじめに表示されるフォルダを指定する
            //  指定しない(空の文字列)の時は、現在のディレクトリが表示される
            ofd.InitialDirectory = @"";

            //  [ファイルの種類]に表示される選択肢を指定する
            //  指定しないとすべてのファイルが表示される
            ofd.Filter = "画像ファイル(*.png,*jpg,)|*.png;,*.jpg|すべてのファイル(*.*)|*.*";

            //  ダイアログを開く。OKだったら続行。
            if(ofd.ShowDialog() == DialogResult.OK)
            {
                //  ファイルのアドレス情報を取得
                filename = ofd.FileName;

                var img = System.Drawing.Image.FromFile(filename);
                int widthBase = img.Width;
                int heightBase = img.Height;
                w = widthBase;
                h = heightBase;
                sw = widthBase;
                sh = heightBase;
                RenderData();


            }

        }

    //----------------------------------------------------------------------------------------
    //          トラック処理全般
    //----------------------------------------------------------------------------------------
        //  初期化

        //  横幅
        private void trackInitializeX(TrackBar tb)
        {
            //  Track
            tb.Maximum = MAX_X;
            tb.Minimum = 0;
        }

        //  縦幅
        private void trackInitializeY(TrackBar tb)
        {
            //  Track
            tb.Maximum = MAX_Y;
            tb.Minimum = 0;
        }


        //  トラックの値処理
        private void trackUpdate()
        {

        }
        
        private void trackBar1_Scroll(object sender, EventArgs e)
        {
            textBox1.Text = trackBar1.Value.ToString();
        }

        private void trackBar2_Scroll(object sender, EventArgs e)
        {
            textBox2.Text = trackBar2.Value.ToString();
        }

        private void trackBar3_Scroll(object sender, EventArgs e)
        {
            textBox3.Text = trackBar3.Value.ToString();
        }

        private void trackBar4_Scroll(object sender, EventArgs e)
        {
            textBox4.Text = trackBar4.Value.ToString();
        }

        private void trackBar5_Scroll(object sender, EventArgs e)
        {
            textBox5.Text = trackBar5.Value.ToString();
        }

        private void trackBar6_Scroll(object sender, EventArgs e)
        {
            textBox6.Text = trackBar6.Value.ToString();
        }

        private void trackBar7_Scroll(object sender, EventArgs e)
        {
            textBox7.Text = trackBar7.Value.ToString();
        }

        private void trackBar8_Scroll(object sender, EventArgs e)
        {
            textBox8.Text = trackBar8.Value.ToString();
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            textBox1.Text = x.ToString();
            textBox2.Text = y.ToString();
            textBox3.Text = w.ToString();
            textBox4.Text = h.ToString();
            textBox5.Text = sx.ToString();
            textBox6.Text = sy.ToString();
            textBox7.Text = sw.ToString();
            textBox8.Text = sh.ToString();

        }




    }
}
