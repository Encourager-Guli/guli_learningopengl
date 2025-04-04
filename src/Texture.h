#pragma once
#include <glad/glad.h>
#include"stb_image.h"
#include<iostream>
class Texture
{
public:
	unsigned int ID;
	int width, height, nrChannels;


	Texture(const char* texture_path,unsigned int WARP_MODE,bool bit_16=false,bool HDR=false);
	void Bind(unsigned int channel)const;
private:
};
