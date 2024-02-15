// Part of ImGui Bundle - MIT License - Copyright (c) 2022-2024 Pascal Thomet - https://github.com/pthom/imgui_bundle
#include "immapp/immapp.h"
#ifdef IMGUI_BUNDLE_WITH_IMPLOT
#include "implot/implot.h"
#endif
#include "imgui_md_wrapper.h"

#include <cmath>

void Gui()
{
    ImGuiMd::RenderUnindented(R"(
            # Dear ImGui Bundle, Anthony
        )");

    ImGui::Separator();
    ImGuiMd::RenderUnindented("Drag to reorder items \n");
    ImGui::Separator();

    static const char* names[10] =
    {
        "Chong", "Faat", "Baat", "East", "South", "West", "North", "1 Maan", "1 Tong", "1 Suuk"
    };

    for (int n = 0; n < IM_ARRAYSIZE(names); n++)
    {
        ImGui::PushID(n);
        ImGui::SameLine();
        ImGui::Button(names[n], ImVec2(30, 50));

        // Our buttons are both drag sources and drag targets here!
        if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None))
        {
            // Set payload to carry the index of our item (could be anything)
            ImGui::SetDragDropPayload("DND_DEMO_CELL", &n, sizeof(int));

            // Display preview (could be anything, e.g. when dragging an image we could decide to display
            // the filename and a small preview of the image, etc.)
            ImGui::Text("Swap %s", names[n]); 
            ImGui::EndDragDropSource();
        }
        if (ImGui::BeginDragDropTarget())
        {
            if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("DND_DEMO_CELL"))
            {
                IM_ASSERT(payload->DataSize == sizeof(int));
                int payload_n = *(const int*)payload->Data;

                // Swap 
                const char* tmp = names[n];
                names[n] = names[payload_n];
                names[payload_n] = tmp;
            }
            ImGui::EndDragDropTarget();
        }
        ImGui::PopID();
    }
}

int main(int , char *[])
{
    HelloImGui::SimpleRunnerParams runnnerParams;
    runnnerParams.guiFunction = Gui;
    runnnerParams.windowSize = {600, 800};

    ImmApp::AddOnsParams addOnsParams;
    addOnsParams.withMarkdown = true;
    addOnsParams.withImplot = true;

    ImmApp::Run(runnnerParams, addOnsParams);
    return 0;
}
