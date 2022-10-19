#include <Map.h>

Map::Map(): ground("models/eggy/map/eggy_ground.obj"), moon("models/eggy/map/eggy_moon.obj"){
    background_layers.push_back(Model("models/eggy/map/eggy_background_0.obj"));
    background_layers.push_back(Model("models/eggy/map/eggy_background_1.obj"));
    background_layers.push_back(Model("models/eggy/map/eggy_background_2.obj"));
    background_layers.push_back(Model("models/eggy/map/eggy_background_3.obj"));
    background_layers.push_back(Model("models/eggy/map/eggy_background_4.obj"));

    //Active terrain
    for(Mesh &mesh : ground.meshes){
        terrain_meshes.push_back(&mesh);
    }
    

}

void Map::draw(Shader& shader, glm::vec2 offset){

    shader.setVec2("uv_scale",glm::vec2(1,1));
    shader.setVec2("uv_offset",glm::vec2(0,0));
    shader.setVec2("vertex_offset",glm::vec2(0,0));

    //draw true bg
    background_layers[0].draw(shader);

    //draw moon
    moon.draw(shader);

    float speedup = 2.05f;

    //draw extas
    for(int i = 1; i < background_layers.size(); i++){
        float direction = i%2==0 ? -1.0f : 1.0f;
        shader.setVec2("uv_offset",glm::vec2(1,0) * direction * speedup * ((time_offset*i*speedup + offset.x)*0.001f));
        background_layers[i].draw(shader);
    }

    //draw ground
    shader.setVec2("uv_offset",glm::vec2(-1,0) * offset.x * 8.0f);
    ground.draw(shader);

}
