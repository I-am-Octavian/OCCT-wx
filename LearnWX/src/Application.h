#pragma once

#include "Viewer.h"

#include <wx/app.h>

#include <memory>
#include <BRepPreviewAPI_MakeBox.hxx>
#include <AIS_Shape.hxx>
#include <AIS_ColoredShape.hxx>


class Application : public wxApp
{
public:
	bool OnInit();

private:
	Viewer* m_Viewer;
};

