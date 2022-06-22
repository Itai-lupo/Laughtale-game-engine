#shader vertex
#version 330 core 


layout(location = 0) in vec3 postion;
layout(location = 1) in vec2 texCoord;

out vec4 MatrialColor;
out vec2 textCoord;



void main(){
   gl_Position =  vec4(postion, 1.0);
   // MatrialColor = MatColor;
   textCoord = texCoord;
};




#shader fragment
#version 330 core 


layout(location = 0) out vec4 color;

// in vec4 MatrialColor;
in vec2 textCoord;

uniform vec4 MatColor;
uniform sampler2D textureData;

vec4 calcColor(vec4 textureColor)
{
   if(textureColor.rgba == vec4(0.0))
      return vec4(0.0);
      
   return textureColor + MatColor;

}

void main(){
   vec4 textureColor;
   textureColor = texture(textureData, textCoord);

   color = calcColor(textureColor);
};