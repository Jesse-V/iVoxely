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
uniform vec3 ambientLight; //Scene
uniform vec3 lightPosition, lightColor; //Light
uniform float lightPower; //Light
uniform sampler2D textureSampler; //SampledBuffer

//inputs from vertex shader
varying vec3 pos_world; //Scene+VertexBuffer
varying vec3 eyedirection_camera; //Scene+Camera+VertexBuffer
varying vec3 normal_camera; //Camera+Scene+NormalBuffer
varying vec3 lightdirection_camera; //Scene+Camera+VertexBuffer+Light

in vec2 UV; //TextureBuffer


float specularLighting(inout vec3 normal, inout vec3 light) //Light
{
	vec3 eye = normalize(eyedirection_camera);
	vec3 reflect = reflect(-light, normal);
	return clamp(dot(eye, reflect), 0, 1);
}



float diffusedLighting(inout vec3 normal, inout vec3 light) //Light
{
	return max(0.0, clamp(dot(normal, -light), 0, 1));
}



void main()
{
	float lightDistance = length(lightPosition - pos_world); //Light+Scene+VertexBuffer

	vec3 normal = normalize(normal_camera);
	vec3 light  = normalize(lightdirection_camera);

	//float theta = diffusedLighting(normal, light); //choice of lighting
	float theta = specularLighting(normal, light);

	vec3 textureColor = texture(textureSampler, UV).rgb; //TextureBuffer
	vec3 lighting = lightColor * lightPower * theta / pow(lightDistance, 2); //Light
	vec3 color =  textureColor * (ambientLight + lighting); //blending colors

	gl_FragColor = vec4(color, 1.0); //persistent
}
