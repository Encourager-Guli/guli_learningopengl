#pragma once

class Texture
{
public:
	unsigned int ID;
	int width, height, nrChannels;


	Texture(const char* texture_path,unsigned int WARP_MODE);
	void Bind(unsigned int channel)const;
private:
};