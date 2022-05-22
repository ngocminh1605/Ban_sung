#pragma once

//

#ifndef XULY_FPS_TIMER_H_
#define XULY_FPS_TIMER_H_

class Xuly_Fps_Timer
{
public:
	Xuly_Fps_Timer();
	~Xuly_Fps_Timer();

	// hàm đếm thời gian xử lý các nhiệm vụ chạy và dừng fps

	void batdau(); // start
	void ketthuc(); // stop
	void tamdung(); // paused
	void resume(); // unpaused

	// đếm thời gian = tick
	int get_thoigian(); // get_ticks

	bool batdau_(); // is_started()
	bool dung_(); // is_paused()


private:
	// thời điểm chạy
	int thoigian_batdau; // start_tick_;

	// thời điểm tạm dừng
	int thoigian_dung; // paused_tick_;

	bool dungnv; //is_paused
	bool batdaunv; // is_started



};






#endif // !XULY_FPS_TIMER_H_
