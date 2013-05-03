
// different for every vertex
attribute vec3 vertex, vertexNormal;

//constant data for all vertices
uniform mat4 viewMatrix, projMatrix, matrixModel;
uniform vec3 worldLightPos, ambientLight;

// Outputs to fragment shader
varying vec3 pos_world, normal_camera, eyedirection_camera, lightdirection_camera;
varying vec3 vColor;


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
	vec3 lightpos_camera = (viewMatrix * vec4(worldLightPos, 1)).xyz;
	lightdirection_camera = normalize(lightpos_camera + eyedirection_camera);

	// normal of the vertex in camera space
	normal_camera = normalize((viewMatrix * matrixModel * vec4(vertexNormal, 0)).xyz);
}



/* Scales val, which is the range of (0, 1) to the given range and returns the result */
float scale(float val, int begin, int end)
{
	return val * (end - begin) + begin;
}



void main()
{
	gl_Position = projectVertex();
	pos_world = (matrixModel * vec4(vertex, 1)).xyz; //Convert from model space to world space
	communicateCamera();

	float height = vertex.y;
	const float SNOW_LEVEL = 0.6;
	const float MOUNTAIN_HEIGHT = 1.0;

	if (height > SNOW_LEVEL)
	{
		float topScale = (height - SNOW_LEVEL) / (MOUNTAIN_HEIGHT - SNOW_LEVEL);
		height * 2 - 1;

		vColor = vec3(
			scale(topScale, 34, 238) / 255,
			scale(topScale, 139, 233) / 255,
			scale(topScale, 34, 233) / 255
		);
	}
	else
	{
		float topScale = height / SNOW_LEVEL;

		vColor = vec3(
			scale(topScale, 160, 34) / 255,
			scale(topScale, 82, 139) / 255,
			scale(topScale, 45, 34) / 255
		);
	}
}
