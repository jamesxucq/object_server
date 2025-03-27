
/* 
 * File:   seion_utili.h
 * Author: James Xu
 *
 * Created on 2023.4.12, PM 1:41
 */

#ifndef SEION_UTILI_H
#define SEION_UTILI_H

#ifdef __cplusplus
extern "C" {
#endif

    // LEVEL OSEV BASE, AUTHEN
#define CHECK_OSAUTH_PRIVILE(RESCTL, APVAL, PRIVI) { \
    if (osau_privile_bzl((APVAL)->use_privi, (PRIVI))) { \
        _LOG_WARN("NO PERMISSIONS!"); \
        (RESCTL)->status_code = FORBIDDEN; \
    } \
}

#define CHECK_BSAUTH_PRIVILE(RESCTL, SEION, PRIVI) { \
    if (bsau_privile_bzl(SEION->apval->use_privi, SEION->baval, (PRIVI))) { \
        _LOG_WARN("NO PERMISSIONS!"); \
        (RESCTL)->status_code = FORBIDDEN; \
    } \
}

    // LEVEL OSEV BASE, STATUS
#ifdef NOAUTH

#define CHECK_POST_PRIVILE(RESCTL, APVAL, PRIVI, REV_ERRNO);

#else

#define CHECK_POST_PRIVILE(RESCTL, APVAL, PRIVI, REV_ERRNO) { \
    if (osev_privile_bzl((APVAL)->use_privi, (PRIVI))) { \
        _LOG_WARN("NO PERMISSIONS!"); \
        (RESCTL)->status_code = FORBIDDEN; \
        return REV_ERRNO; \
    } \
}

#endif // NOAUTH
    
    // LEVEL OSEV BASE, STATUS
#ifdef NOAUTH

#define CHECK_STATUS_PRIVILE(RESCTL, APVAL, PRIVI, REV_ERRNO);

#else

#define CHECK_STATUS_PRIVILE(RESCTL, APVAL, PRIVI, REV_ERRNO) { \
    if (osev_privile_bzl((APVAL)->use_privi, (PRIVI))) { \
        _LOG_WARN("NO PERMISSIONS!"); \
        (RESCTL)->status_code = FORBIDDEN; \
        return REV_ERRNO; \
    } \
}

#endif // NOAUTH
    
    // LEVEL OSEV BASE, COMAND
#ifdef NOAUTH

#define CHECK_COMMAND_PRIVILE(RESCTL, APVAL, PRIVI, REV_ERRNO);

#else

#define CHECK_COMMAND_PRIVILE(RESCTL, APVAL, PRIVI, REV_ERRNO) { \
    if (osev_privile_bzl((APVAL)->use_privi, (PRIVI))) { \
        _LOG_WARN("NO PERMISSIONS!"); \
        (RESCTL)->status_code = FORBIDDEN; \
        return REV_ERRNO; \
    } \
}

#endif // NOAUTH

    // LEVEL OSEV BASE, PRIVILE
#ifdef NOAUTH

#define CHECK_OPRIVLU_PRIVILE(RESCTL, APVAL, PRIVI, REV_ERRNO);
#define CHECK_OPRIVRO_PRIVILE(RESCTL, APVAL, PRIVI, PAMVS);
#define CHECK_BPRIVI_PRIVILE(RESCTL, APVAL, PRIVI, REV_ERRNO);

#else

#define CHECK_OPRIVLU_PRIVILE(RESCTL, APVAL, PRIVI, REV_ERRNO) { \
    if (osev_privile_bzl((APVAL)->use_privi, (PRIVI))) { \
        _LOG_WARN("NO PERMISSIONS!"); \
        (RESCTL)->status_code = FORBIDDEN; \
        return REV_ERRNO; \
    } \
}

#define CHECK_OPRIVRO_PRIVILE(RESCTL, APVAL, PRIVI, PAMVS) { \
    if (osev_privile_bzl((APVAL)->use_privi, (PRIVI))) { \
        _LOG_WARN("NO PERMISSIONS!"); \
        (RESCTL)->status_code = FORBIDDEN; \
        return; \
    } \
    if (orole_privile_bzl(RESCTL, (APVAL)->use_privi, PAMVS)) { \
        _LOG_WARN("NO PERMISSIONS!"); \
        (RESCTL)->status_code = FORBIDDEN; \
        return; \
    } \
}

#define CHECK_BPRIVI_PRIVILE(RESCTL, APVAL, PRIVI, REV_ERRNO) { \
    if (osev_privile_bzl((APVAL)->use_privi, (PRIVI))) { \
        _LOG_WARN("NO PERMISSIONS!"); \
        (RESCTL)->status_code = FORBIDDEN; \
        return REV_ERRNO; \
    } \
}

#endif // NOAUTH

    // LEVEL COLLE INVOK

#ifdef NOAUTH

#define CHECK_LEVCI_PRIVILE(RESCTL, APVAL, PRIVI, REV_ERRNO);

#else

#define CHECK_LEVCI_PRIVILE(RESCTL, APVAL, PRIVI, REV_ERRNO) { \
    if (levci_privile_bzl((APVAL)->use_privi, &(APVAL)->prau_obid, (PRIVI))) { \
        _LOG_WARN("NO PERMISSIONS!"); \
        (RESCTL)->status_code = FORBIDDEN; \
        return REV_ERRNO; \
    } \
}

#endif // NOAUTH

    // LEVEL CONSTR

#ifdef NOAUTH

#define CHECK_LEVEN_PRIVILE(RESCTL, APVAL, CONT_OBID, PRIVI, REV_ERRNO);

#else

#define CHECK_LEVEN_PRIVILE(RESCTL, APVAL, CONT_OBID, PRIVI, REV_ERRNO) { \
    if (levco_privile_bzl((APVAL)->use_privi, &(APVAL)->prau_obid, (CONT_OBID), (PRIVI))) { \
        _LOG_WARN("NO PERMISSIONS!"); \
        (RESCTL)->status_code = FORBIDDEN; \
        return REV_ERRNO; \
    } \
}

#endif // NOAUTH

    // LEVEL QUERY

#ifdef NOAUTH

#define CHECK_LEVQUP_PRIVILE(RESCTL, APVAL, BAVAL, PAMVS, PRIVI);
#define CHECK_LEVQUE_STAEHO_PRIVILE(RESCTL, APVAL, BAVAL, PAMVS, PRIVI);
#define CHECK_LEVQUE_ATTSTA_PRIVILE(RESCTL, APVAL, BAVAL, PAMVS, PRIVI);
#define CHECK_LEVQUC_PRIVILE(RESCTL, APVAL, BAVAL, PAMVS, PRIVI);
#define CHECK_LEVQUD_PRIVILE(RESCTL, APVAL, BAVAL, PAMVS, PRIVI);
#define CHECK_LEVQUU_PRIVILE(RESCTL, APVAL, BAVAL, PAMVS, PRIVI);
#define CHECK_LEVQUI_PRIVILE(RESCTL, APVAL, BAVAL, PAMVS, PRIVI);
#define CHECK_LEVQUS_PRIVILE(RESCTL, APVAL, BAVAL, PAMVS, PRIVI);
#define CHECK_LEVQUV_PRIVILE(RESCTL, APVAL, BAVAL, PAMVS, PRIVI);
#define CHECK_LEVQUF_PRIVILE(RESCTL, APVAL, BAVAL, PAMVS, PRIVI);

#else

#define CHECK_LEVQUP_PRIVILE(RESCTL, APVAL, BAVAL, PAMVS, PRIVI) { \
    valid_cobid vaoid; \
    if(bvali_qpcont_bzl(&vaoid, BAVAL, PAMVS)) { \
        _LOG_WARN("LOST TARGET!"); \
        (RESCTL)->status_code = FORBIDDEN; \
        return; \
    } \
    if (levqu_privile_bzl((APVAL)->use_privi, &(APVAL)->prau_obid, &vaoid, (PRIVI))) { \
        _LOG_WARN("NO PERMISSIONS!"); \
        (RESCTL)->status_code = FORBIDDEN; \
        return; \
    } \
}

#define CHECK_LEVQUE_STAEHO_PRIVILE(RESCTL, APVAL, BAVAL, PAMVS, PRIVI) { \
    valid_cobid vaoid; \
    if(bvali_qeconton_bzl(&vaoid, BAVAL, PAMVS, (APVAL)->use_privi)) { \
        _LOG_WARN("LOST TARGET!"); \
        (RESCTL)->status_code = FORBIDDEN; \
        return; \
    } \
    if (levqu_privile_bzl((APVAL)->use_privi, &(APVAL)->prau_obid, &vaoid, (PRIVI))) { \
        _LOG_WARN("NO PERMISSIONS!"); \
        (RESCTL)->status_code = FORBIDDEN; \
        return; \
    } \
}

#define CHECK_LEVQUE_ATTSTA_PRIVILE(RESCTL, APVAL, BAVAL, PAMVS, PRIVI) { \
    valid_cobid vaoid; \
    if(bvali_qecontas_bzl(&vaoid, BAVAL, PAMVS)) { \
        _LOG_WARN("LOST TARGET!"); \
        (RESCTL)->status_code = FORBIDDEN; \
        return; \
    } \
    if (levqu_privile_bzl((APVAL)->use_privi, &(APVAL)->prau_obid, &vaoid, (PRIVI))) { \
        _LOG_WARN("NO PERMISSIONS!"); \
        (RESCTL)->status_code = FORBIDDEN; \
        return; \
    } \
}  

#define CHECK_LEVQUC_PRIVILE(RESCTL, APVAL, BAVAL, PAMVS, PRIVI) { \
    valid_cobid vaoid; \
    if(bvali_qccont_bzl(&vaoid, BAVAL, PAMVS)) { \
        _LOG_WARN("LOST TARGET!"); \
        (RESCTL)->status_code = FORBIDDEN; \
        return; \
    } \
    if (levqu_privile_bzl((APVAL)->use_privi, &(APVAL)->prau_obid, &vaoid, (PRIVI))) { \
        _LOG_WARN("NO PERMISSIONS!"); \
        (RESCTL)->status_code = FORBIDDEN; \
        return; \
    } \
}

#define CHECK_LEVQUD_PRIVILE(RESCTL, APVAL, BAVAL, PAMVS, PRIVI) { \
    valid_cobid vaoid; \
    if(bvali_qdcont_bzl(&vaoid, BAVAL, PAMVS)) { \
        _LOG_WARN("LOST TARGET!"); \
        (RESCTL)->status_code = FORBIDDEN; \
        return; \
    } \
    if (levqu_privile_bzl((APVAL)->use_privi, &(APVAL)->prau_obid, &vaoid, (PRIVI))) { \
        _LOG_WARN("NO PERMISSIONS!"); \
        (RESCTL)->status_code = FORBIDDEN; \
        return; \
    } \
}

#define CHECK_LEVQUU_PRIVILE(RESCTL, APVAL, BAVAL, PAMVS, PRIVI) { \
    valid_cobid vaoid; \
    if(bvali_qucont_bzl(&vaoid, BAVAL, PAMVS)) { \
        _LOG_WARN("LOST TARGET!"); \
        (RESCTL)->status_code = FORBIDDEN; \
        return; \
    } \
    if (levqu_privile_bzl((APVAL)->use_privi, &(APVAL)->prau_obid, &vaoid, (PRIVI))) { \
        _LOG_WARN("NO PERMISSIONS!"); \
        (RESCTL)->status_code = FORBIDDEN; \
        return; \
    } \
}

#define CHECK_LEVQUI_PRIVILE(RESCTL, APVAL, BAVAL, PAMVS, PRIVI) { \
    valid_cobid vaoid; \
    if(bvali_qicont_bzl(&vaoid, BAVAL, PAMVS)) { \
        _LOG_WARN("LOST TARGET!"); \
        (RESCTL)->status_code = FORBIDDEN; \
        return; \
    } \
    if (levqu_privile_bzl((APVAL)->use_privi, &(APVAL)->prau_obid, &vaoid, (PRIVI))) { \
        _LOG_WARN("NO PERMISSIONS!"); \
        (RESCTL)->status_code = FORBIDDEN; \
        return; \
    } \
}

#define CHECK_LEVQUS_PRIVILE(RESCTL, APVAL, BAVAL, PAMVS, PRIVI) { \
    valid_cobid vaoid; \
    if(bvali_qscont_bzl(&vaoid, BAVAL, PAMVS)) { \
        _LOG_WARN("LOST TARGET!"); \
        (RESCTL)->status_code = FORBIDDEN; \
        return; \
    } \
    if (levqu_privile_bzl((APVAL)->use_privi, &(APVAL)->prau_obid, &vaoid, (PRIVI))) { \
        _LOG_WARN("NO PERMISSIONS!"); \
        (RESCTL)->status_code = FORBIDDEN; \
        return; \
    } \
}

#define CHECK_LEVQUV_PRIVILE(RESCTL, APVAL, BAVAL, PAMVS, PRIVI) { \
    valid_cobid vaoid; \
    if(bvali_qvcont_bzl(&vaoid, BAVAL, PAMVS)) { \
        _LOG_WARN("LOST TARGET!"); \
        (RESCTL)->status_code = FORBIDDEN; \
        return; \
    } \
    if (levqu_privile_bzl((APVAL)->use_privi, &(APVAL)->prau_obid, &vaoid, (PRIVI))) { \
        _LOG_WARN("NO PERMISSIONS!"); \
        (RESCTL)->status_code = FORBIDDEN; \
        return; \
    } \
}

#define CHECK_LEVQUF_PRIVILE(RESCTL, APVAL, BAVAL, PAMVS, PRIVI) { \
    valid_cobid vaoid; \
    if(bvali_qfcont_bzl(&vaoid, BAVAL, PAMVS)) { \
        _LOG_WARN("LOST TARGET!"); \
        (RESCTL)->status_code = FORBIDDEN; \
        return; \
    } \
    if (levqu_privile_bzl((APVAL)->use_privi, &(APVAL)->prau_obid, &vaoid, (PRIVI))) { \
        _LOG_WARN("NO PERMISSIONS!"); \
        (RESCTL)->status_code = FORBIDDEN; \
        return; \
    } \
}

#endif // NOAUTH

    //


#ifdef __cplusplus
}
#endif

#endif /* SEION_UTILI_H */

