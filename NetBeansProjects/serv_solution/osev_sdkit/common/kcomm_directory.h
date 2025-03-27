
/* 
 * File:   kcomm_directory.h
 * Author: James Xu
 *
 * Created on 2017.1.4, PM 4:48
 */

#ifndef KCOMM_DIRECTORY_H
#define KCOMM_DIRECTORY_H

#include "commo_macro.h"
#include "osev_datyp.h"
#include "osev_macro.h"
#include "stri_utili.h"

#ifdef __cplusplus
extern "C" {
#endif

    extern char _commo_directory_[MAX_PATH * 3];
#define _COMMO_DIRECTORY_     _commo_directory_
    char *commo_directory_init(char *directory);

    // osev
#define CREAT_OSEV_FILE(OSEV_FILE, DATA_DIRECTORY, FILE_NAME) { \
    char *last_str = lscpy(OSEV_FILE, DATA_DIRECTORY); \
    last_str = lccpy(last_str, '/'); \
    lscpy(last_str, FILE_NAME); }

    // base
#define CREAT_BASE_DIRECTORY(BASE_DIRE, BASEN) { \
    char *last_str = lscpy(BASE_DIRE, _commo_directory_); \
    last_str = lccpy(last_str, '/'); \
    lscpy(last_str, BASEN); }

#define CREAT_BASE_SUBDIRE(BASE_DIRE, BASEN, SUB_DIRE) { \
    char *last_str = lscpy(BASE_DIRE, _commo_directory_); \
    last_str = lccpy(last_str, '/'); \
    last_str = lscpy(last_str, BASEN); \
    last_str = lccpy(last_str, '/'); \
    lscpy(last_str, SUB_DIRE); }

#define CREAT_BASE_SUBDIRE_LAST(LAST_STR, BASE_DIRE, BASEN, SUB_DIRE) { \
    LAST_STR = lscpy(BASE_DIRE, _commo_directory_); \
    LAST_STR = lccpy(LAST_STR, '/'); \
    LAST_STR = lscpy(LAST_STR, BASEN); \
    LAST_STR = lccpy(LAST_STR, '/'); \
    LAST_STR = lscpy(LAST_STR, SUB_DIRE); }

    // contain
#define CREAT_CONTAIN_DIRECTORY(CONT_DIRE, BASEN, ENGINE) { \
    char *last_str = lscpy(CONT_DIRE, _commo_directory_); \
    last_str = lccpy(last_str, '/'); \
    last_str = lscpy(last_str, BASEN); \
    last_str = lscpy(last_str, "/contain/"); \
    lscpy(last_str, ENGINE); }

#define CREAT_CONTAIN_FILE(CONT_FILE, BASEN, FILE_NAME) { \
    char *last_str = lscpy(CONT_FILE, _commo_directory_); \
    last_str = lccpy(last_str, '/'); \
    last_str = lscpy(last_str, BASEN); \
    last_str = lscpy(last_str, "/contain/"); \
    lscpy(last_str, FILE_NAME); }

#define CONTAIN_ENGINE_FILE(ENGI_FILE, BASEN, ENGINE, FILE_NAME) { \
    char *last_str = lscpy(ENGI_FILE, _commo_directory_); \
    last_str = lccpy(last_str, '/'); \
    last_str = lscpy(last_str, BASEN); \
    last_str = lscpy(last_str, "/contain/"); \
    last_str = lscpy(last_str, ENGINE); \
    last_str = lccpy(last_str, '/'); \
    lscpy(last_str, FILE_NAME); }

    // class
#define CREAT_CLASS_DIRECTORY(LVTP_DIRE, BASEN) { \
    char *last_str = lscpy(LVTP_DIRE, _commo_directory_); \
    last_str = lccpy(last_str, '/'); \
    last_str = lscpy(last_str, BASEN); \
    lscpy(last_str, "/class/"); }

#define LVTP_DECLA_FILE(LVTD_FILE, BASEN, LVTPN) { \
    char *last_str = lscpy(LVTD_FILE, _commo_directory_); \
    last_str = lccpy(last_str, '/'); \
    last_str = lscpy(last_str, BASEN); \
    last_str = lscpy(last_str, "/class/"); \
    last_str = lscpy(last_str, LVTPN); \
    lscpy(last_str, DECLA_SUFFIX); }

#define LVTP_ATTRI_FILE(LVTT_FILE, BASEN, LVTPN) { \
    char *last_str = lscpy(LVTT_FILE, _commo_directory_); \
    last_str = lccpy(last_str, '/'); \
    last_str = lscpy(last_str, BASEN); \
    last_str = lscpy(last_str, "/class/"); \
    last_str = lscpy(last_str, LVTPN); \
    lscpy(last_str, ATTRI_SUFFIX); }

#define LVTP_EXPAN_FILE(LVTE_FILE, BASEN, LVTPN) { \
    char *last_str = lscpy(LVTE_FILE, _commo_directory_); \
    last_str = lccpy(last_str, '/'); \
    last_str = lscpy(last_str, BASEN); \
    last_str = lscpy(last_str, "/class/"); \
    last_str = lscpy(last_str, LVTPN); \
    lscpy(last_str, EXPAN_SUFFIX); }

#define CREAT_LVTP_FILE(LVTP_FILE, BASEN, FILE_NAME, SUFFIX) { \
    char *last_str = lscpy(LVTP_FILE, _commo_directory_); \
    last_str = lccpy(last_str, '/'); \
    last_str = lscpy(last_str, BASEN); \
    last_str = lscpy(last_str, "/class/"); \
    last_str = lscpy(last_str, FILE_NAME); \
    lscpy(last_str, SUFFIX); }

    // object
#define CREAT_LIBRARY_FILE(LIBRA_FILE, BASEN, FILE_NAME) { \
    char *last_str = lscpy(LIBRA_FILE, _commo_directory_); \
    last_str = lccpy(last_str, '/'); \
    last_str = lscpy(last_str, BASEN); \
    last_str = lscpy(last_str, "/object/"); \
    lscpy(last_str, FILE_NAME); }

#define LIBRARY_SUFFIX_FILE(LIBRA_FILE, BASEN, FILE_NAME, SUFFIX) { \
    char *last_str = lscpy(LIBRA_FILE, _commo_directory_); \
    last_str = lccpy(last_str, '/'); \
    last_str = lscpy(last_str, BASEN); \
    last_str = lscpy(last_str, "/object/"); \
    last_str = lscpy(last_str, FILE_NAME); \
    lscpy(last_str, SUFFIX); }

    // cache
#define CREAT_CACHE_FILE(CACHE_FILE, BASEN, FILE_NAME) { \
    char *last_str = lscpy(CACHE_FILE, _commo_directory_); \
    last_str = lccpy(last_str, '/'); \
    last_str = lscpy(last_str, BASEN); \
    last_str = lscpy(last_str, "/cache/"); \
    lscpy(last_str, FILE_NAME); }

    // instant
#define CREAT_INSTANT_FILE(INSTA_FILE, BASEN, FILE_NAME) { \
    char *last_str = lscpy(INSTA_FILE, _commo_directory_); \
    last_str = lccpy(last_str, '/'); \
    last_str = lscpy(last_str, BASEN); \
    last_str = lscpy(last_str, "/instant/"); \
    lscpy(last_str, FILE_NAME); } 

    // temp
#define CREAT_TEMPORA_FILE(TEMPO_FILE, BASEN, FILE_NAME) { \
    char *last_str = lscpy(TEMPO_FILE, _commo_directory_); \
    last_str = lccpy(last_str, '/'); \
    last_str = lscpy(last_str, BASEN); \
    last_str = lscpy(last_str, "/temp/"); \
    lscpy(last_str, FILE_NAME); }

#define TEMPORA_SUFFIX_FILE(TEMPO_FILE, BASEN, FILE_NAME, SUFFIX) { \
    char *last_str = lscpy(TEMPO_FILE, _commo_directory_); \
    last_str = lccpy(last_str, '/'); \
    last_str = lscpy(last_str, BASEN); \
    last_str = lscpy(last_str, "/temp/"); \
    last_str = lscpy(last_str, FILE_NAME); \
    lscpy(last_str, SUFFIX); }

#define TEMPORA_BAKUP_FILE(BAKUP_FILE, BASEN, FILE_NAME, SUFFIX) { \
    char *last_str = lscpy(BAKUP_FILE, _commo_directory_); \
    last_str = lccpy(last_str, '/'); \
    last_str = lscpy(last_str, BASEN); \
    last_str = lscpy(last_str, "/temp/_bakup_"); \
    last_str = lscpy(last_str, FILE_NAME); \
    lscpy(last_str, SUFFIX); }

#ifdef __cplusplus
}
#endif

#endif /* KCOMM_DIRECTORY_H */

