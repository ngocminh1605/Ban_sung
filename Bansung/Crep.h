#pragma once
#ifndef CREP_H_
#define CREP_H_

#include "stdafx.h"
#include "BaseFunction.h"
#include "BaseObject.h"
#include "VienDan.h"

class Crep : public BaseObject
{
public:
    Crep();
    ~Crep();
    
    
    // lấy vào giá trị cho giatri_x và giatri_y
    void set_giatri_x(float giatriX) { giatri_x = giatriX; }
    void set_giatri_y(float giatriY) { giatri_y = giatriY; }

    // lấy vào giá trị 
    void set_vitrihientai_x(float vthtX) { vitrihientai_x = vthtX; }
    void set_vitrihientai_y(float vthtY) { vitrihientai_y = vthtY; }

    // trả về giá trị vị trí hiện tại
    int get_vitrihientai_x() { return vitrihientai_x; }
    int get_vitrihientai_y() { return vitrihientai_y; }

    // lấy vào giá trị vị trí trên bản đồ
    void SetMapXY( int map_x,  int map_y) { ValueMap_x = map_x, ValueMap_y = map_y; }

    void SetAnimation();
    bool TaiAnhCrep(std::string duongdan, SDL_Renderer* manhinh);
    void HienthiCrep(SDL_Renderer* Crep);

    // trả về giá trị của frame để check va chạm 
    int Get_W_frame() { return w_frame_; };
    int Get_H_frame() { return h_frame_; };

    // di chuyen Crep
    void DichuyenCrep(BanDo& dulieu_bando);

    void CheckVaCham(BanDo& dulieu_bando);

    // tra ve list vien dan cho crep
    std::vector<VienDan*> Get_DanofCrep_list() const { return list_VDanofCrep; };

    // lay list vien dan xu ly va cham giua nhan vat va vien dan cua crep
    void Set_DanofCrep_list(const std::vector<VienDan*>& vdCrep_list) { list_VDanofCrep = vdCrep_list; };

    // khoi tao thong so vien dan cua cac crep
    void KhoiTaoVD(VienDan* viendan_crep, SDL_Renderer* manhinh);
    // tao vien dan
    void CreateVienDan(SDL_Renderer* manhinh, const int& gioihan_x, const int& gioihan_y);

    void XoaVienDan(const int& viendani);
    void ResetVienDan(VienDan* viendan);

    // lấy thông số frame của crep
    SDL_Rect GetRectFrame();

private:
    
    SDL_Rect framelist[8];
    int w_frame_;
    int h_frame_;
    int frame_; // quản lý frame của crep
    
    // vị trí hiện tại của crep
    float vitrihientai_x;
    float vitrihientai_y;
    float giatri_x; // tăng giảm theo chiều ngang một giá trị nhất định khi ấn phím trái phải
    float giatri_y; // tăng giảm theo chiều dọc một giá trị nhất định khi ấn phím lên xuống

    // gía trị check xem đến mép bản đồ
    int ValueMap_x;
    int ValueMap_y;

    bool onMAP;

    std::vector<VienDan*> list_VDanofCrep;
    
};


#endif // !CREP_H_
