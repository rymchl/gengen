#ifndef TRI
#define TRI

#include <glm/glm.hpp>
#include <string>
#include <sstream>


 class Tri{
    public:
        glm::vec3* a;
        glm::vec3* b;
        glm::vec3* c;

        Tri(glm::vec3* a, glm::vec3* b, glm::vec3* c) : a(a), b(b), c(c) {}
        bool check_collision(const Tri* B) const;
        std::string toString() const;

        private:
            bool sign(const float& a) const;
            bool sameside(const glm::vec3* p1, const glm::vec3* p2, const glm::vec3* a, const glm::vec3* b) const;
            bool seperates(const glm::vec3& A, const glm::vec3& B, const glm::vec3* point, const Tri* tri) const;
};

 

#endif
