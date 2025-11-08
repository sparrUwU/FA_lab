#include "functions.h"
#include <stdio.h>
#include "error_list.h"


void *memchr(const void *str, int c, size_t n) {
    const unsigned char *ptr = (unsigned char *)str;
    unsigned char search = (unsigned char)c;
    
    for (size_t i = 0; i < n; i++) {
        if (ptr[i] == search) {
            return (void *)(ptr + i);
        }
    }

    return NULL;
}

int memcmp(const void *str1, const void *str2, size_t n) {
    const unsigned char *ptr1 = (unsigned char *)str1;
    const unsigned char *ptr2 = (unsigned char *)str2;
    
    for (size_t i = 0; i < n; ++i) {
        if (ptr1[i] < ptr2[i]) {
            return -1;
        }

        if (ptr1[i] > ptr2[i]) {
            return 1;
        }
    }

    return 0;
}

void *memcpy(void *dest, const void *src, size_t n) {
    unsigned char *ptr1 = (unsigned char *)dest;
    const unsigned char *ptr2 = (unsigned char *)src;

    for (size_t i = 0; i != n; ++i) {
        ptr1[i] = ptr2[i];
    }

    return dest;
}

void *memset(void *str, int c, size_t n) {
    unsigned char *ptr = (unsigned char *)str;
    const unsigned char elem = (unsigned char)c;

    for (size_t i = 0; i != n; ++i) {
        ptr[i] = elem;
    }

    return str;
}

char *strncat(char *dest, const char *src, size_t n) {
    char *ptr = dest;
    
    while (*ptr != '\0') {
        ptr++;
    }
    
    while (n-- && *src != '\0') {
        *ptr++ = *src++;
    }
    
    *ptr = '\0';
    
    return dest;
}

char *strchr(const char *str, int c) {
    unsigned char *ptr = (unsigned char *)str;
    const unsigned char elem = (unsigned char)c;

    int i = 0;
    while (ptr[i] != elem && ptr[i] != '\0') {
        ++i;
    }

    if (ptr[i] == elem) {
        return (char *)(ptr + i);
    }

    return NULL;
}

int strncmp(const char *str1, const char *str2, size_t n) {
    const unsigned char *ptr1 = (unsigned char *)str1;
    const unsigned char *ptr2 = (unsigned char *)str2;
        
    for (size_t i = 0; i < n; ++i) {
        if (ptr1[i] < ptr2[i]) {
            return -1;
        }

        if (ptr1[i] > ptr2[i]) {
            return 1;
        }

        if (ptr1[i] == '\0') {
            return 0;
        }
    }
    
    return 0;
}

char *strncpy(char *dest, const char *src, size_t n) {
    char *ptr1 = dest;
    char *ptr2 = src;
    
    while (n > 0 && *ptr2 != '\0') {
        *ptr1++ = *ptr2++;
        n--;
    }
    
    while (n--) {
        *ptr1++ = '\0';
    }
    
    return dest;
}

size_t strcspn(const char *str1, const char *str2) {
    const char *p1 = str1;
    
    while (*p1 != '\0') {
        const char *p2 = str2;
        while (*p2 != '\0') {
            if (*p1 == *p2) {
                return p1 - str1;
            }
            p2++;
        }
        p1++;
    }
    
    return p1 - str1;
}


char *strerror(int errnum)
{
#ifdef __APPLE__
    if (errnum >= 0 && errnum < m_num_errors) {
        return (char *)mac_errlist[errnum];
    }
#elif __linux__
    if (errnum >= 0 && errnum < l_num_errors) {
        return (char *)linux_errlist[errnum];
    }
#else
    return "Unsupported operating system";
#endif

    return "Unknown error";
}

size_t strlen(const char *str) {
    unsigned char *ptr = (unsigned char *)str;
    size_t len = 0;

    while (*ptr != '\0') {
        ++ptr;
        ++len;
    }

    return len;
}

char *strpbrk(const char *str1, const char *str2) {
    const char *s1 = str1;
    
    while (*s1 != '\0') {
        const char *s2 = str2;
        while (*s2 != '\0') {
            if (*s1 == *s2) {
                return (char *)s1;
            }
            s2++;
        }
        s1++;
    }
    
    return NULL;
}

char *strrchr(const char *str, int c) {
    const char *last_occurrence = NULL;
    const char *current = str;
    unsigned char search_char = (unsigned char)c;
    
    while (*current != '\0') {
        if (*current == search_char) {
            last_occurrence = current;
        }
        current++;
    }
    
    if (search_char == '\0') {
        return (char *)current;
    }
    
    return (char *)last_occurrence;
}

char *strstr(const char *haystack, const char *needle) {
    if (*needle == '\0') {
        return (char *)haystack;
    }
    
    const char *h = haystack;
    
    while (*h != '\0') {
        const char *h_ptr = h;
        const char *n_ptr = needle;
        
        while (*h_ptr != '\0' && *n_ptr != '\0' && *h_ptr == *n_ptr) {
            h_ptr++;
            n_ptr++;
        }
        
        if (*n_ptr == '\0') {
            return (char *)h;
        }
        
        if (*h_ptr == '\0') {
            return NULL;
        }
        
        h++;
    }
    
    return NULL;
}

char *strtok(char *str, const char *delim) {
    static char *save_ptr = NULL;
    char *token_start;
    
    if (str != NULL) {
        save_ptr = str;
    }
    
    if (save_ptr == NULL || *save_ptr == '\0') {
        return NULL;
    }
    
    while (*save_ptr != '\0' && strchr(delim, *save_ptr) != NULL) {
        save_ptr++;
    }
    
    if (*save_ptr == '\0') {
        return NULL;
    }
    
    token_start = save_ptr;
    
    while (*save_ptr != '\0' && strchr(delim, *save_ptr) == NULL) {
        save_ptr++;
    }
    
    if (*save_ptr != '\0') {
        *save_ptr = '\0';
        save_ptr++;
    }
    
    return token_start;
}