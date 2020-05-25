namespace Yellow
{
class Scene
{
private:
	std::vector<Yellow::RenderObject*> renderObjects;
public:
	std::vector<RenderObject*>& RenderObjects();

	Scene();
	~Scene();
};
}
