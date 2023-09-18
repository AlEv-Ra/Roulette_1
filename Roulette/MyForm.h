#pragma once

namespace Roulette {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	using namespace System::Reflection;
	using namespace System::Resources;
	using namespace System::Media;


	/// <summary>
	/// Сводка для MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void);

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ bExit;
	private: System::Windows::Forms::Button^ bMin;
	private: System::Windows::Forms::PictureBox^ pbStart;



	private: System::Windows::Forms::Timer^ tGime;

	private: System::ComponentModel::IContainer^ components;

	protected:

	protected:

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>

		
	

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->bExit = (gcnew System::Windows::Forms::Button());
			this->bMin = (gcnew System::Windows::Forms::Button());
			this->pbStart = (gcnew System::Windows::Forms::PictureBox());
			this->tGime = (gcnew System::Windows::Forms::Timer(this->components));
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbStart))->BeginInit();
			this->SuspendLayout();
			// 
			// bExit
			// 
			this->bExit->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"bExit.BackgroundImage")));
			this->bExit->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->bExit->Cursor = System::Windows::Forms::Cursors::Hand;
			this->bExit->Location = System::Drawing::Point(558, 0);
			this->bExit->Name = L"bExit";
			this->bExit->Size = System::Drawing::Size(42, 42);
			this->bExit->TabIndex = 0;
			this->bExit->UseVisualStyleBackColor = true;
			this->bExit->Click += gcnew System::EventHandler(this, &MyForm::bExit_Click);
			// 
			// bMin
			// 
			this->bMin->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"bMin.BackgroundImage")));
			this->bMin->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->bMin->Cursor = System::Windows::Forms::Cursors::Hand;
			this->bMin->Location = System::Drawing::Point(510, 0);
			this->bMin->Name = L"bMin";
			this->bMin->Size = System::Drawing::Size(42, 42);
			this->bMin->TabIndex = 1;
			this->bMin->UseVisualStyleBackColor = true;
			this->bMin->Click += gcnew System::EventHandler(this, &MyForm::bMin_Click);
			// 
			// pbStart
			// 
			this->pbStart->BackColor = System::Drawing::Color::Transparent;
			this->pbStart->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->pbStart->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pbStart.Image")));
			this->pbStart->Location = System::Drawing::Point(224, 227);
			this->pbStart->Name = L"pbStart";
			this->pbStart->Size = System::Drawing::Size(152, 142);
			this->pbStart->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pbStart->TabIndex = 2;
			this->pbStart->TabStop = false;
			this->pbStart->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pbStart_MouseClick);
			// 
			// tGime
			// 
			this->tGime->Tick += gcnew System::EventHandler(this, &MyForm::tGime_Tick);
			// 
			// MyForm
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->AutoValidate = System::Windows::Forms::AutoValidate::Disable;
			this->BackColor = System::Drawing::Color::Blue;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->ClientSize = System::Drawing::Size(600, 600);
			this->ControlBox = false;
			this->Controls->Add(this->pbStart);
			this->Controls->Add(this->bMin);
			this->Controls->Add(this->bExit);
			this->DoubleBuffered = true;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"MyForm";
			this->RightToLeftLayout = true;
			this->ShowIcon = false;
			this->SizeGripStyle = System::Windows::Forms::SizeGripStyle::Hide;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Roulette";
			this->TransparencyKey = System::Drawing::Color::Blue;
			this->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::MyForm_MouseDown);
			this->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::MyForm_MouseMove);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbStart))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	
	// Данные игры
	System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
	private: Image^ imageEtalon = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));

	 Assembly^ assembly = Assembly::GetExecutingAssembly();
	 ResourceManager^ rm = gcnew ResourceManager(assembly->GetName()->Name + ".MyForm", assembly);
	 //private: Image^ imageBall = gcnew SoundPlayer(rm->GetStream("Ball"));
	 private: Image^ imageBall = (Bitmap^)rm->GetObject("Ball");

	//private: Image^ imageBall = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject("Ball")));
	//private: Graphics^ canv{};

	//private: int x0 = 235; // центр окружности
	//private: int y0 = 235; // центр окружности

	private: int x0 = 300; // центр окружности
	private: int y0 = 300; // центр окружности

	private: const int r_max_ball  {260}; // большой радиус движения шарика
	private: const int r_midl_ball {210}; // среднийрадиус движения шарика
	private: const int r_min_ball  {162}; // малый радиус движения шарика
	private: float r_cur_ball {}; // текущий радиус движения шарика

	private: float v_ball {};  // скорость шарика
	private: int angle_ball{}; // угол в градусах шарика
	private: int win_angle_ball{}; // угол в градусах шарика
	private: const float g_ball{ 0.4 };
	private: int start_time{}; // время старта в секундах с 1970 года
	private: int t_play{};       // время игры, движение шарика

	private: float v_desk{};   // скорость рулетки
	private: int angle_desk{0}; // угол в градусах рулетки. Исходное - 0 граудусов
	private: const float g_desk{0.05};      // ускорение (торможение).
	
	private: bool IsPlay{};      // Идет игра или нет

	private: void StartGame();
	private: void RotationDesk();
	private: void RotationBall();

	

	public: System::Drawing::Point mouse_offset;

	
	
	private: System::Void bExit_Click(System::Object^ sender, System::EventArgs^ e) {
		this->Close();
	}
	private: System::Void bMin_Click(System::Object^ sender, System::EventArgs^ e) {
		this->WindowState = FormWindowState::Minimized;
	}
	private: System::Void MyForm_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		if (e->Button == System::Windows::Forms::MouseButtons::Left)
		{
			Point mousePos = Control::MousePosition;
			mousePos.Offset(mouse_offset.X, mouse_offset.Y);
			Location = mousePos;
		}

	}
	private: System::Void MyForm_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		mouse_offset = System::Drawing::Point(-e->X, -e->Y);
	}

private: System::Void pbStart_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
private: System::Void tGime_Tick(System::Object^ sender, System::EventArgs^ e);


};
}
