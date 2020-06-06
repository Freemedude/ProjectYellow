

struct GameMemory
{
	Scene scene;
	Mesh triangle_mesh;
	Shader vertex_shader;
	Shader fragment_shader;
	ShaderProgram program;
	Material material;
};


// Platform -> Game
struct GameInput
{
	bool quit;
	bool reload_shaders;
};
void 
GameInitialize();

void 
GameUpdateAndRender(GameMemory *memory, GameInput *gameInput);