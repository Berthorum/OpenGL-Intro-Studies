#version 330 core // Seta o profile e versão do OpenGL

// Define as entradas e saídas do shader de fragmento
in vec3 fragmentColor;

out vec4 screenColor;

void main(){
  screenColor = vec4(fragmentColor, 1.0);
}