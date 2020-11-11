#ifndef COREENGINE_H
#define COREENGINE_H

#include <memory>
#include "Window.h"
#include "Timer.h"
#include "GameInterface.h"
#include "Scene.h"
#include "Debugger.h"

#include "../Rendering/3D/GameObject.h"
#include "../Rendering/SceneGraph.h"

#include "../Graphics/ShaderHandler.h"
#include "../Graphics/TextureHandler.h"

#include "../Camera/Camera.h"

#include "../Event/EventListener.h"


#include "../../Engine/Rendering/ImGui/imgui.h"
#include "../../Engine/Rendering/ImGui/imgui_impl_sdl_gl3.h"

#include "../../Engine/Rendering/Audio/AudioHandler.h"


class CoreEngine
{
public:
	CoreEngine(const CoreEngine&) = delete;
	CoreEngine(CoreEngine&&) = delete;
	CoreEngine& operator=(const CoreEngine&) = delete;
	CoreEngine& operator=(CoreEngine&&) = delete;

	bool OnCreate(std::string name_, int width_, int height_);

	void Run();
	bool GetIsRunning() const;

	void EventHandler();

	static CoreEngine* GetInstance();

	void SetGameInterface(GameInterface* gameInterface_);

	int GetCurrentScene();
	void SetCurrentScene(int sceneNum_);

	glm::vec2 GetWindowSize() const;

	Camera* GetCamera() const;
	void SetCamera(Camera* camera_);

	void Exit();

	void NotifyMousePressed(glm::vec2 mouse_);
	void NotifyMouseReleased(glm::vec2 mouse_, int buttonType_);
	void NotifyMouseMove(glm::vec2 mouse_);
	void NotifyMouseScroll(int y_);

	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);


private:
	CoreEngine();
	~CoreEngine();

	SDL_Event eventWindow;

	static std::unique_ptr<CoreEngine> engineInstance;
	friend std::default_delete<CoreEngine>;

	void Update(const float deltaTime_);
	void Render();
	void OnDestroy();

	Window* window;

	SDL_Window* sdlWindow;

	bool isRunning;

	Timer timer;
	unsigned int fps;

	GameInterface* gameInterface;

	int currentSceneNum;

	Camera* camera;

	float windowColourR = 0;
	float windowColourG = 0;
	float windowColourB = 0;

	/*bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);*/

};
#endif

