#ifndef MESH
#define MESH

#include <Vertex.h>
#include <Texture.h>
#include <Shader.h>

#include <sstream>
#include <vector>

 class Tri{
    public:
        glm::vec3* a;
        glm::vec3* b;
        glm::vec3* c;

        Tri(glm::vec3* a_in, glm::vec3* b_in, glm::vec3* c_in) {  
            a = a_in;
            b = b_in;
            c = c_in;
        }


        bool check_collision(const Tri* B) const{
            //TA1
            if(seperates(*a,*b,c,B)) return false; 
            //TA2
            if(seperates(*b,*c,a,B)) return false;
            //TA3
            if(seperates(*c,*a,b,B)) return false;

            //TB1
            if(seperates(*B->a,*B->b,B->c,this)) return false;
            //TB2
            if(seperates(*B->b,*B->c,B->a,this)) return false;
            //TB3
            if(seperates(*B->c,*B->a,B->c,this)) return false;

            return true;
        }

        std::string toString() const{
            std::stringstream ss;
            ss << "<" << a->x << "," << a->y << ">" << "<" << b->x << "," << b->y << ">" << "<" << c->x << "," << c->y << ">";
            return ss.str();
            
        }

        private:
            bool sign(const float& a) const{
                if(a > 0) return 1;
                if(a < 0) return -1;
                return 0;
            }

            glm::vec2 toVec2(const glm::vec3& v) const{
                return glm::vec2(v.x,v.y);
            }

            bool sameside(const glm::vec3* p1, const glm::vec3* p2, const glm::vec3* a, const glm::vec3* b) const{
                glm::vec3 cp1 = glm::cross(*b-*a, *p1-*a);
                glm::vec3 cp2 = glm::cross(*b-*a, *p2-*a);
                return (glm::dot(cp1, cp2) >= 0);
            }

            bool seperates(const glm::vec3& A, const glm::vec3& B, const glm::vec3* point, const Tri* tri) const{
                return (!sameside(point,tri->a,&A,&B)
                     && !sameside(point,tri->b,&A,&B)
                     && !sameside(point,tri->c,&A,&B));
            }
};

class Mesh {
    public:
        // mesh data
        std::vector<Vertex>       vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture>      textures;

        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
        void draw(Shader &shader);
        void draw(Shader &shader, glm::vec3 color);

        //returns direction of collision or 0vec if none
        bool check_collision(Mesh* mesh);
    private:
        //  render data
        unsigned int VAO, VBO, EBO;

        void setupMesh();
};  

#endif