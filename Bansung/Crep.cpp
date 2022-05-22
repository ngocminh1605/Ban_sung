
#include "stdafx.h"
#include "Crep.h"
#include "VienDan.h"

Crep::Crep()
{
	w_frame_ = 0;
	h_frame_ = 0;
	giatri_x = 0.0;
	giatri_y = 0.0;
	vitrihientai_x = 0.0;
	vitrihientai_y = 0.0;
	onMAP = false;
	frame_ = 0;

}

Crep::~Crep() {}

SDL_Rect Crep::GetRectFrame()
{
	SDL_Rect rect;
	rect.x = rect_.x;
	rect.y = rect_.y;
	rect.w = rect_.w / 8;
	rect.h = rect_.h;

	return rect;
}

void Crep::XoaVienDan(const int& viendani)
{
	if (list_VDanofCrep.size() > 0 && viendani < list_VDanofCrep.size())
	{
		VienDan* VienDan = list_VDanofCrep.at(viendani);
		list_VDanofCrep.erase(list_VDanofCrep.begin() + viendani);

		if (VienDan)
		{
			delete VienDan;
			VienDan = NULL;
		}
	}
}

void Crep::ResetVienDan(VienDan* viendan)
{
	viendan->SetRect(vitrihientai_x + 20, vitrihientai_y + 10);
	viendan->ThietLapGiaTriX(15);
}

bool Crep::TaiAnhCrep(std::string duongdan, SDL_Renderer* manhinh) 
{
	bool ret_crep = BaseObject::TaiAnh(duongdan, manhinh); // kế thừa và tận dụng lại class Tải ảnh của BaseObject
	if (ret_crep == true)
	{
		// lấy ra kích thước của 1 frame
		h_frame_ = rect_.h;
		w_frame_ = rect_.w / 8;
	}

	return ret_crep;
}

void Crep::SetAnimation()
{
	if (w_frame_ > 0 && h_frame_ > 0)
	{
		for (int i = 0; i < 8; i++)
		{
			framelist[i].x = w_frame_ * i; // frame 0 trong list tức frame đầu tiên tại vị trí x = 0
			framelist[i].y = 0; // frame 0 trong list tức frame đầu tiên tại vị trí y = 0
			framelist[i].h = h_frame_; // frame 0 trong list tức frame đầu tiên có độ cao frame = docaoFrame
			framelist[i].w = w_frame_;// frame 0 trong list tức frame đầu tiên có độ rộng frame = docrongFrame
		}
	}
}

void Crep::HienthiCrep(SDL_Renderer* Crep)
{
	rect_.x = vitrihientai_x - ValueMap_x;
	rect_.y = vitrihientai_y - ValueMap_y;
	frame_++;
	if (frame_ >= 8)
	{
		frame_ = 0;
	}
	// kiểm tra frame hiện tại để trả về hình ảnh frame tương ứng
	SDL_Rect* current_frame = &framelist[frame_];

	// biến chứa thông tin frame đang ở vị trí nào, độ dài độ rông là bao nhiêu (renderquad)
	SDL_Rect rectFrame = { rect_.x, rect_.y, w_frame_, h_frame_ };
	// sử dụng hàm sdl_rendercopy để render tức xuất Nv
	SDL_RenderCopy(Crep, p_doituong_, current_frame, &rectFrame);
}

void Crep::DichuyenCrep(BanDo& dulieu_bando)
{
	giatri_x = 0;
	giatri_y += 4; // roi xuong

	if (giatri_y >= 10)
	{
		giatri_y = 10;
	}

	CheckVaCham(dulieu_bando);
}

void Crep::CheckVaCham(BanDo& dulieu_bando)
{
	int x1 = 0; // giới hạn kiểm tra theo chiều ngang
	int x2 = 0;
	int y1 = 0; // giới hạn kiểm tra theo chiều dọc
	int y2 = 0;


	// kiểm tra chiều ngang
	int chieucaoMIN = h_frame_ < KICHTHUOC_O_LUOI ? h_frame_ : KICHTHUOC_O_LUOI;
	// kiểm tra xem ông nào nhỏ hơn lấy ông đó, giống như ông nào giàu lấy ông đấy làm chồng

	x1 = (vitrihientai_x + giatri_x) / KICHTHUOC_O_LUOI;
	x2 = (vitrihientai_x + giatri_x + w_frame_ - 1) / KICHTHUOC_O_LUOI;

	y1 = (vitrihientai_y) / KICHTHUOC_O_LUOI;
	y2 = (vitrihientai_y + chieucaoMIN - 1) / KICHTHUOC_O_LUOI;

	//Kiểm tra x1, x2 với toàn bộ chiều rộng của bản đồ
	//Kiểm tra y1, y2 với toàn bộ chiều cao của bản đồ
	if (x1 >= 0 && x2 < COT_X_MAX && y1 >= 0 && y2 < HANG_Y_MAX)
	{
		if (giatri_x > 0) // khi đối tượng đang di chuyển bên phải 
		{
			
				// Kiểm tra vị trí hiện tại của bản đồ. Nếu không phải là ô trống.
				if (dulieu_bando.viengach[y1][x2] != 0 || dulieu_bando.viengach[y2][x2] != 0)
				{
					// Cố định vị trí của đối tượng tại vị trí hiện tại của bản đồ dẫn đến Không thể di chuyển khi nhấn nút
					vitrihientai_x = x2 * KICHTHUOC_O_LUOI;
					vitrihientai_x -= w_frame_ + 1;
					giatri_x = 0; // không thể di chuyển
				}
			

		}
		else if (giatri_x < 0) // Khi di chuyển sang trái   
		{
			
				if (dulieu_bando.viengach[y1][x1] != 0 || dulieu_bando.viengach[y2][x1] != 0)
				{
					vitrihientai_x = (x1 + 1) * KICHTHUOC_O_LUOI;
					giatri_x = 0;
				}
			
		}
	}

	// kiểm tra chiều dọc
	int chieurongMIN = w_frame_ < KICHTHUOC_O_LUOI ? w_frame_ : KICHTHUOC_O_LUOI; // kiểm tra xem ông nào nhỏ hơn lấy ông đó

	x1 = (vitrihientai_x) / KICHTHUOC_O_LUOI;
	x2 = (vitrihientai_x + chieurongMIN) / KICHTHUOC_O_LUOI;

	y1 = (vitrihientai_y + giatri_y) / KICHTHUOC_O_LUOI;
	y2 = (vitrihientai_y + giatri_y + h_frame_ - 1) / KICHTHUOC_O_LUOI;

	if (x1 >= 0 && x2 < COT_X_MAX && y1 >= 0 && y2 < HANG_Y_MAX)
	{
		if (giatri_y > 0)
		{

				// tương tự như trên chiều ngang
				if (dulieu_bando.viengach[y2][x1] != 0 || dulieu_bando.viengach[y2][x2] != 0)
				{
					vitrihientai_y = y2 * KICHTHUOC_O_LUOI;
					vitrihientai_y -= h_frame_;
					giatri_y = 0;
					// đang đúng trên bản đồ
					onMAP = true;
				}

		}
		else if (giatri_y < 0)
		{
				if (dulieu_bando.viengach[y1][x1] != 0 || dulieu_bando.viengach[y1][x2] != 0)
				{
					vitrihientai_y = (y1 + 1) * KICHTHUOC_O_LUOI;
					giatri_y = 0;
				}
		}
	}

	// khi không va chạm với bản đồ di chuyển btg cộng thêm cho giatri_x hoặc giatri_y
	vitrihientai_x += giatri_x;
	vitrihientai_y += giatri_y;
	// trường hợp quay trái đến mép bản đồ rồi thì đưa giá trị về 0 để không thể di chuyển qua mep bản đồ
	if (vitrihientai_x < 0)
	{
		vitrihientai_x = 0;
	}
	else if (vitrihientai_x + w_frame_ > dulieu_bando.chiso_x)
	{
		vitrihientai_x = dulieu_bando.chiso_x - w_frame_ - 1;
	}
}

void Crep::KhoiTaoVD(VienDan* viendan_crep, SDL_Renderer* manhinh)
{
	if (viendan_crep != NULL)
	{
		bool ret_crep_vd = viendan_crep->TaiAnh("Images//dancrep.png", manhinh);
		if (ret_crep_vd)
		{
			viendan_crep->HuongVienDan(VienDan::TRAI);
			viendan_crep->Setup_Dichuyen(true);
			viendan_crep->SetRect(rect_.x + 5, vitrihientai_y + 10); // set vi tri
			viendan_crep->ThietLapGiaTriX(20); // toc độ viên đạn bắn ra của crep
			list_VDanofCrep.push_back(viendan_crep);
		}
	}
}

void Crep::CreateVienDan(SDL_Renderer* manhinh, const int& gioihan_x, const int& gioihan_y)
{
	for (int i = 0; i < list_VDanofCrep.size(); i++)
	{
		VienDan* viendan = list_VDanofCrep.at(i);
		if (viendan != NULL)
		{
			if (viendan->GetCheck_Dichuyen())
			{
				int khoangcachdanbay = rect_.x + w_frame_ - viendan->GetRect().x;
				if (khoangcachdanbay > 0 && khoangcachdanbay < 600)
				{
					viendan->VienDanBay(gioihan_x, gioihan_y);
					viendan->Xuat(manhinh);
				}
				else
				{
					viendan->Setup_Dichuyen(false);
				}
			}
			else
			{
				viendan->Setup_Dichuyen(true);
				viendan->SetRect(this->rect_.x + 5, this->rect_.y + 10);
			}
			
		}
	}
}
