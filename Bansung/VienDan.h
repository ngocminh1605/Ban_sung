#pragma once


#ifndef VIENDAN_H_
#define VIENDAN_H_

#include "BaseFunction.h"
#include "BaseObject.h"


class VienDan : public BaseObject
{
public:
	VienDan();
	~VienDan();

	enum HuongVD
	{
		PHAI = 20,
		TRAI = 21,
		TREN = 22,
		TRENBENTRAI = 23,
		TRENBENPHAI = 24,
	};

	void ThietLapGiaTriX(const int& GtriX) { giatri_x_vd = GtriX; }
	void ThietLapGiaTriY(const int& GtriY) { giatri_y_vd = GtriY; }

	int LayGiaTriX() const { return giatri_x_vd; }
	int LayGiaTriY() const  { return giatri_y_vd; }

	void Setup_Dichuyen(const bool& Dchuyen) { danbay = Dchuyen; }
	bool GetCheck_Dichuyen() const  { return danbay; }

	void HuongVienDan(const int& huongvdan) { huongduongdan = huongvdan; }


	// Hàm xử lý di chuyển viên đạn trên bản đồ
	void VienDanBay(const int& gioihan_x, const int& gioihan_y);


private:
	// biến lưu giá trị thay đổi khi đạn bay

	int giatri_x_vd; // x_val_
	int giatri_y_vd; // y_val_

	// trạng thái viên đạn có xuất hiện và bay hay không

	bool danbay; // is_move_

	int huongduongdan;
};




#endif // !VIENDAN_H_
