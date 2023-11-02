#include <OpenGl_GraphicDriver.hxx>
#include <Windows.h>
#include "Viewer.h"

#include <V3d_View.hxx>

#include <Aspect_Handle.hxx>
#include <Aspect_DisplayConnection.hxx>

#ifdef WNT
#include <WNT_Window.hxx>
#elif defined(__APPLE__) && !defined(MACOSX_USE_GLX)
#include <Cocoa_Window.hxx>
#else
#undef Bool
#undef CursorShape
#undef None
#undef KeyPress
#undef KeyRelease
#undef FocusIn
#undef FocusOut
#undef FontChange
#undef Expose
#include <Xw_Window.hxx>
#endif

static Handle(Graphic3d_GraphicDriver)& GetGraphicDriver()
{
    static Handle(Graphic3d_GraphicDriver) aGraphicDriver;
    return aGraphicDriver;
}

Viewer::Viewer(const std::string& title, wxWindow* parent = nullptr)
    : wxFrame(parent, wxID_ANY, title)
{
    init();
    
    this->Bind(wxEVT_MOTION, &Viewer::onLButtonDown, this);
    this->Bind(wxEVT_SIZE, &Viewer::resizeEvent, this);
}

Handle(V3d_View) Viewer::GetView()
{
    return m_View;
}

void Viewer::init()
{
    Handle(Aspect_DisplayConnection) aDisplayConnection = new Aspect_DisplayConnection();

    if (GetGraphicDriver().IsNull())
    {
        GetGraphicDriver() = new OpenGl_GraphicDriver(aDisplayConnection);
    }
    auto hand = this->GetHandle();
#ifdef WNT
    // Handle(WNT_Window) window = new WNT_Window((Aspect_Handle)this->GetHandle());
    Handle(WNT_Window) window = new WNT_Window((Aspect_Handle)hand);
#elif defined(__APPLE__) && !defined(MACOSX_USE_GLX)
    Handle(Cocoa_Window) window = new Cocoa_Window((NSView*)window_handle);
#else
#error  // Does not work on Linux
    Handle(Xw_Window) window = new Xw_Window(aDisplayConnection, (Window)window_handle);
#endif

    m_Viewer = new V3d_Viewer(GetGraphicDriver());

    m_View = m_Viewer->CreateView();
    m_View->SetWindow(window);

    if (!window->IsMapped())
        window->Map();

    m_Context = new AIS_InteractiveContext(m_Viewer);

    m_Viewer->SetDefaultLights();
    m_Viewer->SetLightOn();

    m_View->SetBackgroundColor(Quantity_NOC_BLACK);
    m_View->MustBeResized();
    m_View->TriedronDisplay(Aspect_TOTP_LEFT_LOWER, Quantity_NOC_WHITE, 0.2, V3d_ZBUFFER);

    m_Context->SetDisplayMode(AIS_Shaded, Standard_True);
}

void Viewer::resizeEvent(wxSizeEvent& theEvent)
{
    if (!m_View.IsNull())
    {
        m_View->MustBeResized();
        m_View->Redraw();
    }
}

void Viewer::onLButtonDown(wxMouseEvent& theEvent)
{
    if (theEvent.Dragging() && theEvent.LeftIsDown())
    {
        wxPoint thePoint = theEvent.GetPosition();
        
        m_Xmin = thePoint.x;
        m_Ymin = thePoint.y;
        m_Xmax = thePoint.x;
        m_Ymax = thePoint.y;

        m_View->StartRotation(thePoint.x, thePoint.y);
        //
    }
}

const Handle(AIS_InteractiveContext)& Viewer::getContext() const
{
    return m_Context;
}
