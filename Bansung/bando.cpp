#include "stdafx.h"
#include "bando.h"


// định nghĩa cho hàm tải bản bản đồ

void BanDoGAME::TaiBanDo( char* tenfile)
{
	// đọc file
	FILE* file_map_game = NULL;
	fopen_s(&file_map_game, tenfile, "rb");
	if (file_map_game == NULL ) // Kiểm tra xem có tải đc file ko
	{
		return;
	}

	// vòng lặp for trong for để đọc mảng 2 chiều, vì khi chia bản đồ thành dạng lưới, có hàng và cột 
	// tạo ma trận tương đương mảng 2 chiều
	// mỗi 1 phần tử tương đương 1 ô kích thước 64

	bando_game_.chiso_x = bando_game_.chiso_y = 0; // thời điểm ban đầu đang ở vị trí mặc định là ô có vị trí [0][0]
	for (int i = 0; i < HANG_Y_MAX; i++)
	{
		for (int j = 0; j < COT_X_MAX; j++)
		{
			// đọc dữ liệu từ file lưu vào trong mảng bando_game_ đã khai báo trong bando.h
			fscanf_s(file_map_game, "%d", &bando_game_.viengach[i][j]);
			if (bando_game_.viengach[i][j] > 0)
			{
				// kiểm tra nếu vượt qua lượng cộng thêm thì bằng chính lượng đó
				if (j > bando_game_.chiso_x)
				{
					bando_game_.chiso_x = j;
				}

				if (i > bando_game_.chiso_y)
				{
					bando_game_.chiso_y = i;
				}
			}
		}
	}

	// khi chạy xong vòng for, đọc dữ liệu xong. gán dữ liệu
	bando_game_.chiso_x = (bando_game_.chiso_x + 1) * KICHTHUOC_O_LUOI;
	bando_game_.chiso_y = (bando_game_.chiso_y + 1) * KICHTHUOC_O_LUOI;
	bando_game_.vitri_x = 0;
	bando_game_.vitri_y = 0;
	bando_game_.file_ = tenfile;
	fclose(file_map_game);
}

// tải hình ảnh tương úng cho các ô tương ứng
void BanDoGAME::TaiHinhAnh_Ovuong(SDL_Renderer* manhinh)
{
	char file_hinhanh[40];
	FILE* filehinhanh = NULL;

	// tạo 1 chuỗi từ 0 đến 10 file_hinhanh để truyền chỉ số ứng với tên file hình ảnh cho từng dạng bản đồ cho mỗi ô có thuộc tính riêng
	for (int i = 0; i < 20; i++)
	{
		sprintf_s(file_hinhanh, "map/%d.png", i);
		// mở file và kiểm tra xem mở thành công hay không
		fopen_s(&filehinhanh, file_hinhanh, "rb");
		if (filehinhanh == NULL) // nếu như không đọc được hoặc hình ảnh đó không có trong thư mục thì ta bỏ qua đọc các hình ảnh khác
		{
			continue;
		}
		// đọc được thì ta đóng pointer(con trỏ) này lại
		fclose(filehinhanh);
		// khi đã đọc được và xác nhận bức ảnh đó có tồn tại và tải sẵn lên các biến đối tượng hình ảnh chờ render
		o_bando_[i].TaiAnh(file_hinhanh,manhinh);
	}
}

void BanDoGAME::VeBanDo(SDL_Renderer* manhinh)
{
	// khởi tạo vị trí fill hình ảnh vào các ô, cần biết đc fill từ vị trí nào đến vị trí nào 
	int x1 = 0;
	int x2 = 0;
	int y1 = 0;
	int y2 = 0;
	int o_vitrix = 0;
	int o_vitriy = 0;


	// x1 được tính bằng vị trí hiện tại trên bản đồ chia lấy dư cho kích thước của ô lưới xong trừ đi 1 để ra phần bắt đầu fill
	// vị trí x2 là vị trí cuối cùng để fill
	x1 = (bando_game_.vitri_x % KICHTHUOC_O_LUOI) * -1;
	x2 = x1 + DORONG_MANHINH + (x1 == 0 ? 0 : KICHTHUOC_O_LUOI);

	// y1 và y2 tính tương tự như x1, x2 nhưng là theo chiều vuông góc để fill đc cả 1 ô
	y1 = (bando_game_.vitri_y % KICHTHUOC_O_LUOI) * -1;
	y2 = y1 + DOCAO_MANHINH + (y1 == 0 ? 0 : KICHTHUOC_O_LUOI);

	// bắt đầu fill các hình ảnh vào các ô lưới
	for (int i = y1; i < y2; i += KICHTHUOC_O_LUOI)
	{
		o_vitrix = bando_game_.vitri_x / KICHTHUOC_O_LUOI;
		for (int j = x1; j < x2; j += KICHTHUOC_O_LUOI)
		{
			if (bando_game_.viengach[o_vitriy][o_vitrix] != 0)
			{
				o_bando_[bando_game_.viengach[o_vitriy][o_vitrix]].SetRect(j, i); // thiết lập vị trí fill hình ảnh
				o_bando_[bando_game_.viengach[o_vitriy][o_vitrix]].Xuat(manhinh); // bắt đầu fill hình ảnh và xuất lên màn hình
			}
			o_vitrix++;
		}
		o_vitriy++;
	}
}
