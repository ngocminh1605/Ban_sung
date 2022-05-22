#include "stdafx.h"
#include "BaseFunction.h"
#include "ThongSoInGame.h"

bool SDLBaseFunction::Checkvacham2Obj(const SDL_Rect& doituong1, const SDL_Rect& doituong2)
{
    int left_a = doituong1.x;
    int right_a = doituong1.x + doituong1.w;
    int top_a = doituong1.y;
    int bottom_a = doituong1.y + doituong1.h;

    int left_b = doituong2.x;
    int right_b = doituong2.x + doituong2.w;
    int top_b = doituong2.y;
    int bottom_b = doituong2.y + doituong2.h;

    // Case 1: 
    if (left_a > left_b && left_a < right_b)
    {
        if (top_a > top_b && top_a < bottom_b)
        {
            return true;
        }
    }

    if (left_a > left_b && left_a < right_b)
    {
        if (bottom_a > top_b && bottom_a < bottom_b)
        {
            return true;
        }
    }

    if (right_a > left_b && right_a < right_b)
    {
        if (top_a > top_b && top_a < bottom_b)
        {
            return true;
        }
    }

    if (right_a > left_b && right_a < right_b)
    {
        if (bottom_a > top_b && bottom_a < bottom_b)
        {
            return true;
        }
    }

    // Case 2: 
    if (left_b > left_a && left_b < right_a)
    {
        if (top_b > top_a && top_b < bottom_a)
        {
            return true;
        }
    }

    if (left_b > left_a && left_b < right_a)
    {
        if (bottom_b > top_a && bottom_b < bottom_a)
        {
            return true;
        }
    }

    if (right_b > left_a && right_b < right_a)
    {
        if (top_b > top_a && top_b < bottom_a)
        {
            return true;
        }
    }

    if (right_b > left_a && right_b < right_a)
    {
        if (bottom_b > top_a && bottom_b < bottom_a)
        {
            return true;
        }
    }

    // Case 3: 
    if (top_a == top_b && right_a == right_b && bottom_a == bottom_b)
    {
        return true;
    }

    return false;
}

