#ifndef _HASH_TABLE_H
#define _HASH_TABLE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>

    struct tab_nod {
        const void *key;
        void *data;
        //
        struct tab_nod *next;
    };

    struct _hashtable_ {
        unsigned int (*gethash)(const void *);
        int (*compare)(const void *, const void *);
        unsigned int hashsize;
        unsigned int count;
        struct tab_nod **hashlist;
    };

    typedef struct _hashtable_ hashtable;

    // size = 2^n
    hashtable *hash_create(unsigned int (*keyfunc)(const void *), int (*compare)(const void *, const void *), unsigned int size);
    void hash_destroy(hashtable *htab);
    void hash_insert(const void *key, void *data, hashtable *htab);
    void hash_remove(const void *key, hashtable *htab);
    void *hash_value(const void *key, hashtable *htab);
    void hash_for_each_do(hashtable *htab, int (*call_back) (const void *, void *));
    // 

    inline int hash_count(hashtable *htab) {
        return htab->count;
    }

    //
    void hash_insert_adler32(const void *key, void *data, unsigned int sum, hashtable *htab);
    struct tab_nod *hash_value_adler32(unsigned int sum, hashtable *htab);
    void *hash_value_md5(const void *key, struct tab_nod *root, hashtable *htab);

#ifdef __cplusplus
}
#endif

#endif

