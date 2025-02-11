#include "Texture.h"
#include <glad/glad.h>
#include"stb_image.h"
#include<iostream>
Texture::Texture(const char * texture_path)
{
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    unsigned char* data = stbi_load(texture_path, &width, &height, &nrChannels, 0);
    unsigned int open_way;
    if (nrChannels == 3)
    {
        open_way = GL_RGB;
    }
    else if (nrChannels == 4)
    {
        open_way = GL_RGBA;
    }
    else
    {
        std::cout << "error :unknown channels!\n"<<nrChannels;
    }
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, open_way, width, height, 0, open_way, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
}

void Texture::Bind(unsigned int channel) const
{
    glActiveTexture(channel);
    glBindTexture(GL_TEXTURE_2D, ID);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

