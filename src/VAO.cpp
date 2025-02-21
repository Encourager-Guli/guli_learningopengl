#include "VAO.h"
#include <glm.hpp>
#include<iostream>
VAO::VAO(float* buffer, unsigned int buffer_size, const unsigned int layout[], unsigned int num_layouts)
{
    this->buffer = buffer;
    this->buffer_size = buffer_size;
    this->num_layouts = num_layouts;
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
    this->one_size = one_size;
    for (unsigned int i = 0; i < num_layouts; i++)
    {
        
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, layout[i], GL_FLOAT, GL_FALSE, one_size*sizeof(float), (void*)(offset*sizeof(float)));
        offset += layout[i];
    }
    glBindVertexArray(0);
}

void VAO::add_TBN()
{
    //遍历整个顶点数据，每次获取三个顶点，计算他们的tbn，为着色器输入tbn向量
    //需要新生成一块缓冲，还需要绑定原VAO
    unsigned int num_v = buffer_size / (one_size * sizeof(float));
    vector<float> tb;

    vector<glm::vec3> pos;//位置
    vector<glm::vec2> uv;//材质
    for (int i = 0; i < num_v; i++)//遍历每一个顶点
    {
        //std::cout << buffer[i * one_size] << ' ' << buffer[i * one_size + 1] << ' ' << buffer[i * one_size + 2] << ' ' << buffer[i * one_size + 6] << buffer[i * one_size + 7] << '\n';
        pos.push_back(glm::vec3(buffer[i*one_size], buffer[i * one_size+1], buffer[i * one_size+2]));
        uv.push_back(glm::vec2(buffer[i * one_size+6], buffer[i * one_size + 7]));
        if (i % 3 == 2)//三个顶点构成一个三角形
        {
            glm::vec3 edge1 = pos[1] - pos[0];
            glm::vec3 edge2 = pos[2] - pos[0];
            glm::vec2 deltaUV1 = uv[1] - uv[0];
            glm::vec2 deltaUV2 = uv[2] - uv[0];

            GLfloat f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);
            glm::vec3 tangent1, bitangent1;
            tangent1.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
            tangent1.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
            tangent1.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
            tangent1 = glm::normalize(tangent1);

            bitangent1.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
            bitangent1.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
            bitangent1.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
            bitangent1 = glm::normalize(bitangent1);

            for (int j = 0; j < 3; j++)//填补三顶点数据
            {
                tb.push_back(tangent1.x);
                tb.push_back(tangent1.y);
                tb.push_back(tangent1.z);
                tb.push_back(bitangent1.x);
                tb.push_back(bitangent1.y);
                tb.push_back(bitangent1.z);

            }
            pos.clear();
            uv.clear();
        }

        
    }
    unsigned int tb_VBO;
    glBindVertexArray(VAOID);
    glGenBuffers(1, &tb_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, tb_VBO);
    glBufferData(GL_ARRAY_BUFFER, tb.size()*sizeof(float), tb.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(num_layouts);
    glVertexAttribPointer(num_layouts,3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(num_layouts+1);
    glVertexAttribPointer(num_layouts+1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glBindVertexArray(0);


}

void VAO::bind()
{
    glBindVertexArray(VAOID);
}


