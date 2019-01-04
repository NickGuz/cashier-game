#include "Collider.h"

Collider::Collider()
{

}

Collider::~Collider()
{

}

void Collider::init(int w, int h, int x, int y)
{
    collider_rect = {w, h, x, y};
}

bool Collider::collides(SDL_Rect obj)
{
    if (collider_rect.x + (collider_rect.w) >= obj.x && collider_rect.x <= obj.x + (obj.w))
    {
        if (collider_rect.y + (collider_rect.h) >= obj.y && collider_rect.y <= obj.y + (obj.h))
        {
            return true;
        }
    }

    return false;
}

SDL_Rect Collider::getCollider()
{
    return collider_rect;
}