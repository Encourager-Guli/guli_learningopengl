#pragma once

class myTexture
{
public:
	unsigned int ID;
	int width, height, nrChannels;


	myTexture(const char* texture_path);
	void Bind(unsigned int channel)const;
private:
};