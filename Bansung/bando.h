#pragma once
#ifndef BANDO_H_
#define BANDO_H_

#include "stdafx.h"
#include "BaseFunction.h"
#include "BaseObject.h"

// Tạo một class kế thừa từ BaseObject làm nhiệm vụ quán lý các hình ảnh cho các ô vuông trong lưới bản đồ
class O_Bando : public BaseObject
{
public:
	O_Bando() {;}
	~O_Bando(){;}
};

// tạo class quản lý xây dựng bản đồ, sử dụng class O_Bando kế thừa từ BaseObject để fill hình ảnh vào các ô vuông trong lưới bản đồ 
// ở từng vị trí khác nhau à vị trí đã được khai báo trong struct BanDo ở BaseFunction
class BanDoGAME
{
public:
	BanDoGAME() {;}
	~BanDoGAME() {;}

	// tải file txt chứa thông số của bản đồ
	//void TaiBanDo(char* ten_file);
	void TaiBanDo(char* tenfile );
	// load hình ảnh cho các ô từ file hình ảnh chứa trong folder Map
	void TaiHinhAnh_Ovuong(SDL_Renderer* manhinh);
	// hàm xây dựng bản đồ, nhiệm vụ fill các hình ảnh từ TaiHinhAnh_Ovuong vào các ô ở các vị trí tương ứng
	void VeBanDo(SDL_Renderer* manhinh);


	BanDo getBanDo() const { return bando_game_; };


	// hàm set Bando phục vụ cho việc di chuyển bản đồ theo nhân vật khi nhân vật đến góc phải màn hình
	void SetBanDo(BanDo& dulieu_bando) { bando_game_ = dulieu_bando; };


private:
	BanDo bando_game_; // chứa toàn bộ thông tin về bản đồ
	O_Bando o_bando_[20]; // lưu trữ các dạng hình ảnh cho các ô, ví dụ hình ảnh nền đất, hình ảnh nền gỗ, kim cương
};


#endif // !BANDO_H_
