#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 worldPos;
in vec3 worldNormal;

uniform sampler2D texture_diffuse1;
uniform vec3 lightPos;
uniform vec3 cameraPos;

const int CEL_STEPS = 8;

void main()
{    

    vec3 v = cameraPos - worldPos;
    float len_v = length(v);

    //EDGE DETECTION:
    //if(dot(normalize(v),worldNormal) < 0.1f){
    //    FragColor = vec4(1,1,1,1);
    //    return;
    //}

    vec4 texture_color = texture(texture_diffuse1, TexCoords);

    vec3 l = worldPos - lightPos;
    
    float falloff = pow(1.0f / length(l),2);
    float light_intensity = max(0,-dot(normalize(l),worldNormal));

    float coeff = min(1.0f, max(0.0f, 0.5f * light_intensity * falloff ));


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