
/* 
 * File:   opera_utili_rssi.h
 * Author: James Xu
 *
 * Created on 2024.6.21, AM 10:08
 */

#ifndef OPERA_UTILI_RSSI_H
#define OPERA_UTILI_RSSI_H

#ifdef __cplusplus
extern "C" {
#endif

    //
    int merge_data_obid_rssi(FILE *filed, FILE *file1, FILE *file2);
    int cartesi_product_data_rssi(FILE *filed, FILE *file1, FILE *file2);
    int shared_data_obid_rssi(FILE *filed, FILE *file1, FILE *file2);


#ifdef __cplusplus
}
#endif

#endif /* OPERA_UTILI_RSSI_H */

