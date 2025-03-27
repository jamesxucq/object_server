
#include "commo_header.h"
#include "kcomm_header.h"
#include "opera_utili_rssi.h"


// rssi
//

static int inse_file_hmd_rssi(OBIDHMD *ohmd, FILE *fild, FILE *data) {
    OSEVPF("[FUNC]:inse_data_db\n");
    osv_oid_i reso_obid;
    rewind(data);
    while (0x00 < fread(&reso_obid, sizeof (osv_oid_i), 0x01, data)) {
        PRIN_osv_oid_t_08X((osv_oid_t *) & reso_obid);
        if (oidhmd_insert(ohmd, (char *) &reso_obid))
            return -1;
        if (0x00 >= APPEND_DATAS(fild, &reso_obid, sizeof (osv_oid_i)))
            return -1;
    }
    OSEVPF("inse_data_db, end!\n");
    return 0x00;
}

//

int merge_data_obid_rssi(FILE *filed, FILE *file1, FILE *file2) {
    OSEVPF("[FUNC]:merge_data_obid\n");
    OBIDHMD *ohmd = creat_temp_ohmd();
    if (!ohmd) return -1;
    if (inse_file_hmd_rssi(ohmd, filed, file2)) {
        oidhmd_close(ohmd, 0x00);
        oidhmd_dele(ohmd);
        return -1;
    }
    //
    osv_oid_i reso_obid;
    rewind(file1);
    while (0x00 < fread(&reso_obid, sizeof (osv_oid_i), 0x01, file1)) {
        PRIN_osv_oid_t_08X((osv_oid_t *) & reso_obid);
        if (oidhmd_find(ohmd, (char *) &reso_obid)) {
            OSEVPF("APPEND_DATAS, ");
            PRIN_osv_oid_t_08X((osv_oid_t *) & reso_obid);
            if (0x00 >= APPEND_DATAS(filed, &reso_obid, sizeof (osv_oid_i))) {
                oidhmd_close(ohmd, 0x00);
                oidhmd_dele(ohmd);
                return -1;
            }
        }
    }
    //
    if (oidhmd_close(ohmd, 0x00)) {
        OSEVPF("oidhmd_close, ERROR!\n");
        oidhmd_dele(ohmd);
        return -1;
    }
    oidhmd_dele(ohmd);
    OSEVPF("merge_data_obid, end.....\n");
    return 0x00;
}

//

int cartesi_product_data_rssi(FILE *filed, FILE *file1, FILE *file2) {
    OSEVPF("[FUNC]:cartesi_product_data\n");
    //
    return 0x00;
}

//

static int inse_data_hmd_rssi(OBIDHMD *ohmd, FILE *data) {
    OSEVPF("[FUNC]:inse_data_db\n");
    osv_oid_i reso_obid;
    rewind(data);
    while (0x00 < fread(&reso_obid, sizeof (osv_oid_i), 0x01, data)) {
        PRIN_osv_oid_t_08X((osv_oid_t *) & reso_obid);
        if (oidhmd_insert(ohmd, (char *) &reso_obid))
            return -1;
    }
    OSEVPF("inse_data_db, end!\n");
    return 0x00;
}

int shared_data_obid_rssi(FILE *filed, FILE *file1, FILE *file2) {
    OSEVPF("[FUNC]:shared_data_obid\n");
    OBIDHMD *ohmd = creat_temp_ohmd();
    if (!ohmd) return -1;
    if (inse_data_hmd_rssi(ohmd, file2)) {
        oidhmd_close(ohmd, 0x00);
        oidhmd_dele(ohmd);
        return -1;
    }
    //
    osv_oid_i reso_obid;
    rewind(file1);
    while (0x00 < fread(&reso_obid, sizeof (osv_oid_i), 0x01, file1)) {
        PRIN_osv_oid_t_08X((osv_oid_t *) & reso_obid);
        if (!oidhmd_find(ohmd, (char *) &reso_obid)) {
            OSEVPF("APPEND_DATAS, ");
            PRIN_osv_oid_t_08X((osv_oid_t *) & reso_obid);
            if (0x00 >= APPEND_DATAS(filed, &reso_obid, sizeof (osv_oid_i))) {
                oidhmd_close(ohmd, 0x00);
                oidhmd_dele(ohmd);
                return -1;
            }
        }
    }
    //
    if (oidhmd_close(ohmd, 0x00)) {
        OSEVPF("oidhmd_close, ERROR!\n");
        oidhmd_dele(ohmd);
        return -1;
    }
    oidhmd_dele(ohmd);
    OSEVPF("shared_data_obid, end.....\n");
    return 0x00;
}

