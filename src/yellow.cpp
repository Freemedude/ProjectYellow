

//-------------------------------------------
// Globals
//-------------------------------------------

// TODO (danh): Move all of these into heap.
Scene scene;
Mesh triangleMesh;

Shader vShader;
Shader fShader;
ShaderProgram program;

Material material;

void 
GameInitialize()
{
	triangleMesh = CreateDemoMeshTriangle();
	bool success = false;
	vShader = CreateShader("shaders/OnlyPosition.vert", ShaderType_VertexShader, &success);
	fShader = CreateShader("shaders/ColorPosition.frag", ShaderType_FragmentShader, &success);
	program = CreateShaderProgram(&vShader, &fShader);

	material.program = &program;

	scene.objects = new RenderObject[2];

	scene.objects[0] = CreateRenderObject(&triangleMesh, &material, {{0.5 , 0, 0}, {0.5, 1, 1}});
	scene.objects[1] = CreateRenderObject(&triangleMesh, &material, {{-0.5, 0.25, 0}, {1, 1, 1}});
	scene.object_count = 2;
}

void
MoveObjectBackAndForth(RenderObject *ro)
{
	V3 *pos = &ro->transform.position;
	static float moveObjectDelta = 0.001;
	pos->m[0] += moveObjectDelta;

	if (pos->m[0] < -0.5 || pos->m[0] > 0.5)
	{
		moveObjectDelta *= -1;
	}
}

void 
RenderScene(Scene *scene)
{
	glClearColor(0.5, 0.2, 0.2, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	for(uint objectIndex = 0; objectIndex < scene->object_count; objectIndex++)
	{
		RenderObject *ro = &scene->objects[objectIndex];
		RenderRenderObject(ro);
	}
}

void 
GameUpdateAndRender(GameInput* input)
{
	MoveObjectBackAndForth(&scene.objects[1]);
	RenderScene(&scene);
}