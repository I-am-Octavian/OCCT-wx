#include "Application.h"


extern "C"
{
    _declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
}

wxIMPLEMENT_APP(Application);

bool Application::OnInit()
{
    m_Viewer = new Viewer("Window", nullptr);

    // MainFrame* mainWindow = new MainFrame("wx Window");
    // mainWindow->SetClientSize(800, 600);
    // mainWindow->Center();
    // mainWindow->Show();
    TopoDS_Shape shape = BRepPrimAPI_MakeBox(100.0, 200.0, 300.0).Shape();

    Handle(AIS_Shape) aisShape = new AIS_Shape(shape);

    aisShape->SetColor(Quantity_NOC_WHITE);

    m_Viewer->getContext()->Display(aisShape, Standard_True);
    m_Viewer->Center();
    m_Viewer->Show();


    auto view = m_Viewer->GetView();
    if (!view.IsNull())
    {
        view->Redraw();
        view->Reset();
    }

    return true;
}
