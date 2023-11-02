#pragma once

#ifndef VIEWER_H
#define VIEWER_H
#include <wx/wx.h>
#include <wx/frame.h>
#include <wx/panel.h>

#include <AIS_InteractiveContext.hxx>
#include <V3d_View.hxx>

class Viewer : public wxFrame
{
    

public:
    Viewer(const std::string& title, wxWindow* parent);

    Handle(V3d_View) GetView();

    const Handle(AIS_InteractiveContext)& getContext() const;

protected:
    void init();

protected:
    //void wheelEvent(QWheelEvent* theEvent);
    //void mousePressEvent(wxMouseEvent& theEvent);
    //void mouseMoveEvent(wxMouseEvent* theEvent);
    //
    //void onMouseWheel(const int theFlags, const int theDelta, const QPoint thePoint);
    void resizeEvent(wxSizeEvent& theEvent);
    void onLButtonDown(wxMouseEvent& theEvent);
    //void onMoveMouse(const int theFlags, const QPoint thePoint);

private:
    Handle(V3d_View) m_View; // 3d View

    Handle(V3d_Viewer) m_Viewer; // 3d Viewer

    Handle(AIS_InteractiveContext) m_Context; // To interact with viewer

    // To store position of mouse(for mouse events)
    Standard_Integer m_Xmin;
    Standard_Integer m_Xmax;
    Standard_Integer m_Ymin;
    Standard_Integer m_Ymax;

};

#endif // VIEWER_H
