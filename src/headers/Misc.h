#pragma once

#ifndef MISC_H
#define MISC_H

#include <glm/glm.hpp>
#include <vector>
#include <Tri.h>
#include <string>

#include <Intersection.h>

static glm::vec2 toVec2(const glm::vec3 &v){ return glm::vec2(v.x,v.y); }

static float cross2D(glm::vec2 v, glm::vec2 w){ return v.x * w.y - v.y * w.x; }

static std::string vecToString(glm::vec3 v){  return "<" + std::to_string(v.x)  + "," + std::to_string(v.y)  + "," + std::to_string(v.z)  + ">"; }
static std::string vecToString(glm::vec3* v){ return "<" + std::to_string(v->x) + "," + std::to_string(v->y) + "," + std::to_string(v->z) + ">"; }
static std::string vecToString(glm::vec2 v){  return "<" + std::to_string(v.x)  + "," + std::to_string(v.y)  + ">"; }
static std::string vecToString(glm::vec2* v){ return "<" + std::to_string(v->x) + "," + std::to_string(v->y) + ">"; }

static Intersection find_intersection(glm::vec2 p, glm::vec2 r, glm::vec2 q, glm::vec2 s){

    glm::vec2 qmp = q-p;
    
    float rxs = cross2D(r,s);
    float qmpxr = cross2D(qmp,r);

    if(rxs == 0){
        //case1: overlapping, return starting point
        if(qmpxr == 0){
            return Intersection(p);
        }
        //case2: paralell
        else
            return Intersection(false);
    }
    else{
        float t = cross2D(qmp,s) / rxs;
        float u = qmpxr / rxs;

        //case3: unique intersect
        if( (0 <= t && t <= 1) && (0 <= u && u <= 1) ){
            return Intersection(p + (t * r));
        }
    }
    //case4: not paralell and do not intersect
    return Intersection(false);
}

static void get_min_intersection(Intersection& min, glm::vec2& min_offset, const Intersection& b, const glm::vec2& p){
    if(!b.found) return;

    glm::vec2 new_offset = b.position - p;

    if(!min.found){
        min = b;
        min_offset = new_offset;
        return;
    }
    
    if(glm::length(new_offset) < glm::length(min_offset)){
        min = b;
        min_offset = new_offset;
    }
}

static Intersection find_closest_intersection(std::vector<Intersection>& intersections, glm::vec2 p){
    Intersection* min = &intersections[0];
    for(int i = 1; i < 2; i++){
        if(!min->found && intersections[i].found) min = &intersections[i];
        else if(min->found && ( glm::length(intersections[i].position - p) < glm::length(min->position - p) ) ) 
            min = &intersections[i];
    }
    return min;
}

static Intersection find_closest_intersection(Intersection* intersections, unsigned int size, glm::vec2 p){
    Intersection* min = &intersections[0];
    for(int i = 1; i < size; i++){
        if(!intersections[i].found)
            continue;
        if(!min->found) {
            min = &intersections[i];       
            continue;
        }
        if(glm::distance(intersections[i].position, p) < glm::distance(min->position,p) ) 
            min = &intersections[i];
    }
    return *min;
}

static Intersection find_min_intersection(glm::vec2 p, glm::vec2 r, Tri tri){
    Intersection intersections[3];

    //printf("casting from %s in direction %s\n",vecToString(p).c_str(),vecToString(r).c_str());

    glm::vec2 a = toVec2(*tri.a);
    glm::vec2 b = toVec2(*tri.b);
    glm::vec2 c = toVec2(*tri.c);
    
    //A-B
    intersections[0] = find_intersection(p, r, a, b-a);
    //B-C
    intersections[1] = find_intersection(p, r, b, c-b);
    //C-A
    intersections[2] = find_intersection(p, r, c, a-c);
    //Return intersection with closest distance to p (or empty intersection if none hit)
    if(intersections[0].found || intersections[1].found || intersections[2].found) return find_closest_intersection(intersections,3,p);
    return Intersection(false);
}


#endif