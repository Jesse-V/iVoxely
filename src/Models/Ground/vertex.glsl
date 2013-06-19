#version 130

// different for every vertex
attribute vec3 vertex;
attribute vec3 vertexNormal;
attribute vec2 texcoord;

//constant data for all vertices
uniform mat4 viewMatrix, projMatrix;
uniform mat4 modelMatrix;
uniform vec3 lightPosition;

// Outputs to fragment shader
varying vec3 pos_world;
varying vec3 eyedirection_camera;
varying vec3 normal_camera;
varying vec3 lightdirection_camera;

out vec2 UV;


vec4 projectVertex()
{
	mat4 MVP = projMatrix * viewMatrix * modelMatrix; //Calculate the Model-View-Projection matrix
	return MVP * vec4(vertex, 1); // Convert from model space to clip space
}



void communicateCamera()
{
	// vector from vertex to camera, in camera space
	vec3 vpos_camera = (viewMatrix * modelMatrix * vec4(vertex, 1)).xyz;
	eyedirection_camera = -vpos_camera;

	// vector from vertex to light in camera space
	vec3 lightpos_camera = (viewMatrix * vec4(lightPosition, 1)).xyz;
	lightdirection_camera = normalize(lightpos_camera + eyedirection_camera);
}



void main()
{
	gl_Position = projectVertex();
	pos_world = (modelMatrix * vec4(vertex, 1)).xyz; //Convert from model space to world space, Scene + VertexBuffer, safe
	communicateCamera();

	// normal of the vertex in camera space
	normal_camera = normalize((viewMatrix * modelMatrix * vec4(vertexNormal, 0)).xyz);

	UV = texcoord;
}
