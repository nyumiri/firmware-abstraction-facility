#ifndef FAF_ITERATOR
#define FAF_ITERATOR

#ifdef __cplusplus
#   include <cstdint>
#   include <cstddef>
#else
#   include <stdint.h>
#   include <stddef.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct faf_iterator_t {
    uintptr_t m_Magic;
    void* m_data;
    size_t m_size;
    int m_initialized;
} FAF_Iterator;

#ifdef __cplusplus
}
#endif

#endif // FAF_ITERATOR