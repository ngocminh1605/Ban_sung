#pragma once
// xây dựng các hàm và biến để quản lý đối tương nhận vật

#ifndef NHANVAT_OBJECT_H_
#define NHANVAT_OBJECT_H_

#include <vector> // thư viện quản lý danh sách, lưu trữ các list

#include "stdafx.h"
#include "BaseFunction.h" // chứa thông tin chung cho game và chứa các thư viện SDL
#include "BaseObject.h" // quản lý các hình ảnh và đc gọi vào để kế thừa 
#include "VienDan.h"

#define tocdoroi 3
#define doroimax 10
#define tocdodichuyenNV 12


// kế thừa từ BaseObject
class DoiTuongNhanVat : public BaseObject
{
public:
	DoiTuongNhanVat(); // hàm constructor
	~DoiTuongNhanVat();  // hàm destructor
	// 2 hàm này là gì thì đọc lại kiến thức OOP C++

	// khai báo kiểu di chuyển cho các trạng thái
	enum KieuDiChuyen
	{
		DICHUYENPHAI = 1,
		DICHUYENTRAI = 0,
	};

 	bool TaiNhanVat(std::string duongdan_nv, SDL_Renderer* manhinh); // tải lên hình ảnh nhân vật từ đường dẫn
	void HienThiNV(SDL_Renderer* Nv); // hiển thị nhân vật
	void InputHanhDong(SDL_Event sukien, SDL_Renderer* manhinh); // quản lý sự kiện di chuyển từ bàn phím khi ấn các phím di chuyển
	void Set_Animation_HanhDong();// tạo hoạt ảnh cho các frame

	void DiChuyenNhanVat(BanDo& dulieu_bando); // thực hiện di chuyển nhân vật trên bản đồ và có thể va chạm với các vật thể
	void KiemtraNVvachamBanDo(BanDo& dulieu_bando); // kiểm tra va chạm giữa nhân vật và bản đồ để nhân vật có thể đứng và di chuyển trên bản đồ

	// set vị trí x và y của bản đồ để di chuyển bản đồ
	void SetBanDoXY(const int chiso_x, const int chiso_y) { bando_cs_x = chiso_x; bando_cs_y = chiso_y; }; 

	// tính toán thông số bản đồ khi di chuyển nhân vật
	void VtriTrungTamBanDo(BanDo& dulieu_bando);


	void Thietlap_list_Viendan(std::vector<VienDan*> list_vdan) { list_VienDan = list_vdan; }
	std::vector<VienDan*> Lay_list_Viendan() const { return list_VienDan; }

	void DanBay(SDL_Renderer* desdanBay);
	void XoaVienDan(const int& viendan);
	// lấy thông số frame của nhân vật
	SDL_Rect GetRectFrame();


	void set_thoigian_hoisinh(const int& thoigian_hoisinh) { thoigian_roi = thoigian_hoisinh; }

	

	//int get_die_count() const { return die; };
	int get_sinhmenh() const { return sinhmenh; }

	void tru_sinhmenh() { sinhmenh--;  }

private:

	std::vector<VienDan*> list_VienDan; // p_bullet_object, một danh sách các viên đạn


	float giatri_x; // tăng giảm theo chiều ngang một giá trị nhất định khi ấn phím trái phải
	float giatri_y; // tăng giảm theo chiều dọc một giá trị nhất định khi ấn phím lên xuống

	// vị trí hiện tại của nhân vật
	float vitrihientai_x; 
	float vitrihientai_y;

	// hình ảnh nhân vật anh up cho e là có chiều cao của 1 khung hình và chiều dài là 8 khung hình. 1 frame = 1 khung hình
	// càng nhiều frame thì chuyển động của nhân vật tức animation càng mượt càng thú vị hơn nhưng khá lâu nên ta dùng 8 frame là nhanh nhất
	// ngoài 8 frame có thể là 4, 8, 16, 32, 64 frame tùy vào mục đích

	// khai báo biến chiều cao và chiều rộng của 1 frame
	int dorongFrame_;
	int docaoFrame_;

	SDL_Rect frame_list[8]; // nhiệm vụ lưu trữ các frame theo mảng 1 chiều từ 0 đến 7 ứng vs 8 frame trong ảnh anh đã upload
	DauVaoDiChuyen kieu_dauvao; // lưu các trạng thái đầu vào

	int frame_; // lưu chỉ số của frame để biết được là đang ở frame thứ mấy trong chuỗi frame từ 0 đến 7
	int trangthai_dichuyen_; // xem trạng thái di chuyển khi ấn button trên phím ví dụ đi sang trái hay đi sang phải

	bool dungtrenbando;

	int bando_cs_x;
	int bando_cs_y;

	int thoigian_roi; // come_back_time

	int sinhmenh;
	//int die;

	Mix_Chunk* hitSound = Mix_LoadWAV("audio/hitSound.wav");
	
};


#endif // !NHANVAT_OBJECT_H_
