void GameInitialize()
{
	Shader vShader(L"shaders/OnlyPosition.vert", GL_VERTEX_SHADER);
	Shader fShader(L"shaders/ColorPosition.frag", GL_FRAGMENT_SHADER);
	Program prog(&vShader, &fShader);

	RenderObject objects[2]

	Material material{};
	material.program = &prog;

	Mesh *triangleMesh = Mesh::Triangle();
	Transform transforms[2];

	// Fill scene
	{
		objects[0].Create(triangleMesh, &material,
		                  &transforms[0]);
		objects[0].transform->position = {0.5, 0, 0};
		objects[0].transform->scale = {aspectRatio, 1, 1};
		scene.RenderObjects().push_back(&objects[0]);
	}
	{
		objects[1].Create(triangleMesh, &material,
		                  &transforms[1]);
		objects[1].transform->position = { -0.5, 0.25, 0};
		scene.RenderObjects().push_back(&objects[1]);
	}
}

void MoveObjectBackAndForth(Yellow::RenderObject *ro)
{
    Yellow::V3 *pos = &ro->transform->position;
    static float moveObjectDelta = 0.001;
    pos->m[0] += moveObjectDelta;

    if (pos->m[0] < -0.5 || pos->m[0] > 0.5)
    {
        moveObjectDelta *= -1;
    }
}

void Render()
{
    GLCall(glClearColor(0.5, 0.2, 0.2, 0));
    GLCall(glClear(GL_COLOR_BUFFER_BIT));

    for (auto &ro : scene.RenderObjects())
    {
        ro->Render();
    }

    SwapBuffers();
}

void GameUpdateAndRender(GameMemory *memory, GameInput* input)
{
	MoveObjectBackAndForth(scene.RenderObjects()[1]);
	Render();
}

