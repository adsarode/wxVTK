/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile$
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

  Copyright (c) 1993-2002 Ken Martin, Will Schroeder, Bill Lorensen 
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

// .NAME  wxVTKRenderWindowInteractor - class to enable VTK to render to 
// and interact with wxWindow.
// .SECTION Description
//  wxVTKRenderWindowInteractor provide a VTK widget for wxWindow. This class
// was completely rewrote to have the 'Look & Feel' of the python version:
// wxVTKRenderWindowInteractor.py
// .SECTION Caveats 
//  - There is a know bug that prevent this class to works for more info see 
// WX_USE_X_CAPTURE. This bug only affect wxGTK from 2.3.2 to wxGTK 2.4.0.
//  - Furthermore this class is tempated over either wxWindows or wxGLCanvas,
// in wxWindows 2.3.1 and earlier, the wxGLCanvas had scroll bars, you can avoid
// this effect by playing with WX_BASE_CLASS at your risk (you might end up with
// lot of flickering.)
//  - This class might not be easily readable as it tried to work with VTK 3.2
//  and 4.x. This class doesn't support reparenting with VTK 4.2 and earlier.
// .SECTION see also
// wxVTKRenderWindowInteractor.py wxVTKRenderWindow.py

#ifndef _wxVTKRenderWindowInteractor_h_
#define _wxVTKRenderWindowInteractor_h_

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "wx/timer.h"
#define ID_wxVTKRenderWindowInteractor_TIMER 1001

// vtk includes
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderWindow.h>

// Use wxGLCanvas as base class instead of wxWindow.
// This is sometimes necessary under wxGTK or the image is blank.
// Furthermore GLCanvas makes disappear flickering (reported by Prabhu
// Ramachandran) with wxGTK 2.3.1
// See: http://public.kitware.com/pipermail/vtkusers/2001-September/007895.html
// Notes: in wxWindows 2.3.1 and earlier, the GLCanvas had scroll bars)
#if wxUSE_GLCANVAS
#ifdef __WXMSW__
#define WX_BASE_CLASS wxWindow
#define WX_USE_X_CAPTURE 1
#else
#include <wx/glcanvas.h>
#define WX_BASE_CLASS wxGLCanvas
#endif //__WXMSW__
#endif //wxUSE_GLCANVAS


#ifdef __WXGTK__
#  include "gdk/gdkprivate.h"
#  include <wx/gtk/win_gtk.h>
// Keep capturing mouse after mouse is dragged out of window
// (in wxGTK 2.3.2 there is a bug that keeps this from working,
// but it is only relevant in wxGTK if there are multiple windows)
#if wxCHECK_VERSION(2, 3, 2)
#  define WX_USE_X_CAPTURE  0
#else // replacement code for old version
#  define WX_USE_X_CAPTURE 1
#endif //wxCHECK_VERSION(2, 3, 2)
#endif //__WXGTK__


//If you are using wxGTK 2.3.2 or upper you'll have to read this first:
//http://lists.wxwindows.org/cgi-bin/ezmlm-cgi?8:msn:35600:hanbmbolbbdkidoopbai
//After making the change you'll be able to use WX_USE_X_CAPTURE = 1
//Just uncomment the following line:
//#define WX_USE_X_CAPTURE 1

// wx forward declarations
class wxPaintEvent;
class wxMouseEvent;
class wxTimerEvent;
class wxKeyEvent;
class wxSizeEvent;

class wxVTKRenderWindowInteractor : public WX_BASE_CLASS, virtual public vtkRenderWindowInteractor
{
  DECLARE_DYNAMIC_CLASS(wxVTKRenderWindowInteractor)
  
  public:
  //constructors
    wxVTKRenderWindowInteractor();
    wxVTKRenderWindowInteractor(wxWindow *parent, wxWindowID id, const wxPoint &pos = wxDefaultPosition,
	        const wxSize &size = wxDefaultSize, long style = wxWANTS_CHARS | wxNO_FULL_REPAINT_ON_RESIZE,
           const wxString &name = wxPanelNameStr);
	//vtk ::New()
    static wxVTKRenderWindowInteractor * New();
	 //destructor
    ~wxVTKRenderWindowInteractor() {};

    // vtkRenderWindowInteractor overrides
    void Initialize();
    void Enable();
    void Disable();
    void Start();
    void UpdateSize(int x, int y);
    int CreateTimer(int timertype);
    int DestroyTimer();
    void TerminateApp() {};

    // event handlers
    void OnPaint(wxPaintEvent &event);
    void OnEraseBackground (wxEraseEvent& event);
    void OnMotion(wxMouseEvent &event);

    void OnButtonDown(wxMouseEvent &event);
    void OnButtonUp(wxMouseEvent &event);
    void OnEnter(wxMouseEvent &event);
    void OnLeave(wxMouseEvent &event);
    
    void OnKeyDown(wxKeyEvent &event);
    void OnKeyUp(wxKeyEvent &event);
    void OnTimer(wxTimerEvent &event);
    void OnSize(wxSizeEvent &event);
    
    void Render();
    void SetRenderWhenDisabled(int newValue);

    // Description:
    // Prescribe that the window be created in a stereo-capable mode. This
    // method must be called before the window is realized. Default if off.
    vtkGetMacro(Stereo,int);
    vtkBooleanMacro(Stereo,int);
    virtual void SetStereo(int capable);

    // Description:
    // As CaptureMouse could be a problem sometimes on a window box
    // This method allow to set or not the CaptureMouse.
    // This method actually will works only if WX_USE_X_CAPTURE was set to 1
    vtkSetMacro(UseCaptureMouse,int);
    vtkBooleanMacro(UseCaptureMouse,int);

  protected:
    wxTimer timer;
    int ActiveButton;
    int RenderAllowed;
    long GetHandle();
    int Stereo;
    
  private:
    long Handle;
    bool Created;
    int RenderWhenDisabled;
    int UseCaptureMouse;

    DECLARE_EVENT_TABLE()
};

#endif //_wxVTKRenderWindowInteractor_h_