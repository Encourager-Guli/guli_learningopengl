#include "VAO.h"

VAO::VAO(float* buffer, unsigned int buffer_size, const unsigned int layout[], unsigned int num_layouts)
{
    glGenVertexArrays(1, &VAOID);
    glGenBuffers(1, &VBOID);
    glBindVertexArray(VAOID);
    glBindBuffer(GL_ARRAY_BUFFER, VBOID);
    glBufferData(GL_ARRAY_BUFFER, buffer_size, buffer, GL_STATIC_DRAW);
    unsigned int offset = 0;//记录偏移量
    int one_size = 0;//计算一个顶点的数据大小
    for (int i = 0; i < num_layouts; i++)
    {
        one_size += layout[i];
    }
    
    for (unsigned int i = 0; i < num_layouts; i++)
    {
        
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, layout[i], GL_FLOAT, GL_FALSE, one_size*sizeof(float), (void*)(offset*sizeof(float)));
        offset += layout[i];
    }
    glBindVertexArray(0);
}

void VAO::bind()
{
    glBindVertexArray(VAOID);
}
