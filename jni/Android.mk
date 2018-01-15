LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

OpenCV_INSTALL_MODULES := on
OpenCV_CAMERA_MODULES := off
OPENCV_LIB_TYPE := STATIC
include F:/OpenCV-3.1.0-android-sdk/OpenCV-android-sdk/sdk/native/jni/OpenCV.mk

LOCAL_MODULE    := opencv_mixed
LOCAL_SRC_FILES := ORBCompute.cpp
LOCAL_LDLIBS    +=  -llog -ldl -android -lc -lz -lm
LOCAL_STATIC_LIBRARIES += android_native_app_glue   #

include $(BUILD_SHARED_LIBRARY)

$(call import-add-path,E:/android-ndk-r10d/sources)  ## add NDK_MODULE_PATH
$(call import-module,android/native_app_glue)        ## add native_app_glue from NDK_MODULE_PATH
