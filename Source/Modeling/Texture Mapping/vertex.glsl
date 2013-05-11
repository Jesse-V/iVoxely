attribute vec3 coord3d;
attribute vec3 v_normal;
attribute vec2 texcoord;



out vec3 Position_worldspace;
out vec3 Normal_cameraspace;
out vec3 EyeDirection_cameraspace;
out vec3 LightDirection_cameraspace;
out vec2 UV;

uniform mat4 mvp;
uniform mat4 v;
uniform mat4 m;
uniform vec3 LightPosition_worldspace;

void main(void) {
  
	gl_Position = mvp * vec4(coord3d, 1.0);


	Position_worldspace = (m * vec4(coord3d,1)).xyz;

	vec3 vertexPosition_cameraspace = (v * m * vec4(coord3d,1)).xyz;
	EyeDirection_cameraspace = vec3(0,0,0) - vertexPosition_cameraspace;

	vec3 LightPosition_cameraspace = (v * vec4(LightPosition_worldspace,1)).xyz;
	LightDirection_cameraspace = LightPosition_cameraspace + EyeDirection_cameraspace;

	Normal_cameraspace = (v * m * vec4(v_normal, 0)).xyz;

	UV = texcoord;
 
}
