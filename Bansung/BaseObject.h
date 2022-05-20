#pragma once

#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_

#include "BaseFunction.h"

// Class ( lớp ) này là class nền tảng có nhiệm vụ tải ảnh lên màn hình 
// dù là nhân vật, bản đồ hay quái thì đều dùng hình ảnh
class BaseObject
{
public:
	BaseObject(); // Hàm constructor
	~BaseObject(); // Hàm Destructor

	

	void SetRect(const int& x, const int& y) { rect_.x = x, rect_.y = y; }; // hàm thiết lập kích thước

	// lấy ra các kích thước đã thiết lập
	SDL_Rect GetRect() const { return rect_; }
	// lấy ra hình ảnh p_doituong_
	SDL_Texture* GetObject() const { return p_doituong_; }


	virtual bool TaiAnh(std::string duongdan, SDL_Renderer* manhinh); // load ảnh bitmap lên đối tượng hình ảnh p_doituong_ để sử dụng
	void Xuat(SDL_Renderer* x_manhinh, const	SDL_Rect* clip = NULL); // xuất ảnh lên màn hình
	void GiaiPhong();


protected:
	SDL_Texture* p_doituong_; // chứa một tập hợp các pixel để có thể render lên Window sử dụng GPU. Lưu trữ các hình ảnh
	SDL_Rect rect_; // struct đại diện cho một hình chữ nhật gồm có các thông tin là x, y, w, h. Lưu kích thước của các tấm ảnh p_doituong_

};








#endif // !BASE_OBJECT_H_

