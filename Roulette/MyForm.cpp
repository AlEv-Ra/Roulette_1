#include "MyForm.h"
#include <Windows.h>
#include "resource.h"
#include <stdlib.h> // нужен для вызова функций rand(), srand()
#include <time.h> // нужен для вызова функции time()
#include <math.h>
#include <string>





using namespace System;
using namespace System::Windows::Forms;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Data;
using namespace System::Drawing::Drawing2D;
using namespace System::Drawing::Imaging;

using namespace System::Reflection;
using namespace System::Resources;
using namespace System::Media;

struct winResult {
    int point; std::string color; bool odd;
};


HBITMAP g_hBitmap;
int GetRandomNumber(int min, int max);


int TimeCurent {};

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    //Application::Run(gcnew MyForm);
    Roulette::MyForm form;
    Application::Run(% form);
    return 0;
}

Roulette::MyForm::MyForm(void)
{
	InitializeComponent();

}

System::Void Roulette::MyForm::pbStart_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
{
    // Start game
    this->StartGame();

   

   
    
    return System::Void();
}

System::Void Roulette::MyForm::tGime_Tick(System::Object^ sender, System::EventArgs^ e)
{
    if (!this->IsPlay) return System::Void();

    TimeCurent = time(NULL);
    if (this->v_desk > 0)
    {
        RotationDesk();
    }
    else
    {
        this->IsPlay = false;
        this->pbStart->Visible = true;
        this->tGime->Stop();
    }

    //if (this->v_ball > 0)
    //{
    //    RotationBall();
    //}
    RotationBall();
    
    

    
    
    
    return System::Void();
}

void Roulette::MyForm::StartGame()
{
    // Изменение отображения
    this->pbStart->Visible = false;


    // Установка переменных в состояние для начала игры
    //this->canv = this->CreateGraphics();
    //this->x0 = this->Size.Width / 2; // Центр вращения
    //this->y0 = this->Size.Height / 2;

    this->r_cur_ball = this->r_max_ball;        // траектория шарика - по большому кругу

    this->t_play     = GetRandomNumber(7, 14);  // время игры в секундах

    this->v_ball     = GetRandomNumber(57, 97); // скорость шарика
    this->angle_ball = GetRandomNumber(0, 359); // угол в градусах шарика
    this->start_time = time(NULL); // время старта
    //this->g_ball{};     // ускорение шарика

    //this->v_desk = GetRandomNumber(7, 17);   // начальная скорость рулетки
    this->v_desk = GetRandomNumber(17, 27);   // начальная скорость рулетки


    this->IsPlay = true;      // Идет игра или нет

    this->tGime->Start();

    //MessageBox::Show(this->x0 + " - " + this->y0);

    Assembly^ assembly = Assembly::GetExecutingAssembly();

    ResourceManager^ rm = gcnew ResourceManager(assembly->GetName()->Name + ".MyForm", assembly);

    SoundPlayer^ player = gcnew SoundPlayer(rm->GetStream("roll"));
    player->PlayLooping();





}

void Roulette::MyForm::RotationDesk()
{
    //Image^ image = Image::FromFile("C:\\CppProjects\\Pr_1\\Roulette\\Roulette.png");

    // расчет угла вращения
    //this->angle_desk += this->v_max_desk * (TimeCurent - start_time);
    //this->angle_desk = this->angle_desk % 360;

    this->v_desk -= this->g_desk;
    if (this->v_desk <= 0) return;

    this->angle_desk += this->v_desk;
    this->angle_desk = this->angle_desk % 360;
    
        
    Graphics^ canv = this->CreateGraphics();
    canv->TranslateTransform(this->x0, this->y0);
    canv->RotateTransform(this->angle_desk); // angle - угол поворота в градусах
    canv->DrawImage(imageEtalon, -this->x0, -this->y0, this->Size.Width, this->Size.Height);
   
   
    //throw gcnew System::NotImplementedException();
}

void Roulette::MyForm::RotationBall()
{
    this->v_ball -= this->g_ball;

    if (this->v_ball == 0)
    {
        this->r_cur_ball = this->r_min_ball;
        this->win_angle_ball = (angle_ball - angle_desk) - (angle_ball - angle_desk) % 10;
        this->win_angle_ball %= 360;
        
        this->angle_ball = angle_ball + v_desk;
        
    }
    else if ((this->v_ball <= 37) & (this->v_ball > 0))
    {
        if (r_cur_ball >= r_midl_ball)
        {
            r_cur_ball -= 0.8;

        }
        else
        {
            r_cur_ball = r_min_ball + GetRandomNumber(0, 24);
        }
        this->angle_ball -= this->v_ball;
    }
    else if (this->v_ball < 0)
    {
        this->angle_ball = angle_ball + v_desk;
    }

    else
    {
        this->angle_ball -= this->v_ball;
    }
    
    this->angle_ball = this->angle_ball % 360;
    
    int x = this->x0 - 12 + r_cur_ball * cos(this->angle_ball * 0.0174533);
    int y = this->y0 - 12 + r_cur_ball * sin(this->angle_ball * 0.0174533);
    //this->pbBall->Location = System::Drawing::Point(x, y);

    Graphics^ canv = this->CreateGraphics();
    canv->DrawImage(this->imageBall, x, y, 30, 30);
       
}

// Функция генерирования случайного целочисленного числа в указанных пределах.
// Диапазон чисел: [min, max]
int GetRandomNumber(int min, int max)
{
    // Установить генератор случайных чисел
    srand(time(NULL));

    // Получить случайное число - формула
    int num = min + rand() % (max - min + 1);

    return num;
}

winResult win_result(float grad)
{
    winResult wr;

    if (grad > 355 & grad <= 5) {
        wr.point = 34;
        wr.color = "red";
        }
    if (grad > 5 & grad <= 15) {
        // 9.73 :
        wr.point = 6;
        wr.color = "black";
    }
    else if (grad > 15 & grad <= 24) {
        // 9.73 * 2 :
        wr.point = 27;
        wr.color = "red";
}
    else if (grad > 24 & grad <= 34) {
        // 9.73 * 3 :
        wr.point = 13;
        wr.color = "black";
        }
    else if (grad > 34 & grad <= 44) {
        // 9.73 * 4 :
        wr.point = 36;
        wr.color = "red";
        }
    else if (grad > 44 & grad <= 54) {
        // 9.73 * 5 :
        wr.point = 11;
        wr.color = "black";
        }
    else if (grad > 54 & grad <= 64) {
        // 9.73 * 6 :
        wr.point = 30;
        wr.color = "red";
    }
    else if (grad >= 64 & grad <= 73) {
        // 9.73 * 7 :
        wr.point = 8;
        wr.color = "black";
        }
    else if (grad > 73 & grad <= 83) {
        // 9.73 * 8 :
        wr.point = 23;
        wr.color = "red";
        }
    else if (grad > 83 & grad <= 93) {
        // 9.73 * 9 :
        wr.point = 10;
        wr.color = "black";
        }
    else if (grad > 93 & grad <= 103) {
        // 9.73 * 10 :
        wr.point = 5;
        wr.color = "red";
        }
    else if (grad > 103 & grad <= 112) {
        // 9.73 * 11 :
        wr.point = 24;
        wr.color = "black";
        }
    else if (grad > 112 & grad <= 122) {
        // 9.73 * 12 :
        wr.point = 16;
        wr.color = "red";
        }
    else if (grad > 122 & grad <= 132) {
        // 9.73 * 13 :
        wr.point = 33;
        wr.color = "black";
        }
    else if (grad > 132 & grad <= 142) {
        // 9.73 * 14 :
        wr.point = 1;
        wr.color = "red";
        }
    else if (grad > 142 & grad <= 151) {
        // 9.73 * 15 :
        wr.point = 20;
        wr.color = "black";
        }
    else if (grad > 151 & grad <= 161) {
        // 9.73 * 16 :
        wr.point = 14;
        wr.color = "red";
    }
    else if (grad > 161 & grad <= 1701) {
        // 9.73 * 17 :
        wr.point = 31;
        wr.color = "black";
        }
    else if (grad > 170 & grad <= 180) {
        // 9.73 * 18 :
        wr.point = 9;
        wr.color = "red";
        }
    else if (grad > 180 & grad <= 190) {
        // 9.73 * 19 :
        wr.point = 22;
        wr.color = "black";
        }
    else if (grad > 190 & grad <= 200) {
        // 9.73 * 20 :
        wr.point = 18;
        wr.color = "red";
        }
    else if (grad > 200 & grad <= 210) {
        // 9.73 * 21 :
        wr.point = 29;
        wr.color = "black";
        }
    else if (grad > 210 & grad <= 220) {
        // 9.73 * 22 :
        wr.point = 7;
        wr.color = "red";
        }
    else if (grad >= 220 & grad <= 229) {
        // 9.73 * 23 :
        wr.point = 28;
        wr.color = "black";
        }
    else if (grad > 229 & grad <= 238) {
        // 9.73 * 24 :
        wr.point = 12;
        wr.color = "red";
        }
    else if (grad > 238 & grad <= 248) {
        // 9.73 * 25 :
        wr.point = 35;
        wr.color = "black";
        }
    else if (grad > 248 & grad <= 257) {
        // 9.73 * 26 :
        wr.point = 3;
        wr.color = "red";
        }
    else if (grad > 257 & grad <= 267) {
        // 9.73 * 27 :
        wr.point = 26;
        wr.color = "black";
        }
    else if (grad > 267 & grad <= 277) {
        // 9.73 * 28 :
        wr.point = 0;
        wr.color = "green";
        }
    else if (grad > 277 & grad <= 287) {
        // 9.73 * 29 :
        wr.point = 32;
        wr.color = "red";
        }
    else if (grad > 287 & grad <= 296) {
        // 9.73 * 30 :
        wr.point = 15;
        wr.color = "black";
        }
    else if (grad > 296 & grad <= 306) {
        // 9.73 * 31 :
        wr.point = 19;
        wr.color = "red";
    }
    else if (grad > 306 & grad <= 316) {
        // 9.73 * 32 :
        wr.point = 4;
        wr.color = "black";
        }
    else if (grad > 316 & grad <= 326) {
        // 9.73 * 33 :
        wr.point = 21;
        wr.color = "red";
        }
    else if (grad > 326 & grad <= 335) {
        // 9.73 * 34 :
        wr.point = 2;
        wr.color = "black";
        }
    else if (grad > 335 & grad <= 345) {
        // 9.73 * 35 :
        wr.point = 25;
        wr.color = "red";
        }
    else if (grad > 345 & grad <= 355) {
        // 9.73 * 36 :
        wr.point = 17;
        wr.color = "black";
        }

    wr.odd = (wr.point % 2 == 0);
  

    return wr;

}







