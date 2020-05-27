
// Game -> Platform
void PlatformReadFile(const char* path);
char *GetAssetRoot();


// Platform -> Game
struct GameInput
{
	bool quit;
	bool reload_shaders;
};

struct GameMemory
{
	Scene *scene;
};

void GameInitialize();
void GameUpdateAndRender(GameInput *gameInput);