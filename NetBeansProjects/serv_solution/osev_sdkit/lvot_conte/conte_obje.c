#include "commo_header.h"

#include "conte_obje.h"

//

int save_clang_file(char *clan_path, char *clang_cont) {
    // OSEVPF("[FUNC]:save_clang_file.\n");
    FILE *data_fp = fopen64(clan_path, "ab+");
    if (!data_fp) {
        _LOG_ERROR("open file error! %s", clan_path);
        return -1;
    }
    if (0 >= fwrite(clang_cont, 0x01, strlen(clang_cont), data_fp)) {
        fclose(data_fp);
        _LOG_ERROR("fwrite file error! %s", clan_path);
        return -1;
    }
    fclose(data_fp);
    //
    return 0x00;
}