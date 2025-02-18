#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec2 aOffset;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;

uniform mat4 model;
layout (std140) uniform Matrices
{
    mat4 projection;
    mat4 view;
};
void main()
{
    gl_Position = projection * view * model * vec4(aPos + vec3(aOffset.x,0,aOffset.y), 1.0);
    FragPos=aPos;
    Normal = mat3(transpose(inverse(model))) * aNormal; 
    TexCoords=aTexCoords;
}