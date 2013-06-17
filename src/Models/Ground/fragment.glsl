#version 130

/*
struct Light
{
	vec3 position, color;
	float power;
};
// http://stackoverflow.com/questions/8202173/setting-the-values-of-a-struct-array-from-js-to-glsl
uniform Light light[1];
*/

//constant data for all vertices
uniform vec3 ambientLight, lightPosition, lightColor;
uniform float lightPower;
uniform sampler2D textureSampler;

//inputs from vertex shader
varying vec3 pos_world, normal_camera, eyedirection_camera, lightdirection_camera;

in vec2 UV;


float specularLighting(inout vec3 normal, inout vec3 light)
{
	vec3 eye = normalize(eyedirection_camera);
	vec3 reflect = reflect(-light, normal);
	return clamp(dot(eye, reflect), 0, 1);
}



float diffusedLighting(inout vec3 normal, inout vec3 light)
{
	return max(0.0, clamp(dot(normal, -light), 0, 1));
}



void main()
{
	float lightDistance = length(lightPosition - pos_world);

	vec3 normal = normalize(normal_camera);
	vec3 light  = normalize(lightdirection_camera);

	//float theta = diffusedLighting(normal, light); //choice of lighting
	float theta = specularLighting(normal, light);

	vec3 textureColor = texture(textureSampler, UV).rgb;// * vec3(0.5, 0.5, 0.5);
	vec3 lighting = lightColor * lightPower * theta / (lightDistance * lightDistance);
	vec3 color =  textureColor * (ambientLight + lighting);

	gl_FragColor = vec4(color, 1.0);
}
