#include "triangleMesh.hpp"

TriangleMesh::TriangleMesh() {
    
    /* 
        Valores das coordenadas normalizadas (-1 e 1 os extremos, 0 o meio)
        Os três primeiros valores de cada linha são as coordenadas do ponto, 
        os outros três valores são relacionados as cores (RGB) do ponto.

        Cada linha equivale a um vertex.
    */
    std::vector<float> data = {
        -1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
         1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,

        -1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,  0.0f, 1.0f, 0.0f
    };
    vertex_count = 6;

    // Cria os Vertex Arrays e armazena sua estrutura na variável VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Cria buffers e armazena esse endereço na variavel VBO
    glGenBuffers(1, &VBO);

    // Realiza o binding do conteúdo da variavel VBO para GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    // Envia os dados do GL_ARRAY_BUFFER, alocando o espaço de memória baseado no tamanho dos vértices.
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);

    //Informa para GPU qual parte do vértice representa o atributo de posição do ponto e o habilita
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 24, (void*)0);
    glEnableVertexAttribArray(0);

   //Informa para GPU qual parte do vértice representa o atributo de cor do ponto e o habilita
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 24, (void*)12);
    glEnableVertexAttribArray(1);

}

void TriangleMesh::draw() {
    // Realiza o bind dos dados do VBO e seus atributos na variável VAO
    glBindVertexArray(VAO);

    // Desenha a geometria baseado nos dados contidos no VAO.
    glDrawArrays(GL_TRIANGLES, 0, vertex_count);
}

TriangleMesh::~TriangleMesh() {
    // Deleta o VBO e VAO construidos
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}