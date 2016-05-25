#include "Entity/EnemyThree.h"
#include "Constants/TextureEnemyConstants.h"
#include "Manager/PlayerManager.h"
#include "cmath"
#include <iostream>

EnemyThree::EnemyThree(SDL_Texture* tex, unsigned int tile_size, unsigned int val_x, unsigned int val_y)
: Enemy(tex, tile_size, val_x, val_y)
{
    m_speed = 100; //timer speed
    m_move_speed = m_move_speed *m_tile_size/32; //speed according to 32px tile size

    m_rotation_const = 7;
    m_enemy_size_w = TEXTURE_ENEMY_THREE_SIZE_W *tile_size/32;
    m_enemy_size_h = TEXTURE_ENEMY_THREE_SIZE_H *tile_size/32; //size according to 32px tile size
}

void EnemyThree::Draw(SDL_Renderer* renderer)
{
    SDL_Rect SrcR;
    SDL_Rect DestR;

    SrcR.y = TEXTURE_ENEMY_THREE_Y;
    SrcR.w = TEXTURE_ENEMY_THREE_SOURCE_W;
    SrcR.h = TEXTURE_ENEMY_THREE_SOURCE_H;

    if(m_status % m_rotation_const == 0)
    {
        SrcR.x = TEXTURE_ENEMY_THREE_X;
    }
    if(m_status % m_rotation_const == 1)
    {
        SrcR.x = TEXTURE_ENEMY_THREE_X + TEXTURE_ENEMY_THREE_TEXTURE_OFFSET;
    }
    if(m_status % m_rotation_const == 2)
    {
        SrcR.x = TEXTURE_ENEMY_THREE_X + 2*TEXTURE_ENEMY_THREE_TEXTURE_OFFSET;
    }
    if(m_status % m_rotation_const == 3)
    {
        SrcR.x = TEXTURE_ENEMY_THREE_X + 3*TEXTURE_ENEMY_THREE_TEXTURE_OFFSET;
    }
    if(m_status % m_rotation_const == 4)
    {
        SrcR.x = TEXTURE_ENEMY_THREE_X + 4*TEXTURE_ENEMY_THREE_TEXTURE_OFFSET;
    }
    if(m_status % m_rotation_const == 5)
    {
        SrcR.x = TEXTURE_ENEMY_THREE_X + 5*TEXTURE_ENEMY_THREE_TEXTURE_OFFSET;
    }
    if(m_status % m_rotation_const == 6)
    {
        SrcR.x = TEXTURE_ENEMY_THREE_X + 6*TEXTURE_ENEMY_THREE_TEXTURE_OFFSET;
    }

    DestR.x = m_x;
    DestR.y = m_y;
    DestR.w = m_enemy_size_w;
    DestR.h = m_enemy_size_h;

    SDL_RenderCopy(renderer, m_tex, &SrcR, &DestR);
}

void EnemyThree::Update(Relay *relay, Player *player)
{
    unsigned int player_x = player->GetX();
    unsigned int player_y = player->GetY();
    unsigned int player_w = player->GetSizeW();
    unsigned int player_h = player->GetSizeH();

    //Setting coordinates for better collision
    player_x = player_x + m_tile_size/6;
    player_y = player_y + m_tile_size/6;
    player_w = player_w - m_tile_size/3;
    player_h = player_h - m_tile_size/4;
    //----------------------------------------

    if(Touch(player_x, player_y))
    {
        player->SetHealth(0);
    }
    else if(Touch(player_x+player_w, player_y))
        {
            player->SetHealth(0);
        }
        else if(Touch(player_x, player_y+player_h))
            {
                player->SetHealth(0);
            }
            else if(Touch(player_x+player_w, player_y+player_h))
                {
                    player->SetHealth(0);
                }

    EnemyThreeDirection(relay);
    std::cout<< "UPDATE!!!"<< std::endl;
}

void EnemyThree::EnemyThreeDirection(Relay *relay)
{
    unsigned int player_min = UINT_MAX; // closest player
    Player * p = nullptr;
    int x, y;

    for(auto it = relay->GetPlayerManager()->GetPlayers()->begin(); it != relay->GetPlayerManager()->GetPlayers()->end(); it++)
    {
        x = m_x - (*it)->GetX();
        y = m_y - (*it)->GetY();
        if(player_min > sqrt(x*x + y*y))
        {
            player_min = sqrt(x*x + y*y);//abs(m_x - (*it)->GetX() ) + abs(m_y - (*it)->GetY() );
            p = *it;
        }
    }

    if(player_min <= 2*m_tile_size)
        m_chase = true;
    else
        m_chase = false;

    if(m_chase)
    {
        ChasePlayer(p);
    }
    else
    {
        std::cout<< "Usao u Random!!!"<< std::endl;
        int r;

        if(m_walk_len <= 0)
        {

            m_walk_len = rand()%5 + 10;
            r = rand()%4;
            switch(r)
            {
                case 0:
                    m_direction = LEFT;
                    break;
                case 1:
                    m_direction = RIGHT;
                    break;
                case 2:
                    m_direction = UP;
                    break;
                case 3:
                    m_direction = DOWN;
                    break;
                default:
                    m_direction = DOWN;
            }
        }
    }
    if(m_timer.GetTimeElapsed() > m_speed)
    {
        m_walk_len--;
        this->EnemyMove(relay);
        m_timer.ResetTimer();
    }
}

void EnemyThree::ChasePlayer(Player * player)
{
    std::cout<< "Usao u ChasePlayer!!!"<< std::endl;
    if( abs((int)m_x - (int)player->GetX()) > abs((int)m_y - (int)player->GetY()) )
    {
        std::cout << m_x - player->GetX() << std::endl;
        if(m_x > player->GetX())
            {m_direction = LEFT;std::cout<< "Usao u LEFT!!!"<< std::endl;}
        else
            {m_direction = RIGHT;std::cout<< "Usao u RIGH!!!"<< std::endl;}
    }
    else
    {
        std::cout << m_y - player->GetY() << std::endl;
        if(m_y > player->GetY())
            {m_direction = UP; std::cout<< "Usao u UP!!!"<< std::endl;}
        else
            {m_direction = DOWN;std::cout<< "Usao u DOWN!!!"<< std::endl;}
    }

}




