#include "LaughTaleEngine.hpp"
#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>
#include <glm/gtc/type_ptr.hpp>

static inline LTE::scene *gameScene;


float pilarPostions[8*3] = 
{
    -1 / 5.0f, -1 / 5.0f, 0 / 5.0f,
    1 / 5.0f, -1 / 5.0f, 0 / 5.0f,
    1 / 5.0f, 1 / 5.0f, 0 / 5.0f,
    -1 / 5.0f, 1 / 5.0f, 0 / 5.0f,
    -0.5f / 5.0f, -0.5f / 5.0f, 0.5f / 5.0f,
    0.5f / 5.0f, -0.5f / 5.0f, 0.5f / 5.0f,
    0.5f / 5.0f, 0.5f / 5.0f, 0.5f / 5.0f,
    -0.5f / 5.0f, 0.5f / 5.0f, 0.5f / 5.0f
};


unsigned int pilarIndices[6 * 6] = 
{
    0, 1, 3, 3, 1, 2,
    1, 5, 2, 2, 5, 6,
    5, 4, 6, 6, 4, 7,
    4, 0, 7, 7, 0, 3,
    3, 2, 7, 7, 2, 6,
    4, 5, 0, 0, 5, 1
};

class cube: LTE::osEvent
{
    private:
        LTE::windowPieceId winId; 
        std::string name;
    public:
        std::shared_ptr<LTE::gameObject> cubeObj; 

        cube(LTE::windowPieceId winId, const std::string& name): LTE::osEvent({LTE::osEventsType::WindowClose}), winId(winId), name(name)
        {
            cubeObj =  gameScene->addGameObject(name);
            cubeObj->getTransform()->changeXRotation(1.5f);
            cubeObj->addComponent<LTE::mesh>(LTE::mesh::build([=, this](LTE::mesh::meshBuilder *builder)
                {
                    builder->setIndexBuffer(pilarIndices, 6 * 6)->
                    setVertices(pilarPostions, 8*3)->
                    setShaderName("res/moduleLoading/shaders/Basic.glsl");
                }));
            cubeObj->addComponent<LTE::material>(glm::vec4({1.0f, 1.0f, 0.0f, 1.0f}));
        }
        
        virtual void onWindowClose(LTE::osEventData *sendor)
        {
            LTE::app::keepRunning = false;
        }

}; 


class editor: LTE::osEvent
{
    private:
        LTE::windowPieceId winId; 
        bool dockspaceOpen = true;
        bool opt_fullscreen_persistant = true;
        std::shared_ptr<LTE::gameObject> selectionContext;

    public:
        

        editor(LTE::windowPieceId winId): LTE::osEvent({LTE::osEventsType::WindowImGuiRender, LTE::osEventsType::WindowClose}), winId(winId)
        {
        }

        virtual void onWindowImGuiRender(LTE::windowRenderData *sendor)
        {
            bool opt_fullscreen = opt_fullscreen_persistant;
            static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

            // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
            // because it would be confusing to have two docking targets within each others.
            ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
            if (opt_fullscreen)
            {
                ImGuiViewport* viewport = ImGui::GetMainViewport();
                ImGui::SetNextWindowPos(viewport->Pos);
                ImGui::SetNextWindowSize(viewport->Size);
                ImGui::SetNextWindowViewport(viewport->ID);
                ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
                ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
                window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
                window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
            }

            // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to not render a background.
            if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
                window_flags |= ImGuiWindowFlags_NoBackground;

            // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
            // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive, 
            // all active windows docked into it will lose their parent and become undocked.
            // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise 
            // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
            ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
            ImGui::PopStyleVar();

            if (opt_fullscreen)
                ImGui::PopStyleVar(2);

            // DockSpace
            ImGuiIO& io = ImGui::GetIO();
            if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
            {
                ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
                ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
            }

            if (ImGui::BeginMenuBar())
            {
                if (ImGui::BeginMenu("File"))
                {
                    // Disabling fullscreen would allow the window to be moved to the front of other windows, 
                    // which we can't undo at the moment without finer window depth/z control.
                    //ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen_persistant);

                    if (ImGui::MenuItem("Exit")) LTE::app::keepRunning = false;
                    ImGui::EndMenu();
                }

                ImGui::EndMenuBar();
            }

            ImGui::Begin("Scene Hierarchy");
            gameScene->forEachObject(
                [&, this]( std::shared_ptr<LTE::gameObject> obj)
                {		
                    ImGuiTreeNodeFlags flags = ((selectionContext == obj) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
                    bool opened = ImGui::TreeNodeEx((void*)obj->getId(), flags, obj->getName().c_str());
                    if (ImGui::IsItemClicked())
                    {
                        selectionContext = obj;
                    }

                    if (opened)
                    {
                        ImGui::TreePop();
                    }
                });
            
                const char* str_id = "add";
                if (ImGui::IsWindowHovered() && ImGui::IsMouseClicked(1)){
                    ImGui::OpenPopup(str_id);
                }
            
                if(ImGui::BeginPopup(str_id))
                {
                    char buffer[256] = "default";
                    if (ImGui::InputText("##newName", buffer, sizeof(buffer)))
                    {
                        selectionContext->setName(std::string(buffer));
                    }
                    if(ImGui::Button("+"))
                    {
                        gameScene->addGameObject(buffer);
                    }
                    ImGui::EndPopup();
                }
            
            ImGui::End();
    

            ImGui::Begin("Properties");
            if(selectionContext)
            {
                char buffer[256];
                memset(buffer, 0, sizeof(buffer));
                std::strncpy(buffer, selectionContext->getName().c_str(), sizeof(buffer));
                if (ImGui::InputText("##Tag", buffer, sizeof(buffer)))
                {
                    selectionContext->setName(std::string(buffer));
                }
            
            
                ImGui::SameLine();
                ImGui::PushItemWidth(-1);

                if (ImGui::Button("Add Component"))
                    ImGui::OpenPopup("AddComponent");

                if (ImGui::BeginPopup("AddComponent"))
                {
                        if (ImGui::MenuItem("material"))
                        {
                            if(!selectionContext->hasComponent<LTE::material>())
                                selectionContext->addComponent<LTE::material>(glm::vec4{0, 0, 0, 0});
                            ImGui::CloseCurrentPopup();
                        }

                        if (ImGui::MenuItem("mesh"))
                        {
                            if(!selectionContext->hasComponent<LTE::mesh>())
                                selectionContext->addComponent<LTE::mesh>(LTE::mesh::build([=, this](LTE::mesh::meshBuilder *builder)
                                                {
                                                    builder->setIndexBuffer(pilarIndices, 6 * 6)->
                                                    setVertices(pilarPostions, 8*3)->
                                                    setShaderName("res/moduleLoading/shaders/Basic.glsl");
                                                }));
                            ImGui::CloseCurrentPopup();
                        }

                    ImGui::EndPopup();
                }

                ImGui::PopItemWidth();

                selectionContext->forEachComponent([](std::shared_ptr<LTE::component> c){
                    const ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_FramePadding;
	
                    ImVec2 contentRegionAvailable = ImGui::GetContentRegionAvail();

                    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4, 4 });
                    float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
                    ImGui::Separator();
                    bool open = ImGui::TreeNodeEx((void*)c.get(), treeNodeFlags, c->getName().c_str());
                    ImGui::PopStyleVar();
                    ImGui::SameLine(contentRegionAvailable.x - lineHeight * 0.5f);
                    if (ImGui::Button("+", ImVec2{ lineHeight, lineHeight }))
                    {
                        ImGui::OpenPopup("ComponentSettings");
                    }

                    bool removeComponent = false;
                    if (ImGui::BeginPopup("ComponentSettings"))
                    {
                        if (ImGui::MenuItem("Remove component"))
                            removeComponent = true;

                        ImGui::EndPopup();
                    }

                    if (open)
                    {
                        c->displayComponentProprties();
                        ImGui::TreePop();
                    }

                });

            }
            ImGui::End();
    
            ImGui::Begin("Settings");

            ImGui::Text("background color");
            gameScene->backgroundColor->displayComponentProprties();
            

            ImGui::End();

            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
            ImGui::Begin("Viewport");

            // Application::Get().GetImGuiLayer()->BlockEvents(!ImGui::IsWindowFocused() || !ImGui::IsWindowHovered());

            ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();

            ImGui::Image(reinterpret_cast<void*>(LTE::assetManager::getAsset<LTE::texture>("LTE editor/screen texture")->getId() ), ImVec2{ viewportPanelSize.x, viewportPanelSize.y  }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
            ImGui::End();
            ImGui::PopStyleVar();

            ImGui::End();

        }

        virtual void onWindowClose(LTE::osEventData *sendor)
        {
            LTE::app::keepRunning = false;
        }

};

int main()
{
    LTE::app::init();
    
    LTE::windowPieceId winId =  LTE::app::getWindowManger()->addWindow([=](LTE::windowBuilder *build)
    {
        build->setTitle("LTE editor")->useImGui();
    });

    gameScene =  LTE::sceneManger::addScene();

    gameScene->backgroundColor->setBaseColor({0.2f, 0.2f, 0.2f, 1.0f});

    editor *e = new editor(winId);

    cube *c1 = new cube(winId, "cube 1");
    cube *c2 = new cube(winId, "cube 2");
    
    gameScene->renderToTextureAtEvent("LTE editor/screen texture", "window render/LTE editor/render scene");

    LTE::app::run();
    LTE::app::close();
    exit(0);

}
