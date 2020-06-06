

//-------------------------------------------
// Globals
//-------------------------------------------

// TODO (danh): Move all of these into game memory
void 
GameInitialize(void *memory)
{
	GameMemory *gameMemory = (GameMemory*)memory;
	gameMemory->triangle_mesh = CreateDemoMeshTriangle();
	bool success = false;
	gameMemory->vertex_shader = CreateShader(
		"shaders/OnlyPosition.vert", 
		ShaderType_VertexShader, 
		&success);
	gameMemory->fragment_shader = CreateShader(
		"shaders/ColorPosition.frag", 
		ShaderType_FragmentShader, 
		&success);
	gameMemory->program = CreateShaderProgram(
		&gameMemory->vertex_shader, 
		&gameMemory->fragment_shader);

	gameMemory->material.program = &gameMemory->program;

	gameMemory->scene.objects = new RenderObject[2];

	gameMemory->scene.objects[0] = CreateRenderObject(&gameMemory->triangle_mesh, &gameMemory->material, {{0.5 , 0, 0}, {0.5, 1, 1}});
	gameMemory->scene.objects[1] = CreateRenderObject(&gameMemory->triangle_mesh, &gameMemory->material, {{-0.5, 0.25, 0}, {1, 1, 1}});
	gameMemory->scene.object_count = 2;
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
GameUpdateAndRender(void *memory, GameInput* input)
{
	GameMemory *gameMemory = (GameMemory*)memory;
	MoveObjectBackAndForth(&gameMemory->scene.objects[1]);
	RenderScene(&gameMemory->scene);
}