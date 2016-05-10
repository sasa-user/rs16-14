#include "MapObject.h"

MapObject::MapObject(unsigned int id, SDL_Texture *texture, SDL_Rect SrcR)
    : m_id(id), m_texture(texture), m_SrcR(SrcR)
{

}

void MapObject::Draw(SDL_Renderer* renderer, const SDL_Rect *DestR)
{
    SDL_RenderCopy(renderer, m_texture, &m_SrcR, DestR);
}
