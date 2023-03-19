// pch.h: 这是预编译标头文件。
// 下方列出的文件仅编译一次，提高了将来生成的生成性能。
// 这还将影响 IntelliSense 性能，包括代码完成和许多代码浏览功能。
// 但是，如果此处列出的文件中的任何一个在生成之间有更新，它们全部都将被重新编译。
// 请勿在此处添加要频繁更新的文件，这将使得性能优势无效。

#ifndef PCH_H
#define PCH_H

// ReSharper disable once CppInconsistentNaming
#define _SILENCE_CXX17_ITERATOR_BASE_CLASS_DEPRECATION_WARNING // NOLINT(bugprone-reserved-identifier, clang-diagnostic-reserved-macro-identifier)

// #define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
#pragma warning(push, 0)
// Some includes with unfixable warnings
#include <vtk-9.2/vtkObject.h>
#include <vtk-9.2/vtkActor.h>
#include <vtk-9.2/vtkAutoInit.h>
#include <vtk-9.2/vtkAxesActor.h>
#include <vtk-9.2/vtkCamera.h>
#include <vtk-9.2/vtkCapsuleSource.h>
#include <vtk-9.2/vtkCellArray.h>
#include <vtk-9.2/vtkColorTransferFunction.h>
#include <vtk-9.2/vtkCompassRepresentation.h>
#include <vtk-9.2/vtkCompassWidget.h>
#include <vtk-9.2/vtkConeSource.h>
#include <vtk-9.2/vtkContourFilter.h>
#include <vtk-9.2/vtkCubeSource.h>
#include <vtk-9.2/vtkCylinderSource.h>
#include <vtk-9.2/vtkDICOMImageReader.h>
#include <vtk-9.2/vtkDataSetMapper.h>
#include <vtk-9.2/vtkDoubleArray.h>
#include <vtk-9.2/vtkEarthSource.h>
#include <vtk-9.2/vtkFixedPointVolumeRayCastMIPHelper.h>
#include <vtk-9.2/vtkFixedPointVolumeRayCastMapper.h>
#include <vtk-9.2/vtkFloatArray.h>
#include <vtk-9.2/vtkGlyph3DMapper.h>
#include <vtk-9.2/vtkImageCast.h>
#include <vtk-9.2/vtkImageData.h>
#include <vtk-9.2/vtkImageShiftScale.h>
#include <vtk-9.2/vtkImageStencil.h>
#include <vtk-9.2/vtkWin32RenderWindowInteractor.h>
#include <vtk-9.2/vtkImageStencilToImage.h>
#include <vtk-9.2/vtkIntArray.h>
#include <vtk-9.2/vtkInteractorStyleTrackball.h>
#include <vtk-9.2/vtkInteractorStyleTrackballCamera.h>
#include <vtk-9.2/vtkLODProp3D.h>
#include <vtk-9.2/vtkLight.h>
#include <vtk-9.2/vtkMetaImageReader.h>
#include <vtk-9.2/vtkMetaImageWriter.h>
#include <vtk-9.2/vtkNamedColors.h>
#include <vtk-9.2/vtkOBJExporter.h>
#include <vtk-9.2/vtkOutlineFilter.h>
#include <vtk-9.2/vtkPiecewiseFunction.h>
#include <vtk-9.2/vtkPointData.h>
#include <vtk-9.2/vtkPoints.h>
#include <vtk-9.2/vtkPolyData.h>
#include <vtk-9.2/vtkPolyDataMapper.h>
#include <vtk-9.2/vtkPolyDataNormals.h>
#include <vtk-9.2/vtkPolyDataReader.h>
#include <vtk-9.2/vtkPolyDataToImageStencil.h>
#include <vtk-9.2/vtkPolyVertex.h>
#include <vtk-9.2/vtkPolygon.h>
#include <vtk-9.2/vtkProperty.h>
#include <vtk-9.2/vtkRenderWindow.h>
#include <vtk-9.2/vtkWin32OpenGLRenderWindow.h>
#include <vtk-9.2/vtkRenderWindowInteractor.h>
#include <vtk-9.2/vtkRenderer.h>
#include <vtk-9.2/vtkSmartPointer.h>
#include <vtk-9.2/vtkSphereSource.h>
#include <vtk-9.2/vtkStripper.h>
#include <vtk-9.2/vtkSuperquadricSource.h>
#include <vtk-9.2/vtkTransform.h>
#include <vtk-9.2/vtkTransformFilter.h>
#include <vtk-9.2/vtkTransformPolyDataFilter.h>
#include <vtk-9.2/vtkTriangleFilter.h>
#include <vtk-9.2/vtkUnstructuredGrid.h>
#include <vtk-9.2/vtkVolumeProperty.h>
#include <vtk-9.2/vtkVoxelModeller.h>
#include <vtk-9.2/vtkXMLUnstructuredGridWriter.h>

VTK_MODULE_INIT(vtkRenderingOpenGL2);
VTK_MODULE_INIT(vtkInteractionStyle);

#pragma warning(pop)

#define WIN32_LEAN_AND_MEAN // 从 Windows 头文件中排除极少使用的内容

#include <Windows.h>

#define C_EXPORT extern "C" __declspec(dllexport)

#endif // PCH_H
