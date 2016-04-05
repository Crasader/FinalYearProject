#ifndef VIBRATOR_H_ 
#define VIBRATOR_H_
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "platform/android/jni/JniHelper.h"
#endif
#define  CLASS_NAME "org/cocos2dx/lib/Cocos2dxHelper"
class Vibrator
{
public:
	static void Vibrate(int time);
	static void CancelVibrate();
};
#endif