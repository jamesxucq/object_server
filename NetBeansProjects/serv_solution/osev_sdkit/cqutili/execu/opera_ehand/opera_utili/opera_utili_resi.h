
/* 
 * File:   opera_utili_resi.h
 * Author: James Xu
 *
 * Created on 2024.6.21, AM 10:08
 */

#ifndef OPERA_UTILI_RESI_H
#define OPERA_UTILI_RESI_H

#ifdef __cplusplus
extern "C" {
#endif

    //
    int merge_data_obid_resi(FILE *filed, FILE *file1, FILE *file2);
    int cartesi_product_data_resi(FILE *filed, FILE *file1, FILE *file2);
    int shared_data_obid_resi(FILE *filed, FILE *file1, FILE *file2);


#ifdef __cplusplus
}
#endif

#endif /* OPERA_UTILI_RESI_H */

