#pragma once
#include<glad/glad.h>
#include<vector>
using namespace std;
class VAO {
public:
	unsigned int num_layouts;
	unsigned int VAOID,VBOID;
	VAO(float* buffer, unsigned int buffer_size,  const unsigned int layout[], unsigned int num_layouts);
	void bind();
};