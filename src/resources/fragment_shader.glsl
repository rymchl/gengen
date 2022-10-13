#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 worldPos;
in vec3 worldNormal;

uniform sampler2D texture_diffuse1;
uniform vec3 lightPos;
uniform vec3 cameraPos;

const vec3 sunDir = vec3(1,-1,1);
const float sunBrightness = 0.15f;

const int CEL_STEPS = 4;

void main()
{    

    vec3 v = cameraPos - worldPos;
    float len_v = length(v);

    //Max Falloff
    if(len_v > 35){
        FragColor = vec4(0,0,0,1);
        return;
    }

    //EDGE DETECTION:
    if(dot(normalize(v),worldNormal) < 0.1f){
        FragColor = vec4(1,1,1,1) * min(1, pow(len_v,-0.5f));
        return;
    }

    vec4 texture_color = texture(texture_diffuse1, TexCoords);

    vec3 l = worldPos - lightPos;
    

    float falloff = pow(1.0f / length(l),2) * pow(len_v,-0.65f);

    float light_intensity = max(0,-dot(normalize(l),worldNormal));

    float sun_intensity = max(0,-sunBrightness * dot(sunDir,worldNormal));

    float coeff = min(1.0f, max(0.0f, 1.25f * (light_intensity  + sun_intensity) * falloff ));


    //Cel Shading 
    //---------------------------------

    float min_diff = 10.0f;
    float final_coeff = 0.0f;
    float dC = 1.0f / CEL_STEPS;

    //------
    
    for(int i = 0; i < CEL_STEPS; i++){
        float step = abs(i*dC- coeff);
        if(step < min_diff){
            min_diff = step;
            final_coeff = i*dC;
        }
    }

    FragColor = texture_color * final_coeff;
}