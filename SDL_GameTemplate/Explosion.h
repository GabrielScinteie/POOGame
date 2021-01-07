#pragma once
#include "GameObject.h"

class Explosion : public GameObject
{
protected:
	int** fire;
	int lungime, latime;
	 unsigned int** firetime;//firetime[x][y] = cand s-a aprins focul in regiunea [x][y]
public:
	int** getfire() { return fire; }
	unsigned int** getfiretime() { return firetime; }	
	void setfire(int x, int y);
	void stopfire(int x, int y);

	int getlg() { return lungime; }
	int getlt() { return latime; }
	void Render() {}


	Explosion(const char* textureSheet, SDL_Renderer* renderer, int x, int y);
	~Explosion();
	void Draw(SDL_Rect camera);
};