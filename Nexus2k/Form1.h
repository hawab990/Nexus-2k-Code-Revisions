#pragma once
#include "Main.h"

namespace Nexus2k {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Form1
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Main^ main;

		Form1(void)
		{
			InitializeComponent();
			main = gcnew Main(panel1->CreateGraphics());
			List<int>^ highScoreList= main->getHighScore();
			//Looping through the list of high scores and adding them to the collections of the listbox.
			//list box will display it.
			for each ( int item in highScoreList)
			{
			listBox1->Items->Add(item);

			}
			MessageBox::Show("Welcome To Nexus 2k","Message", MessageBoxButtons::OK);
			timerGame->Enabled = true;
			timerDraw->Enabled = true;

			
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Timer^  timerGame;
	protected: 

	private: System::Windows::Forms::Panel^  panel1;

	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Timer^  timerDraw;
	private: System::Windows::Forms::Label^  label1;

	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::ListBox^  listBox1;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  button3;


	protected: 
	private: System::ComponentModel::IContainer^  components;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
			this->timerGame = (gcnew System::Windows::Forms::Timer(this->components));
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->timerDraw = (gcnew System::Windows::Forms::Timer(this->components));
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->listBox1 = (gcnew System::Windows::Forms::ListBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// timerGame
			// 
			this->timerGame->Tick += gcnew System::EventHandler(this, &Form1::timer1_Tick);
			// 
			// panel1
			// 
			this->panel1->Location = System::Drawing::Point(12, 12);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(359, 359);
			this->panel1->TabIndex = 0;
			this->panel1->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::panel1_MouseDown);
			// 
			// button2
			// 
			this->button2->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"button2.Image")));
			this->button2->Location = System::Drawing::Point(551, 64);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(95, 94);
			this->button2->TabIndex = 2;
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
			// 
			// timerDraw
			// 
			this->timerDraw->Interval = 80;
			this->timerDraw->Tick += gcnew System::EventHandler(this, &Form1::timerDraw_Tick);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(372, 96);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(145, 25);
			this->label1->TabIndex = 3;
			this->label1->Text = L"Current Score";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label3->Location = System::Drawing::Point(377, 164);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(135, 25);
			this->label3->TabIndex = 5;
			this->label3->Text = L"High Scores:";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label4->Location = System::Drawing::Point(372, 64);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(74, 25);
			this->label4->TabIndex = 6;
			this->label4->Text = L"Score:";
			// 
			// listBox1
			// 
			this->listBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)), 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->listBox1->FormattingEnabled = true;
			this->listBox1->ItemHeight = 20;
			this->listBox1->Location = System::Drawing::Point(523, 164);
			this->listBox1->Name = L"listBox1";
			this->listBox1->Size = System::Drawing::Size(123, 184);
			this->listBox1->TabIndex = 7;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(377, 15);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(123, 42);
			this->button1->TabIndex = 8;
			this->button1->Text = L"Start";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(506, 15);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(136, 43);
			this->button3->TabIndex = 9;
			this->button3->Text = L"Wipe High Scores";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &Form1::button3_Click);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"$this.BackgroundImage")));
			this->ClientSize = System::Drawing::Size(658, 407);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->listBox1);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->panel1);
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		//Event Handlers.

		//Timer tick initiation of the game.
	private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) 
			 {
				main->playTurn();
			 }
			 //mouse click events.
	private: System::Void panel1_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) 
			 {
				 main->click(e->Location);
			 }
			 //Redraw time tick.
	private: System::Void timerDraw_Tick(System::Object^  sender, System::EventArgs^  e) {
				 main->draw();
				 label1->Text = main->score.ToString();
			 }
			 //Undo.
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 main->undo();

		 }



private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
			main = gcnew Main(panel1->CreateGraphics());
			listBox1->Items->Clear();
			List<int>^ highScoreList= main->getHighScore();
			//Looping through the list of high scores and adding them to the collections of the listbox.
			//list box will display it.
			for each ( int item in highScoreList)
			{
			listBox1->Items->Add(item);

			}
			timerGame->Enabled = true;
			timerDraw->Enabled = true;

			

		 }
	//Wipes the elements of the high scores in the list box for a fresh start.
private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
			 main-> wipeScore();
			 listBox1->Items->Clear();
		 }
};
}

