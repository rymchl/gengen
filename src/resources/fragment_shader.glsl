#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 worldPos;
in vec3 worldNormal;

uniform sampler2D texture_diffuse1;
uniform vec2 uv_offset;
uniform vec2 uv_scale;


void main()
{    
    vec2 tex_coords_final = vec2(TexCoords.x * uv_scale.x, TexCoords.y * uv_scale.y) + uv_offset;
    vec4 texture_color = texture(texture_diffuse1, tex_coords_final);
    
    if(texture_color.w == 0.0f){
        discard;
        return;
    }

    FragColor = texture_color;
}