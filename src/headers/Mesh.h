#ifndef MESH
#define MESH

#include <Vertex.h>
#include <Texture.h>
#include <Shader.h>

#include <vector>

class Mesh {
    public:
        // mesh data
        std::vector<Vertex>       vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture>      textures;

        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
        void draw(Shader &shader);
        void draw(Shader &shader, glm::vec3 color);
    private:
        //  render data
        unsigned int VAO, VBO, EBO;

        void setupMesh();
};  

#endif