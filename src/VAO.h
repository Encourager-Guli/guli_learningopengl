#pragma once
#include<glad/glad.h>
#include<vector>
using namespace std;
class VAO {
public:
	float* buffer;
	unsigned int num_layouts;//布局具有的类型数,也是作为下一个添加的通道号
	unsigned int one_size;//单个顶点大小
	unsigned int VAOID,VBOID;
	unsigned int buffer_size;//数据缓冲的大小
	VAO(float* buffer, unsigned int buffer_size,  const unsigned int layout[], unsigned int num_layouts);
	void add_TBN();
	void bind();
};