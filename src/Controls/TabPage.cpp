#include <XAGUI.h>

namespace XAGUI
{

TabPage::TabPage() { }

void TabPage::AddControl(Control* control) { AddChild(control); }

};