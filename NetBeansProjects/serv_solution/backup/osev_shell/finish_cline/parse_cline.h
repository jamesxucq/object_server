
/* 
 * File:   parse_cline.h
 * Author: james
 *
 * Created on 2023.4.15, AM 9:31
 */

#ifndef PARSE_CLINE_H
#define PARSE_CLINE_H

#ifdef __cplusplus
extern "C" {
#endif

    // 0x00: end
    int split_instru_conte(char (*inst_stri)[LARGE_TEXT_SIZE], char *cline_whole, uint32 cli_mode);

    // 0:end 1:contine 0x02:exception -1:error
    int finis_cline_valid(char *line_str, uint32 cli_mode, uint32 run_level);

#ifdef __cplusplus
}
#endif

#endif /* PARSE_CLINE_H */

