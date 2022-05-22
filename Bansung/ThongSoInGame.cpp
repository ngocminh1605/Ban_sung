#include "stdafx.h"
#include "ThongSoInGame.h"

ThongSoInGame::ThongSoInGame(void)
{
    colortext.r = 255;
    colortext.g = 255;
    colortext.b = 255;
}


ThongSoInGame::~ThongSoInGame(void)
{
}


bool ThongSoInGame::loadFromRenderedText(TTF_Font* font, SDL_Renderer* manhinh)
{
    // xuat ra man hinh text
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, noidung.c_str(), colortext);
    if (textSurface != NULL)
    {
        texture_ = SDL_CreateTextureFromSurface(manhinh, textSurface);
        if (texture_ != NULL)
        {
            //nhan vao kich thuoc cua khung text
            w = textSurface->w;
            h = textSurface->h;
        }

        //loai bo lop text cu
        SDL_FreeSurface(textSurface);
    }

    //tra ve gia tri dung
    return texture_ != NULL;
}

void ThongSoInGame::GiaiPhong()
{
    if (texture_ != NULL)
    {
        SDL_DestroyTexture(texture_);
        texture_ = NULL;
    }
}

void ThongSoInGame::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
    colortext.r = red;
    colortext.g = green;
    colortext.b = blue;
}

void ThongSoInGame::setColor(int type)
{
    if (type == RED_TEXT)
    {
        SDL_Color color = { 255, 0, 0 };
        colortext = color;
    }
    else if (type == WHITE_TEXT)
    {
        SDL_Color color = { 255, 255, 255 };
        colortext = color;
    }
    else
    {
        SDL_Color color = { 0, 0, 0 };
        colortext = color;
    }
}
void ThongSoInGame::RenderText(SDL_Renderer* screen, int x, int y, SDL_Rect* clip /* = NULL */, double angle /* = 0.0 */, SDL_Point* center /* = NULL */, SDL_RendererFlip flip /* = SDL_FLIP_NONE */)
{
    //Set rendering space and render to screen
    SDL_Rect renderQuad = { x, y, w, h };

    //Set clip rendering dimensions
    if (clip != NULL)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    //Render to screen
    SDL_RenderCopyEx(screen, texture_, clip, &renderQuad, angle, center, flip);
}
