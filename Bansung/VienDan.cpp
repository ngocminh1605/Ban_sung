
#include "stdafx.h"
#include "VienDan.h"


VienDan::VienDan()
{
	giatri_x_vd = 0;
	giatri_y_vd = 0;
	danbay = false;
}


VienDan::~VienDan()
{
	
}

// 

void VienDan::VienDanBay(const int& gioihan_x, const int& gioihan_y)
{
	// vị trí của viên đạn khi theo chiều X từ trái sang phải nếu vượt quá giới hạn thì sẽ không
	//di chuyển tức là sẽ không cộng thêm một lượng để di chuyển nữa và mất hình ảnh
	if (huongduongdan == PHAI)
	{
		rect_.x += giatri_x_vd;
		if (rect_.x > gioihan_x)
		{
			danbay = false;
		}
	}
	else if(huongduongdan == TRAI)
	{
		rect_.x -= giatri_x_vd;
		if (rect_.x < 0)
		{
			danbay = false;
		}
	}
	
}