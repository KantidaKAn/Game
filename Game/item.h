
#ifndef ITEM_H
#define ITEM_H

#include"Player.h"
class item
{
private:
	sf::Sprite itemsprite;
	sf::Texture itemtexture;

	sf::Vector2f itemposition;
	
	void inititemTexture();
	void inititemSprite();

	int types;

public:
	item(float pos_x, float pos_y,int type);
	virtual ~item();

	const sf::FloatRect getBounds() const;
	
	const int gettype() const;

	void updatemovement();
	void updated();
	void render(sf::RenderTarget& target);
};
#endif //!ITEM_H