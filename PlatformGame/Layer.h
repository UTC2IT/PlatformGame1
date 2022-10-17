#ifndef LAYER_H
#define LAYER_H

#include "TextureManager.h"

class Layer
{
private:

public:
	virtual void Render() = 0;
	virtual void Update() = 0;
};
#endif // !LAYER
