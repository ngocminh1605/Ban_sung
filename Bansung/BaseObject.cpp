#include "stdafx.h"
#include "BaseObject.h"

BaseObject::BaseObject()
{
	p_doituong_ = NULL;
	rect_.w = 0;
	rect_.h = 0;
	rect_.x = 0;
	rect_.y = 0;
}

BaseObject::~BaseObject()
{
	GiaiPhong(); // khi kết thúc chương trình sẽ hủy các đối tượng tránh việc còn dữ liệu khiến chiếm dụng bố nhớ
}

bool BaseObject::TaiAnh(std::string duongdan, SDL_Renderer* manhinh)
{
	GiaiPhong();  // cai cho nay bai 8, hay bai 9 co noi den, nhung anh them truo vao cho em
	// final varibal texture
	SDL_Texture* newTexture = NULL; // mặc định là đúng

	// tải ảnh lên từ đường dẫn chỉ định
	SDL_Surface* loadedSurface = IMG_Load(duongdan.c_str());// hàm IMG_Load tải ảnh lên trả về surface sau đó đưa surface thành texture
	if (loadedSurface != NULL) // kiểm tra
	{
		// transparent background cho các tấm ảnh
		SDL_SetColorKey(loadedSurface, 
						SDL_TRUE, 
						SDL_MapRGB(loadedSurface->format, Color_R, Color_G, Color_B));

		// khởi tạo texture từ surface pixel
		newTexture = SDL_CreateTextureFromSurface(manhinh, loadedSurface);
		if (newTexture != NULL) // bây h, tại thời điểm cần khởi tạo, có nghĩ newTexture phải khác rỗng ms là đúng
		{
			// nhận dạng kích thước của ảnh mà đã tải lên
			rect_.w = loadedSurface->w;
			rect_.h = loadedSurface->h;
		}
		// Khi này toàn bộ thông số và thuộc tính của hình ảnh tải lên đang nằm trong biến newTexture

		// loại loadedSurface cũ vì thông số của ảnh đã được newTexture lưu 
		SDL_FreeSurface(loadedSurface);
	}

	p_doituong_ = newTexture;
	return p_doituong_ != NULL; // nếu không có giá trị trả về 0 là false còn có giá trị trả về là 1 tức là true
}

void BaseObject::Xuat(SDL_Renderer* x_manhinh, const	SDL_Rect* clip) // load ảnh lên đối tượng 
{
	SDL_Rect xuat_g = {rect_.x, rect_.y, rect_.w, rect_.h}; // x,y là vị trí của tấm ảnh. w,h là kích thước tấm ảnh

	SDL_RenderCopy(x_manhinh, p_doituong_, clip, &xuat_g); // đẩy toàn bộ thông số của p_doituong_ lên x_manhinh vơi thông số và kích thước từ xuat_g
}

void BaseObject::GiaiPhong()
{
	if (p_doituong_ != NULL) 
	{
		SDL_DestroyTexture(p_doituong_);
		p_doituong_ = NULL;
		rect_.w = 0;
		rect_.h = 0;
	}
}