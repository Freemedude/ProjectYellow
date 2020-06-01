
struct Scene;

// Game -> Platform
char *GetAssetRoot();

#define MAX_FILE_PATH_LENGTH 256
struct File
{
	char filename[MAX_FILE_PATH_LENGTH];
	u64 size_in_bytes;
	char *text;
};

File ReadFile(const char* path, bool *success);

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