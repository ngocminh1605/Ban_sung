# Ban_sung
I> Cách lấy chương trình về :

Cách 1 :

. git clone https://github.com/ngocminh1605/Ban_sung.git

. Hoặc download zip và giải nén

. Vào mục Debug chọn RUN.exe

Cách 2 :
* Nếu muốn chạy trong Visual Studio Code 2022 :

          + Ấn chuột phải vào project bắn súng rồi chọn properties: 
               . Vào mục VC++ Directories : 
                             Chọn Include Directories : add các đường link 
                                   + $(SolutionDir)include
                                   + $(SolutionDir)SDL2_image-2.0.3\include
                                   + $(SolutionDir)SDL2_mixer-2.0.2\include 
                                   + $(SolutionDir)SDL2_ttf-2.0.14\include
                             Chọn Library Directories : add các đường link
                                   + $(SolutionDir)SDL2_ttf-2.0.14\lib\x86
                                   + $(SolutionDir)SDL2_image-2.0.3\lib\x86 
                                   + $(SolutionDir)SDL2_mixer-2.0.2\lib\x86
                                   + $(SolutionDir)lib\x86
                                   
              .Vào mục Linker chọn Input điền :SDL2.lib
                                               SDL2main.lib
                                               SDL2_image.lib
                                               SDL2_mixer.lib
                                               SDL2_ttf.lib
             
II> Link youtube mô tả : https://www.youtube.com/watch?v=ex95Zp58tLg

III> Mô tả chung về trò chơi :

1.Tóm tắt:

Di chuyển nhân vật vượt chướng ngại vật né tránh những viên đạn được bắn ra từ quái và bắn phi tiêu hủy diệt quái. Phải di chuyển đến cuối bản đồ trong vòng 10p và tiêu diệt hết các quái vật.Nhân vật ban đầu được khởi tạo 1 sinh mạng, trong quá trình chơi khi ăn nấm sẽ được cộng thêm 1 điểm sinh mạng,trái lại khi rớt xuống vực, bị trúng đạn do quái bắn ra, hay đụng trúng người quái thì sẽ bị trừ 1 điểm sinh mạng. Khi nào điểm sinh mạng về không thì nhân vật sẽ chết trò chơi kết thúc. 

2.Chức năng :

. Di chuyển nhân vật bằng các nút :

       + A : sang trái
       
       + D : sang phải
       
       + W : nhảy lên
       
       + Chuột trái : bắn phi tiêu
       
. Ăn nấm để có thể tăng thêm sinh mạng (khi nào sinh mạng về 0 thì sẽ thua)

. Bắn quái tăng điểm số (mỗi con 1 điểm)

. Thời gian sẽ đếm ngược trong vòng 10p

. Quái biết phun lửa để tấn công người chơi


IV >Các kỹ thuật được sử dụng trong game : 
+ vector (để quản lý những biến như quái ,viên đạn)
+ con trỏ và các tham trị, tham chiếu
+ lớp (cấu trúc) (quản lý các đối tượng như nhân vật,quái,...)
+ 4 thư viện SDL2 <SDL2_image-2.0.3,SDL2_mixer-2.0.2,SDL2_mixer-2.0.2,SDL2 2.0.8>, ...
* Ngoài ra còn dùng các công cụ hỗ trợ như : photoshop để edit ảnh và tiled để edit map

V >Hướng phát triển : Game còn có thể cải tiến thêm nhiều chức năng như là tạo thêm máu cho quái,tăng lv nhân vật, thêm số lượng băng đạn hạn định,  mở rộng bản đồ hơn, đổi nhân vật, đổi đạn, nâng cấp đạn ,....

VI >Kết luận : Lập trình game giúp bản thân làm quen dần với lập trình hướng đối tượng, nâng cao kỹ năng code, biết cách cấu trúc chia file trong một chương trình,

VII >Điều tâm đắc rút ra khi hoàn thiện game : Xử lý gần hết được những chức năng mà mình đã đặt ra cho game , biết cách tách 1 chương trình lớn thành nhiều file để dễ dàng quản lý 


       
  


