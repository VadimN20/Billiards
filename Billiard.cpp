//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Billiard.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormTable *FormTable;
//---------------------------------------------------------------------------
const int LEN = 7;
int power;

class Ball {
private:
	int x, y;
	int speed;
	int r;
	int dx, dy;
	int number;

public:
	Ball() {
		x = y = 0;
		r = 25;
		dx = dy = 0;
		speed = 1;
		number = 0;
	}

	Ball(int Xr, int Yr, int Speed, int num) {
		r = 25;
		x = Xr;
		y = Yr;
		dx = dy = 1;
		speed = Speed;
		number = num;
	}

	void setX(int X) {
		x = X;
	}

	int getX() {
		return x;
	}

	void setY(int Y) {
		y = Y;
	}

	int getY() {
		return y;
	}

	void setDx(int dX) {
		dx = dX;
	}

	int getDx() {
		return dx;
	}

	void setDy(int dY) {
		dy = dY;
	}

	int getDy() {
		return dy;
	}

	void setSpeed(int Speed) {
		speed = Speed;
	}

	int getSpeed() {
        return speed;
	}

	String getInfo() {
		return IntToStr(dx/speed) + " " + IntToStr(dy/speed) + " ";
	}
};

Ball arr[LEN];

__fastcall TFormTable::TFormTable(TComponent* Owner)
	: TForm(Owner)
{
	ifMouseL = false;
	int xt = 200, yt = ClientHeight / 2;

	int k = -13;
	int t = -25;
	//Первые координаты игральных шаров
	for(int i = 0; i < 6; i++) {
		if(i < 1) {
			arr[i].setX(xt+45);
			arr[i].setY(yt);
		}
		else if(i >= 1 && i < 3) {
			arr[i].setX(xt+23);
			arr[i].setY(yt+k);
			k = 13;
		}
		else if(i >= 3 && i < 6) {
			arr[i].setX(xt);
			arr[i].setY(yt+t);
			t+=26;
		}
	}
	arr[6].setX(700);
	arr[6].setY(yt);  //первые координаты ударного шара



	//for(int i = 0; i < 7; i++) {Label1->Caption += arr[i].getInfo() + "\n";}
	//pow(a.getX() - b.getX(), 2) + pow(a.getY() - b.getY(), 2) - 26 <= 26


}
//---------------------------------------------------------------------------


void calcB(Ball a, Ball b) {
	FormTable->Label1->Caption = a.getX() - b.getX() + 26;
	if(pow(a.getX() - b.getX(), 2) <= 15) { // + pow(a.getY() - b.getY(), 2) <= 45)  {
		arr[6].setDx(-arr[6].getDx());
		//arr[6].setDy(-arr[6].getDy());

		arr[0].setDx(-arr[0].getDx());
	}
}

void __fastcall TFormTable::FormMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	ifMouseL = true;
	GaugePower->Visible = true;
	TimerB->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TFormTable::FormMouseMove(TObject *Sender, TShiftState Shift,
		  int X, int Y)
{
	if(ifMouseL) {
		Refresh();
		//Рассчитываем движение вспомогательной прямой в зависимости от положения мышки и шара
		Canvas->MoveTo(arr[6].getX(), arr[6].getY());
		if(X >= arr[6].getX() && Y >= arr[6].getY()) { //Мышка в Прав Ниж
			Canvas->LineTo(arr[6].getX() - abs(arr[6].getX() - X),
						   arr[6].getY() - abs(arr[6].getY() - Y));
		}
		else if(X <= arr[6].getX() && Y >= arr[6].getY()) {//Мышка в Лев Ниж
			Canvas->LineTo(arr[6].getX() + abs(arr[6].getX() - X),
						   arr[6].getY() - abs(arr[6].getY() - Y));
		}
		else if(X <= arr[6].getX() && Y <= arr[6].getY()) {//Мышка в Лев Верх
			Canvas->LineTo(arr[6].getX() + abs(arr[6].getX() - X),
						   arr[6].getY() + abs(arr[6].getY() - Y));
		}
		else if(X >= arr[6].getX() && Y <= arr[6].getY()) {//Мышка в Прав Верх
			Canvas->LineTo(arr[6].getX() - abs(arr[6].getX() - X),
						   arr[6].getY() + abs(arr[6].getY() - Y));
		}


		//Рассчитываем силу(Длину прямой) и отображаем это в процентах
		power = sqrt(abs(X - arr[6].getX())*abs(X - arr[6].getX())
					+ abs(Y - arr[6].getY())*abs(Y - arr[6].getY()));
		GaugePower->Progress = power/3;

		//Прорисовываем остальные мячи
		for(int i = 0; i < 7; i++) {
			Canvas->Pen->Color = clBlack;
			Canvas->Ellipse(arr[i].getX() - 13, arr[i].getY() - 13, arr[i].getX() + 13, arr[i].getY() + 13);
		}
	}

}
//---------------------------------------------------------------------------
void __fastcall TFormTable::FormMouseUp(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
	ifMouseL = false;
	Refresh();
	GaugePower->Visible = false;

	//Обернуть это в функцию
	if(power > 100) power = 12;
	else if(power > 80 && power <= 100) power = 10;
	else if(power > 60 && power <= 80) power = 8;
	else if(power > 40 && power <= 60) power = 6;
	else if(power > 20 && power <= 40) power = 4;
	else power = 2;
	arr[6].setSpeed(power);
	//|
	TimerB->Interval = 10;
	TimerB->Enabled = true;
	//Переменные в помощь для расчёта скорости движения шара
	int dX = -X + arr[6].getX();
	int dY = -Y + arr[6].getY();
	//Заносим переменные в данные о шарике
	//arr[6].setDx((int)(dX/power));
	//arr[6].setDy((int)(dY/power));

	arr[6].setDx(dX);
	arr[6].setDy(dY);
}
//---------------------------------------------------------------------------
void __fastcall TFormTable::ButtonStartClick(TObject *Sender)
{
	for(int i = 0; i < 7; i++) {
		Canvas->Pen->Color = clBlack;
		Canvas->Ellipse(arr[i].getX() - 13, arr[i].getY() - 13,
						arr[i].getX() + 13, arr[i].getY() + 13);
	}
}
//---------------------------------------------------------------------------


void __fastcall TFormTable::TimerBTimer(TObject *Sender)
{
	for(int i = 0; i < 7; i++) {
		Canvas->Pen->Color = clBtnFace;
		Canvas->Ellipse(arr[i].getX() - 13, arr[i].getY() - 13,
					arr[i].getX() + 13, arr[i].getY() + 13);
	}



	//Изменение направлений шара при ударе о стенки
	if(arr[6].getX() + (int)(arr[6].getDx()/arr[6].getSpeed()) - 13 < 0 ||
		arr[6].getX() + (int)(arr[6].getDy()/arr[6].getSpeed()) + 13> ClientWidth) {
		arr[6].setDx(-arr[6].getDx());
	}
	//Изменение направления шара при ударе об пол или потолок
	if(arr[6].getY() + (int)(arr[6].getDx()/arr[6].getSpeed()) - 13 < 100 ||
		arr[6].getY() + (int)(arr[6].getDy()/arr[6].getSpeed()) + 13 > ClientHeight) {
		arr[6].setDy(-arr[6].getDy());
	}


	calcB(arr[6], arr[0]);
	/*if(arr[6].getDx()/arr[6].getSpeed() + arr[6].getX() - 13 - arr[0].getX() -13 < 100) {
		arr[6].setDx(-arr[6].getDx());
		arr[0].setDx(-arr[0].getDx());
	}*/



	//Изменение координат шара перед следующей перерисовкой
	arr[6].setX(arr[6].getX() + (int)(arr[6].getDx()/arr[6].getSpeed()));
	arr[6].setY(arr[6].getY() + (int)(arr[6].getDy()/arr[6].getSpeed()));
	//arr[6].setSpeed(arr[6].getSpeed() + 1);
	//arr[6].setSpeed(arr[6].getSpeed() + 1);


	//Нарисовать шар по новым координатам
	for(int i = 0; i < 7; i++) {
		Canvas->Pen->Color = clBlack;
		Canvas->Ellipse(arr[i].getX() - 13, arr[i].getY() - 13,
					arr[i].getX() + 13, arr[i].getY() + 13);
	}
}
//---------------------------------------------------------------------------
