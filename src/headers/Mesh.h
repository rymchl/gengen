#ifndef MESH
#define MESH

#include <Vertex.h>
#include <Texture.h>
#include <Shader.h>
#include <Tri.h>
#include <stb_image.h>

#include <vector>


class Mesh {
    public:
        // mesh data
        std::vector<Vertex>       vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture>      textures;

        int active_texture = -1;
        Mesh() {};
        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<std::string> texture_paths);
        void draw(Shader &shader);
        void draw(Shader &shader, glm::vec3 color);

        std::vector<Tri> getTris(){
            std::vector<glm::vec3*> tri_points;
            std::vector<Tri> tris;
            int i = 0;
            for(const unsigned int &index : indices){
                tri_points.push_back(&vertices[index].Position);
                i++;
                if(i % 3 == 0){
                    tris.push_back(Tri(tri_points[0],tri_points[1],tri_points[2]));
                    tri_points.clear();
                    i = 0;
                }

            }
            return tris;
        };

        Tri check_collision(Mesh* mesh);
    private:
        //  render data
        unsigned int VAO, VBO, EBO;
        

        void setupMesh();
};  


#endif