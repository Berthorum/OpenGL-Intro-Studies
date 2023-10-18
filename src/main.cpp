#include "config.hpp"
#include "triangleMesh.hpp"

unsigned int makeShader(const std::string& vertexFilePath, const std::string& fragmentFilePath);
unsigned int makeModule(const std::string& filePath, unsigned int moduleType);

int main() {

	GLFWwindow* window;

	if (!glfwInit()) { // Inicializa as funções do GLFW
		std::cout << "GLFW couldn't start" << std::endl;
		return -1;
	}

	window = glfwCreateWindow(640, 480, "Hello Window!", NULL, NULL); // Cria uma Janela.
	glfwMakeContextCurrent(window); // Adiciona a Janela no Contexto para uso do OpenGL

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) { // Carrega as funções do OpenGL
		std::cout << "Couldn't load opengl" << std::endl;
		glfwTerminate(); // Finaliza a Janela
		return -1;
	}

	glClearColor(0.25f, 0.5f, 0.75f, 1.0f); // Adiciona a cor especificada na variável de color buffer
	
	int w, h;

	// Seta as variáveis w e h com a largura e altura definida na criação da janela
	glfwGetFramebufferSize(window, &w, &h);

	// Cria uma viewport a partir da origem 0,0 (bottom left) com a largura e altura contidas em w e h
	glViewport(0, 0, w, h);

	TriangleMesh* triangle = new TriangleMesh();

	unsigned int shader = makeShader(
		"../../src/shaders/vertex.glsl",
		"../../src/shaders/fragment.glsl"
	);

	while (!glfwWindowShouldClose(window)) { // Checa se o usuário fechou a janela
		glfwPollEvents(); // Adiciona os eventos dentro da janela no pool stack

		glClear(GL_COLOR_BUFFER_BIT); // Limpa a tela com a cor contida na constante
		glUseProgram(shader);
		
		// Desenha a geometria dentro da janela criada e da respectiva viewport
		triangle->draw();
		glfwSwapBuffers(window); // Realiza o swap no Sistema de Double Buffers
	}

	glDeleteProgram(shader);
	delete triangle;
	glfwTerminate();

	return 0;
}

unsigned int makeShader(const std::string& vertexFilePath, const std::string& fragmentFilePath){
	// Vetor dinâmico que recebe os módulos (shaders especificados compilados)
	std::vector<unsigned int> modules;
	modules.push_back(makeModule(vertexFilePath, GL_VERTEX_SHADER));
	modules.push_back(makeModule(fragmentFilePath, GL_FRAGMENT_SHADER));

	// Cria a estrutura de um shader (programa)
	unsigned int shader = glCreateProgram();

	// Anexa cada shader especificado a estrutura do shader (programa)
	for(unsigned int shaderModule : modules){
		glAttachShader(shader, shaderModule);
	}

	// Processo de linkagem dos shaders especificados no programa
	glLinkProgram(shader);


	// Checagem se a linkagem foi realizada com sucesso
	int successShaderLink;
	glGetProgramiv(shader, GL_LINK_STATUS, &successShaderLink);

	if(!successShaderLink){
		char errorLog[1024];
		glGetProgramInfoLog(shader, 1024, NULL, errorLog);
		std::cout << "Shader Linking error:\n" << errorLog << std::endl;
	}


	// Remoção dos shaders compilados da memória após linkagem bem sucedida.
	for(unsigned int shaderModule : modules){
		glDeleteShader(shaderModule);
	}

	return shader;
}

unsigned int makeModule(const std::string& filePath, unsigned int moduleType){
	// Inicialização de variáveis para manipulação do arquivo que contém a implementação do shader especificado
	std::ifstream file;
	std::stringstream bufferedLines;
	std::string line;

	file.open(filePath);

	if(!file.is_open()){
		std::cout << "Cannot open File" << std::endl;
		exit(1);
	}

	// Leitura das linhas do arquivo
	while(std::getline(file, line)){
		bufferedLines << line << std::endl;
	}


	// Transformação do arquivo em uma unica string
	std::string shaderSource = bufferedLines.str();
	const char* shaderSrc = shaderSource.c_str();
	bufferedLines.str("");
	file.close();

	// Criação, anexo e compilação do shader especificado
	unsigned int shaderModule = glCreateShader(moduleType);
	glShaderSource(shaderModule, 1, &shaderSrc, NULL);
	glCompileShader(shaderModule);

	// Checagem se a compilação foi realizada com sucesso
	int successShaderCompile;
	glGetShaderiv(shaderModule, GL_COMPILE_STATUS, &successShaderCompile);

	if(!successShaderCompile){
		char errorLog[1024];
		glGetShaderInfoLog(shaderModule, 1024, NULL, errorLog);
		std::cout << "Shader Module compilation Error\n" << errorLog << std::endl;
	}

	return shaderModule;


}