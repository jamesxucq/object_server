
/* 
 * File:   conte_resou.h
 * Author: James Xu
 *
 * Created on 20210301, PM3:10
 */

#ifndef CONTE_RESOU_H
#define CONTE_RESOU_H

#ifdef __cplusplus
extern "C" {
#endif

    // #include "plan/quer_plan_ensi.h"

    //

    struct _physi_conte_ {
        int initi; // 0:uninit 1:ok
        stor_seio *sto_seio;
    };

    typedef struct _physi_conte_ physi_conte;

#define INITI_PHYSI_CONTE(PHYSI_CONTE) (PHYSI_CONTE).initi = 0x00;
    
    //

    // cursa operation
    int hand_open_conte_ensi(physi_conte *phys_cont, rive_conne *rivcon, rive_ha *stora_ha);
    int hand_close_conte_ensi(physi_conte *phys_cont, rive_conne *rivcon, rive_ha *stora_ha);

    //
    int hand_open_conte_enco(physi_conte *phys_cont, rive_conne *rivcon, rive_ha *stora_ha);
    int hand_close_conte_enco(physi_conte *phys_cont, rive_conne *rivcon, rive_ha *stora_ha);

    //

    inline riv_curso_t *creat_curso(rive_ha *stora_ha, physi_conte *phys_cont, char *contn) {
        riv_curso_t *curso;
        OSEVPF("[FUNC]:creat_curso, contn:|%s|\n", contn);
        if (stora_ha->open_curso_cont(&curso, phys_cont->sto_seio->seion, contn, "raw"))
            return NULL;
        return curso;
    }

    //

    inline riv_curso_t *proje_curso(rive_ha *stora_ha, physi_conte *phys_cont, char *contn, char *lid_valu) {
        riv_curso_t *curso;
        OSEVPF("[FUNC]:proje_curso, contn:|%s|, lid_valu:|%s|\n", contn, lid_valu);
        if (stora_ha->open_curso_prop(&curso, phys_cont->sto_seio->seion, contn, lid_valu, "raw"))
            return NULL;
        return curso;
    }

#define CLOSE_CURSO(STORA_HA, LID_CURSO) STORA_HA->close_curso(LID_CURSO)

#ifdef __cplusplus
}
#endif

#endif /* CONTE_RESOU_H */

