#version 130

//OK, the Scene is common

//Scene has modelMatrix and ambientLight
//Camera has viewMatrix and projMatrix

// different for every vertex
attribute vec3 vertex; //VertexBuffer
attribute vec3 vertexNormal; //NormalBuffer
attribute vec2 texcoord; //TextureBuffer

//constant data for all vertices
uniform mat4 viewMatrix, projMatrix; //Camera
uniform mat4 modelMatrix; //Scene
uniform vec3 lightPosition; //Light

// Outputs to fragment shader
varying vec3 pos_world; //Scene+VertexBuffer
varying vec3 eyedirection_camera; //Scene+Camera+VertexBuffer
varying vec3 normal_camera; //Camera+Scene+NormalBuffer
varying vec3 lightdirection_camera; //Scene+Camera+VertexBuffer+Light

out vec2 UV; //TextureBuffer


vec4 projectVertex() //Camera+Scene+VertexBuffer
{
	mat4 MVP = projMatrix * viewMatrix * modelMatrix; //Calculate the Model-View-Projection matrix
	return MVP * vec4(vertex, 1); // Convert from model space to clip space
}



void communicateCamera() //Camera, Scene, VertexBuffer, Light
{
	//Camera, Scene, VertexBuffer
	// vector from vertex to camera, in camera space
	vec3 vpos_camera = (viewMatrix * modelMatrix * vec4(vertex, 1)).xyz;
	eyedirection_camera = -vpos_camera;

	//Camera, Light, previous paragraph
	// vector from vertex to light in camera space
	vec3 lightpos_camera = (viewMatrix * vec4(lightPosition, 1)).xyz;
	lightdirection_camera = normalize(lightpos_camera + eyedirection_camera);
}



void main()
{
	gl_Position = projectVertex();
	pos_world = (modelMatrix * vec4(vertex, 1)).xyz; //Convert from model space to world space, Scene + VertexBuffer
	communicateCamera();

	// normal of the vertex in camera space
	normal_camera = normalize((viewMatrix * modelMatrix * vec4(vertexNormal, 0)).xyz); //Scene+NormalBuffer

	UV = texcoord; //TextureBuffer
}
