#shader vertex
#version 330 core
        
layout(location = 0)in vec4 position;
layout(location = 1)in vec2 textureCoord;


out vec2 vTextCoord;
        
void main() { 
    gl_Position = position;
    vTextCoord = textureCoord;
};


#shader fragment
#version 330 core
        
layout(location = 0)out vec4 color;
in vec2 vTextCoord;

uniform vec4 uniformColor;
uniform sampler2D unifTexture;

        
void main() { 
    
    vec4 texColor = texture(unifTexture, vTextCoord);
    color = texColor;

};