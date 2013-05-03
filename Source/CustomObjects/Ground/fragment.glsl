
//constant data for all vertices
uniform vec3 worldLightPos, ambientLight;

//inputs from vertex shader
varying vec3 pos_world, normal_camera, eyedirection_camera, lightdirection_camera;
varying vec3 vColor;


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
	vec3 lightColor   = vec3(1, 1, 1); //todo: get this in from the Light obj
	float lightDistance = length(worldLightPos - pos_world);
	float lightPower  = 0.03f; //todo: get this in from the Light obj

	vec3 normal = normalize(normal_camera);
	vec3 light  = normalize(lightdirection_camera);

	//float theta = diffusedLighting(normal, light); //choice of lighting
	float theta = specularLighting(normal, light);

	vec3 lighting = lightColor * lightPower * theta / (lightDistance * lightDistance);
	vec3 color =  vColor * (ambientLight + lighting);

	gl_FragColor = vec4(color, 1.0);
}
