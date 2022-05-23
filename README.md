# Ban_sung
I> Cách lấy chương trình về :

. git clone https://github.com/ngocminh1605/Ban_sung.git

. Hoặc download zip và giải nén

(Nếu chưa có MinGW) Tải MinGW Installer https://sourceforge.net/projects/mingw/. Cài đặt MinGW Installer theo mặc định, đến bước hiện ra các package cài đặt image

Tick chọn mingw32-base và mingw32-gcc-g++, ấn vào Installation -> Apply Changes. Sau khi cài xong, vào thư mục mingw vừa cài đặt, vào bin và copy đường dẫn (VD:

C:\MinGW\bin) Add đường dẫn vào PATH trong system variables của environment .

. Vào mục Debug chọn Bansung.exe

* Nếu muốn chạy trong IDE Visual Studio Code :
* 
          + Ấn chuột phải vào project bắn súng rồi chọn properties: 
          + 
              . Vào mục VC++ Directories : 
              
                            Chọn Include Directories : add các đường link 
                            
                                   + $(SolutionDir)LibSdl2\SDL2-2.0.8\include
                                   + 
                                   + $(SolutionDir)LibSdl2\SDL2_image-2.0.3\include
                                   + 
                                   + $(SolutionDir)LibSdl2\SDL2_mixer-2.0.2\include
                                   + 
                                   + $(SolutionDir)LibSdl2\SDL2_ttf-2.0.14\include
                                   + 
                             Chọn Library Directories : add các đường link
                             
                                   + $(SolutionDir)LibSdl2\SDL2_ttf-2.0.14\lib\x86
                                   + 
                                   + $(SolutionDir)LibSdl2\SDL2_image-2.0.3\lib\x86
                                   + 
                                   + $(SolutionDir)LibSdl2\SDL2_mixer-2.0.2\lib\x86
                                   
                                   + $(SolutionDir)LibSdl2\SDL2-2.0.8\lib\x86
                                   
              .Vào mục Linker chọn Input điền :         SDL2.lib
              
                                                        SDL2main.lib
                                                        
                                                        SDL2_image.lib
                                                        
                                                        SDL2_mixer.lib
                                                        
                                                        SDL2_ttf.lib
             

II> Mô tả chung về trò chơi :

Tóm tắt:

Di chuyển nhân vật vượt chướng ngại vật và bắn phi tiêu hủy diệt quái. Phải di chuyển đến cuối bản đồ trong vòng 10p và tiêu diệt hết quái là thắng.

Chức năng :

. Di chuyển nhân vật bằng các nút :

       + A : sang trái
       
       + D : sang phải
       
       + S : nhảy lên
       
       + chuột trái : bắn phi tiêu
       
. Ăn nấm để có thể tăng thêm sinh mạng

. Bắn quái tăng điểm số (mỗi con 1 điểm)

Các kỹ thuật được sử dụng trong game : vector, con trỏ và các tham trị, tham chiếu, lớp (cấu trúc), 4 thư viện SDL2 như đã đề cập, ...

Hướng phát triển : cải tiến thêm nhiều chức năng : tạo thêm máu cho quái,tăng lv nhân vật, có thêm nhạc , thêm số lượng băng đạn,  mở rộng bản đồ hơn, đổi nhân vật,
đổi đạn, nâng cấp đạn ,....

Kết luận : Lập trình game giúp bản thân làm quen dần với lập trình hướng đối tượng, nâng cao kỹ năng code, biết cách quản lý các chức năng trong game,...

Điều tâm đắc rút ra khi hoàn thiện game : Xử lý gần hết được những chức năng mà mình đã đặt ra cho game. 


       
  


