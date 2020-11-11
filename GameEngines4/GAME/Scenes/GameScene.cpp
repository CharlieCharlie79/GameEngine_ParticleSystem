#include "GameScene.h"

GameScene::GameScene() : Scene()
{
;
}

GameScene::~GameScene()
{
	SceneGraph::GetInstance()->OnDestroy();
}

bool GameScene::OnCreate()
{
	
	Debugger::Info("Creating Game Scene ", "GameScene.cpp", __LINE__);

	CoreEngine::GetInstance()->SetCamera(new Camera);
	CoreEngine::GetInstance()->GetCamera()->SetPosition(glm::vec3(0.0f, 0.5f, 4.0f));

	lightSource = new LightSource(glm::vec3(0.0f), 0.0f, 0.0f, glm::vec3(0.0f));
	lightSource->SetPosition(glm::vec3(0.0f, 0.0f, 4.0f));
	lightSource->SetAmbient(0.1f); 
	lightSource->SetDiffuse(0.5f);
	lightSource->SetLightColour(glm::vec3(1.0f, 1.0f, 1.0f));

	CoreEngine::GetInstance()->GetCamera()->AddLightSource(lightSource);

	CollisionHandler::GetInstance()->OnCreate(100.0f);

	AudioHandler::GetInstance()->Initialize(CoreEngine::GetInstance()->GetCamera()->GetPosition());

	
	Model* model1 = new Model("./Resources/Models/Dice.obj", "./Resources/Materials/Dice.mtl", ShaderHandler::GetInstance()->GetShader("basicShader"));
	SceneGraph::GetInstance()->AddModel(model1);
	
	Model* model2 = new Model("./Resources/Models/Apple.obj", "./Resources/Materials/Apple.mtl", ShaderHandler::GetInstance()->GetShader("basicShader"));
	SceneGraph::GetInstance()->AddModel(model2);

	SceneGraph::GetInstance()->AddGameObject(new GameObject(model1));

	//GameObject* apple = new GameObject(model1, glm::vec3(-10.0f, -1.0f, 0.0f));

	

	GameObject* apple = new GameObject(model2, glm::vec3(3.0f, 0.0f, 0.0f));
	apple->SetScale(glm::vec3(0.5f));
	/*apple->AddComponent<ComponentA>();
	apple->AddComponent<ComponentC>();
	apple->AddComponent<ComponentB>();
	apple->RemoveComponent<ComponentC>();*/

	particleEmitter = new ParticleEmitter(15, "red_sqaure.jpg", "particleShader");

	SceneGraph::GetInstance()->AddGameObject(apple, "apple");

	apple->AddComponent<AudioSource>("YiesEcho.mp3", true, true, false);

	return true;
}

void GameScene::Update(const float deltaTime_)
{
	
	SceneGraph::GetInstance()->Update(deltaTime_);
	particleEmitter->Update(deltaTime_);
}

void GameScene::Render()
{
	
	SceneGraph::GetInstance()->Render(CoreEngine::GetInstance()->GetCamera());
	particleEmitter->renderEmitter(CoreEngine::GetInstance()->GetCamera());

}

