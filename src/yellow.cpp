static Scene scene;
static Mesh triangleMesh = CreateDemoMeshTriangle();

void GameInitialize()
{

	bool success = false;
	Shader vShader = CreateShader("shaders/OnlyPosition.vert", ShaderType_VertexShader, &success);
	Shader fShader = CreateShader("shaders/ColorPosition.frag", ShaderType_FragmentShader, &success);
	ShaderProgram prog = CreateShaderProgram(&vShader, &fShader);

	Material material{};
	material.program = &prog;

	scene.objects = new RenderObject[2];

	scene.objects[0] = CreateRenderObject(&triangleMesh, &material, {{0.5 , 0, 0}, {0.5, 1, 1}});
	scene.objects[1] = CreateRenderObject(&triangleMesh, &material, {{-0.5, 0.25, 0}, {1, 1, 1}});
}

void MoveObjectBackAndForth(RenderObject *ro)
{
	V3 *pos = &ro->transform.position;
	static float moveObjectDelta = 0.001;
	pos->m[0] += moveObjectDelta;

	if (pos->m[0] < -0.5 || pos->m[0] > 0.5)
	{
		moveObjectDelta *= -1;
	}
}

void RenderScene(Scene *scene)
{
	glClearColor(0.5, 0.2, 0.2, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	for(uint objectIndex = 0; objectIndex < scene->object_count; objectIndex++)
	{
		RenderObject *ro = &scene->objects[objectIndex];
		RenderRenderObject(ro);
	}
}

void GameUpdateAndRender(GameInput* input)
{
	MoveObjectBackAndForth(&scene.objects[1]);
	RenderScene(&scene);
}
