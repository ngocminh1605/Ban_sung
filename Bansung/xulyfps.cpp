

#include "stdafx.h"
#include "xulyfps.h"
#include "BaseFunction.h"

Xuly_Fps_Timer::Xuly_Fps_Timer()
{
	// khởi tạo dữ liệu

	thoigian_batdau = 0;
	thoigian_dung = 0;
	dungnv = false;
	batdaunv = false;
}

Xuly_Fps_Timer::~Xuly_Fps_Timer()
{
	
}


void Xuly_Fps_Timer::batdau()
{
	// bắt đầu chương trình gán biến batdauctr = true

	batdaunv = true;
	dungnv = false;

	// liên tục lấy thời gian trôi qua bằng SDL_Get_ticks

	thoigian_batdau = SDL_GetTicks();
}

void Xuly_Fps_Timer::ketthuc()
{
	// kết thúc chương trình 

	dungnv = false;
	batdaunv = false;
}

void Xuly_Fps_Timer::tamdung()
{
	// kiểm tra dừng hoạt ảnh nhân vật 

	if (batdaunv == true && dungnv == false)
	{
		dungnv = true;
		thoigian_dung = SDL_GetTicks() - thoigian_batdau;
	}
}


void Xuly_Fps_Timer::resume()
{
	// kiểm tra xem có đang dừng đếm thời gian không, nếu có thì ms resume

	if (dungnv == true)
	{
		dungnv = false;
		thoigian_batdau = SDL_GetTicks() - thoigian_dung;
		thoigian_dung = 0;
	}
}

int Xuly_Fps_Timer::get_thoigian()
{
	// đếm thời gian khi đang chạy 

	if (batdaunv == true)
	{
		if(dungnv == true) // trả về giá trị hiện tại tức là lúc dừng
		{
			return thoigian_dung;
		}
		else
		{
			return SDL_GetTicks() - thoigian_batdau; // thời gian chạy qua từ khi bắt đầu
		}
	}

	return 0;
}

bool Xuly_Fps_Timer::batdau_()
{
	return batdaunv;
}

bool Xuly_Fps_Timer::dung_()
{
	return dungnv;
}