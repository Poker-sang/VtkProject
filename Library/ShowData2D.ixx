#include "pch.h"
#pragma once
export module ShowData2D;

import Hash;
import VtkHelper;
import Config;

class TimerCallback final : public vtkCommand {
public:
    explicit TimerCallback(vtkActor* actor) { Actor = actor; }

    void Execute(vtkObject* caller, unsigned long eventId, void* callData) override
    {
        if (TimerEvent == eventId) {
            Actor->RotateX(30);
            dynamic_cast<vtkWin32RenderWindowInteractor*>(caller)->Render();
        }
    }
    vtkActor* Actor;
};

C_EXPORT vtkWin32RenderWindowInteractor* GetInterActor(const HWND hWnd, const int x, const int y, const int width, const int height)
{
    using namespace Data2D;
    using namespace Config;
    using namespace Config2D;

    const auto colors = New<vtkNamedColors>();
    // 创建一个浮点型数组存储"点"
    const auto coords = New<vtkFloatArray>();
    // 设置维度，点->3
    coords->SetNumberOfComponents(3);
    // 设置数组个数
    coords->SetNumberOfTuples(Width * Height);
    const auto standAlone = ScalarData != ElevationData;
    const auto scalar = New<vtkDoubleArray>();
    const auto cellArray = New<vtkCellArray>();
    // 指定每一个数组，具体的点坐标
    auto rMin = .0, rMax = .0;
    auto first = true;
    scalar->SetName(ScalarName.c_str());

    // 行
    for (auto i = 0; i < Height; ++i)
        // 列
        for (auto j = 0; j < Width; ++j) {
            const auto index = i * Width + j;
            // 设置数组中的点
            const auto tempElevation = (*ElevationData)[i][j];
            const auto tempScalar = standAlone ? (*ScalarData)[i][j] : (*ElevationData)[i][j];
            scalar->InsertNextValue(tempScalar);
            const double t[3] = { static_cast<double>(i), static_cast<double>(j), tempElevation };
            coords->SetTuple(index, t);
            if (first) {
                rMin = tempScalar;
                rMax = tempScalar;
                first = false;
            }
            else {
                rMin = std::min(tempScalar, rMin);
                rMax = std::max(tempScalar, rMax);
            }
            if (i < Height - 1 && j < Width - 1) {
                cellArray->InsertNextCell(4);
                cellArray->InsertCellPoint(index);
                cellArray->InsertCellPoint(index + 1);
                cellArray->InsertCellPoint(index + Width);
                cellArray->InsertCellPoint(index + Width + 1);
            }
        }

    const auto points = New<vtkPoints>();
    points->SetData(coords);

    // 创建数据集
    const auto polyData = New<vtkPolyData>();
    // 指定点和网格
    polyData->SetPoints(points);
    switch (Config2D::CellType) {
    case CellType::Strip:
        polyData->SetStrips(cellArray);
        break;
    case CellType::Vertex:
        polyData->SetVerts(cellArray);
        break;
    case CellType::Line:
        polyData->SetLines(cellArray);
        break;
    case CellType::Poly:
        polyData->SetPolys(cellArray);
        break;
    }

    // 指定标量
    polyData->GetPointData()->SetScalars(scalar);
    /*auto contourFilter = vtkSmartPointer<vtkContourFilter>::New();
    contourFilter->SetInputData(polyData);
    contourFilter->SetValue(1, 5);
    auto contourMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    contourMapper->SetInputConnection(contourFilter->GetOutputPort());
    auto contourActor = vtkSmartPointer<vtkActor>::New();
    contourActor->SetMapper(contourMapper);
    contourActor->GetProperty()->SetLineWidth(5);*/

    const auto mapper = New<vtkPolyDataMapper>();
    mapper->SetInputData(polyData);
    mapper->SetScalarRange(rMin, rMax);
    // Create an actor.
    const auto actor = New<vtkActor>();
    actor->SetMapper(mapper);
    // Create the rendering objects.
    const auto renderer = New<vtkRenderer>();
    renderer->AddActor(actor);
    // ren->AddActor(contourActor);
    renderer->SetBackground(colors->GetColor3d("Burlywood").GetData());

    const auto win = CreateWindowEx(WS_EX_LAYERED, L"Static", L"", WS_VISIBLE | WS_CHILD, x, y, width, height, hWnd, nullptr, nullptr, nullptr);
    SetLayeredWindowAttributes(win, 0, 255, LWA_ALPHA);

    // 代表显示场景的窗口，和操作平台有关系
    const auto renderWindow = New<vtkWin32OpenGLRenderWindow>();
    renderWindow->SetWindowId(win);
    // renderWindow->SetSize(WindowWidth, WindowHeight);
    renderWindow->AddRenderer(renderer);
    // 提供键盘、鼠标等交互机制
    const auto renderWindowInteractor = vtkWin32RenderWindowInteractor::New();
    renderWindowInteractor->SetRenderWindow(renderWindow);
    renderWindowInteractor->Initialize();
    // 控制旋转、缩放、移动 的交互样式
   // const auto style = New<vtkInteractorStyleTrackballCamera>();

    auto cb = new TimerCallback(actor);
    renderWindowInteractor->AddObserver(vtkCommand::TimerEvent, cb);
    renderWindowInteractor->CreateRepeatingTimer(100);
    // renderWindow->SetParentId(reinterpret_cast<HWND>(hWnd));
    // vtkSetWindowLong(renderWindow->GetWindowId(), GWL_EXSTYLE, (~WS_EX_TRANSPARENT & vtkGetWindowLong(renderWindow->GetWindowId(), GWL_EXSTYLE)) | WS_EX_LAYERED);
    // vtkSetWindowLong(renderWindow->GetWindowId(), GWL_STYLE, WS_CHILD | vtkGetWindowLong(renderWindow->GetWindowId(), GWL_EXSTYLE));
    // SetWindowPos(renderWindow->GetWindowId(), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE);
    // renderWindow->Render();
    // renderWindowInteractor->Start();
    return renderWindowInteractor;
}



C_EXPORT HWND GetWindowFromInterActor(vtkRenderWindowInteractor* interActor)
{
    const auto window = static_cast<vtkWin32OpenGLRenderWindow*>(interActor->GetRenderWindow());
    return window->GetWindowId();
}

C_EXPORT void Render(vtkRenderWindowInteractor* interActor)
{
    interActor->Render();
}

C_EXPORT void Start(vtkRenderWindowInteractor* interActor)
{
    interActor->Start();
}

C_EXPORT void ReleaseObject(vtkObjectBase* obj)
{
    obj->Delete();
}
