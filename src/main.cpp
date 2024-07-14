 #include <wx/wx.h>
 
class TerrainGen : public wxApp
{
public:
    bool OnInit() override;
};
 
wxIMPLEMENT_APP(TerrainGen);
 
class TGFrame : public wxFrame
{
public:
    TGFrame();
 
private:
    void OnHello(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
};
 
enum
{
    ID_Hello = 1
};
 
bool TerrainGen::OnInit()
{
    TGFrame *frame = new TGFrame();
    frame->Show(true);
    return true;
}
 
TGFrame::TGFrame()
    : wxFrame(nullptr, wxID_ANY, "Hello World")
{
    wxMenu *menuFile = new wxMenu;
    menuFile->Append(ID_Hello, "&Hello...\tCtrl-H",
                     "Help string shown in status bar for this menu item");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);
 
    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);
 
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");
 
    SetMenuBar( menuBar );
 
    CreateStatusBar();
    SetStatusText("Welcome to Terrain Generator!");
 
    Bind(wxEVT_MENU, &TGFrame::OnHello, this, ID_Hello);
    Bind(wxEVT_MENU, &TGFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &TGFrame::OnExit, this, wxID_EXIT);
}
 
void TGFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}
 
void TGFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox("This app uses wxWidgets",
                 "About Terrain Generator", wxOK | wxICON_INFORMATION);
}
 
void TGFrame::OnHello(wxCommandEvent& event)
{
    wxLogMessage("Terrain Generator has been rebuilt");
}