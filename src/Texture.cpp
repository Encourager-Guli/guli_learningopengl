#include "Texture.h"
Texture::Texture(const char * texture_path,unsigned int WARP_MODE, bool bit_16, bool HDR)
{
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, WARP_MODE);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, WARP_MODE);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    void* data = nullptr;
    if (HDR)
    {
        float* data_t= stbi_loadf(texture_path, &width, &height, &nrChannels, 0);
        data= static_cast<void*>(data_t);
    }
    else
    {
        unsigned char *data_t= stbi_load(texture_path, &width, &height, &nrChannels, 0);
        data = static_cast<void*>(data_t);
    }
        
    unsigned int open_way = GL_RGBA; 
    unsigned int store_way = GL_RGBA;
    if (bit_16)
    {
        switch (nrChannels)
        {
        case 1:
            open_way = GL_RED;
            store_way = GL_R16F;
            break;
        case 3:
            open_way = GL_RGB;
            store_way = GL_RGB16F;
            break;
        case 4:
            open_way = GL_RGBA;
            store_way = GL_RGBA16F;
            break;
        default:
        {
            std::cout << "error :unknown channels!\n" << nrChannels;
            break;
        }
            
        }
    }
    else
    {
        switch (nrChannels)
        {
        case 1:
            open_way = GL_RED;
            store_way = GL_RED;
            break;
        case 3:
            open_way = GL_RGB;
            store_way = GL_RGB;
            break;
        case 4:
            open_way = GL_RGBA;
            store_way = GL_RGBA;
        default:
        {
            std::cout << "error :unknown channels!\n" << nrChannels;
            break;
        }

        }
    }
    
    if (data)
    {
        if (HDR)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, store_way, width, height, 0, open_way, GL_FLOAT, static_cast<float*>(data));

        }
        else
        {
            glTexImage2D(GL_TEXTURE_2D, 0, store_way, width, height, 0, open_way, GL_UNSIGNED_BYTE, static_cast<unsigned char*>(data));

        }
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
    /*glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);*/
}

