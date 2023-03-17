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
#include <vtk-9.0/vtkActor.h>;
#include <vtk-9.0/vtkAutoInit.h>
#include <vtk-9.0/vtkAxesActor.h>
#include <vtk-9.0/vtkCamera.h>
#include <vtk-9.0/vtkCapsuleSource.h>
#include <vtk-9.0/vtkCellArray.h>
#include <vtk-9.0/vtkColorTransferFunction.h>
#include <vtk-9.0/vtkCompassRepresentation.h>
#include <vtk-9.0/vtkCompassWidget.h>
#include <vtk-9.0/vtkConeSource.h>
#include <vtk-9.0/vtkContourFilter.h>
#include <vtk-9.0/vtkCubeSource.h>
#include <vtk-9.0/vtkCylinderSource.h>
#include <vtk-9.0/vtkDICOMImageReader.h>
#include <vtk-9.0/vtkDataSetMapper.h>
#include <vtk-9.0/vtkDoubleArray.h>
#include <vtk-9.0/vtkEarthSource.h>
#include <vtk-9.0/vtkFixedPointVolumeRayCastMIPHelper.h>
#include <vtk-9.0/vtkFixedPointVolumeRayCastMapper.h>
#include <vtk-9.0/vtkFloatArray.h>
#include <vtk-9.0/vtkGlyph3DMapper.h>
#include <vtk-9.0/vtkImageCast.h>
#include <vtk-9.0/vtkImageData.h>
#include <vtk-9.0/vtkImageShiftScale.h>
#include <vtk-9.0/vtkImageStencil.h>
#include <vtk-9.0/vtkImageStencilToImage.h>
#include <vtk-9.0/vtkIntArray.h>
#include <vtk-9.0/vtkInteractorStyleTrackball.h>
#include <vtk-9.0/vtkInteractorStyleTrackballCamera.h>
#include <vtk-9.0/vtkLODProp3D.h>
#include <vtk-9.0/vtkLight.h>
#include <vtk-9.0/vtkMetaImageReader.h>
#include <vtk-9.0/vtkMetaImageWriter.h>
#include <vtk-9.0/vtkNamedColors.h>
#include <vtk-9.0/vtkOBJExporter.h>
#include <vtk-9.0/vtkOutlineFilter.h>
#include <vtk-9.0/vtkPiecewiseFunction.h>
#include <vtk-9.0/vtkPointData.h>
#include <vtk-9.0/vtkPoints.h>
#include <vtk-9.0/vtkPolyData.h>
#include <vtk-9.0/vtkPolyDataMapper.h>
#include <vtk-9.0/vtkPolyDataNormals.h>
#include <vtk-9.0/vtkPolyDataReader.h>
#include <vtk-9.0/vtkPolyDataToImageStencil.h>
#include <vtk-9.0/vtkPolyVertex.h>
#include <vtk-9.0/vtkPolygon.h>
#include <vtk-9.0/vtkProperty.h>
#include <vtk-9.0/vtkRenderWindow.h>
#include <vtk-9.0/vtkWin32OpenGLRenderWindow.h>
#include <vtk-9.0/vtkRenderWindowInteractor.h>
#include <vtk-9.0/vtkRenderer.h>
#include <vtk-9.0/vtkSmartPointer.h>
#include <vtk-9.0/vtkSphereSource.h>
#include <vtk-9.0/vtkStripper.h>
#include <vtk-9.0/vtkSuperquadricSource.h>
#include <vtk-9.0/vtkTransform.h>
#include <vtk-9.0/vtkTransformFilter.h>
#include <vtk-9.0/vtkTransformPolyDataFilter.h>
#include <vtk-9.0/vtkTriangleFilter.h>
#include <vtk-9.0/vtkUnstructuredGrid.h>
#include <vtk-9.0/vtkVolumeProperty.h>
#include <vtk-9.0/vtkVoxelModeller.h>
#include <vtk-9.0/vtkXMLUnstructuredGridWriter.h>

VTK_MODULE_INIT(vtkRenderingOpenGL2);
VTK_MODULE_INIT(vtkInteractionStyle);

#pragma warning(pop)

#define WIN32_LEAN_AND_MEAN // 从 Windows 头文件中排除极少使用的内容

#include <Windows.h>

#define C_EXPORT extern "C" __declspec(dllexport)

#endif // PCH_H
