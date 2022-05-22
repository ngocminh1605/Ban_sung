#pragma once
#ifndef THONGSO_INGAME_H_
#define THONGSO_INGAME_H_
#include "stdafx.h"
#include "BaseFunction.h"

class ThongSoInGame
{
public:
    ThongSoInGame(void);
    ~ThongSoInGame(void);

    enum TextColor
    {
        RED_TEXT = 0,
        WHITE_TEXT = 1,
        BLACK_TEXT = 2,
    };

    bool LoadFileText(std::string duongdan);
    bool loadFromRenderedText(TTF_Font* font, SDL_Renderer* manhinh);
    void GiaiPhong();

    void setColor(Uint8 red, Uint8 green, Uint8 blue);
    void setColor(int kieumau);

    // angle goc nghien
    void RenderText(SDL_Renderer* manhinh, 
                    int x, int y, 
                    SDL_Rect* clip = NULL, 
                    double angle = 0.0,
                    SDL_Point* center = NULL, 
                    SDL_RendererFlip flip = SDL_FLIP_NONE);




    int layChieuRong() const { return w; }
    int layChieuCao() const { return h; }
    void SetText(const std::string& text) { noidung = text; }
    std::string LayNoiDung() const { return noidung; }

private:
    std::string noidung;
    SDL_Color colortext;
    SDL_Texture* texture_;
    int w;
    int h;

};

#endif