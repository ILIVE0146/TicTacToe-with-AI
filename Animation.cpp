#include "animation.hpp"
Animation::Animation(sf::Texture *texture, sf::Vector2u imageCount, float switchTime)
{
    this->imageCount = imageCount;
    this->switchTime = switchTime;
    uvRect.width = texture->getSize().x / float(imageCount.y);
    uvRect.height = texture->getSize().y / float(imageCount.y);
}
void Animation::update(int row, float deltaTime)
{
    currentImage.y = row;
    this->totalTime += deltaTime;
    if (this->totalTime >= this->switchTime)
    {
        this->totalTime -= this->switchTime;
        this->currentImage.x++;
        if (currentImage.x >= imageCount.x)
        {
            this->currentImage.x = 0;
        }
    }
    this->uvRect.left = this->currentImage.x * this->uvRect.width;
    this->uvRect.top = this->currentImage.y * this->uvRect.height;
}