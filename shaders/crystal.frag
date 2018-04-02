#version 410

layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec3 inColor;
out vec3 color;

void main(){
  //color = vec3(0.1, 0.4, 0.7);
  //color = length(vPosition.xyz) * 10 * vec3(0.1f, 0.4f, 0.7f);
  //color = 10 * vec3(0.1f * abs(vPosition.x), 0.4f * abs(vPosition.y), 0.7f * abs(vPosition.z));
  color = inColor;
  //if (length(vPosition.xyz) < 0.00001f) color = vec3(1.0f, 0.0, 0.0);
  //if (color.b < 0.1f) color = vec3(0f, 0f, 0.4f);
  //gl_FragColor = vec3(0.1f, 0.4f, 0.7f);
}


