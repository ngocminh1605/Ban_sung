
#include "NhanVatObject.h"

// hàm constructor
DoiTuongNhanVat::DoiTuongNhanVat()
{
	// khai báo các giá trị cơ bản mặc định
	frame_ = 0;
	vitrihientai_x = 1;
	vitrihientai_y = 1;
	giatri_x = 0;
	giatri_y = 0;
	docaoFrame_ = 0;
	dorongFrame_ = 0;
	trangthai_dichuyen_ = -1;
	kieu_dauvao.trai_ = 0;
	kieu_dauvao.phai_ = 0;
	kieu_dauvao.len_ = 0;
	kieu_dauvao.xuong_ = 0;
	kieu_dauvao.nhay_ = 0;
	dungtrenbando = false;
	bando_cs_x = 0;
	bando_cs_y = 0;
	thoigian_roi = 0;
	sinhmenh = 1;
	//die = 0;
}

// hmà hủy destructor
DoiTuongNhanVat::~DoiTuongNhanVat() 
{
	
}

SDL_Rect DoiTuongNhanVat::GetRectFrame() // lay lai cai thong so vi tri 
{
	SDL_Rect rect;
	rect.x = rect_.x;
	rect.y = rect_.y;
	rect.w = rect_.w /8;
	rect.h = rect_.h;
	return rect;
}

bool DoiTuongNhanVat::TaiNhanVat(std::string duongdan_nv, SDL_Renderer* manhinh)
{
	bool ret_nv = BaseObject::TaiAnh(duongdan_nv, manhinh); // kế thừa và tận dụng lại class Tải ảnh của BaseObject
	if (ret_nv == true)
	{
		// lấy ra kích thước của 1 frame
		docaoFrame_ = rect_.h;
		dorongFrame_ = rect_.w / 8;
	}

	return ret_nv;
}

void DoiTuongNhanVat::Set_Animation_HanhDong()
{
	if (dorongFrame_ > 0 && docaoFrame_ > 0)
	{
		for (int i = 0; i < 8; i++)
		{
			frame_list[i].x = dorongFrame_ * i; // frame 0 trong list tức frame đầu tiên tại vị trí x = 0
			frame_list[i].y = 0; // frame 0 trong list tức frame đầu tiên tại vị trí y = 0
			frame_list[i].h = docaoFrame_; // frame 0 trong list tức frame đầu tiên có độ cao frame = docaoFrame
			frame_list[i].w = dorongFrame_;// frame 0 trong list tức frame đầu tiên có độ rộng frame = docrongFrame
		}
	}
}

void DoiTuongNhanVat::HienThiNV(SDL_Renderer* Nv)
{
	if (dungtrenbando == true)
	{
		// kiểm tra trạng thái di chuyển đầu vào để load ảnh lên tuong ứng
		if (trangthai_dichuyen_ == DICHUYENTRAI)
		{
			TaiAnh("Images//player_left.png", Nv);
		}

		if (trangthai_dichuyen_ == DICHUYENPHAI)
		{
			TaiAnh("Images//player_right.png", Nv);
		}
	}
	// load frame theo kiểu đầu vào từ button
	if ( kieu_dauvao.trai_ == 1 || kieu_dauvao.phai_ == 1)
	{
		frame_++;
	}
	else
	{
		frame_ = 0;
	}
	if (frame_ >= 8)
	{
		frame_ = 0;
	}

	if (thoigian_roi == 0)
	{
		// gán vị trí đầu tiên = vị trí hiện tại, nếu khi chạy nhân vật thì phải trừ đi 1 lượng chi số x,y của bản đồ đã bị cuộn đi
		rect_.x = vitrihientai_x - bando_cs_x;
		rect_.y = vitrihientai_y - bando_cs_y;

		// kiểm tra frame hiện tại để trả về hình ảnh frame tương ứng
		SDL_Rect* current_frame = &frame_list[frame_];

		// biến chứa thông thin frame đang ở vị trí nào, độ dài độ rông là bao nhiêu (renderquad)
		SDL_Rect rectFrame = { rect_.x, rect_.y, dorongFrame_, docaoFrame_ };
		// sử dụng hàm sdl_rendercopy để render tức xuất Nv
		SDL_RenderCopy(Nv, p_doituong_, current_frame, &rectFrame);
	}
}


// nhận input đầu vào và bắt đầu xử lý các sự kiện di chuyển
void DoiTuongNhanVat::InputHanhDong(SDL_Event sukien, SDL_Renderer* manhinh)
{
	if (sukien.type == SDL_KEYDOWN) // khi phím bất kì đc ấn xuống là bắt đầu sự kiện
	{
		switch (sukien.key.keysym.sym)// xem phím đc ấn xuống alf ký tự nào để xử lý sự kiện tiếp theo sau khi sự kiện ấn phím đã xong
		{
		case SDLK_d: {
			trangthai_dichuyen_ = DICHUYENPHAI;
			kieu_dauvao.phai_ = 1;
			kieu_dauvao.trai_ = 0; 
			if (dungtrenbando == true)
			{
				TaiAnh("Images//player_right.png", manhinh);
			}
			else {
				TaiAnh("Images//jum_right.png", manhinh);
			}
		} break;
		case SDLK_a: {
			trangthai_dichuyen_ = DICHUYENTRAI; 
			kieu_dauvao.trai_ = 1;
			kieu_dauvao.phai_ = 0;
			if (dungtrenbando == true)
			{
				TaiAnh("Images//player_left.png", manhinh);
			}
			else {
				TaiAnh("Images//jum_left.png", manhinh);
			}
		} break;
		case SDLK_w: {
			kieu_dauvao.nhay_ = 1;
			kieu_dauvao.xuong_ = 0;
			TaiAnh("Images//jum.png", manhinh);
			if (kieu_dauvao.nhay_ == 1 && kieu_dauvao.trai_ == 1)
			{
				TaiAnh("Images//jum_left.png", manhinh);
			}
			if (kieu_dauvao.nhay_ == 1 && kieu_dauvao.phai_ == 1)
			{
				TaiAnh("Images//jum_right.png", manhinh);
			}
		} break;
		case SDLK_s: {
			kieu_dauvao.nhay_ = 0;
			kieu_dauvao.xuong_ = 1;
			TaiAnh("Images//jum.png", manhinh);
			if (kieu_dauvao.xuong_ == 1 && kieu_dauvao.trai_ == 1)
			{
				TaiAnh("Images//jum_left.png", manhinh);
			}
			if (kieu_dauvao.xuong_ == 1 && kieu_dauvao.phai_ == 1)
			{
				TaiAnh("Images//jum_right.png", manhinh);
			}
		} break;
		}
	}
	else if (sukien.type == SDL_KEYUP)
	{
		switch (sukien.key.keysym.sym)// xem phím đc ấn xuống alf ký tự nào để xử lý sự kiện tiếp theo sau khi sự kiện ấn phím đã xong
		{
		case SDLK_d: { kieu_dauvao.phai_ = 0; } break;
		case SDLK_a: { kieu_dauvao.trai_ = 0; } break;
		case SDLK_w: {kieu_dauvao.nhay_ = 0; } break;
		case SDLK_s: {kieu_dauvao.xuong_ = 0; } break;
		}
	}

	if (sukien.type == SDL_MOUSEBUTTONDOWN)
	{
		if (sukien.button.button == SDL_BUTTON_LEFT) // kiểm tra xem có phải bấm chuột trái hay ko
		{
			VienDan* vienDan = new VienDan(); // p_bullet, tạo ra viên đạn mơi khi click chuột trái
			
			if (trangthai_dichuyen_ == DICHUYENTRAI)
			{
				// tải lên hình ảnh viên đạn
				vienDan->TaiAnh("Images/dannhanvat2.png", manhinh);
				vienDan->HuongVienDan(VienDan::TRAI);
				// thiết lập vị trí ban đầu của viên đạn sao cho khớp với nhân vật
				vienDan->SetRect(this->rect_.x + dorongFrame_ - 20, this->rect_.y + docaoFrame_ * 0.5);
			}
			else if (trangthai_dichuyen_ == DICHUYENPHAI) 
			{
				// tải lên hình ảnh viên đạn
				vienDan->TaiAnh("Images/dannhanvat.png", manhinh);
				vienDan->HuongVienDan(VienDan::PHAI);
				// thiết lập vị trí ban đầu của viên đạn sao cho khớp với nhân vật
				vienDan->SetRect(this->rect_.x + dorongFrame_ - 40, this->rect_.y + docaoFrame_ * 0.5);
			}


			// nếu di chuyển viên đạn tương đương cộng thêm một lương, như vậy lượng này có thể xem là tốc độ bay của viên đạn
			// như vậy có thể thấy tốc độ của viên đạn phải nhanh hơn tốc độ của nhân vật
			vienDan->ThietLapGiaTriX(25);

			// gán trạng thái chỉ cần cứ bấm chuột là nhận sự kiến -> bắn đạn
			vienDan->Setup_Dichuyen(true);

			// tạo một danh sách, để hiển thị thấy nhiều viên đạn bay chứ không phải từng viên 1 FIFO
			list_VienDan.push_back(vienDan);
		}
	}
}

// xử lý đường đạn bay
void DoiTuongNhanVat::DanBay(SDL_Renderer* desdanBay)
{
	// liên tục kiểm tra xem danh sách các viên đạn có trống hay không
	for (int i = 0; i < list_VienDan.size(); i++)
	{
		VienDan* v_Dan = list_VienDan.at(i);
		if (v_Dan != NULL)
		{
			if (v_Dan->GetCheck_Dichuyen() == true)
			{
				v_Dan->VienDanBay(DORONG_MANHINH - 128, DOCAO_MANHINH);
				v_Dan->Xuat(desdanBay);
			}
			else // kiểm tra trước xem list có trống ko, nếu trống thì khi viendan ra khỏi giới hạn cẩn phải hủy đi
			{
				list_VienDan.erase(list_VienDan.begin() + i);
				if (v_Dan != NULL)
				{
					delete v_Dan;
					v_Dan = NULL;
				}
			}
		}
	}
}

void DoiTuongNhanVat::XoaVienDan(const int& viendani)
{
	if (list_VienDan.size() > 0 && viendani < list_VienDan.size())
	{
		VienDan* VDan = list_VienDan.at(viendani);
		list_VienDan.erase(list_VienDan.begin() + viendani);

		if (VDan)
		{
			delete VDan;
			VDan = NULL;
		}
	}
}


void DoiTuongNhanVat::DiChuyenNhanVat(BanDo& dulieu_bando)
{

	if (thoigian_roi == 0) // tức là khi này nhân vật vẫn ở trong bản đồ
	{
		giatri_x = 0; // x giữ nguyên là sẽ không tự động chạy về trái hoặc phải
		giatri_y += tocdoroi; // tự động rơi theo chiều dọc từng ô một

		// giới hạn rơi đên một lượng ô nhất định
		if (giatri_y >= doroimax)
		{
			giatri_y = doroimax;
		}

		// khi bấm nút thì cần tăng giảm một lượng để thể hiện nhân vật di chuyển từ ô này sang ô khác
		if (kieu_dauvao.trai_ == 1)
		{
			giatri_x -= tocdodichuyenNV;
		}
		else if (kieu_dauvao.phai_ == 1) // đúng
		{
			giatri_x += tocdodichuyenNV;
		}

		if (kieu_dauvao.nhay_ == 1)
		{
			if (dungtrenbando == true)
			{
				giatri_y = -30;
			}
			dungtrenbando = false; 
			//kieu_dauvao.nhay_ = 0;
		}
		// kiểm tra xem nhân vật rơi đúng bản đồ thì có thể đứng trên bản đồ đc chứ ko cho rơi xuống đáy
		KiemtraNVvachamBanDo(dulieu_bando);
		// tính toán thông số bản đồ
		VtriTrungTamBanDo(dulieu_bando);
	}

	// nếu thoigianroi > 0 tức đang rơi ko ở trong bản đồ
	if (thoigian_roi > 0)
	{
		thoigian_roi--;
			if (thoigian_roi == 0)
			{
				dungtrenbando = false;
				if (vitrihientai_x > 192) // 192 tương đương với 3 ô
				{
					bando_cs_x -= 192;
					vitrihientai_x -= 192;
				}
				else
				{
					vitrihientai_x = 0;
				}
				vitrihientai_y = 0;
				giatri_x = 0;
				giatri_y = 0;
			}

	}
	
}


void DoiTuongNhanVat::VtriTrungTamBanDo(BanDo& dulieu_bando)
{
	// nhân vật di chuyển đến vị trí giữa bản đồ thì bản đồ sẽ cuốn theo nhân vật

	dulieu_bando.vitri_x = vitrihientai_x - (DORONG_MANHINH/2); // vị trí center 
	// đi quá trung tâm thì ms di chuyển bản đồ, còn đi lùi nhỏ hơn vị trí trung tâm thì bản đồ giữ nguyên còn nhân vật vẫn di chuyển
	if (dulieu_bando.vitri_x < 0)
	{
		dulieu_bando.vitri_x = 0; 
	}
	else if (dulieu_bando.vitri_x + DORONG_MANHINH >= dulieu_bando.chiso_x) // khi đến cuối bản đồ không cho di chuyển thêm nữa
	{
		dulieu_bando.vitri_x = dulieu_bando.chiso_x - DORONG_MANHINH;
	}

	dulieu_bando.vitri_y = vitrihientai_y - (DOCAO_MANHINH / 2);
	if (dulieu_bando.vitri_y < 0)
	{
		dulieu_bando.vitri_y = 0;
	}
	else if (dulieu_bando.vitri_y + DOCAO_MANHINH >= dulieu_bando.chiso_y)
	{
		dulieu_bando.vitri_y = dulieu_bando.chiso_y - DOCAO_MANHINH;
	}
}

void DoiTuongNhanVat::KiemtraNVvachamBanDo(BanDo& dulieu_bando)
{
	int x1 = 0; // giới hạn kiểm tra theo chiều ngang
	int x2 = 0;
	int y1 = 0; // giới hạn kiểm tra theo chiều dọc
	int y2 = 0;


	// kiểm tra chiều ngang
	int chieucaoMIN = docaoFrame_ < KICHTHUOC_O_LUOI ? docaoFrame_ : KICHTHUOC_O_LUOI;
	

	x1 = (vitrihientai_x + giatri_x) / KICHTHUOC_O_LUOI;
	x2 = (vitrihientai_x + giatri_x + dorongFrame_ - 1) / KICHTHUOC_O_LUOI;

	y1 = (vitrihientai_y) / KICHTHUOC_O_LUOI;
	y2 = (vitrihientai_y + chieucaoMIN - 1) / KICHTHUOC_O_LUOI;

	//Kiểm tra x1, x2 với toàn bộ chiều rộng của bản đồ
	//Kiểm tra y1, y2 với toàn bộ chiều cao của bản đồ
	if (x1 >= 0 && x2 < COT_X_MAX && y1 >= 0 && y2 < HANG_Y_MAX)
	{
		if (giatri_x > 0) // khi đối tượng đang di chuyển bên phải 
		{
			if (dulieu_bando.viengach[y1][x2] == 4 || dulieu_bando.viengach[y2][x2] == 4)
			{
				sinhmenh++;
				//die--;
				dulieu_bando.viengach[y1][x2] = 0;
				dulieu_bando.viengach[y2][x2] = 0;
				
			}
			else
			{
				// Kiểm tra vị trí hiện tại của bản đồ. Nếu không phải là ô trống.
				if (dulieu_bando.viengach[y1][x2] != 0 || dulieu_bando.viengach[y2][x2] != 0)
				{
					// Cố định vị trí của đối tượng tại vị trí hiện tại của bản đồ dẫn đến Không thể di chuyển khi nhấn nút
					vitrihientai_x = x2 * KICHTHUOC_O_LUOI;
					vitrihientai_x -= dorongFrame_ + 1;
					giatri_x = 0; // không thể di chuyển
				}
			}
			
		}
		else if (giatri_x < 0) // Khi di chuyển sang trái   
		{
			if (dulieu_bando.viengach[y1][x1] == 4 || dulieu_bando.viengach[y2][x1] == 4)
			{
				sinhmenh++;
				//die--;
				dulieu_bando.viengach[y1][x1] = 0;
				dulieu_bando.viengach[y2][x1] = 0;
				
			}
			else
			{
				if (dulieu_bando.viengach[y1][x1] != 0 || dulieu_bando.viengach[y2][x1] != 0)
				{
					vitrihientai_x = (x1 + 1) * KICHTHUOC_O_LUOI;
					giatri_x = 0;
				}
			}
		}
	}

	// kiểm tra chiều dọc
	int chieurongMIN = dorongFrame_ < KICHTHUOC_O_LUOI ? dorongFrame_ : KICHTHUOC_O_LUOI; // kiểm tra xem ông nào nhỏ hơn lấy ông đó
	

	x1 = (vitrihientai_x) / KICHTHUOC_O_LUOI;
	x2 = (vitrihientai_x + chieurongMIN) / KICHTHUOC_O_LUOI;

	y1 = (vitrihientai_y + giatri_y) / KICHTHUOC_O_LUOI;
	y2 = (vitrihientai_y + giatri_y + docaoFrame_ - 1) / KICHTHUOC_O_LUOI;

	if (x1 >= 0 && x2 < COT_X_MAX && y1 >= 0 && y2 < HANG_Y_MAX)
	{
		if (giatri_y > 0)
		{
			if (dulieu_bando.viengach[y2][x1] == 4 || dulieu_bando.viengach[y2][x2] == 4)
			{
				sinhmenh++;
				//die--;
				dulieu_bando.viengach[y2][x1] = 0;
				dulieu_bando.viengach[y2][x2] = 0;
				
			}
			else
			{
				// tương tự như trên chiều ngang
				if (dulieu_bando.viengach[y2][x1] != 0 || dulieu_bando.viengach[y2][x2] != 0)
				{
					vitrihientai_y = y2 * KICHTHUOC_O_LUOI;
					vitrihientai_y -= docaoFrame_;
					giatri_y = 0;
					// đang đúng trên bản đồ
					dungtrenbando = true;
				}
			}
		}
		else if (giatri_y < 0)
		{
			if (dulieu_bando.viengach[y1][x1] == 4 || dulieu_bando.viengach[y1][x2] == 4)
			{
				sinhmenh++;
				//die--;
				dulieu_bando.viengach[y1][x1] = 0;
				dulieu_bando.viengach[y1][x2] = 0;
				
			}
			else
			{
				if (dulieu_bando.viengach[y1][x1] != 0 || dulieu_bando.viengach[y1][x2] != 0)
				{
					vitrihientai_y = (y1 + 1) * KICHTHUOC_O_LUOI;
					giatri_y = 0;
				}
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
	else if (vitrihientai_x + dorongFrame_ > dulieu_bando.chiso_x)
	{
		vitrihientai_x = dulieu_bando.chiso_x - dorongFrame_ - 1;
	}

	// kiểm tra nếu rơi vượt quá mép bản đồ thì gán giá trị cho thời gian rơi một khoảng và cho nhân vật trở lại
	if (vitrihientai_y > dulieu_bando.chiso_y)
	{
		thoigian_roi = 50;
		// thêm code trừ đi sinh mệnh
		//die++;
		sinhmenh--;
	}
}































