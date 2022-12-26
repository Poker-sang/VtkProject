// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"

auto a = 0;

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD ul_reason_for_call,
    LPVOID lpReserved)
{
    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
        break;
    case DLL_THREAD_ATTACH:
        break;
    case DLL_THREAD_DETACH:
        break;
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

typedef std::uint64_t hash_t;

constexpr hash_t prime = 0x100000001B3ull;
constexpr hash_t basis = 0xCBF29CE484222325ull;
constexpr hash_t hash_(std::string s)
{
    auto str = s.c_str();
    hash_t ret { basis };

    while (*str) {
        ret ^= *str;
        ret *= prime;
        str++;
    }

    return ret;
}
constexpr hash_t hash_compile_time(char const* str, hash_t last_value = basis)
{
    return *str ? hash_compile_time(str + 1, (*str ^ last_value) * prime) : last_value;
}
constexpr unsigned long long operator""_hash(char const* p, size_t)
{
    return hash_compile_time(p);
}

template <class T>
vtkSmartPointer<T> New()
    requires(std::is_base_of_v<vtkObject, T>)
{
    return vtkSmartPointer<T>::New();
}

C_EXPORT int Show(char* path)
{
    const auto name = std::string(path);
    const auto ext = name.find_last_of('.') + 1;

    const auto file = std::make_unique<std::ifstream>(name, ios::in);
    if (!file->is_open())
        return 1;
    auto width = 0ll, height = 0ll;
    auto abandon = std::string();
    switch (hash_(name.substr(ext, name.length() - ext))) {
    case "grd"_hash:
        *file >> width >> height >> abandon >> abandon >> abandon >> abandon;
        break;
    case "dem"_hash:
        *file >> abandon >> abandon >> abandon >> abandon >> abandon >> abandon >> abandon >> abandon >> abandon >> width >> height >> abandon;
        break;
    default:
        return 1;
    }

    const auto colors = vtkSmartPointer<vtkNamedColors>::New();
    // 创建一个浮点型数组存储"点"
    const auto coords = New<vtkFloatArray>();
    // 设置维度，点->3
    coords->SetNumberOfComponents(3);
    // 设置数组个数
    coords->SetNumberOfTuples(width * height);
    const auto elevation = New<vtkDoubleArray>();
    const auto strips = New<vtkCellArray>();
    // 指定每一个数组，具体的点坐标
    auto rMin = .0, rMax = .0;
    auto first = true;
    elevation->SetName("Elevation");
    auto pointsVector = std::vector<std::vector<double>>();
    // 行
    for (auto i = 0; i < height; ++i) {
        pointsVector.emplace_back();
        pointsVector[i].reserve(width);
        // 列
        for (auto j = 0; j < width; ++j) {
            auto temp = .0;
            *file >> temp;
            pointsVector[i].emplace_back(temp);
        }
    }
    auto count1 = 0;
    auto count = 0;
    // 行
    for (auto i = 0; i < height; ++i)
        // 列
        for (auto j = 0; j < width; ++j) {
            const auto index = i * width + j;
            // 设置数组中的点
            auto temp = pointsVector[i][j];
            if (temp < -9999) {
                ++count1;
                if (i == 0 && pointsVector[i + 1][j] > -999)
                    temp = pointsVector[i + 1][j];
                else if (i == height - 1 && pointsVector[i - 1][j] > -999)
                    temp = pointsVector[i - 1][j];
                else if (i > 0 && i < height && pointsVector[i - 1][j] > -999 && pointsVector[i + 1][j] > -999)
                    temp = (pointsVector[i - 1][j] + pointsVector[i + 1][j]) / 2;
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
            if (i < height - 1 && j < width - 1) {
                strips->InsertNextCell(4);
                strips->InsertCellPoint(index);
                strips->InsertCellPoint(index + 1);
                strips->InsertCellPoint(index + width);
                strips->InsertCellPoint(index + width + 1);
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
    return 0;
}
