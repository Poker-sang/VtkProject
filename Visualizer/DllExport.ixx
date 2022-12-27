#pragma once
#include "pch.h";
export module DllExport;

namespace Data2D {
auto Array = std::make_shared<std::vector<std::vector<double>>>();
int Width;
int Height;
}

C_EXPORT void SetData2D(double* arr, const int width, const int height)
{
    Data2D::Width = width;
    Data2D::Height = height;
    // 行
    for (auto i = 0; i < height; ++i) {
        Data2D::Array->emplace_back();
        (*Data2D::Array)[i].reserve(width);
        // 列
        for (auto j = 0; j < width; ++j) {
            (*Data2D::Array)[i].emplace_back(arr[i * width + j]);
        }
    }
}

C_EXPORT void ReleaseData2D()
{
    Data2D::Array = nullptr;
}

import Hash;
import VtkHelper;

C_EXPORT bool Show2D()
{
    using namespace Data2D;

    const auto colors = vtkSmartPointer<vtkNamedColors>::New();
    // 创建一个浮点型数组存储"点"
    const auto coords = New<vtkFloatArray>();
    // 设置维度，点->3
    coords->SetNumberOfComponents(3);
    // 设置数组个数
    coords->SetNumberOfTuples(Width * Height);
    const auto elevation = New<vtkDoubleArray>();
    const auto strips = New<vtkCellArray>();
    // 指定每一个数组，具体的点坐标
    auto rMin = .0, rMax = .0;
    auto first = true;
    elevation->SetName("Elevation");

    auto count1 = 0;
    auto count = 0;
    // 行
    for (auto i = 0; i < Height; ++i)
        // 列
        for (auto j = 0; j < Width; ++j) {
            const auto index = i * Width + j;
            // 设置数组中的点
            auto temp = (*Array)[i][j];
            if (temp < -9999) {
                ++count1;
                if (i == 0 && (*Array)[i + 1][j] > -999)
                    temp = (*Array)[i + 1][j];
                else if (i == Height - 1 && (*Array)[i - 1][j] > -999)
                    temp = (*Array)[i - 1][j];
                else if (i > 0 && i < Height && (*Array)[i - 1][j] > -999 && (*Array)[i + 1][j] > -999)
                    temp = ((*Array)[i - 1][j] + (*Array)[i + 1][j]) / 2;
                else {
                    temp = 1000;
                    ++count;
                }
            }
            const double a[3] = { static_cast<double>(i), static_cast<double>(j), temp };
            coords->SetTuple(index, a);
            elevation->InsertNextValue(temp);
            if (first) {
                rMin = temp;
                rMax = temp;
                first = false;
            } else {
                rMin = std::min(temp, rMin);
                rMax = std::max(temp, rMax);
            }
            if (i < Height - 1 && j < Width - 1) {
                strips->InsertNextCell(4);
                strips->InsertCellPoint(index);
                strips->InsertCellPoint(index + 1);
                strips->InsertCellPoint(index + Width);
                strips->InsertCellPoint(index + Width + 1);
            }
        }

    const auto points = New<vtkPoints>();
    points->Print(cout);
    // 获得四个点
    points->SetData(coords);

    // 创建数据集
    const auto polyData = New<vtkPolyData>();
    // 指定点和网格
    polyData->SetPoints(points);
    polyData->SetLines(strips);
    // 指定标量
    polyData->GetPointData()->SetScalars(elevation);
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

    // 代表显示场景的窗口，和操作平台有关系
    const auto renderWindow = New<vtkRenderWindow>();
    renderWindow->SetSize(600, 600);
    renderWindow->AddRenderer(renderer);

    // 提供键盘、鼠标等交互机制
    const auto renderWindowInteractor = New<vtkRenderWindowInteractor>();
    renderWindowInteractor->SetRenderWindow(renderWindow);
    // 控制旋转、缩放、移动 的交互样式
    const auto style = New<vtkInteractorStyleTrackballCamera>();
    renderWindowInteractor->SetInteractorStyle(style);
    renderWindow->Render();
    renderWindowInteractor->Start();
    return true;
}
