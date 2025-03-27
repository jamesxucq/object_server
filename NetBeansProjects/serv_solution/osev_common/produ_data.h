
/* 
 * File:   produ_data.h
 * Author: James Xu
 *
 * Created on 2023.5.2, PM 3:41
 */

#ifndef PRODU_DATA_H
#define PRODU_DATA_H

#ifdef __cplusplus
extern "C" {
#endif

    // PDAT_PRODUCEN_TAIL // none, once multi send
#define PDAT_PRODUCEN_TAIL(RESCTL) \
        (RESCTL)->content_length = 0x00;

    // PDAT_PRODUCEO_TAIL // once send
#define PDAT_PRODUCEO_TAIL(RESCTL, CONT_LENG) \
        (RESCTL)->content_length = CONT_LENG;

    // PDAT_PRODUCEM_TAIL // multi send
#define PDAT_PRODUCEM_TAIL(RESCTL, CONT_LENG) { \
        (RESCTL)->content_length = CONT_LENG; \
        (RESCTL)->posi_resp = (char *) (RESCTL)->resp_memo; \
    }

    // FDAT_PRODUCE_TAIL // multi send
#define FDAT_PRODUCE_TAIL(RESCTL, CONT_LENG) { \
        (RESCTL)->content_length = CONT_LENG; \
        rewind((RESCTL)->resp_stram); \
    }

    // PDAT_PRODUCE_INITI => PDAT_LASTPOS_PCAT => PDAT_PRODUCE_FINAL // once send
#define PDAT_PRODUCE_INITI(RESCTL) { \
        (RESCTL)->content_length = 0x00; \
        (RESCTL)->posi_resp = (char *) (RESCTL)->resp_memo; \
    }

#define PDAT_LASTPOS_PCAT(RESCTL, POSI_LAST) \
        (RESCTL)->posi_resp = POSI_LAST;

#define PDAT_PRODUCE_FINAL(RESCTL) \
        (RESCTL)->content_length = (RESCTL)->posi_resp - (char *) (RESCTL)->resp_memo;

    // exception attach
    // PDAT_EATTACH_HEAD => PDAT_EATTACH_END // once send
#define PDAT_EATTACH_HEAD(RESCTL, EXECEP_CODE) { \
        ((unsigned int *) (RESCTL)->resp_memo)[0x00] = EXECEP_CODE; \
        (RESCTL)->content_length = EXCEP_LENG; \
        (RESCTL)->posi_resp = (char *) ((RESCTL)->resp_memo + EXCEP_LENG); \
    }

#define PDAT_EATTACH_END(RESCTL, CONT_LENG) \
        (RESCTL)->content_length += CONT_LENG;

    // PDAT_EXCEPTIO_TAIL // once send
#define PDAT_EXCEPTIO_TAIL(RESCTL, EXECEP_CODE) { \
        ((unsigned int *) (RESCTL)->resp_memo)[0x00] = EXECEP_CODE; \
        (RESCTL)->content_length = EXCEP_LENG; \
    }

    // PDAT_EXCEPTIM_TAIL // multi send
#define PDAT_EXCEPTIM_TAIL(RESCTL, EXECEP_CODE) { \
        ((unsigned int *) (RESCTL)->resp_memo)[0x00] = EXECEP_CODE; \
        (RESCTL)->content_length = EXCEP_LENG; \
        (RESCTL)->posi_resp = (char *) (RESCTL)->resp_memo; \
    }

    // FDAT_EXCEPTI_TAIL // multi send
#define FDAT_EXCEPTI_TAIL(RESCTL, EXECEP_CODE) { \
        ((unsigned int *) (RESCTL)->resp_memo)[0x00] = EXECEP_CODE; \
        fwrite((RESCTL)->resp_memo, 0x01, EXCEP_LENG, (RESCTL)->resp_stram); \
        (RESCTL)->content_length = EXCEP_LENG; \
        rewind((RESCTL)->resp_stram); \
    }

    // FDAT_PRODUCE_INITI => FDAT_PRODUCE_PCAT <=> FDAT_PRODUCE_FCAT => FDAT_PRODUCE_FINAL // multi send
#define FDAT_PRODUCE_INITI(RESCTL) { \
        (RESCTL)->content_length = 0x00; \
        (RESCTL)->posi_resp = (char *) (RESCTL)->resp_memo; \
        rewind((RESCTL)->resp_stram); \
    }

    // FDAT_PRODUCE_PCAT

#define FDAT_PRODUCE_FCAT(RESCTL, MMAP, DCURSO, BAVAL, STORA_HA, STO_SEIO) { \
        unsigned long long pcat_size = (RESCTL)->posi_resp - (char *) (RESCTL)->resp_memo; \
        if(pcat_size != fwrite((RESCTL)->resp_memo, 0x01, pcat_size, (RESCTL)->resp_stram)) { \
            unpmmap_file64(mmap); \
            stora_ha->close_curso(dcurso); \
            QUIET_SESSION_BZL(baval->rivcon, stora_ha, STO_SEIO); \
            return -1; \
        } \
        (RESCTL)->content_length += pcat_size; \
        (RESCTL)->posi_resp = (char *) (RESCTL)->resp_memo; \
    }

#define FDAT_PRODUCE_FINAL(RESCTL) \
        rewind((RESCTL)->resp_stram);

#ifdef __cplusplus
}
#endif

#endif /* PRODU_DATA_H */

