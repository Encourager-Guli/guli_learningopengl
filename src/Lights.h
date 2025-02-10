#pragma once
#include <glm.hpp>
#include"Shader.h"
class Light {
public:
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    std::string name;
    Light(std::string name, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);
    void send(Shader shader);
};
class dirLight : public Light {
public:
    glm::vec3 direction;
    dirLight(std::string name, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 direction);
    void send(Shader shader);
};

class pointLight :public Light {
public:
    glm::vec3 position;
    float constant;
    float linear;
    float quadratic;
    pointLight(std::string name, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 position, float constant, float linear, float quadratic);
    void send(Shader shader);
};