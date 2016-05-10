LOCAL_PATH := $(call my-dir)/../../../src

include $(CLEAR_VARS)
LOCAL_MODULE    := libXAGUI
LOCAL_SRC_FILES := \
    Font.cpp \
	Renderer.cpp \
	StaticText.cpp \
	Texture.cpp \
	XAGUI.cpp \
    Controls/AnalogStick.cpp \
	Controls/Button.cpp \
	Controls/CheckBox.cpp \
	Controls/ComboBox.cpp \
	Controls/Container.cpp \
	Controls/Control.cpp \
	Controls/ControlBase.cpp \
	Controls/Form.cpp \
	Controls/Label.cpp \
	Controls/ListBox.cpp \
	Controls/MultilineTextBox.cpp \
	Controls/PasswordTextBox.cpp \
	Controls/PictureBox.cpp \
	Controls/ProgressBar.cpp \
	Controls/RadioButton.cpp \
	Controls/ScrollableControl.cpp \
	Controls/ScrollBar.cpp \
	Controls/Slider.cpp \
	Controls/TabControl.cpp \
	Controls/TabPage.cpp \
	Controls/TextBox.cpp \
	Controls/TextButton.cpp \
	Controls/Window.cpp \
	Layouts/HorizontalLayout.cpp \
	Layouts/Layout.cpp \
	Layouts/VerticalLayout.cpp \
    
LOCAL_CFLAGS := -D__ANDROID__ -fsigned-char -I"../../include"
LOCAL_STATIC_LIBRARIES := android_native_app_glue

include $(BUILD_STATIC_LIBRARY)

$(call import-module,android/native_app_glue)
