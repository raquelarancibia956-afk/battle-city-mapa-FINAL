#pragma once
#include "CJuegoFacade.h"  

namespace Battle {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Resumen de Juego
	/// </summary>
	public ref class Juego : public System::Windows::Forms::Form
	{
	public:
		CJuegoFacade* juego = new CJuegoFacade();
		Bitmap^ bmpPiso = gcnew Bitmap("imagenes\\pisos.png");
		Bitmap^ bmpBloques = gcnew Bitmap("imagenes\\bloques.png");
		Bitmap^ bmpTrofeo = gcnew Bitmap("imagenes\\trofeo.png");
		///////////////
		Bitmap^ bmpTanques = gcnew Bitmap("imagenes\\tanques.png");
		EDireccion direccionMantenida = EDireccion::ninguno;
		Juego(void)
		{
			InitializeComponent();
			//////////////////////////
			bmpTanques->MakeTransparent(bmpTanques->GetPixel(767, 0));
			this->KeyPreview = true;
			this->timer1->Interval = 50;
			this->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &Juego::Juego_KeyUp);
		}

	protected:
		/// <summary>
		/// Limpiar los recursos que se estén usando.
		/// </summary>
		/// 
		~Juego()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Timer^ timer1;
	protected:

	private: System::ComponentModel::IContainer^ components;
	private:
		/// <summary>
		/// Variable del diseñador necesaria.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Método necesario para admitir el Diseñador. No se puede modificar
		/// el contenido de este método con el editor de código.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Tick += gcnew System::EventHandler(this, &Juego::timer1_Tick);
			// 
			// Juego
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(387, 354);
			this->Name = L"Juego";
			this->Text = L"Juego";
			this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
			this->Load += gcnew System::EventHandler(this, &Juego::Juego_Load);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Juego::Juego_KeyDown);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
		Graphics^ g = this->CreateGraphics();
		BufferedGraphicsContext^ espacio = BufferedGraphicsManager::Current;
		BufferedGraphics^ buffer = espacio->Allocate(g, this->ClientRectangle);

		if (direccionMantenida != EDireccion::ninguno) {
			juego->moverJugador(direccionMantenida);
		}

		juego->dibujarEscena(buffer->Graphics, bmpPiso, bmpBloques, bmpTrofeo, bmpTanques);
		actualizarTitulo();

		buffer->Render(g);
		buffer->Render(g);

		delete buffer, espacio, g;
	}
	private: void actualizarTitulo() {
		CMarcadorObserver* m = juego->getMarcador();
		if (m != nullptr) {
			System::String^ est = gcnew System::String(m->getEstadoJugador().c_str());
			this->Text = System::String::Format("Battle City | Nivel: {0} | Vidas: {1} | Puntos: {2} | Estado: {3} (Tecla E)",
				m->getNivel(), m->getVidas(), m->getPuntuacion(), est);
		}
	}
	private: System::Void Juego_Load(System::Object^ sender, System::EventArgs^ e) {
		juego->iniciarNivel(1, 4);
		actualizarTitulo();
	}
	private: System::Void Juego_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		switch (e->KeyCode) {
		case Keys::Up:
		case Keys::W:
			if (direccionMantenida != EDireccion::arriba) {
				direccionMantenida = EDireccion::arriba;
				juego->moverJugador(EDireccion::arriba);
			}
			break;
		case Keys::Down:
		case Keys::S:
			if (direccionMantenida != EDireccion::abajo) {
				direccionMantenida = EDireccion::abajo;
				juego->moverJugador(EDireccion::abajo);
			}
			break;
		case Keys::Left:
		case Keys::A:
			if (direccionMantenida != EDireccion::izquierda) {
				direccionMantenida = EDireccion::izquierda;
				juego->moverJugador(EDireccion::izquierda);
			}
			break;
		case Keys::Right:
		case Keys::D:
			if (direccionMantenida != EDireccion::derecha) {
				direccionMantenida = EDireccion::derecha;
				juego->moverJugador(EDireccion::derecha);
			}
			break;
		case Keys::Space:
			juego->dispararJugador();
			break;
		case Keys::E:
			juego->rotarEstadoJugador();
			actualizarTitulo();
			break;
		case Keys::D1:
		case Keys::NumPad1:
			juego->iniciarNivel(1, 4);
			actualizarTitulo();
			break;
		case Keys::D2:
		case Keys::NumPad2:
			juego->iniciarNivel(2, 4);
			actualizarTitulo();
			break;
		case Keys::D3:
		case Keys::NumPad3:
			juego->iniciarNivel(3, 4);
			actualizarTitulo();
			break;
		case Keys::D4:
		case Keys::NumPad4:
			juego->iniciarNivel(4, 4);
			actualizarTitulo();
			break;
		case Keys::D5:
		case Keys::NumPad5:
			juego->iniciarNivel(5, 4);
			actualizarTitulo();
			break;
		default:
			break;
		}
	}
	private: System::Void Juego_KeyUp(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		switch (e->KeyCode) {
		case Keys::Up:
		case Keys::W:
			if (direccionMantenida == EDireccion::arriba) direccionMantenida = EDireccion::ninguno;
			break;
		case Keys::Down:
		case Keys::S:
			if (direccionMantenida == EDireccion::abajo) direccionMantenida = EDireccion::ninguno;
			break;
		case Keys::Left:
		case Keys::A:
			if (direccionMantenida == EDireccion::izquierda) direccionMantenida = EDireccion::ninguno;
			break;
		case Keys::Right:
		case Keys::D:
			if (direccionMantenida == EDireccion::derecha) direccionMantenida = EDireccion::ninguno;
			break;
		default:
			break;
		}
	}
	};
}