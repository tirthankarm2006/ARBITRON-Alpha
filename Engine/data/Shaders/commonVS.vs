#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

uniform mat4 model;//for taking the coordinates into world coordinates
uniform mat4 view;
uniform mat4 projection;

out vec3 Normal;
out vec3 FragPos;//this is the fragment position
out vec2 TexCoords;

void main()
{
	gl_Position = projection*view*model*vec4(aPos, 1.0);//multipying the transformation matrix with the vectors of our vertices
	//Normal = vec3(model*vec4(aNormal, 0.0));(Not used as it might scale the vector as well unnecessarily)

	//we are only rotating the vector not transforming it into eye space
	Normal = transpose(inverse(mat3(model)))*aNormal;//proof in copy
	//or Normal = mat3(transpose(inverse(model)))*aNormal; which is less optimized

	FragPos = vec3(model * vec4(aPos, 1.0));//aPos is the value in the vertices matrix but that is wrt origin, 
	//we transform it into the world coordinate by multiplying model matrix to it

	TexCoords = aTexCoords;
}