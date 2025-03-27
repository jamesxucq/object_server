
/* 
 * File:   EarthLvtpHeader.h
 * Author: james
 *
 * Created on 2023.12.9, PM 1:46
 */

#ifndef CHECK_ATTRIBU_DECLARE
#define CHECK_ATTRIBU_DECLARE

// 系统自动检测服务器端类定义变更的频率
// 启用_CHECK_VERSION_INTERVAL和_CHECK_ATTRIBU_INTERVAL需使用这个宏
#define CHECK_ATTRIBU_FREQUENCY   (1024-1) // 2^10-1

// 下面的宏是五种检测服务器类变化方式选项
// check server and local lv2p attribute: version, external

// 每次都检测类版本的变化
// #define _CHECK_VERSION_EVERYTIME

// 按上面的频率检测类版本的变化
// #define _CHECK_VERSION_INTERVAL // interval

// 每次都检测类版本和外联属性的变化
// #define _CHECK_ATTRIBU_EVERYTIME

// 按上面的频率检测类版本的变化和外联属性
// #define _CHECK_ATTRIBU_INTERVAL // interval

//　不检测类版本的变化和外联属性
#define _DONOT_CHECK_ATTRIBU

//
#include "OSEVClieCPP.h" 

#endif /* CHECK_ATTRIBU_DECLARE */

//

#ifndef EARTH_LVTP_HEADER_H
#define EARTH_LVTP_HEADER_H

//
#include "txxt.h"


#endif /* EARTH_LVTP_HEADER_H */

