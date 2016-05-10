#ifndef XAGUI_TEST_TEST_FORM_H
#define XAGUI_TEST_TEST_FORM_H

struct TestForm : public XAGUI::Form
{
	TestForm(XAGUI::SizeType width, XAGUI::SizeType height)
	{ 
		SetID("frmTest");
		SetSize(width, height);
		SetSrc(980, 276, 300, 400);
		SetImage(XAGUI::XAGUI::GetRenderer()->GetTexture("res/skin.png"));
		AddChild(btnExit());
		AddChild(wndWindow());
		AddChild(sldHSlider());
		AddChild(sldVSlider());	
		AddChild(asAnalogStick());
		AddChild(btnDecrease());
		AddChild(btnIncrease());
		AddChild(btnProgressBar());
	}

	XAGUI::Control* btnExit()
	{
		XAGUI::TextButton* control = new XAGUI::TextButton();
		control->SetID("btnExit");
		control->SetPosition(-4, 4);
		control->SetAlignment(ALIGNMENT_RIGHT);
		control->SetSize(38, 38);
		control->SetSrc(379, 115, 136, 40);
		control->SetSrcY(CONTROL_STATE_HOVER, 155);
		control->SetSrcX(CONTROL_STATE_ACTIVE, 515);
		control->SetSrc(CONTROL_STATE_DISABLED, 515, 155, 136, 40);
		control->SetText("res/arial.ttf", 30, "X");
		return control;
	}
	
	XAGUI::Control* wndWindow()
	{
		XAGUI::Window* control = new XAGUI::Window();
		control->SetID("wndWindow");
		control->SetY(50);
		control->SetAlignment(ALIGNMENT_HCENTER);
		control->SetSize(640, 480);
		control->SetSrc(37, 27, 320, 480);
		control->AddChild(tabControl());
		control->AddChild(sbHScrollBar());
		control->AddChild(sbVScrollBar());
		return control;
	}

	XAGUI::Control* tabControl()
	{
		XAGUI::TabControl* control = new XAGUI::TabControl();
		control->SetID("tabControl");
		control->SetY(35);
		control->SetAlignment(ALIGNMENT_HCENTER);
		control->GetTab(0)->GetButton()->SetSrc(651, 311, 95, 28);
		control->GetTab(0)->GetButton()->SetSrcX(CONTROL_STATE_ACTIVE, 746);
		control->GetTab(0)->GetButton()->SetSrcX(CONTROL_STATE_DISABLED, 746);
		control->SetSize(375, 445);
		control->SetSrc(651, 338, 297, 135);
		control->AddTab(new XAGUI::TabControl::Tab());
		control->GetTab(0)->GetPage()->AddControl(tbTextBox());
		control->GetTab(0)->GetPage()->AddControl(tbPasswordTextBox());
		control->GetTab(0)->GetPage()->AddControl(tbMultilineTextBox());
		control->GetTab(0)->GetPage()->AddControl(cbCheckBox());
		control->GetTab(0)->GetPage()->AddControl(rbRadioButton());
		control->GetTab(0)->GetPage()->AddControl(btnButton());
		control->GetTab(1)->GetPage()->AddControl(lbListBox());
		return control;
	}

	XAGUI::Control* tbTextBox()
	{
		XAGUI::TextBox* control = new XAGUI::TextBox();
		control->SetID("tbTextBox");
		control->SetY(20);
		control->SetAlignment(ALIGNMENT_HCENTER);
		control->SetSize(270, 45);
		control->SetSrc(651, 338, 297, 135);
		control->GetLabel()->SetText("res/arial.ttf", 18, "Your Name");
		control->GetLabel()->SetX(10);
		control->GetLabel()->SetAlignment(ALIGNMENT_VCENTER);
		control->SetMaxCharacters(18);
		control->SetCaretSrc(650, 196, 1, 27);
		return control;
	}

	XAGUI::Control* tbPasswordTextBox()
	{
		XAGUI::PasswordTextBox* control = new XAGUI::PasswordTextBox();
		control->SetID("tbPasswordTextBox");
		control->SetY(70);
		control->SetAlignment(ALIGNMENT_HCENTER);
		control->SetSize(270, 45);
		control->SetSrc(651, 338, 297, 135);
		control->GetLabel()->SetFont("res/arial.ttf", 18);
		control->GetLabel()->SetX(10);
		control->GetLabel()->SetAlignment(ALIGNMENT_VCENTER);
		control->SetMaxCharacters(5);
		control->SetCaretSrc(650, 196, 1, 27);
		control->SetText("PIN");
		control->SetPasswordChar("*");
		return control;
	}

	XAGUI::Control* tbMultilineTextBox()
	{
		XAGUI::MultilineTextBox* control = new XAGUI::MultilineTextBox();
		control->SetID("tbMultilineTextBox");
		control->SetY(120);
		control->SetAlignment(ALIGNMENT_HCENTER);
		control->GetLabel()->SetText("res/arial.ttf", 16, "");
		control->GetLabel()->SetPosition(10, 10);
		control->SetCaretSrc(650, 196, 1, 27);
		/*control->GetVerticalScrollBar()->GetFirstButton()->SetSrc(419, 223, 12, 20);
		control->GetVerticalScrollBar()->GetFirstButton()->SetSrcX(CONTROL_STATE_HOVER, 483);
		control->GetVerticalScrollBar()->GetFirstButton()->SetSrcX(CONTROL_STATE_ACTIVE, 547);
		control->GetVerticalScrollBar()->GetFirstButton()->SetSrcX(CONTROL_STATE_DISABLED, 611);
		control->GetVerticalScrollBar()->GetSecondButton()->SetSrc(431, 223, 12, 20);
		control->GetVerticalScrollBar()->GetSecondButton()->SetSrcX(CONTROL_STATE_HOVER, 495);
		control->GetVerticalScrollBar()->GetSecondButton()->SetSrcX(CONTROL_STATE_ACTIVE, 559);
		control->GetVerticalScrollBar()->GetSecondButton()->SetSrcX(CONTROL_STATE_DISABLED, 623);
		control->GetVerticalScrollBar()->SetSrc(367, 91, 12, 397);
		control->GetVerticalScrollBar()->GetMarker()->SetSrc(367, 489, 12, 14);*/
		control->SetSize(335, 150);
		control->SetSrc(651, 338, 297, 135);
		return control;
	}

	XAGUI::Control* cbCheckBox()
	{
		XAGUI::CheckBox* control = new XAGUI::CheckBox();
		control->SetID("cbCheckBox");
		control->SetPosition(20, 280);
		control->SetSrc(427, 91, 24, 24);
		control->SetCheckedSrc(379, 91);
		control->AddChild(lblCheckBox());
		return control;
	}
	
	XAGUI::Control* lblCheckBox()
	{
		XAGUI::Label* control = new XAGUI::Label();
		control->SetID("lblCheckBox");
		control->SetX(35);
		control->SetAlignment(ALIGNMENT_VCENTER);
		control->SetText("res/Cargo Bay.ttf", 25, "dEtOnAtE wOrLd");
		return control;
	}

	XAGUI::Control* rbRadioButton()
	{
		XAGUI::RadioButton* control = new XAGUI::RadioButton();
		control->SetID("rbRadioButton");
		control->SetPosition(20, 310);
		control->SetSrc(475, 91, 24, 24);
		control->SetCheckedSrc(451, 91);
		control->AddChild(lblRadioButton());
		return control;
	}

	XAGUI::Control* lblRadioButton()
	{
		XAGUI::Label* control = new XAGUI::Label();
		control->SetID("lblRadioButton");
		control->SetX(35);
		control->SetAlignment(ALIGNMENT_VCENTER);
		control->SetText("res/Cargo Bay.ttf", 25, "y O l O");
		return control;
	}

	XAGUI::Control* btnButton()
	{
		XAGUI::TextButton* control = new XAGUI::TextButton();
		control->SetID("btnButton");
		control->SetY(-15);
		control->SetAlignment(ALIGNMENT_BOTTOM_HCENTER);
		control->SetWidth(140);
		control->SetSrc(379, 115, 136, 40);
		control->SetSrcY(CONTROL_STATE_HOVER, 155);
		control->SetSrcX(CONTROL_STATE_ACTIVE, 515);
		control->SetSrc(CONTROL_STATE_DISABLED, 515, 155, 136, 40);
		control->SetText("res/Cargo Bay.ttf", 26, "SUICIDE");
		control->GetLabel()->SetColor(0, 0, 0, 255);
		return control;
	}

	XAGUI::Control* lbListBox()
	{
		XAGUI::ListBox* control = new XAGUI::ListBox();
		control->SetID("lbListBox");
		control->SetAlignment(ALIGNMENT_VCENTER_HCENTER);
		control->SetSize(200, 250);
		control->SetSrc(651, 338, 297, 135);
		return control;
	}

	XAGUI::Control* sbHScrollBar()
	{
		XAGUI::ScrollBar* control = new XAGUI::ScrollBar();
		control->SetID("sbHScrollBar");
		control->SetY(-5);
		control->SetAlignment(ALIGNMENT_BOTTOM_HCENTER);
		control->GetFirstButton()->SetSrc(399, 223, 20, 12);
		control->GetFirstButton()->SetSrcX(CONTROL_STATE_HOVER, 463);
		control->GetFirstButton()->SetSrcX(CONTROL_STATE_ACTIVE, 527);
		control->GetFirstButton()->SetSrcX(CONTROL_STATE_DISABLED, 591);
		control->GetSecondButton()->SetSrc(379, 223, 20, 12);
		control->GetSecondButton()->SetSrcX(CONTROL_STATE_HOVER, 443);
		control->GetSecondButton()->SetSrcX(CONTROL_STATE_ACTIVE, 507);
		control->GetSecondButton()->SetSrcX(CONTROL_STATE_DISABLED, 571);
		control->SetOrientation(ORIENTATION_HORIZONTAL);
		control->GetMarker()->SetSrc(366, 504, 14, 12);
		control->SetSrc(380, 490, 397, 12);
		control->SetMinValue(0);
		control->SetMaxValue(100);
		return control;
	}

	XAGUI::Control* sbVScrollBar()
	{
		XAGUI::ScrollBar* control = new XAGUI::ScrollBar();
		control->SetID("sbVScrollBar");
		control->SetX(5);
		control->SetAlignment(ALIGNMENT_VCENTER);
		control->GetFirstButton()->SetSrc(419, 223, 12, 20);
		control->GetFirstButton()->SetSrcX(CONTROL_STATE_HOVER, 483);
		control->GetFirstButton()->SetSrcX(CONTROL_STATE_ACTIVE, 547);
		control->GetFirstButton()->SetSrcX(CONTROL_STATE_DISABLED, 611);
		control->GetSecondButton()->SetSrc(431, 223, 12, 20);
		control->GetSecondButton()->SetSrcX(CONTROL_STATE_HOVER, 495);
		control->GetSecondButton()->SetSrcX(CONTROL_STATE_ACTIVE, 559);
		control->GetSecondButton()->SetSrcX(CONTROL_STATE_DISABLED, 623);
		control->SetOrientation(ORIENTATION_VERTICAL);
		control->GetMarker()->SetSrc(367, 489, 12, 14);
		control->SetSrc(367, 91, 12, 397);
		control->SetMinValue(0);
		control->SetMaxValue(100);
		return control;
	}

	XAGUI::Control* btnProgressBar()
	{
		XAGUI::Button* control = new XAGUI::Button();
		control->SetID("btnProgressBar");
		control->SetAlignment(ALIGNMENT_BOTTOM_HCENTER);
		control->SetSize(CANVAS_WIDTH, 28);
		control->SetSrc(0, 692, 1280, 28);
		control->AddChild(pgProgressBar());
		return control;
	}

	XAGUI::Control* pgProgressBar()
	{
		XAGUI::ProgressBar* control = new XAGUI::ProgressBar();
		control->SetID("pgProgressBar");
		control->SetPosition(13, 9);
		control->SetSize(CANVAS_WIDTH - 26, 10);
		control->SetSrc(0, 682, 1250, 9);
		return control;
	}

	XAGUI::Control* btnDecrease()
	{
		XAGUI::TextButton* control = new XAGUI::TextButton();
		control->SetID("btnDecrease");
		control->SetPosition(2, -32);
		control->SetAlignment(ALIGNMENT_BOTTOM);
		control->SetWidth(90);
		control->SetSrc(379, 115, 136, 40);
		control->SetSrcY(CONTROL_STATE_HOVER, 155);
		control->SetSrcX(CONTROL_STATE_ACTIVE, 515);
		control->SetSrc(CONTROL_STATE_DISABLED, 515, 155, 136, 40);
		control->SetText("res/arial.ttf", 30, "-");
		return control;
	}

	XAGUI::Control* btnIncrease()
	{
		XAGUI::TextButton* control = new XAGUI::TextButton();
		control->SetID("btnIncrease");
		control->SetPosition(-2, -32);
		control->SetAlignment(ALIGNMENT_BOTTOM_RIGHT);
		control->SetWidth(90);
		control->SetSrc(379, 115, 136, 40);
		control->SetSrcY(CONTROL_STATE_HOVER, 155);
		control->SetSrcX(CONTROL_STATE_ACTIVE, 515);
		control->SetSrc(CONTROL_STATE_DISABLED, 515, 155, 136, 40);
		control->SetText("res/arial.ttf", 30, "+");
		return control;
	}

	XAGUI::Control* asAnalogStick()
	{
		XAGUI::AnalogStick* control = new XAGUI::AnalogStick();
		control->SetID("asAnalogStick");
		control->SetY(-60);
		control->SetAlignment(ALIGNMENT_BOTTOM_HCENTER);
		control->SetSrc(651, 115, 160, 160);
		control->SetStickSrcX(850);
		control->SetStickSrcY(83);
		control->AddChild(lblAnalogStickValue());
		return control;
	}

	XAGUI::Control* lblAnalogStickValue()
	{
		XAGUI::Label* control = new XAGUI::Label();
		control->SetID("lblAnalogStickValue");
		control->SetY(30);
		control->SetAlignment(ALIGNMENT_BOTTOM_HCENTER);
		control->SetText("res/arial.ttf", 16, "");
		return control;
	}

	XAGUI::Control* sldHSlider()
	{
		XAGUI::Slider* control = new XAGUI::Slider();
		control->SetID("sldHSlider");
		control->SetY(15);
		control->SetAlignment(ALIGNMENT_HCENTER);
		control->SetSrc(380, 490, 397, 12);
		control->SetOrientation(ORIENTATION_HORIZONTAL);
		control->GetMarker()->SetSrc(366, 504, 14, 12);
		control->SetMinValue(0);
		control->SetMaxValue(100);
		return control;
	}

	XAGUI::Control* sldVSlider()
	{
		XAGUI::Slider* control = new XAGUI::Slider();
		control->SetID("sldVSlider");
		control->SetX(-15);
		control->SetAlignment(ALIGNMENT_VCENTER_RIGHT);
		control->SetSrc(367, 91, 12, 397);
		control->GetMarker()->SetSrc(367, 489, 12, 14);
		control->SetMinValue(0);
		control->SetMaxValue(100);
		return control;
	}
};

#endif