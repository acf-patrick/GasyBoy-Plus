#include "debugger.h"
#include "defs.h"

Debugger::Debugger(Mmu *pmmu, Cpu *pcpu)
{
    ImGui_ImplSdl_Init(window);
    window = SDL_CreateWindow("GasyBoy", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH_TEMP, HEIGHT_TEMP,SDL_WINDOW_OPENGL| SDL_WINDOW_RESIZABLE);
    glcontext = SDL_GL_CreateContext(window);
    mmu = pmmu;
    stackView = new Stack_viewer(cpu, mmu);
    memview = new Memory_viewer(mmu);
    cpu = pcpu;
    reg_viewer = new Register_viewer(cpu);
    instrViewer = new Instruction_viewer(cpu,mmu);
}

Debugger::~Debugger()
{
    ImGui_ImplSdl_Shutdown();
    SDL_GL_DeleteContext(glcontext);
    SDL_DestroyWindow(window);
}


void Debugger::HandleEvent(SDL_Event event)
{
    ImGui_ImplSdl_ProcessEvent(&event);
}

void Debugger::Render()
{
    ImGui_ImplSdl_NewFrame(window);

    instrViewer->Render();
    reg_viewer->Render();
    memview->Render();
    stackView->Render();


    glViewport(0,0,(int)ImGui::GetIO().DisplaySize.x, (int)ImGui::GetIO().DisplaySize.y);
    glClearColor(1,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui::Render();
    SDL_GL_SwapWindow(window);
}

void Debugger::step()
{
    if (cpu->get_cpuState())
            cpu->cpuStep();
    //instrViewer->mouseEvent();
}
