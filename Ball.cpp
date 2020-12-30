
#include "Ball.hpp"
#include <iostream>

namespace APlusPlus{
    Ball::Ball(GameDataRef data): _data(data){
        _landHeight = this->_data->assets.GetTexture("Land").getSize().y;
        _ballSpawnYOffset = 10;
    }
    
    void Ball::SpawnBall()
    {
        sf::Sprite sprite(this->_data->assets.GetTexture("Ball"));
        sprite.setPosition(this->_data->window.getSize().x, _ballSpawnYOffset+50);
        ballSprites.push_back(sprite);
    }

    void Ball::MoveBall(float dt)
    {
        for(int i = 0; i < ballSprites.size(); i++)
        {
            if(ballSprites.at(i).getPosition().x < 0 - ballSprites.at(i).getLocalBounds().width)
            {
                ballSprites.erase(ballSprites.begin() + i);
            }
            else{
                movement = Ball::UpdateSpeed(_nowScore) * dt;
                ballSprites.at(i).move(-movement,0);
            }
        }
    }

    void Ball::DrawBall(){
        for(unsigned short int i = 0; i < ballSprites.size(); i++)
        {
            this->_data->window.draw(ballSprites.at(i));
        }
        
    }

    void Ball::RandomiseBallOffset(){
        _ballSpawnYOffset = rand() % _landHeight;
    }

    const std::vector<sf::Sprite>& Ball::GetSprites() const
    {
        return ballSprites;
    }

    void Ball::ballErase(int i){
        ballSprites.erase(ballSprites.begin()+i);
    }


    int Ball::UpdateSpeed(int _nowScore) const
    {
        float PIPEMOVEMENT = PIPE_MOVEMENT_SPEED;
        if( FIRST_THRESHOLD <= _nowScore && _nowScore < SECOND_THRESHOLD )
        {
            PIPEMOVEMENT += 100;
        }
        else if(SECOND_THRESHOLD <= _nowScore && _nowScore < THIRD_THRESHOLD )
        {
            PIPEMOVEMENT += 200;
        }
        else if(THIRD_THRESHOLD <= _nowScore )
        {
            PIPEMOVEMENT += 300;
        }
        return PIPEMOVEMENT;
    }
    
    void Ball::UpdateScore(int score) {
        _nowScore = score;
    }
        
}
