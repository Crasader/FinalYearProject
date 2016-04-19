LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
   ../../Classes/src/Ambulance.cpp \
   ../../Classes/src/AppDelegate.cpp \
   ../../Classes/src/Coin.cpp \
   ../../Classes/src/GameData.cpp \
   ../../Classes/src/GameOverScene.cpp \
   ../../Classes/src/GameCompleteScene.cpp \
   ../../Classes/src/GameScene.cpp \
   ../../Classes/src/HUD.cpp \
   ../../Classes/src/LevelLoader.cpp \
   ../../Classes/src/MainMenuScene.cpp \
   ../../Classes/src/MiniTruck.cpp \
   ../../Classes/src/OptionsScene.cpp \
   ../../Classes/src/PauseScene.cpp \
   ../../Classes/src/Player.cpp \
   ../../Classes/src/Police.cpp \
   ../../Classes/src/SplashScene.cpp \
   ../../Classes/src/Taxi.cpp \
   ../../Classes/src/TowerBase.cpp \
   ../../Classes/src/LoadingScene.cpp \
   ../../Classes/src/PowerUp.cpp \
   ../../Classes/src/JNIHelpers.cpp \
   ../../Classes/src/SonarFrameworks.cpp \
   ../../Classes/src/EndlessMode.cpp \
   ../../Classes/src/EndlessGameOver.cpp \
   ../../Classes/src/Level2.cpp \
   ../../Classes/src/Level3.cpp \
   ../../Classes/src/TutorialInfo1.cpp \
   ../../Classes/src/TutorialInfo2.cpp \
   ../../Classes/src/TutorialInfo3.cpp \
   ../../Classes/src/TutorialInfo4.cpp \
   ../../Classes/src/TutorialOverScene.cpp \
   ../../Classes/src/TutorialPauseScene.cpp \
   ../../Classes/src/ChooseModeScene.cpp \
   ../../Classes/src/LoadingLevel3.cpp \
   ../../Classes/src/Bike.cpp \
   ../../Classes/src/Tutorial.cpp \
   ../../Classes/src/Global.cpp \
   ../../Classes/src/Truck.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes/include

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
