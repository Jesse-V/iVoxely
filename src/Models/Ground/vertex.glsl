#version 130

// different for every vertex
attribute vec3 vertex, vertexNormal;
attribute vec2 texcoord;

//constant data for all vertices
uniform mat4 viewMatrix, projMatrix, matrixModel;
uniform vec3 lightPosition;

// Outputs to fragment shader
varying vec3 pos_world, normal_camera, eyedirection_camera, lightdirection_camera;

out vec2 UV;


vec4 projectVertex()
{
	mat4 MVP = projMatrix * viewMatrix * matrixModel; //Calculate the Model-View-Projection matrix
	return MVP * vec4(vertex, 1); // Convert from model space to clip space
}



void communicateCamera()
{
	// vector from vertex to camera, in camera space
	vec3 vpos_camera = (viewMatrix * matrixModel * vec4(vertex, 1)).xyz;
	eyedirection_camera = vec3(0, 0, 0) - vpos_camera;

	// vector from vertex to light in camera space
	vec3 lightpos_camera = (viewMatrix * vec4(lightPosition, 1)).xyz;
	lightdirection_camera = normalize(lightpos_camera + eyedirection_camera);

	// normal of the vertex in camera space
	normal_camera = normalize((viewMatrix * matrixModel * vec4(vertexNormal, 0)).xyz);
}



void main()
{
	gl_Position = projectVertex();
	pos_world = (matrixModel * vec4(vertex, 1)).xyz; //Convert from model space to world space
	communicateCamera();

	UV = texcoord;
}
