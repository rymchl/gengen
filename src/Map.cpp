#include <Map.h>

Map::Map(): ground("models/eggy/map/ground/eggy_ground.obj"),
            box("models/eggy/map/terrain/box.obj"),
            background_tex_count(5){

    std::vector<std::string> tex_paths = {
        "models/eggy/map/background/0.png",
        "models/eggy/map/background/1.png",
        "models/eggy/map/background/2.png",
        "models/eggy/map/background/3.png",
        "models/eggy/map/background/4.png",
    };

    Model templateModel("models/eggy/map/background/template.obj");

    background = Mesh(templateModel.meshes[0].vertices,templateModel.meshes[0].indices,tex_paths);


    //Active terrain
    for(Mesh &mesh : ground.meshes){
        terrain_meshes.push_back(&mesh);
    }
    for(Mesh &mesh : box.meshes){
        terrain_meshes.push_back(&mesh);
    }
    

}

void Map::draw(Shader& shader, glm::vec2 offset){

    shader.setVec2("uv_scale",glm::vec2(1,1));
    shader.setVec2("uv_offset",glm::vec2(0,0));
    shader.setVec2("vertex_offset",glm::vec2(0,0));
    

    
    //draw true bg
    shader.setFloat("depth_offset", -.05);
    background.active_texture = 0;
    background.draw(shader);

    //draw moon
    shader.setFloat("depth_offset", -.1f);
    background.active_texture = 1;
    background.draw(shader);

    float speedup = 2.05f;

    //draw extas
    for(int i = 2; i < background_tex_count; i++){
        background.active_texture = i;
        shader.setFloat("depth_offset", ( -i * 0.1f));
        float direction = i%2==0 ? -1.0f : 1.0f;
        shader.setVec2("uv_offset",glm::vec2(1,0) * direction * speedup * ((time_offset*i*speedup + offset.x)*0.001f));
        background.draw(shader);
    }

    shader.setFloat("depth_offset", 0);

    //draw ground
    shader.setVec2("uv_offset",glm::vec2(0,0));
    box.draw(shader);
    shader.setVec2("uv_offset",glm::vec2(-1,0) * offset.x * 8.0f);
    ground.draw(shader);

}
