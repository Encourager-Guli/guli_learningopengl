#include "Lights.h"

Light::Light(std::string name, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
{
	this->name = name;
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
}

void Light::send(Shader shader)
{
	shader.setVec3((name + ".ambient").c_str(), ambient);
	shader.setVec3((name + ".diffuse").c_str(), diffuse);
	shader.setVec3((name + ".specular").c_str(), specular);
}

dirLight::dirLight(std::string name, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular,glm::vec3 direction)
	:Light(name,ambient,diffuse,specular)
{
	this->direction = direction;
}

void dirLight::send(Shader shader)
{
	Light::send(shader);
	shader.setVec3((name+".direction").c_str(), direction);
}

pointLight::pointLight(std::string name, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 position, float constant, float linear, float quadratic)
	:Light(name, ambient, diffuse, specular)
{
	this->linear = linear;
	this->position = position;
	this->constant = constant;
	this->quadratic = quadratic;
}

void pointLight::send(Shader shader)
{
	Light::send(shader);
	shader.setVec3((name +".position").c_str(), position);
	shader.setFloat((name+".constant").c_str(), constant);
	shader.setFloat((name+".linear").c_str(), linear);
	shader.setFloat((name+".quadratic").c_str(), quadratic);
}
