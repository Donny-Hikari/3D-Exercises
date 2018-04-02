#version 410

layout(location = 0) in vec3 vPosition;
layout(location = 0) out vec4 outPosition;
layout(location = 1) out vec3 outColor;

uniform Property {
  float scale;
  vec3 rotation;
};

void main() {
  vec3 sv = sin(rotation);
  vec3 cv = cos(rotation);
  mat3 rot = mat3(
    cv.z+cv.y+1,        -sv.z,       -sv.y,
           sv.z,  cv.z+cv.x+1,       -sv.x,
           sv.y,         sv.x,  cv.y+cv.x+1
  );

  gl_Position = vec4( (rot * vPosition - 2 * vPosition) * scale, 1.0 );
  //gl_Position = vec4(vPosition * 0.1, 1.0);
  outPosition = gl_Position;
  outColor = vec3(length(vPosition.xy) * 0.3, abs(vPosition.y) * 0.4, abs(vPosition.z) / 1.414 * 0.7);
}




