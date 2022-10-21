#include<Tri.h>


bool Tri::check_collision(const Tri* B) const{
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

std::string Tri::toString() const{
std::stringstream ss;
ss << "<" << a->x << "," << a->y << ">" << "<" << b->x << "," << b->y << ">" << "<" << c->x << "," << c->y << ">";
return ss.str();

}

bool Tri::sign(const float& a) const{
    if(a > 0) return 1;
    if(a < 0) return -1;
    return 0;
}

bool Tri::sameside(const glm::vec3* p1, const glm::vec3* p2, const glm::vec3* a, const glm::vec3* b) const{
    glm::vec3 cp1 = glm::cross(*b-*a, *p1-*a);
    glm::vec3 cp2 = glm::cross(*b-*a, *p2-*a);
    return (glm::dot(cp1, cp2) >= 0);
}

bool Tri::seperates(const glm::vec3& A, const glm::vec3& B, const glm::vec3* point, const Tri* tri) const{
    return (!sameside(point,tri->a,&A,&B)
            && !sameside(point,tri->b,&A,&B)
            && !sameside(point,tri->c,&A,&B));
}


 