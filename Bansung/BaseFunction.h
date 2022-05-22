#ifndef BASE_FUNCTION_H_
#define BASE_FUNCTION_H_

#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>


// định nghĩa các biến
// stactic là biến dạng global
static SDL_Window* g_window = NULL; // là struct giữ tất cả các thông tin của cửa sổ mà chúng ta tạo ra như size, postion, border, fullscreen.
static SDL_Event g_sukien; // union chứa tất cả các thông tin của tất cả các event trong bộ thư viện ví dụ như từ bàn phím, chuột,..
static SDL_Renderer* g_manhinh = NULL; //  là struct xử lý tất cả các công việc rendering lên cửa sổ SDL_Window.

				

const int FPS = 25; // fps là frame per second, số khung hình frame trong một khoảng thời gian
const int DOCAO_MANHINH = 640; // Màn hình có độ cao cố định 640 pixel
const int DORONG_MANHINH = 1280; // Màn hình có độ rộng mặc định 1280 pixel
const int SCREEN_BPP = 32; // Bit per Pixel, 32 BPP = 4294967296 màu

// Khai báo màu sắc để transparent ( làm trong suốt ) nền các hình ảnh

const int Color_R = 167;
const int Color_G = 175;
const int Color_B = 180;


// bản đồ
#define KICHTHUOC_O_LUOI 64 // cả bản đồ được chia thành một dạng lưới gồm nhiều ô vuông với mỗi ô có kích thước 64x64

#define COT_X_MAX 400 // Số cột theo chiều dọc X tối đa là 400
#define HANG_Y_MAX 10 // Số hàng theo chiều ngang Y là 10. Bằng với chiều cao ban đầu khai báo 64x10 = 640 = DOCAO_MANHINH Với 400 cột và 10 hàng thì tổng ra có 4000 ô vuông kích thước 64 trên một bản dồ dạng lưới, mỗi một ô sẽ fill giá trị tương ứng bằng hình ảnh như mặt đất, tường, nhân vật hoặc đường đạn


// Tạo cấu trúc dữ liệu trạng thái, vị trí và chỉ số cho từng ô trong lưới
// dành cho phần bản đồ
typedef struct BanDo
{
	// vị trí của ô vuông
	int vitri_x; // start_x_
	int vitri_y; // start_y_

	// chỉ số 
	int chiso_x; // max_x_
	int chiso_y; // max_y_

	// mảng 2 chiều lưu toàn bộ chỉ cố và vị trí của tất cả các ô
	int viengach[HANG_Y_MAX][COT_X_MAX];

	// file lưu thông số

	char* file_;
};


// dành cho phần nhân vật
// khai báo một kiểu dữ liệu nhận các giá trị đầu vào từ bàn phím như lên xuống trái phải mục tiêu sử dụng để di chuyển nhân vật

typedef struct DauVaoDiChuyen
{
	int trai_;
	int phai_;
	int len_;
	int xuong_;
	int nhay_;
};

// kiểm tra va chạm giữa 2 đối tượng cần truyền vào tham số x,y,w,h của 2 đối tượng, đối tượng ở đây có thể là viên đạn có thể là
// nhân vật hoặc là crep
namespace SDLBaseFunction
{
	bool Checkvacham2Obj(const SDL_Rect& doituong1, const SDL_Rect& doituong2);
}



#endif // !BASE_FUNCTION_H_

