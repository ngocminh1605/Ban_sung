#include "stdafx.h"
#include "BaseFunction.h"
#include "BaseObject.h"
#include "bando.h"
#include "NhanVatObject.h"
#include "xulyfps.h"
#include "Crep.h"
#include "VienDan.h"
#include "ThongSoInGame.h"
#include <Windows.h>


BaseObject g_BG; // lưu ảnh để load lên màn hình
BaseObject g_img_Menu;
TTF_Font* g_font_text = NULL; // doi tuong font text


// khởi tạo các thông số môi trường cho SDL
bool KhoiTaoDuLieu()
{
    bool success = true;
    int ret = SDL_Init(SDL_INIT_VIDEO); // thiết lập môi trường ban đầu cho sdl

    if (ret < 0)
    {
        return false;
    }

    // thiết lập tỉ lệ và chất lượng
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    // tạo cửa số window cho game
    g_window = SDL_CreateWindow(
        "Ninja Go", 
        SDL_WINDOWPOS_UNDEFINED, 
        SDL_WINDOWPOS_UNDEFINED, 
        DORONG_MANHINH, 
        DOCAO_MANHINH,
        SDL_WINDOW_SHOWN);


    if (g_window == NULL) // không tạo được cửa sổ window cho game
    {
        success = false;
    }
    else
    {
        // g_window trả về 1 biến renderer cho g_manhinh
        g_manhinh = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
        if (g_manhinh == NULL) // không nhận được giá trị trả về
        {
            success = false;
        }
        else
        {
            SDL_SetRenderDrawColor(g_manhinh, 255, 255, 255, 255);
            // gắn Flag ( cờ ) cho ảnh
            int imgFlags = IMG_INIT_PNG;
            // kiểm tra
            if (!(IMG_Init(imgFlags) && imgFlags))
            {
                success = false;
            }
        }

        // khoi tao du lieu cho text
        if (TTF_Init() == -1) // gan co neu bang -1 la error
        {
            success = false;
        }


        g_font_text = TTF_OpenFont("font//dlxfont.ttf", 15); // size 15 pixel
        if (g_font_text == NULL)
        {
            return false;
        }
    }

    return success; // trả về giá trị success = true tức là thành công
}

// hàm tải ảnh và tạo nền ( backgound )
bool LoadAnhNen()
{
    bool success = g_BG.TaiAnh("Images/background.png", g_manhinh); // tải ảnh từ đường dẫn lên màn hình
    if (success == false)
    {
        return false;
    }

    return true;
}


// giải phóng các đối tượng
void dong_ctr()
{
    // gọi hết tất cả các hàm hủy hàm destroy
    g_BG.GiaiPhong();
    SDL_DestroyRenderer(g_manhinh);
    g_manhinh = NULL;
    SDL_DestroyWindow(g_window);
    g_window == NULL;
    IMG_Quit();
    SDL_Quit();
}

// tạo ra một list các crep , dùng vector.h
std::vector<Crep*> CreateCrepList()
{
    std::vector<Crep*> list_creps;

    Crep* CrepObjList = new Crep[35]; // tao  ra 35 con crep

    for (int i = 0; i < 35; i++)
    {
        Crep* newcrep = (CrepObjList + i);
        if (newcrep != NULL)
        {
            newcrep->TaiAnhCrep("Images//crep.png", g_manhinh);
            newcrep->SetAnimation();
            newcrep->set_vitrihientai_x(1605 + i * 600);
            newcrep->set_vitrihientai_y(200);

            VienDan* viendan = new VienDan();
            newcrep->KhoiTaoVD(viendan,g_manhinh);

            list_creps.push_back(newcrep);
        }
    }


    return list_creps;
}




int main(int argc, char* argv[])
{



    Xuly_Fps_Timer fps;

    // kiểm tra xem khởi tạo dữ liệu thành công hay không, nếu không sẽ trả về -1 tức ctr sẽ kết thúc
    if (KhoiTaoDuLieu() ==  false)
    {
        return -1;
    }
    // Kiểm tra nếu ảnh nền đã tải lên hay chưa
    if (LoadAnhNen() == false)
    {
        return -1;
    }

    // thực hiện gọi và vẽ bản đồ cho game
    BanDoGAME bando_game;
    bando_game.TaiBanDo((char*)"map//ming_map.txt");
    bando_game.TaiHinhAnh_Ovuong(g_manhinh);

    // Khai báo, gọi và hiển thị nhân vật
    DoiTuongNhanVat g_nhanvat;
    g_nhanvat.TaiNhanVat("Images//player_right.png", g_manhinh);
    g_nhanvat.Set_Animation_HanhDong();

    std::vector<Crep*> CREP_list = CreateCrepList();

    // Để chương trình load ảnh nền liên tục tức là chạy đến khi nào mình báo hủy thì tạo trễ bằng vòng lặp while
    bool thoat_ctr = false;
    int dieCount = 0;

    // set mau hien thi cho thoi gian va cac doi tuong khac
    ThongSoInGame time_game;
    time_game.setColor(ThongSoInGame::WHITE_TEXT);

    ThongSoInGame diemso;
    diemso.setColor(ThongSoInGame::WHITE_TEXT);
    int diemsogame = 0;

    ThongSoInGame sinhmenh_game;
    sinhmenh_game.setColor(ThongSoInGame::BLACK_TEXT);


    

    while (!(thoat_ctr))
    {
        // ngay khi bắt đầu thì hàm class xử lý fps đc bắt đầu

        fps.batdau();

        while (SDL_PollEvent(&g_sukien) != 0)
        {
            if (g_sukien.type == SDL_QUIT)
            {
                thoat_ctr = true; // thoát ctr khi sự kiện SDL_QUIT đc gọi
            }
            // sự kiện bấm nút đc gọi trong vòng while
            g_nhanvat.InputHanhDong(g_sukien, g_manhinh);
        }

        // trước khi bắt đầu ctr và tải ảnh nền thì sét lại màu nền trắng cho màn hình và xóa màn hình cũ
        SDL_SetRenderDrawColor(g_manhinh,255,255,255,255);
        SDL_RenderClear(g_manhinh);

        // truyền (fill) ảnh nền vô màn hình
        g_BG.Xuat(g_manhinh, NULL);
        //bando_game.VeBanDo(g_manhinh);
        // lấy dữ liệu lại của bản đồ
        BanDo dulieu_bando = bando_game.getBanDo();
       
        // khi vòng while chạy liên tục và cứ click thì có đạn và đạn bay
        g_nhanvat.DanBay(g_manhinh);

        // di chuyển bản đồ theo nhân vật
        g_nhanvat.SetBanDoXY(dulieu_bando.vitri_x, dulieu_bando.vitri_y);

        g_nhanvat.DiChuyenNhanVat(dulieu_bando);
        // hiển thị nhân vật
        g_nhanvat.HienThiNV(g_manhinh);

       // int diecount2 = g_nhanvat.get_die_count();
        int sinhmenhnv = g_nhanvat.get_sinhmenh();

        // sau khi gán vitri_x,y ở hàm SetBanDoXY thì giá trị đã thay đổi , cập nhật vị trí mới
        bando_game.SetBanDo(dulieu_bando);
        // vẽ lại bản đồ
        bando_game.VeBanDo(g_manhinh);
        for (int  i = 0; i < CREP_list.size(); i++)
        {
            Crep* game_crep = CREP_list.at(i);
            if (game_crep != NULL)
            {
                game_crep->SetMapXY(dulieu_bando.vitri_x, dulieu_bando.vitri_y);
                game_crep->DichuyenCrep(dulieu_bando);
                game_crep->CreateVienDan(g_manhinh, DORONG_MANHINH, DOCAO_MANHINH);
                game_crep->HienthiCrep(g_manhinh);

                // check va cham dan cua crep vs nhan vat
                SDL_Rect rect_nhanvat = g_nhanvat.GetRectFrame();
                bool vacham = false;
                std::vector<VienDan*> viendan_list = game_crep->Get_DanofCrep_list();
                for (int a = 0; a < viendan_list.size(); a++)
                {
                    VienDan* vdCrep = viendan_list.at(a);
                    if (vdCrep != NULL)
                    {
                        vacham = SDLBaseFunction::Checkvacham2Obj(vdCrep->GetRect(), rect_nhanvat);
                        if (vacham == true)
                        {
                            game_crep->ResetVienDan(vdCrep);
                            break;
                        }
                    }
                }

                // check va chạm giữa nhân vật và creep
                SDL_Rect rect_crep = game_crep->GetRectFrame();
                bool vacham2 = SDLBaseFunction::Checkvacham2Obj(rect_nhanvat, rect_crep);
                
                if (sinhmenhnv > 0 ) // alive
                {
                    if (vacham2 || vacham)
                    {
                        //dieCount++;
                        sinhmenhnv--;
                        if (sinhmenhnv > 0) // alive
                        {
                            // sau khi chết sẽ hồi sinh lại trong số lần chết cho phép
                            g_nhanvat.SetRect(0, 0);
                            g_nhanvat.set_thoigian_hoisinh(50);
                            SDL_Delay(1000);  
                            continue;
                        }
                        else
                        {
                            // messagebox
                            
                            game_crep->GiaiPhong();
                            dong_ctr();
                            SDL_Quit();
                            return 0;
                        }
                    }
                }
                else
                {
                    // messagebox
                    game_crep->GiaiPhong();
                    dong_ctr();
                    SDL_Quit();
                    return 0;
                }
            }
        }

        // check va cham crep voi dan tu nhan vat
        std::vector<VienDan*> listviendan2 = g_nhanvat.Lay_list_Viendan();

        for (int i = 0; i < listviendan2.size(); i++)
        {
            VienDan* viendan2 = listviendan2.at(i);
            if (viendan2 != NULL)
            {
                for (int j = 0; j < CREP_list.size(); j++)
                {
                    Crep* crep2 = CREP_list.at(j);
                    if (crep2 != NULL)
                    {
                        SDL_Rect CreepRect;
                        CreepRect.x = crep2->GetRect().x;
                        CreepRect.y = crep2->GetRect().y;
                        CreepRect.w = crep2->Get_W_frame();
                        CreepRect.h = crep2->Get_H_frame();

                        bool vacham3 = SDLBaseFunction::Checkvacham2Obj(viendan2->GetRect(), CreepRect);
                        if (vacham3)
                        {
                            diemsogame++;
                            g_nhanvat.XoaVienDan(i);
                            crep2->GiaiPhong();
                            CREP_list.erase(CREP_list.begin() + j);
                            
                        }
                    }
                }
            }
        }

        // hien thi text thoi gian
        std::string thoigian = "THOI GIAN:";
        Uint32 giatri_thoigian = SDL_GetTicks() / 1000;
        Uint32 thoigiandemnguoc = 600 - giatri_thoigian;

        if (thoigiandemnguoc <= 0)
        {
            thoat_ctr = true;
            break;
        }
        else
        {
            // hien thi len tren man hinh
            std::string time = std::to_string(thoigiandemnguoc);
            thoigian += time;

            time_game.SetText(thoigian);
            time_game.loadFromRenderedText(g_font_text, g_manhinh);
            time_game.RenderText(g_manhinh, DORONG_MANHINH - 300, 30);
        }

        // hien thi diem so
        std::string diemso_ = std::to_string(diemsogame);
        std::string textdiemso("DIEM SO:");
        textdiemso += diemso_;

        diemso.SetText(textdiemso);
        diemso.loadFromRenderedText(g_font_text, g_manhinh);
        diemso.RenderText(g_manhinh, DORONG_MANHINH - 500, 30);

        // hien thi sinh menh
        std::string sinhmenhnhanvat = std::to_string(sinhmenhnv);
        std::string textsinhmenh("SINH MENH:");
        textsinhmenh += sinhmenhnhanvat;

        diemso.SetText(textsinhmenh);
        diemso.loadFromRenderedText(g_font_text, g_manhinh);
        diemso.RenderText(g_manhinh, DORONG_MANHINH - 800, 30);
        
        
        // cập nhật lại màn hình
        SDL_RenderPresent(g_manhinh);


        // xác định thời gian đã trôi qua tức thời gian thực
        int realtime = fps.get_thoigian();

        // thời gian chạy 1 frame
        int thoigian_frame = 1000 / FPS; // tức là chạy 25 khung hình trong 1 giây, 1s = 1000ms 

        // kiểm tra thời gian chạy của 1 frame với thơi gian thực để tạo delay thời gian cho các frame
        if (realtime < thoigian_frame)
        {
            SDL_Delay(thoigian_frame - realtime);
        }
    }

    for (int i = 0; i < CREP_list.size(); i++)
    {
        Crep* crep = CREP_list.at(i);
        crep->GiaiPhong();
        crep = NULL;
    }
    CREP_list.clear();

    dong_ctr();

    return 0;
}