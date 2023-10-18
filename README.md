# Estudos Introdutórios sobre OpenGL

Repositório dedicado aos estudos introdutórios sobre OpenGL, a partir da playlist [OpenGL with C++](https://youtube.com/playlist?list=PLn3eTxaOtL2PHxN8EHf-ktAcN-sGETKfw&si=xTs74DpAEFQs4vYK) do canal no Youtube [GetIntoGameDev](https://www.youtube.com/@GetIntoGameDev) e alguns artigos contidos no site [Learn OpenGL](https://learnopengl.com/)


#####Observações:
Os estudos estão sendo realizados utilizando o VSCode como editor de código e as extensões [CMake](https://marketplace.visualstudio.com/items?itemName=twxs.cmake) e  [CMakeTools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools) para build do projeto. Portanto é necessário configurar o projeto com essas extensões para realizar o build e execução.

Para usuários do Sistema Operacional Windows, ao realizar o primeiro build do projeto é necessário inserir manualmente o arquivo glfw.lib, contido dentro da pasta "glfwLibForWindowsBuild" do projeto, na pasta build gerada, pois o programa é executado dentro do contexto dessa pasta.

Em caso de modificar a estrutura de organização de pastas do projeto, se atenha aos paths dos arquivos a serem carregados, como os shaders, por exemplo, justamente pelo contexto de execução do programa ser dentro da pasta build. Caso contrário, provavelmente ocorrerá erro de compilação ou link dos arquivos.

Os códigos estão sendo comentados, a partir das minhas observações, para auxiliar o entendimento das funcionalidades do OpenGL tanto para mim como para quem utilizar o projeto. Caso algum comentário ou definição esteja incorreta, fique a vontade para me informar :)