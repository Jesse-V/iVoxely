
// different for every vertex
attribute vec3 vertex, vertexNormal;

//constant data for all vertices
uniform mat4 viewMatrix, projMatrix, matrixModel;
uniform vec3 worldLightPos, ambientLight;

// Outputs to fragment shader
varying vec3 pos_world, normal_camera, eyedirection_camera, lightdirection_camera;
varying vec3 vFractalColor;


vec3 getColorAt(vec2 pt)
{
	float ptYSq = pow(pt.y, 2);
	float xOff = pt.x - 0.25;
	float q = pow(xOff, 2) + ptYSq;
	if (q * (q + xOff) < ptYSq / 4)
		return vec3(0, 0, 0); //it's in the main bulb, so return black (optimization)

	int MAX_ITERATIONS = 150;
	float COLORING = 1;

	float x = 0, xSq = 0, y = 0, ySq = 0;
	int iterations;
	for (iterations = 0; iterations < MAX_ITERATIONS && (xSq + ySq <= 144); iterations++)
	{
		y = 2 * x * y + pt.y;
		x = xSq - ySq + pt.x;
		xSq = pow(x, 2);
		ySq = pow(y, 2);
	}

	if (iterations == MAX_ITERATIONS)
		return vec3(0, 0, 0);
	else
	{
		float mu = iterations - log(log(xSq + ySq)) / log(2f);
		float sinVal = sin(mu / COLORING) / 2 + 0.5f;
		float cosVal = cos(mu / COLORING) / 2 + 0.5f;
		return vec3(cosVal, cosVal, sinVal);
	}
}



void colorFractal()
{
	float modelX = sqrt(pow(vertex.x, 2) + pow(vertex.y, 2));
	float modelY = vertex.z;

	float fractalX = modelX * 12.0f - 1.2f;
	float fractalY = modelY * 2.8f - 1.5f;

	vFractalColor = getColorAt(vec2(fractalX, fractalY)) + vec3(0.05, 0.05, 0.05);
}



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



void main()
{
	gl_Position = projectVertex();
	pos_world = (matrixModel * vec4(vertex, 1)).xyz; //Convert from model space to world space
	communicateCamera();

	colorFractal();
}
