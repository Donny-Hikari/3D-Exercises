
#version 410

layout(location = 1) in vec3 fragColor;
out vec3 color;

void main(){
  color = vec3(0.1f, 0.4f, 0.7f);
  //gl_FragColor = vec3(0.1f, 0.4f, 0.7f);
}

