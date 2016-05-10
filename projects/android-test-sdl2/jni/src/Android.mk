TEST_PATH := $(call my-dir)/../../../vs2012/Test-SDL2

# XAGUI
LOCAL_PATH := $(call my-dir)/../../../android/obj/local/armeabi
include $(CLEAR_VARS)
LOCAL_MODULE    := libXAGUI
LOCAL_SRC_FILES := libXAGUI.a
include $(PREBUILT_STATIC_LIBRARY)

LOCAL_PATH := $(TEST_PATH)
include $(CLEAR_VARS)

LOCAL_MODULE := TestSDL2

LOCAL_SRC_FILES := ../../android-test-sdl2/jni/SDL/src/main/android/SDL_android_main.c \
	../../../renderers/SDL2/Font.cpp \
	../../../renderers/SDL2/InputHandler.cpp \
	../../../renderers/SDL2/Renderer.cpp \
	../../../renderers/SDL2/StaticText.cpp \
	../../../renderers/SDL2/Texture.cpp \
	Main.cpp

LOCAL_SHARED_LIBRARIES := SDL2 SDL2_image SDL2_ttf
LOCAL_STATIC_LIBRARIES := android_native_app_glue XAGUI

LOCAL_LDLIBS := -lGLESv1_CM -lGLESv2 -llog
LOCAL_CFLAGS := -D__ANDROID__ -fsigned-char -I"$(TEST_PATH)/../../../include" -I"$(TEST_PATH)/../../../dependencies/include" -I"$(TEST_PATH)/../../../renderers" -I"$(TEST_PATH)/../"

include $(BUILD_SHARED_LIBRARY)

$(call import-module,android/native_app_glue)