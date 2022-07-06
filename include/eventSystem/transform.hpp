#pragma once
#include <functional>
#include <vector>

#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>

#include "glm/glm.hpp"

#include "core.hpp"
#include "component.hpp"

namespace LTE
{
    class gameObject;
    class transform: public component
    {
        private:
            glm::vec3 postion;
            glm::vec3 rotation;
            glm::vec3 scale;
            
        
        public:
            transform(glm::mat3 trans = {{0, 0, 0}, {0, 0, 0}, {1, 1, 1}}):
                postion(trans[0]), rotation(trans[1]), scale(trans[2])
            {
                
            }
            
            void setPostion(const glm::vec3& postion)
            {
                this->postion = postion;
            }


            void setRotation(const glm::vec3& rotation)
            {
                this->rotation = rotation;
            }


            void setScale(const glm::vec3& scale)
            {
                this->scale = scale;
            }

            void setXPostion(float postion)
            {
                this->postion.x = postion;
            }

            void setXRotation(float rotation)
            {
                this->rotation.x = rotation;
            }

            void setXScale(float scale)
            {
                this->scale.x = scale;
            }

            void setYPostion(float postion)
            {
                this->postion.y = postion;
            }


            void setYRotation(float rotation)
            {
                this->rotation.y = rotation;
            }


            void setYScale(float scale)
            {
                this->scale.y = scale;
            }

            void setZPostion(float postion)
            {
                this->postion.z = postion;
            }


            void setZRotation(float rotation)
            {
                this->rotation.z = rotation;
            }


            void setZScale(float scale)
            {
                this->scale.z = scale;
            }

            void changeXPostion(float postion)
            {
                this->postion.x += postion;
            }

            void changeXRotation(float rotation)
            {
                this->rotation.x += rotation;
            }

            void changeXScale(float scale)
            {
                this->scale.x += scale;
            }

            void changeYPostion(float postion)
            {
                this->postion.y += postion;
            }


            void changeYRotation(float rotation)
            {
                this->rotation.y += rotation;
            }


            void changeYScale(float scale)
            {
                this->scale.y += scale;
            }

            void changeZPostion(float postion)
            {
                this->postion.z += postion;
            }


            void changeZRotation(float rotation)
            {
                this->rotation.z += rotation;
            }


            void changeZScale(float scale)
            {
                this->scale.z += scale;
            }


            glm::vec3 getPostion()
            {
                return this->postion;
            }


            glm::vec3 getRotation()
            {
                return this->rotation;
            }


            glm::vec3 getScale()
            {
                return this->scale;
            }


            virtual std::string getName() override
            { 
                return "transform";
            }

            static void DrawVec3Control(const std::string& label, glm::vec3& values, float resetValue = 0.0f, float columnWidth = 100.0f)
            {
                ImGuiIO& io = ImGui::GetIO();
                auto boldFont = io.Fonts->Fonts[0];

                ImGui::PushID(label.c_str());

                ImGui::Columns(2);
                ImGui::SetColumnWidth(0, columnWidth);
                ImGui::Text(label.c_str());
                ImGui::NextColumn();

                ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
                ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

                float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
                ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
                ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
                ImGui::PushFont(boldFont);
                if (ImGui::Button("X", buttonSize))
                    values.x = resetValue;
                ImGui::PopFont();
                ImGui::PopStyleColor(3); 

                ImGui::SameLine();
                ImGui::DragFloat("##X", &values.x, 0.1f, 0.0f, 0.0f, "%.2f");
                ImGui::PopItemWidth();
                ImGui::SameLine();

                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
                ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
                ImGui::PushFont(boldFont);
                if (ImGui::Button("Y", buttonSize))
                    values.y = resetValue;
                ImGui::PopFont();
                ImGui::PopStyleColor(3);

                ImGui::SameLine();
                ImGui::DragFloat("##Y", &values.y, 0.1f, 0.0f, 0.0f, "%.2f");
                ImGui::PopItemWidth();
                ImGui::SameLine();

                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.35f, 0.9f, 1.0f });
                ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
                ImGui::PushFont(boldFont);
                if (ImGui::Button("Z", buttonSize))
                    values.z = resetValue;
                ImGui::PopFont();
                ImGui::PopStyleColor(3);

                ImGui::SameLine();
                ImGui::DragFloat("##Z", &values.z, 0.1f, 0.0f, 0.0f, "%.2f");
                ImGui::PopItemWidth();

                ImGui::PopStyleVar();

                ImGui::Columns(1);

                ImGui::PopID();
            }

            virtual void displayComponentProprties() override
            {
                DrawVec3Control("Translation", postion);
                glm::vec3 rotationD = glm::degrees(rotation);
                DrawVec3Control("Rotation", rotationD);
                rotation = glm::radians(rotationD);
                DrawVec3Control("Scale", scale, 1.0f);
            }

    };

}