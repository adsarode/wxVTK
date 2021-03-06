// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO: reference additional headers your program requires here

#include <vtkAutoInit.h> 
#define vtkRenderingCore_AUTOINIT 4(vtkInteractionStyle,vtkRenderingFreeType, vtkRenderingFreeType,vtkRenderingOpenGL2)
#define vtkRenderingVolume_AUTOINIT 1(vtkRenderingVolumeOpenGL)

#include <vtkSmartPointer.h>

#include <vtkFloatArray.h>
#include <vtkDoubleArray.h>
 #include <vtkMath.h>

#include <vtkObjectFactory.h>	// vtkStandardNewMacro
#include <vtkSetGet.h>			// vtkTypeMacro

#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkCameraActor.h>
#include <vtkMapper.h>
#include <vtkRenderer.h>
#include <vtkRendererCollection.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkProperty.h>

#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>

#include <vtkConeSource.h>


// C RunTime Header Files
