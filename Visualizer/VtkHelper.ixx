#pragma once
#include "pch.h";
export module VtkHelper;

export template <class T>
vtkSmartPointer<T> New()
    requires(std::is_base_of_v<vtkObject, T>)
{
    return vtkSmartPointer<T>::New();
}
